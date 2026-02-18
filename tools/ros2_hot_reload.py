#!/usr/bin/env python3
"""
ROS2 Hot Reload Watcher
Monitors source files and automatically rebuilds and restarts ROS2 nodes via Supervisord
"""
import logging
import os
import subprocess
import shutil
import sys
import time
from pathlib import Path
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

logger = logging.getLogger(__name__)
logger.level = logging.DEBUG

class ROS2HotReloadHandler(FileSystemEventHandler):
    """Handles file system events and triggers rebuild/restart via Supervisord"""
    
    def __init__(
            self, workspace_path: str, package_name: str, node_name: str, 
            debounce_seconds: float = 5.0, supervisord_program: str = "ros2_node"):
        
        self.workspace_path = Path(workspace_path)
        self.package_name = package_name
        self.node_name = node_name
        self.debounce_seconds = debounce_seconds
        self.last_trigger_time = 0
        self.pending_rebuild = False
        self.is_building = False
        self.last_modified_file = None
        self.last_modified_time = 0
        self.last_build_time = 0  # Track when builds complete
        self.supervisord_program = supervisord_program
        self.use_supervisord = self._check_supervisord_available()
        self.interface_files_changed = False  # Track if interface files changed
        
        logger.info(f"🔥 Hot Reload initialized for package: {package_name}, node: {node_name}")
        logger.info(f"🔧 Using Supervisord: {self.use_supervisord} (program: {supervisord_program})")
        
    def on_modified(self, event):
        """Called when a file is modified"""
        # Ignore ALL events while building to prevent loops from setup_interfaces.py
        if self.is_building:
            return
            
        if event.is_directory:
            return
            
        # Watch Python files and ROS2 interface files (.srv, .msg, .action)
        file_path = Path(event.src_path)
        
        # Ignore install, build, log directories
        path_str = str(file_path)
        if any(excluded in path_str for excluded in ['/install/', '/build/', '/log/']):
            logger.debug(f"🚫 Ignoring file in excluded directory: {path_str}")
            return
        
        # Check if it's a Python file in the main package
        is_python_file = file_path.suffix == '.py' and f'/src/{self.package_name}' in path_str
        
        # Check if it's a ROS2 interface file (.srv, .msg, .action) in any package
        is_interface_file = (
            file_path.suffix in ['.srv', '.msg', '.action'] and 
            '/src/' in path_str and
            any(iface_dir in path_str for iface_dir in ['/srv/', '/msg/', '/action/'])
        )
        
        # Ignore interface file events for 20 seconds after build completes
        # This prevents loops from setup_interfaces.py modifying interface files
        if is_interface_file and (time.time() - self.last_build_time < 20.0):
            # logger.debug(f"⏱️ Ignoring interface file during post-build cooldown: {file_path.name}")
            return
        
        if is_python_file or is_interface_file:
            # Check for duplicate event (same file within 10 seconds)
            # This catches multiple save events from editors (save, auto-save, format-on-save)
            current_time = time.time()
            if (self.last_modified_file == path_str and 
                current_time - self.last_modified_time < 10.0):
                # logger.debug(f"🔄 Duplicate event for {file_path.name}, ignoring")
                return
            
            self.last_modified_file = path_str
            self.last_modified_time = current_time
            
            file_type = "interface" if is_interface_file else "Python"
            logger.info(f"📝 {file_type} file changed: {file_path.name} (full path: {path_str})")
            if is_interface_file:
                self.interface_files_changed = True
            self._schedule_rebuild()
    
    def on_created(self, event):
        """Called when a file is created"""
        # Ignore ALL events while building to prevent loops from setup_interfaces.py
        if self.is_building:
            return
            
        if event.is_directory:
            return
            
        file_path = Path(event.src_path)
        path_str = str(file_path)
        
        # Ignore install, build, log directories
        if any(excluded in path_str for excluded in ['/install/', '/build/', '/log/']):
            return
        
        # Check if it's a Python file in the main package
        is_python_file = file_path.suffix == '.py' and f'/src/{self.package_name}' in path_str
        
        # Check if it's a ROS2 interface file (.srv, .msg, .action) in any package
        is_interface_file = (
            file_path.suffix in ['.srv', '.msg', '.action'] and 
            '/src/' in path_str and
            any(iface_dir in path_str for iface_dir in ['/srv/', '/msg/', '/action/'])
        )
        
        # Ignore interface file events for 20 seconds after build completes
        # This prevents loops from setup_interfaces.py modifying interface files
        if is_interface_file and (time.time() - self.last_build_time < 20.0):
            logger.debug(f"⏱️ Ignoring interface file during post-build cooldown: {file_path.name}")
            return
        
        if is_python_file or is_interface_file:
            file_type = "interface" if is_interface_file else "Python"
            logger.info(f"➕ {file_type} file created: {file_path.name}")
            if is_interface_file:
                self.interface_files_changed = True
            
            self.interface_files_changed = False
            self._schedule_rebuild()
    
    def _schedule_rebuild(self):
        """Schedule a rebuild with debouncing"""
        # Skip if already building
        if self.is_building:
            logger.debug("🔒 Build already in progress, skipping trigger")
            return
        
        current_time = time.time()
        
        # Debounce: Only trigger if enough time has passed
        if current_time - self.last_trigger_time < self.debounce_seconds:
            self.pending_rebuild = True
            return
        
        self.last_trigger_time = current_time
        self.pending_rebuild = False
        self._trigger_rebuild()
    
    def _trigger_rebuild(self):
        """Execute the rebuild and restart process via Supervisord"""
        self.is_building = True
        logger.info("🔨 Starting rebuild process...")
        
        # Step 1: Stop running node via Supervisord
        if self.use_supervisord:
            logger.info(f"⏹️ Stopping Supervisord program: {self.supervisord_program}")
            self._supervisorctl("stop", self.supervisord_program)
            time.sleep(1)  # Wait for graceful shutdown
            
            # Additional cleanup: Kill any remaining processes
            logger.info("🧹 Cleaning up remaining processes...")
            self._kill_remaining_processes()
            time.sleep(0.5)
        
        # Step 2: Build the package
        logger.info(f"🔧 Building package: {self.package_name}")
        build_result = self._build_package()
        
        if build_result != 0:
            logger.error(f"❌ Build failed with exit code {build_result}")
            if self.use_supervisord:
                # Restart even if build failed to restore service
                logger.warning("⚠️ Restarting node despite build failure...")
                self._supervisorctl("start", self.supervisord_program)
            self.is_building = False
            return
        
        logger.info("✅ Build successful")
        
        # Step 3: Clear Python module cache to force reload
        logger.info("🧹 Clearing Python module cache...")
        self._clear_python_cache()
        self._clear_logs()
        
        # Step 4: Restart the node via Supervisord
        if self.use_supervisord:
            logger.info(f"🚀 Restarting Supervisord program: {self.supervisord_program}")
            self._supervisorctl("start", self.supervisord_program)
            logger.info(f"✅ Node restarted via Supervisord")
        else:
            logger.warning("⚠️ Supervisord not available, manual restart required")
        
        # Reset timestamp to ignore any file events that occurred during build
        # This prevents loops from setup_interfaces.py modifying files
        self.last_modified_time = time.time()
        self.last_build_time = time.time()  # Start cooldown period
        self.is_building = False
        self.is_building = False
    
    def _build_package(self) -> int:
        """Build the ROS2 package"""
        try:
            # Step 1: If interface files changed, run setup_interfaces.py first
            if self.interface_files_changed:
                logger.info("🔧 Interface files changed, running setup_interfaces.py...")
                self._run_setup_interfaces()
                self.interface_files_changed = False  # Reset flag after processing
                # Reset last_modified_time to ignore changes made by setup_interfaces.py
                self.last_modified_time = time.time()
                time.sleep(1)  # Wait for filesystem to settle
            
            # Step 2: Clean both build AND install directories for fresh build
            # This prevents colcon from trying to use --uninstall on old installations
            # Delete both the main package AND interface packages
            packages_to_clean = [
                self.package_name,
                f'{self.package_name}_interfaces'
            ]
            
            for pkg in packages_to_clean:
                # Clean install directory
                install_dir = self.workspace_path / "install" / pkg
                if install_dir.exists():
                    logger.info(f"🧹 Cleaning install directory: {install_dir}")
                    shutil.rmtree(install_dir)
                
                # Clean build directory to remove cached build info
                build_dir = self.workspace_path / "build" / pkg
                if build_dir.exists():
                    logger.info(f"🧹 Cleaning build directory: {build_dir}")
                    shutil.rmtree(build_dir)
            
            # Step 3: Build all packages to ensure dependencies are up-to-date
            # Note: Removed --uninstall flag as it's no longer supported in setuptools 82+
            result = subprocess.run(
                ["colcon", "build", "--cmake-args", "-DCMAKE_BUILD_TYPE=Release"],
                cwd=self.workspace_path,
                capture_output=True,
                text=True
            )
            
            if result.returncode != 0:
                logger.error(f"Build stderr: {result.stderr}")
            else:
                logger.debug(f"Build stdout: {result.stdout}")
                
            return result.returncode
        except Exception as e:
            logger.exception(f"Build exception: {e}")
            return 1
    
    def _check_supervisord_available(self) -> bool:
        """Check if supervisorctl is available"""
        try:
            result = subprocess.run(
                ["supervisorctl", "-c", "/etc/supervisor/conf.d/supervisord.conf", "status"],
                capture_output=True,
                timeout=5
            )
            # Exit code 0 = all processes running
            # Exit code 3 = some processes stopped (e.g., nginx) - still available!
            available = result.returncode in [0, 3]
            if available:
                logger.info(f"✅ Supervisord is available (exit code: {result.returncode})")
            else:
                logger.warning(f"⚠️ Supervisord not responding: {result.stderr.decode() if result.stderr else 'unknown'}")
            return available
        except (subprocess.TimeoutExpired, FileNotFoundError) as e:
            logger.warning(f"⚠️ Supervisord not available: {e}")
            return False
    
    def _supervisorctl(self, action: str, program: str) -> bool:
        """Execute supervisorctl command with explicit config file"""
        try:
            result = subprocess.run(
                ["supervisorctl", "-c", "/etc/supervisor/conf.d/supervisord.conf", action, program],
                capture_output=True,
                text=True,
                timeout=30  # Increased from 10 to 30 seconds for graceful shutdown
            )
            
            if result.returncode != 0:
                logger.warning(f"supervisorctl {action} {program} failed: {result.stderr}")
                logger.debug(f"stdout: {result.stdout}")
                return False
            
            logger.info(f"✅ supervisorctl {action} {program} successful")
            logger.debug(f"Output: {result.stdout.strip()}")
            return True
        except Exception as e:
            logger.error(f"supervisorctl command failed: {e}")
            return False
    
    def _run_setup_interfaces(self):
        """Run setup_interfaces.py to update CMakeLists.txt and package.xml"""
        try:
            setup_script = self.workspace_path / "tools" / "setup_interfaces.py"
            if not setup_script.exists():
                logger.warning(f"⚠️ setup_interfaces.py not found at {setup_script}")
                return
            
            # Run setup_interfaces.py for {package_name}_interfaces
            result = subprocess.run(
                ["python3", str(setup_script), "--interface_pkg", f"{self.package_name}_interfaces"],
                cwd=self.workspace_path,
                capture_output=True,
                text=True,
                timeout=30
            )
            
            if result.returncode == 0:
                logger.info("✅ setup_interfaces.py completed successfully")
                logger.debug(f"Output: {result.stdout}")
            else:
                logger.error(f"❌ setup_interfaces.py failed: {result.stderr}")
                
        except Exception as e:
            logger.error(f"Exception running setup_interfaces.py: {e}")
    
    def _kill_remaining_processes(self):
        """Kill any remaining processes from the package to prevent process leaks"""
        try:
            # Find all processes matching the package core executable
            result = subprocess.run(
                ["pgrep", "-f", f"{self.package_name}/core"],
                capture_output=True,
                text=True,
                timeout=5
            )
            
            if result.returncode == 0 and result.stdout.strip():
                pids = result.stdout.strip().split('\n')
                logger.info(f"🔍 Found {len(pids)} remaining processes to clean up")
                
                for pid in pids:
                    try:
                        # Send SIGTERM first (graceful)
                        subprocess.run(
                            ["kill", "-TERM", pid],
                            capture_output=True,
                            timeout=2
                        )
                        logger.debug(f"Sent SIGTERM to PID {pid}")
                    except Exception as e:
                        logger.warning(f"Failed to kill PID {pid}: {e}")
                
                # Wait a bit for graceful shutdown
                time.sleep(1)
                
                # Check if any processes are still alive and force kill
                result = subprocess.run(
                    ["pgrep", "-f", f"{self.package_name}/core"],
                    capture_output=True,
                    text=True,
                    timeout=5
                )
                
                if result.returncode == 0 and result.stdout.strip():
                    remaining_pids = result.stdout.strip().split('\n')
                    logger.warning(f"⚠️ {len(remaining_pids)} processes still alive, force killing...")
                    
                    for pid in remaining_pids:
                        try:
                            subprocess.run(
                                ["kill", "-KILL", pid],
                                capture_output=True,
                                timeout=2
                            )
                            logger.debug(f"Sent SIGKILL to PID {pid}")
                        except Exception as e:
                            logger.warning(f"Failed to force kill PID {pid}: {e}")
                    
                    logger.info("✅ All remaining processes terminated")
                else:
                    logger.info("✅ All processes terminated gracefully")
            else:
                logger.debug("No remaining processes found")
                
        except Exception as e:
            logger.warning(f"⚠️ Process cleanup failed: {e}")
    
    def _clear_python_cache(self):
        """Clear Python __pycache__ directories to force module reload"""
        try:
            # Find and remove all __pycache__ directories in package
            package_path = self.workspace_path / "src" / self.package_name
            
            result = subprocess.run(
                ["find", str(package_path), "-type", "d", "-name", "__pycache__", "-exec", "rm", "-rf", "{}", "+"],
                capture_output=True,
                text=True,
                timeout=10
            )
            
            if result.returncode == 0:
                logger.debug("✅ Python cache cleared")
            else:
                logger.warning(f"⚠️ Failed to clear cache: {result.stderr}")
                
        except Exception as e:
            logger.warning(f"⚠️ Cache clearing failed: {e}")
    
    def _clear_logs(self):
        """Clear log files in the package log directory"""
        try:
            log_path: Path = self.workspace_path / "log" / "ros2"
            
            # Use shell=True to allow wildcard expansion
            result = subprocess.run(
                f"rm -rf {self.workspace_path}/log/build_* {log_path}/build_* {log_path}/latest_* {log_path}/python3_*.log",
                shell=True,
                capture_output=True,
                text=True,
                timeout=5
            )
            
            if result.returncode == 0:
                logger.debug("✅ Logs cleared")
            else:
                logger.warning(f"⚠️ Failed to clear logs: {result.stderr}")
                
        except Exception as e:
            logger.warning(f"⚠️ Log clearing failed: {e}")

    def check_pending_rebuild(self):
        """Check if there's a pending rebuild to execute"""
        if self.pending_rebuild:
            current_time = time.time()
            if current_time - self.last_trigger_time >= self.debounce_seconds:
                self.pending_rebuild = False
                self.last_trigger_time = current_time
                self._trigger_rebuild()


def main():
    """Main entry point"""
    logging.basicConfig(
        level=logging.INFO,
        format='[%(asctime)s] %(levelname)s %(name)s: %(message)s',
        datefmt='%Y-%m-%d %H:%M:%S'
    )
    
    # Get configuration from environment or arguments
    workspace_path = os.getenv("WORKSPACE_PATH", "/workspace")
    package_name = os.getenv("ROS2_PACKAGE_NAME", "{{ module_name }}")
    node_name = os.getenv("ROS2_NODE_NAME", "core")
    watch_path = os.getenv("ROS2_WATCH_PATH", f"{workspace_path}/src")
    supervisord_program = os.getenv("ROS2_SUPERVISORD_PROGRAM", "ros2_core")  # Changed from ros2_node to ros2_main
    
    if len(sys.argv) > 1:
        package_name = sys.argv[1]
    if len(sys.argv) > 2:
        node_name = sys.argv[2]
    if len(sys.argv) > 3:
        supervisord_program = sys.argv[3]
    
    logger.info("=" * 60)
    logger.info("🔥 ROS2 Hot Reload Watcher Starting")
    logger.info("=" * 60)
    logger.info(f"📦 Package: {package_name}")
    logger.info(f"🎯 Node: {node_name}")
    logger.info(f"👀 Watching: {watch_path}")
    logger.info(f"🏠 Workspace: {workspace_path}")
    logger.info(f"🎛️ Supervisord Program: {supervisord_program}")
    logger.info("=" * 60)
    
    # Create event handler and observer
    event_handler = ROS2HotReloadHandler(
        workspace_path, package_name, node_name, supervisord_program=supervisord_program)
    
    observer = Observer()
    observer.schedule(event_handler, watch_path, recursive=True)
    
    # Don't start node here - Supervisord manages it
    logger.info("ℹ️ Node managed by Supervisord, not starting here")
    
    # Start watching
    observer.start()
    logger.info("👀 Watching for file changes... (Press Ctrl+C to stop)")
    
    try:
        while True:
            time.sleep(1)
            event_handler.check_pending_rebuild()
    except KeyboardInterrupt:
        logger.info("\n🛑 Stopping hot reload watcher...")
        observer.stop()
    
    observer.join()
    logger.info("✅ Hot reload watcher stopped")


if __name__ == "__main__":
    main()

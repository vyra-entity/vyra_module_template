"""
Operation tracking service with task-based progress and user prompts
"""
import asyncio
from {{ module_name }}.logging_config import get_logger, log_exception, log_function_call, log_function_result
import uuid
from datetime import datetime, timedelta
from typing import Optional, List, Dict, Any, Callable
from dataclasses import dataclass, field

from ..module.operation_models import (
    EnhancedOperationStatus, OperationTask, TaskStatus,
    UserPrompt, PromptOption, UserPromptType, PromptOptionVariant
)

logger = get_logger(__name__)

# TTL for completed operations in seconds
OPERATION_TTL_SECONDS = 60


@dataclass
class OperationContext:
    """Context for a running operation"""
    operation_id: str
    operation_type: str
    module_name: Optional[str] = None
    instance_id: Optional[str] = None
    status: EnhancedOperationStatus = field(init=False)
    tasks: List[OperationTask] = field(default_factory=list)
    prompt_responses: Dict[str, str] = field(default_factory=dict)
    prompt_event: Optional[asyncio.Event] = None
    completed_at_timestamp: Optional[datetime] = None  # Tracks when operation completed for TTL
    
    def __post_init__(self):
        self.status = EnhancedOperationStatus(
            operation_id=self.operation_id,
            operation_type=self.operation_type,
            status="pending",
            tasks=[],
            module_name=self.module_name,
            instance_id=self.instance_id,
            started_at=datetime.now().isoformat()
        )


class OperationTracker:
    """
    Service for tracking operations with task-based progress
    and user interaction support
    """
    
    def __init__(self):
        self._operations: Dict[str, OperationContext] = {}
        self._storage_callback: Optional[Callable] = None
    
    def set_storage_callback(self, callback: Callable):
        """Set callback for persisting operation status to Redis"""
        self._storage_callback = callback
    
    def create_operation(
        self,
        operation_type: str,
        tasks: List[Dict[str, str]],
        module_name: Optional[str] = None,
        instance_id: Optional[str] = None
    ) -> str:
        """
        Create a new tracked operation
        
        Args:
            operation_type: Type of operation (install, update, delete)
            tasks: List of task definitions [{"id": "...", "title": "...", "description": "..."}]
            module_name: Module being operated on
            instance_id: Instance ID if applicable
            
        Returns:
            operation_id: Unique identifier for tracking
        """
        operation_id = str(uuid.uuid4())
        
        context = OperationContext(
            operation_id=operation_id,
            operation_type=operation_type,
            module_name=module_name,
            instance_id=instance_id
        )
        
        # Create task objects
        for task_def in tasks:
            task = OperationTask(
                id=task_def["id"],
                title=task_def["title"],
                description=task_def.get("description"),
                status=TaskStatus.PENDING
            )
            context.tasks.append(task)
        
        context.status.tasks = context.tasks
        context.status.status = "pending"
        
        self._operations[operation_id] = context
        self._persist_status(operation_id)
        
        logger.info(f"✅ Created operation {operation_id} with {len(tasks)} tasks")
        logger.info(f"{self._operations}")
        return operation_id
    
    def start_operation(self, operation_id: str):
        """Mark operation as running"""
        context = self._operations.get(operation_id)
        if not context:
            logger.error(f"Operation {operation_id} not found")
            return
        
        context.status.status = "running"
        self._persist_status(operation_id)
        logger.info(f"▶️  Operation {operation_id} started")
    
    def start_task(self, operation_id: str, task_id: str):
        """Mark a task as running"""
        context = self._operations.get(operation_id)
        if not context:
            return
        
        task = self._find_task(context, task_id)
        if task:
            task.status = TaskStatus.RUNNING
            task.started_at = datetime.now().isoformat()
            context.status.current_task_id = task_id
            context.status.status = "running"
            self._persist_status(operation_id)
            logger.info(f"⏩ Task '{task.title}' started in operation {operation_id}")
    
    def complete_task(
        self, 
        operation_id: str, 
        task_id: str, 
        success: bool = True,
        error: Optional[str] = None
    ):
        """Mark a task as completed or failed"""
        context = self._operations.get(operation_id)
        if not context:
            return
        
        task = self._find_task(context, task_id)
        if task:
            task.status = TaskStatus.COMPLETED if success else TaskStatus.FAILED
            task.completed_at = datetime.now().isoformat()
            if error:
                task.error = error
            
            # Clear current task
            if context.status.current_task_id == task_id:
                context.status.current_task_id = None
            
            self._persist_status(operation_id)
            
            status_icon = "✅" if success else "❌"
            logger.info(f"{status_icon} Task '{task.title}' {'completed' if success else 'failed'}")
    
    def skip_task(self, operation_id: str, task_id: str, reason: Optional[str] = None):
        """Mark a task as skipped"""
        context = self._operations.get(operation_id)
        if not context:
            return
        
        task = self._find_task(context, task_id)
        if task:
            task.status = TaskStatus.SKIPPED
            task.error = reason
            task.completed_at = datetime.now().isoformat()
            self._persist_status(operation_id)
            logger.info(f"⏭️  Task '{task.title}' skipped: {reason}")
    
    def update_task_progress(self, operation_id: str, task_id: str, progress: int):
        """Update task progress"""
        context = self._operations.get(operation_id)
        if not context:
            return
        
        task = self._find_task(context, task_id)
        if task:
            task.progress = min(100, max(0, progress))
            self._persist_status(operation_id)
    
    async def prompt_user(
        self,
        operation_id: str,
        prompt_type: UserPromptType,
        title: str,
        message: str,
        options: List[Dict[str, str]],
        default_option: Optional[str] = None,
        metadata: Optional[Dict[str, Any]] = None
    ) -> str:
        """
        Prompt user for input and wait for response
        
        Args:
            operation_id: Operation ID
            prompt_type: Type of prompt (warning, error, info, question)
            title: Prompt title
            message: Prompt message
            options: List of options [{"label": "...", "value": "...", "variant": "..."}]
            default_option: Default option value
            metadata: Additional metadata
            
        Returns:
            User's response value
        """
        context = self._operations.get(operation_id)
        if not context:
            logger.error(f"Operation {operation_id} not found for prompt")
            return default_option or ""
        
        prompt_id = str(uuid.uuid4())
        
        prompt_options = [
            PromptOption(
                label=opt["label"],
                value=opt["value"],
                variant=PromptOptionVariant(opt.get("variant", "secondary"))
            )
            for opt in options
        ]
        
        prompt = UserPrompt(
            id=prompt_id,
            type=prompt_type,
            title=title,
            message=message,
            options=prompt_options,
            default_option=default_option,
            metadata=metadata or {}
        )
        
        context.status.user_prompt = prompt
        context.status.status = "waiting_for_user"
        context.prompt_event = asyncio.Event()
        
        self._persist_status(operation_id)
        logger.info(f"❓ User prompt displayed: {title}")
        
        # Wait for response (with timeout)
        try:
            await asyncio.wait_for(context.prompt_event.wait(), timeout=300.0)  # 5 min timeout
            response = context.prompt_responses.get(prompt_id, default_option or "")
            
            # Clear prompt
            context.status.user_prompt = None
            context.status.status = "running"
            self._persist_status(operation_id)
            
            logger.info(f"✔️  User responded to prompt: {response}")
            return response
            
        except asyncio.TimeoutError:
            logger.warning(f"⏱️  Prompt timeout, using default: {default_option}")
            context.status.user_prompt = None
            context.status.status = "running"
            self._persist_status(operation_id)
            return default_option or ""
    
    def respond_to_prompt(self, operation_id: str, prompt_id: str, response: str):
        """Submit response to user prompt"""
        context = self._operations.get(operation_id)
        if not context:
            logger.error(f"Operation {operation_id} not found")
            return False
        
        if not context.status.user_prompt or context.status.user_prompt.id != prompt_id:
            logger.error(f"Prompt {prompt_id} not active in operation {operation_id}")
            return False
        
        context.prompt_responses[prompt_id] = response
        
        if context.prompt_event:
            context.prompt_event.set()
        
        return True
    
    def complete_operation(
        self, 
        operation_id: str, 
        success: bool = True,
        message: Optional[str] = None,
        error: Optional[str] = None,
        result: Optional[Dict[str, Any]] = None
    ):
        """Complete an operation"""
        context = self._operations.get(operation_id)
        if not context:
            return
        
        context.status.status = "success" if success else "failed"
        context.status.completed_at = datetime.now().isoformat()
        context.completed_at_timestamp = datetime.now()  # Store timestamp for TTL check
        context.status.current_task_id = None
        context.status.user_prompt = None
        
        if message:
            context.status.message = message
        if error:
            context.status.error = error
        if result:
            context.status.result = result
        
        # Calculate overall progress
        completed = sum(1 for t in context.tasks if t.status == TaskStatus.COMPLETED)
        context.status.progress = int((completed / len(context.tasks)) * 100) if context.tasks else 100
        
        self._persist_status(operation_id)
        
        status_icon = "✅" if success else "❌"
        logger.info(f"{status_icon} Operation {operation_id} {'completed successfully' if success else 'failed'}")
    
    def get_status(self, operation_id: str) -> Optional[EnhancedOperationStatus]:
        """
        Get operation status
        
        Returns None if operation is expired (completed > TTL seconds ago)
        """
        context = self._operations.get(operation_id)
        if not context:
            return None
        
        # Check if operation is expired (completed and TTL exceeded)
        if context.completed_at_timestamp:
            elapsed = datetime.now() - context.completed_at_timestamp
            if elapsed > timedelta(seconds=OPERATION_TTL_SECONDS):
                logger.debug(f"⏱️  Operation {operation_id} expired (completed {elapsed.total_seconds():.1f}s ago)")
                # Remove expired operation from memory
                del self._operations[operation_id]
                return None
        
        return context.status
    
    def cancel_operation(self, operation_id: str):
        """
        Cancel an operation and rollback completed tasks
        
        Bei Install-Operationen werden bereits abgeschlossene Tasks
        zurückgesetzt und als "rollback" markiert
        """
        context = self._operations.get(operation_id)
        if not context:
            return False
        
        # Für Install-Operationen: Markiere completed tasks als rollback
        if context.operation_type == "install":
            logger.info(f"🔄 Starting rollback for install operation {operation_id}")
            
            # Gehe durch Tasks rückwärts und markiere completed als failed (rollback)
            for task in reversed(context.tasks):
                if task.status == TaskStatus.COMPLETED:
                    task.status = TaskStatus.FAILED
                    task.error = "Rückgängig gemacht (Rollback)"
                    logger.info(f"🔴 Rolled back task: {task.title}")
        
        context.status.status = "failed"
        context.status.error = "Operation cancelled by user"
        context.status.completed_at = datetime.now().isoformat()
        context.completed_at_timestamp = datetime.now()  # Store timestamp for TTL check
        
        self._persist_status(operation_id)
        logger.info(f"🚫 Operation {operation_id} cancelled")
        return True
    
    def _find_task(self, context: OperationContext, task_id: str) -> Optional[OperationTask]:
        """Find task by ID"""
        return next((t for t in context.tasks if t.id == task_id), None)
    
    def cleanup_expired_operations(self) -> int:
        """
        Remove expired operations from memory
        
        Returns:
            Number of operations removed
        """
        now = datetime.now()
        expired_ids = []
        
        for operation_id, context in self._operations.items():
            if context.completed_at_timestamp:
                elapsed = now - context.completed_at_timestamp
                if elapsed > timedelta(seconds=OPERATION_TTL_SECONDS):
                    expired_ids.append(operation_id)
        
        for operation_id in expired_ids:
            del self._operations[operation_id]
            logger.debug(f"🗑️  Cleaned up expired operation {operation_id}")
        
        if expired_ids:
            logger.info(f"🧹 Cleaned up {len(expired_ids)} expired operations")
        
        return len(expired_ids)
    
    def _persist_status(self, operation_id: str):
        """Persist operation status to storage"""
        context = self._operations.get(operation_id)
        if context and self._storage_callback:
            try:
                self._storage_callback(operation_id, context.status.model_dump())
            except Exception as e:
                logger.error(f"Failed to persist status for {operation_id}: {e}")


# Global instance
operation_tracker = OperationTracker()

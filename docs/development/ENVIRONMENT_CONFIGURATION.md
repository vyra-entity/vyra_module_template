# VYRA Module Template - Environment Configuration Guide

This template includes an `.env` file that configures module-specific settings for Docker Swarm deployment.

## Quick Start: Creating a New Module

When creating a new module from this template:

1. **Copy this template directory** to your workspace modules folder
2. **Update the `.env` file** with your module-specific values:
   - Change `MODULE_NAME` to your module name
   - Update `MODULE_IMAGE` registry path for production
   - Adjust `ROS_SECURITY_ENCLAVE` to match your module name

## Environment Configuration Structure

### Module-Specific Settings (`.env` in module directory)
- `MODULE_NAME`: Your module's unique identifier
- `MODULE_IMAGE`: Docker image to use (dev vs production)
- `VYRA_DEV_MODE`: Enable/disable development features
- `ENABLE_ROS2_HOT_RELOAD`: Auto-rebuild on code changes
- Module-specific ROS2 and service settings

### Global Settings (`VOS2_WORKSPACE/.env`)
- `VYRA_DEV_MODE`: Global development mode flag
- `VYRA_BUILD_MODE`: Build strategy (dev/ci)
- `VYRA_SECURITY_TOKEN`: Shared security token
- Other workspace-wide settings

## Development vs Production

### Development Mode
```env
VYRA_DEV_MODE=true
MODULE_IMAGE=vyra_base_image:development
ENABLE_ROS2_HOT_RELOAD=true
```
- Uses `vyra_base_image:development` with full dev tools
- Mounts source code for hot-reload
- Automatic ROS2 rebuild on changes
- Vue.js dev server with HMR

### Production Mode
```env
VYRA_DEV_MODE=false
MODULE_IMAGE=ghcr.io/your-org/your-module:latest
ENABLE_ROS2_HOT_RELOAD=false
```
- Uses pre-built production image from registry
- No source code mounts
- Nginx serves static files
- Optimized and minimal runtime

## Docker Compose Integration

Your `docker-compose.yml` should reference the module's `.env`:

```yaml
your_module_service:
  image: vyra_base_image:dev  # For development
  env_file:
    - ./modules/your_module_directory/.env
  volumes:
    - ./modules/your_module_directory:/workspace
  command:
    - /workspace/vyra_entrypoint.sh
```

For production, update the image reference:
```yaml
your_module_service:
  image: ghcr.io/your-org/your-module:latest
  env_file:
    - ./modules/your_module_directory/.env
  # Minimal volume mounts (logs, storage only)
```

## Best Practices

1. **Never commit secrets** to `.env` files
2. **Module-specific config** stays in module's `.env`
3. **Global config** stays in workspace root `.env`
4. **Production images** should use specific version tags, not `latest`
5. **Development** always uses `vyra_base_image:development` with source mounts

## Example: Transitioning from Dev to Production

### Step 1: Develop locally
- Use `VYRA_DEV_MODE=true` and `MODULE_IMAGE=vyra_base_image:development`
- Code changes reflect immediately with hot-reload

### Step 2: Build production image
```bash
docker build -t ghcr.io/your-org/your-module:v1.0.0 -f Dockerfile .
docker push ghcr.io/your-org/your-module:v1.0.0
```

### Step 3: Update module's `.env` for production
```env
VYRA_DEV_MODE=false
MODULE_IMAGE=ghcr.io/your-org/your-module:v1.0.0
```

### Step 4: Update `docker-compose.yml`
```yaml
your_module_service:
  image: ghcr.io/your-org/your-module:v1.0.0
  env_file:
    - ./modules/your_module_directory/.env
  volumes:
    # Only mount essentials, no source code
    - ./modules/your_module_directory/storage:/workspace/storage
    - ./modules/your_module_directory/log:/workspace/log
```

## Troubleshooting

**Service won't start:**
- Check `docker service ps <service_name>` for errors
- Verify image exists locally or in registry
- Ensure `.env` file is properly formatted

**Hot-reload not working:**
- Confirm `VYRA_DEV_MODE=true` and `ENABLE_ROS2_HOT_RELOAD=true`
- Verify source code is mounted in `docker-compose.yml`
- Check that `vyra_base_image:dev` is being used

**Image not found:**
- For dev: Ensure `vyra_base_image:dev` is built
- For prod: Check registry credentials and image name

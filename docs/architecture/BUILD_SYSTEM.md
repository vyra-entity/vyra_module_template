# Build System & Docker Optimization

## Overview

This module uses a modern, cache-optimized build system combining **Poetry** for dependency management and **Docker multi-stage builds** for efficient containerization.

## 🎯 Key Features

- ✅ **Poetry-based dependency management** - Professional, reproducible builds
- ✅ **Docker layer caching** - Fast rebuilds when only code changes
- ✅ **Multi-stage builds** - Minimal production images (~150MB module layer)
- ✅ **Lock files** - Reproducible dependency resolution
- ✅ **Optional extras** - SLIM mode with lightweight dependencies

## Poetry Dependency Management

### Configuration Files

**`pyproject.toml`** - Project metadata and dependencies:
```toml
[tool.poetry]
name = "v2_modulemanager"
version = "0.1.0"

[tool.poetry.dependencies]
python = "^3.10"
fastapi = "^0.109.0"
uvicorn = {extras = ["standard"], version = "^0.27.0"}
# ... more dependencies

[tool.poetry.extras]
slim = ["eclipse-zenoh", "zenoh-python"]  # Optional SLIM mode deps

[tool.poetry.scripts]
v2-modulemanager = "v2_modulemanager.v2_modulemanager.main:main"
v2-modulemanager-slim = "v2_modulemanager.v2_modulemanager.main:main"
```

**`poetry.lock`** - Locked dependency versions (generated automatically)

### Local Development

```bash
# Install dependencies
poetry install

# Install with SLIM mode extras
poetry install -E slim

# Install all extras
poetry install --all-extras

# Add new dependency
poetry add fastapi

# Add dev dependency
poetry add --group dev pytest

# Update dependencies
poetry update

# Build wheel
poetry build
```

### Running with Poetry

```bash
# Via entry point
poetry run v2-modulemanager

# Via Python module
poetry run python -m v2_modulemanager.v2_modulemanager.main

# With environment
VYRA_SLIM=true poetry run v2-modulemanager-slim
```

## Docker Build Optimization

### Layer Caching Strategy

The Dockerfile is optimized for fast rebuilds using **Docker layer caching**:

```dockerfile
# Stage 1: Builder
FROM vyra_base_image:development AS builder

# 1. Install Poetry
RUN pip install --no-cache-dir poetry

# 2. Configure Poetry (no virtualenvs in container)
RUN poetry config virtualenvs.create false

# 3. THE TRICK: Copy ONLY dependency files first
COPY pyproject.toml poetry.lock* ./

# 4. Install dependencies WITHOUT project code (--no-root)
# This layer is CACHED unless pyproject.toml/poetry.lock change
RUN poetry install --only main -E slim --no-interaction --no-ansi --no-root

# 5. NOW copy the code (changes here don't invalidate dependency cache)
COPY . .

# 6. Install project itself (dependencies already cached)
RUN poetry install --only main -E slim --no-interaction --no-ansi
```

### Build Performance

**Without layer caching** (traditional approach):
```bash
# Every code change reinstalls ALL dependencies
COPY . .
RUN poetry install  # 2-5 minutes
```

**With layer caching** (optimized):
```bash
# Only first build installs dependencies (2-5 minutes)
# Subsequent builds with code changes: ~10-30 seconds
```

### Multi-Stage Build

The Dockerfile uses two stages for minimal production images:

**Stage 1: Builder** (~2GB)
- Full build tools (npm, gcc, colcon)
- Compiles ROS2 packages
- Builds frontend assets
- Installs Python dependencies

**Stage 2: Runtime** (~150MB module layer)
- Only runtime artifacts (no build tools)
- Compiled packages from builder
- Python dependencies from builder
- Frontend dist/ from builder

### Build Commands

```bash
# Build development image
docker build -t v2_modulemanager:development \
  --target runtime \
  --build-arg BUILDER_BASE_IMAGE=vyra_base_image:development \
  --build-arg RUNTIME_BASE_IMAGE=vyra_base_image:production \
  .

# Build with cache from registry (CI/CD)
docker build -t v2_modulemanager:latest \
  --cache-from ghcr.io/variobotic-gmbh/v2_modulemanager:latest \
  .

# Build SLIM mode
docker build -t v2_modulemanager:slim \
  --build-arg POETRY_EXTRAS="slim" \
  .
```

## Build Cache Management

### Local Development

```bash
# Check cache usage
docker system df

# Prune build cache (free space)
docker builder prune

# Prune everything (nuclear option)
docker system prune -a --volumes
```

### CI/CD Cache Optimization

GitHub Actions example:
```yaml
- name: Cache Docker layers
  uses: actions/cache@v3
  with:
    path: /tmp/.buildx-cache
    key: ${{ runner.os }}-buildx-${{ github.sha }}
    restore-keys: |
      ${{ runner.os }}-buildx-

- name: Build with cache
  uses: docker/build-push-action@v5
  with:
    cache-from: type=local,src=/tmp/.buildx-cache
    cache-to: type=local,dest=/tmp/.buildx-cache-new
```

## Dependency Updates

### Regular Updates

```bash
# Check for outdated dependencies
poetry show --outdated

# Update all dependencies (respecting constraints)
poetry update

# Update specific package
poetry update fastapi

# Update and regenerate lock file
poetry lock --no-update
```

### Security Updates

```bash
# Check for vulnerabilities
poetry export -f requirements.txt | safety check --stdin

# Or use pip-audit
pip-audit
```

## Troubleshooting

### Poetry Issues

**Problem:** `poetry.lock out of sync`
```bash
# Solution: Regenerate lock file
poetry lock --no-update
```

**Problem:** `Dependency conflicts`
```bash
# Solution: Check conflicts
poetry show --tree

# Manual resolution in pyproject.toml
[tool.poetry.dependencies]
conflicting-package = ">=1.0,<2.0"  # Add explicit constraint
```

**Problem:** `Cache issues`
```bash
# Clear Poetry cache
poetry cache clear . --all
```

### Docker Build Issues

**Problem:** `Build fails at poetry install`
```bash
# Check Poetry version in container
docker run --rm vyra_base_image:development poetry --version

# Verify pyproject.toml syntax
poetry check
```

**Problem:** `Cache not working`
```bash
# Verify layer caching is enabled
docker build --progress=plain . 2>&1 | grep "CACHED"

# Force no-cache build to reset
docker build --no-cache .
```

**Problem:** `Out of disk space`
```bash
# Check space
df -h

# Prune unused images
docker system prune -a
```

## Best Practices

### 1. Keep pyproject.toml Clean

```toml
# ✅ Use version constraints
fastapi = "^0.109.0"  # Compatible with 0.109.x

# ❌ Avoid pinning everything
fastapi = "==0.109.0"  # Too restrictive
```

### 2. Use Dependency Groups

```toml
[tool.poetry.group.dev.dependencies]
pytest = "^7.4.0"
black = "^23.0.0"
ruff = "^0.2.0"

[tool.poetry.group.docs.dependencies]
mkdocs = "^1.5.0"
```

### 3. Regular Maintenance

- Update dependencies monthly: `poetry update`
- Check security vulnerabilities weekly
- Review `poetry.lock` changes in PR reviews
- Keep Poetry itself updated: `pip install --upgrade poetry`

### 4. Docker Best Practices

- **Always** use `.dockerignore` to exclude unnecessary files
- **Never** copy `node_modules/` or `__pycache__/`
- **Use** multi-stage builds for production
- **Leverage** layer caching for development speed
- **Pin** base image versions for reproducibility

## Related Documentation

- [SLIM Mode](SLIM_MODE.md) - Lightweight deployment with Poetry
- [Development Guide](development/DEVEL.md) - Local development setup
- [Deployment Guide](deployment/DEPLOYMENT.md) - Production deployment
- [Dependency Installation](development/DEPENDENCY_INSTALLATION.md) - Dependency management

## References

- [Poetry Documentation](https://python-poetry.org/docs/)
- [Docker Build Cache](https://docs.docker.com/build/cache/)
- [Docker Multi-Stage Builds](https://docs.docker.com/build/building/multi-stage/)
- [Dockerfile Best Practices](https://docs.docker.com/develop/develop-images/dockerfile_best-practices/)

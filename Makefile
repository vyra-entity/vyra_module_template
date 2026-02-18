.PHONY: help install install-slim install-dev test test-slim test-ros2 lint format type-check clean build run run-slim

# Default target
.DEFAULT_GOAL := help

# Colors for output
BLUE := \033[0;34m
GREEN := \033[0;32m
YELLOW := \033[0;33m
RED := \033[0;31m
NC := \033[0m # No Color

help: ## Show this help message
	@echo "$(BLUE)VYRA Module Template - Available Commands$(NC)"
	@echo ""
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  $(GREEN)%-20s$(NC) %s\n", $$1, $$2}'
	@echo ""
	@echo "$(YELLOW)Quick Start:$(NC)"
	@echo "  make install-dev    # Install all dependencies"
	@echo "  make test          # Run all tests"
	@echo "  make run-slim      # Run in SLIM mode (Zenoh)"
	@echo ""

# Installation targets
install: ## Install production dependencies (ROS2 mode)
	@echo "$(BLUE)Installing production dependencies...$(NC)"
	poetry install --only main --no-interaction

install-slim: ## Install production dependencies for SLIM mode (with Zenoh)
	@echo "$(BLUE)Installing SLIM mode dependencies...$(NC)"
	poetry install --only main -E slim --no-interaction

install-dev: ## Install all dependencies including dev tools
	@echo "$(BLUE)Installing all dependencies (dev + main + SLIM)...$(NC)"
	poetry install --all-extras --no-interaction

# Testing targets
test: ## Run all tests with coverage
	@echo "$(BLUE)Running all tests...$(NC)"
	poetry run pytest

test-unit: ## Run unit tests only
	@echo "$(BLUE)Running unit tests...$(NC)"
	poetry run pytest -m unit

test-slim: ## Run SLIM mode tests only
	@echo "$(BLUE)Running SLIM mode tests...$(NC)"
	VYRA_SLIM=true poetry run pytest -m slim

test-ros2: ## Run ROS2 mode tests only
	@echo "$(BLUE)Running ROS2 mode tests...$(NC)"
	VYRA_SLIM=false poetry run pytest -m ros2

test-watch: ## Run tests in watch mode
	@echo "$(BLUE)Running tests in watch mode...$(NC)"
	poetry run pytest-watch

# Code quality targets
lint: ## Run linter (ruff)
	@echo "$(BLUE)Running linter...$(NC)"
	poetry run ruff check src/ tests/

lint-fix: ## Run linter with auto-fix
	@echo "$(BLUE)Running linter with auto-fix...$(NC)"
	poetry run ruff check --fix src/ tests/

format: ## Format code with black and ruff
	@echo "$(BLUE)Formatting code...$(NC)"
	poetry run black src/ tests/
	poetry run ruff format src/ tests/

format-check: ## Check code formatting without changes
	@echo "$(BLUE)Checking code formatting...$(NC)"
	poetry run black --check src/ tests/
	poetry run ruff format --check src/ tests/

type-check: ## Run type checker (mypy)
	@echo "$(BLUE)Running type checker...$(NC)"
	poetry run mypy src/

quality: lint format type-check ## Run all code quality checks

# Build targets
build: ## Build distribution packages
	@echo "$(BLUE)Building distribution packages...$(NC)"
	poetry build

# Run targets
run: ## Run module in ROS2 mode
	@echo "$(BLUE)Starting {{ module_name }} (ROS2 mode)...$(NC)"
	VYRA_SLIM=false poetry run vyra-module-template

run-slim: ## Run module in SLIM mode (Zenoh)
	@echo "$(BLUE)Starting {{ module_name }} (SLIM mode with Zenoh)...$(NC)"
	VYRA_SLIM=true poetry run vyra-module-template-slim

# Clean targets
clean: ## Clean build artifacts and cache
	@echo "$(BLUE)Cleaning build artifacts...$(NC)"
	rm -rf build/
	rm -rf dist/
	rm -rf *.egg-info
	rm -rf .pytest_cache
	rm -rf .mypy_cache
	rm -rf .ruff_cache
	rm -rf htmlcov/
	rm -rf .coverage
	rm -rf .coverage.*
	rm -rf *.pyc
	rm -rf __pycache__
	find . -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null || true
	find . -type f -name "*.pyc" -delete 2>/dev/null || true

clean-logs: ## Clean log files
	@echo "$(BLUE)Cleaning log files...$(NC)"
	rm -rf log/*

clean-all: clean clean-logs ## Clean everything

# Development targets
shell: ## Start Poetry shell
	poetry shell

update: ## Update dependencies
	@echo "$(BLUE)Updating dependencies...$(NC)"
	poetry update

lock: ## Update poetry.lock file
	@echo "$(BLUE)Updating lock file...$(NC)"
	poetry lock --no-update

# Documentation
docs: ## Generate documentation (placeholder)
	@echo "$(YELLOW)Documentation generation not yet implemented$(NC)"

# CI/CD targets
ci: install-dev quality test ## Run CI pipeline locally

.PHONY: pre-commit
pre-commit: format-check lint type-check test-unit ## Pre-commit checks

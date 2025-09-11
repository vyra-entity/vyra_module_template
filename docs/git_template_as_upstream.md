# Git Upstream Setup for Modules

## 1. Situation

- You have a module repository (`module-A`) based on a template framework (`vyra_module_template`).
- Your module may contain custom files and modifications.
- Goal: Easily incorporate future updates from the template without losing your module-specific changes.

## 2. Add the Template as Upstream

```bash
# Navigate to your module directory
cd module-A

# Add the template repository as an upstream remote
git remote add upstream https://github.com/vyra-entity/vyra_module_template.git

# Verify the remote has been added
git remote -v
```

**Example Output:**

```text
origin    git@github.com:vyra-entity/module-A.git (fetch)
origin    git@github.com:vyra-entity/module-A.git (push)
upstream  https://github.com/vyra-entity/vyra_module_template.git (fetch)
upstream  https://github.com/vyra-entity/vyra_module_template.git (push)
```

## 3. Fetch Changes from the Template

```bash
# Fetch all branches from the template
git fetch upstream
```

- This downloads changes locally but does not merge them yet.

## 4. Perform the First Merge

> If your module and template have **unrelated histories** (e.g., the module was copied manually), use `--allow-unrelated-histories`:

```bash
git merge upstream/main --allow-unrelated-histories
```

- Git creates a merge commit.
- Conflicts only occur where template files were modified and you also changed them locally.

## 5. Incorporate Future Template Updates

1. Fetch the latest template changes:

```bash
git fetch upstream
```

2. Merge changes into your module:

```bash
git merge upstream/main
```

- Alternatively, use rebase for a linear history:

```bash
git rebase upstream/main
```

- Conflicts only need to be resolved for modified template files.

## 6. Best Practices for Module-Specific Changes

- Avoid modifying the original template files directly.
- Place your custom configs and modules in **separate files/folders**.
- Only extend template files instead of overwriting them.
- For configuration files:
  - Template provides `config.default.yaml`
  - Module creates `config.yaml` with overrides
  - Template updates can be merged automatically, and your custom settings remain intact.


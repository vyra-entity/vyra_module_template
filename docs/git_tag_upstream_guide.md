# Git Tag and Upstream Guide for Modules

## 1. Creating a Tag in the Template Repository

- Navigate to your template repository:

```bash
cd vyra_module_template
```

- Create an annotated tag (recommended for releases):

```bash
git tag -a v1.0.0 -m "Initial template release"
```

- Push the tag to GitHub:

```bash
git push origin v1.0.0
```

- Verify the tag exists on GitHub:

```bash
git tag
```

You should see:
```
v1.0.0
```

---

## 2. Merging a Specific Template Version into Your Module

- In your module repository (`module-A`), make sure the template is added as `upstream`:

```bash
cd module-A
git remote add upstream https://github.com/your-org/template-framework.git
git fetch upstream
```

- Merge the specific tag from upstream into your module:

```bash
git merge upstream/v1.0.0
```

- Resolve any conflicts if they appear. Only conflicts where both template files and module-specific changes overlap need attention.

---

## 3. Future Updates from Template

- When the template is updated and a new tag is created (e.g., `v1.1.0`):

```bash
git fetch upstream
git merge upstream/v1.1.0
```

- This allows you to upgrade to a new template version while keeping your module-specific modifications intact.

---

## 4. Best Practices

- Use **tags** to mark stable versions of your template.  
- Use **branches** (`main` or `develop`) for ongoing development, not for stable module updates.  
- Prefer **annotated tags** for clarity and GitHub release integration.  
- Always resolve conflicts carefully, and try to keep module-specific files separate from template files.


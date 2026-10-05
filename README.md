# repository_template

> 📌 **Note:** This template is based on **Yoriito v0.2.0**.

A template for creating new GitHub repositories with standard configurations and CI/CD workflows.

## How to Use This Template

1. Click the **"Use this template"** button in GitHub to create your new repository.
2. Clone your newly created repository to your local machine.
3. Follow the [Files to Modify](#files-to-modify-for-each-repository) section below to customize the configuration files.
4. Set up the required [Repository Settings](#repository-settings) (Secrets, Variables, and Security).

For more information, refer to the instructions under ["When you create a new repository"](https://jaspar-sdv-dev.atlassian.net/wiki/spaces/apiwg/pages/574554320/WIP+OSS).

---

## Files

### File Structure

```text
.github/
    ISSUE_TEMPLATE/
        ISSUE_TEMPLATE_BUG.yml
        ISSUE_TEMPLATE_FEATURE.yml
    workflows/
        japanese-check.yml
        pullrequest_check.yml
        release.yml
    CODEOWNERS
    pull_request_template.md
LICENSE
NOTICE.md
SECURITY.md
```

### Files to Modify for Each Repository

After creating your repository, please update or verify the following files:

- **`.github/workflows/release.yml`**: Ensure all required release CI processes are integrated into this workflow. (Note: This file was originally ported from the `action-internal` repository).
- **`.github/CODEOWNERS`**: Update this file with the appropriate code owners for your project.
- **Issue Templates (`ISSUE_TEMPLATE_BUG.yml`, `ISSUE_TEMPLATE_FEATURE.yml`)**: These files will be updated in alignment with the Yoriito release schedule. Please ensure you are using the correct versions.  
- **`README.md`**: Replace this template README with your project's specific documentation (Overview, Installation, Usage, etc.).


---

## Repository Settings

### Repository Secrets & Variables

Refer to the Confluence documentation below to configure the necessary secrets and variables (e.g., PAT, GitHub Apps):

- [PAT / GitHub Apps / Secrets & Variables Configuration](https://jaspar-sdv-dev.atlassian.net/wiki/spaces/apiwg/pages/565510954/v0.2.0#PAT%2FGitHub-Apps%2Fsecrets%2Fvariables%E6%95%B4%E7%90%86)
- [GitHub Authority Management](https://jaspar-sdv-dev.atlassian.net/wiki/spaces/apiwg/pages/395542789/OSS+Github?xpis=eyJicmlkZ2UiOiJxdWlja0ZpbmQiLCJpZCI6IjE3OTA1NzMwNTMzMDkiLCJzb3VyY2UiOiJjb25mbHVlbmNlIn0%3D)

### Repository Security Features

Refer to the Confluence documentation below to enable and configure security scanning features (e.g., Dependabot, CodeQL):

- [GitHub Security Features Setup Guide](https://jaspar-sdv-dev.atlassian.net/wiki/spaces/apiwg/pages/407961615/OSS+Github?xpis=eyJicmlkZ2UiOiJxdWlja0ZpbmQiLCJpZCI6IjE3OTA1NzMwNTMzMDkiLCJzb3VyY2UiOiJjb25mbHVlbmNlIn0%3D)

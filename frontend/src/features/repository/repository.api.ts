import apiClient from '../../api/http'
import type { RepositoryModule, Repository, ApiResponse } from '../../types/common'

/**
 * API calls for module repository
 */
export const repositoryApi = {
  /**
   * Get available repositories with all modules
   */
  async getRepositories(): Promise<Repository[]> {
    const response = await apiClient.get('/repository/list')
    const repos = response.data.repositories || []
    // Filter enabled repositories only and add displayName
    return repos
      .filter((repo: Repository) => !repo.disabled)
      .map((repo: Repository) => ({
        ...repo,
        displayName: repo.displayName || repo.name
      }))
  },

  /**
   * Get modules from a specific repository
   */
  async getModules(repositoryName: string): Promise<RepositoryModule[]> {
    const response = await apiClient.get('/repository/modules', {
      params: { repository_id: repositoryName }
    })
    const modules = response.data.modules || []
    // Add displayName and id if not present
    return modules.map((module: RepositoryModule) => ({
      ...module,
      id: module.id || module.name,
      displayName: module.displayName || module.name
    }))
  },

  /**
   * Install a module from repository
   */
  async installModule(
    moduleName: string,
    moduleId: string, 
    moduleDescription: string,
    moduleAuthor: string,
    moduleTemplate: string,
    moduleIcon: string,
    moduleDependencies: Record<string, string[]>,
    moduleVersion: string,
    repositoryName: string
  ): Promise<{ operation_id: string; status_url: string }> {
    const response = await apiClient.post('/repository/install', {
      module_name: moduleName,
      module_hash: moduleId,
      module_description: moduleDescription,
      module_author: moduleAuthor,
      module_template: moduleTemplate,
      module_icon: moduleIcon,
      module_dependencies: moduleDependencies,
      module_version: moduleVersion,
      repository: { id: repositoryName },
      version: moduleVersion
    })
    return response.data
  },

  /**
   * Install an additional instance of an already installed module
  */
  async installAdditionalInstance(
    moduleName: string,
    moduleId: string, 
    moduleDescription: string,
    moduleAuthor: string,
    moduleTemplate: string,
    moduleIcon: string,
    moduleDependencies: Record<string, any>,
    moduleVersion: string,
    repository: Repository
  ): Promise<{ operation_id: string; status_url: string }> {
    const repository_data: Record<string, any> = { ...repository }
    const response = await apiClient.post('/repository/install-instance', {
      module_name: moduleName,
      module_hash: moduleId,
      module_description: moduleDescription,
      module_author: moduleAuthor,
      module_template: moduleTemplate,
      module_icon: moduleIcon,
      module_dependencies: moduleDependencies,
      module_version: moduleVersion,
      repository: repository_data
    })
    return response.data
  },

  /**
   * Refresh repository metadata
   */
  async refreshRepository(repositoryName: string): Promise<ApiResponse> {
    const response = await apiClient.post('/repository/refresh', {
      repository_id: repositoryName
    })
    return response.data
  }
}


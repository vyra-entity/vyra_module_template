import apiClient from '../../api/http'
import type { OperationStatus, ApiResponse } from '../../types/common'

/**
 * API calls for operation status tracking
 */
export const operationApi = {
  /**
   * Get operation status
   * @param operationId - The operation ID
   * @param statusUrl - Optional custom status URL (e.g. /repository/install/status/{id})
   */
  async getStatus(operationId: string, statusUrl?: string): Promise<OperationStatus> {
    const url = statusUrl || `/modules/status/${operationId}`
    const response = await apiClient.get(url)
    return response.data
  },

  /**
   * Respond to user prompt
   */
  async respondToPrompt(
    operationId: string, 
    promptId: string, 
    response: string
  ): Promise<ApiResponse> {
    const res = await apiClient.post(`/modules/operations/${operationId}/prompts/${promptId}/respond`, {
      response
    })
    return res.data
  },

  /**
   * Cancel an operation
   * @param operationId - The operation ID
   * @param cancelUrl - Optional custom cancel URL (e.g. /repository/install/cancel/{id})
   */
  async cancelOperation(operationId: string, cancelUrl?: string): Promise<ApiResponse> {
    const url = cancelUrl || `/modules/operations/${operationId}/cancel`
    const response = await apiClient.post(url)
    return response.data
  }
}

import axios from 'axios'

/**
 * HTTP client for the module backend API.
 *
 * The baseURL uses the module name prefix injected at build time via
 * the VITE_MODULE_NAME environment variable, or falls back to relative
 * API paths when running behind the Traefik reverse proxy.
 */
const apiClient = axios.create({
  baseURL: `/${import.meta.env.VITE_MODULE_NAME ?? '{{ module_name }}'}/api`,
  timeout: 30000,
  headers: {
    'Content-Type': 'application/json',
    Accept: 'application/json',
  },
})

apiClient.interceptors.response.use(
  (response) => response,
  (error) => {
    console.error('API Error:', error)
    return Promise.reject(error)
  },
)

export default apiClient

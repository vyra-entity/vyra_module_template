import axios, { type AxiosInstance } from 'axios'

/**
 * HTTP client configuration
 */
const apiClient: AxiosInstance = axios.create({
  baseURL: '/{{ module_name }}/api',
  timeout: 30000,
  headers: {
    'Content-Type': 'application/json',
    'Accept': 'application/json'
  }
})

// Request interceptor
apiClient.interceptors.request.use(
  (config) => {
    // Add authentication token if available
    // const token = localStorage.getItem('auth_token')
    // if (token) {
    //   config.headers.Authorization = `Bearer ${token}`
    // }
    return config
  },
  (error) => {
    return Promise.reject(error)
  }
)

// Response interceptor
apiClient.interceptors.response.use(
  (response) => response,
  (error) => {
    const method = (error.config?.method ?? 'HTTP').toUpperCase()
    const url = (error.config?.baseURL ?? '') + (error.config?.url ?? '')
    const status = error.response?.status ?? error.code ?? 'no status'
    console.error(`API Error [${method} ${url}] → ${status}:`, error.message ?? error)
    return Promise.reject(error)
  }
)

export default apiClient

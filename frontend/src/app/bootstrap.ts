import type { App } from 'vue'
import { setupPlugins } from './plugins'
import router from '../router'

/**
 * Bootstrap the application with all necessary plugins and configurations
 */
export function bootstrap(app: App): void {
  // Setup plugins (Pinia, PrimeVue, etc.)
  setupPlugins(app)
  
  // Setup router
  app.use(router)
  
  // Additional global configurations can be added here
  console.log('✅ {{ module_display_name }} Application bootstrapped successfully')
}

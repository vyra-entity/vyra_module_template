import type { App } from 'vue'
import { createPinia } from 'pinia'
import PrimeVue from 'primevue/config'
import Aura from '@primevue/themes/aura'
import ConfirmationService from 'primevue/confirmationservice'
import ToastService from 'primevue/toastservice'
import Tooltip from 'primevue/tooltip'

// Import PrimeVue CSS
import 'primeicons/primeicons.css'
import 'primeflex/primeflex.css'

/**
 * Setup all Vue plugins
 */
export function setupPlugins(app: App): void {
  // Setup Pinia store
  const pinia = createPinia()
  app.use(pinia)

  // Setup PrimeVue
  app.use(PrimeVue, {
    theme: {
      preset: Aura,
      options: {
        darkModeSelector: '.dark-mode'
      }
    }
  })

  // PrimeVue Services
  app.use(ConfirmationService)
  app.use(ToastService)

  // PrimeVue Directives
  app.directive('tooltip', Tooltip)
}

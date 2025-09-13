import { createApp } from 'vue'
import { createRouter, createWebHistory } from 'vue-router'
import { createPinia } from 'pinia'
import App from './App.vue'

// Import Views
import Home from './views/Home.vue'
import Modules from './views/Modules.vue'
import Monitoring from './views/Monitoring.vue'

// Router Setup
const routes = [
  { path: '/', name: 'Home', component: Home },
  { path: '/modules', name: 'Modules', component: Modules },
  { path: '/monitoring', name: 'Monitoring', component: Monitoring }
]

const router = createRouter({
  history: createWebHistory(),
  routes
})

// Pinia Store
const pinia = createPinia()

// App Setup
const app = createApp(App)
app.use(router)
app.use(pinia)
app.mount('#app')

// Global error handling
app.config.errorHandler = (err, vm, info) => {
  console.error('Vue error:', err, info)
}

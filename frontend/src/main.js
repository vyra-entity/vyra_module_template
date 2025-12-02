import { createApp } from 'vue'
import { createRouter, createWebHistory } from 'vue-router'
import { createPinia } from 'pinia'
import App from './App.vue'

// Import Views
import Home from './views/Home.vue'

// Router Setup
const routes = [
  { path: '/', name: 'Home', component: Home }
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

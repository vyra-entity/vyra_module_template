import { createApp } from 'vue'
import App from './App.vue'
import { bootstrap } from './app/bootstrap'

// Import global styles
import './assets/styles.css'

const app = createApp(App)

// Initialize plugins, router, store, etc.
bootstrap(app)

app.mount('#app')

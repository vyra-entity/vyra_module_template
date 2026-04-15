import { createApp } from 'vue'
import * as Vue from 'vue'
import App from './App.vue'
import { bootstrap } from './app/bootstrap'

// Import global styles
import './assets/styles.css'

// Expose Vue globally so dynamically imported plugin scripts (loaded as plain
// ES modules without a bundler) can access Vue via `window.Vue`.
;(window as any).Vue = Vue

const app = createApp(App)

// Initialize plugins, router, store, etc.
bootstrap(app)

app.mount('#app')

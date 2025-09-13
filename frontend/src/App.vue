<template>
  <div id="app">
    <nav class="navbar">
      <div class="nav-brand">
        <h1>🚀 VYRA Dashboard</h1>
      </div>
      <div class="nav-links">
        <router-link to="/" class="nav-link">Home</router-link>
        <router-link to="/modules" class="nav-link">Module</router-link>
        <router-link to="/monitoring" class="nav-link">Monitoring</router-link>
      </div>
    </nav>

    <main class="main-content">
      <router-view />
    </main>

    <footer class="footer">
      <p>&copy; 2025 VYRA Dashboard - Backend: {{ backendStatus }}</p>
    </footer>
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import axios from 'axios'

const backendStatus = ref('Verbinde...')

const checkBackendStatus = async () => {
  try {
    const response = await axios.get('/api/status')
    backendStatus.value = `✅ ${response.data.status}`
  } catch (error) {
    backendStatus.value = '❌ Offline'
    console.error('Backend nicht erreichbar:', error)
  }
}

onMounted(() => {
  checkBackendStatus()
  // Status alle 30 Sekunden aktualisieren
  setInterval(checkBackendStatus, 30000)
})
</script>

<style scoped>
#app {
  min-height: 100vh;
  display: flex;
  flex-direction: column;
}

.navbar {
  background: #2c3e50;
  color: white;
  padding: 1rem 2rem;
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.nav-brand h1 {
  margin: 0;
  font-size: 1.5rem;
}

.nav-links {
  display: flex;
  gap: 1rem;
}

.nav-link {
  color: white;
  text-decoration: none;
  padding: 0.5rem 1rem;
  border-radius: 4px;
  transition: background 0.3s;
}

.nav-link:hover,
.nav-link.router-link-active {
  background: #34495e;
}

.main-content {
  flex: 1;
  padding: 2rem;
  background: #f8f9fa;
}

.footer {
  background: #34495e;
  color: white;
  text-align: center;
  padding: 1rem;
}
</style>

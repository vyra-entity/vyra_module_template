<template>
  <div class="vyra-app">
    <!-- Sidebar navigation -->
    <VyraSidebar
      title="VYRA Dashboard"
      :backend-status="backendStatus"
    />

    <!-- Main content area -->
    <div
      class="vyra-main"
      :class="{ 'sidebar-collapsed': sidebarStore.isCollapsed }"
    >
      <!-- Slim topbar -->
      <header class="vyra-topbar">
        <!-- Mobile hamburger -->
        <button class="mobile-menu-btn" @click="sidebarStore.toggleCollapse()" aria-label="Menü">
          <i class="pi pi-bars" />
        </button>
        <span class="page-title">{{ pageTitle }}</span>
      </header>

      <main class="vyra-content">
        <router-view />
      </main>

      <footer class="vyra-footer">
        <p>&copy; 2025 VYRA Industrial Automation</p>
      </footer>
    </div>
  </div>
</template>

<script setup>
import { ref, computed, onMounted } from 'vue'
import { useRoute } from 'vue-router'
import axios from 'axios'
import VyraSidebar from './components/layout/VyraSidebar.vue'
import { useSidebarStore } from './store/sidebar'

const route        = useRoute()
const sidebarStore = useSidebarStore()

// Page title from route meta or route name
const pageTitle = computed(() =>
  (route.meta?.title) ? String(route.meta.title).split(' - ')[0] : (route.name ?? 'Home')
)

// Backend health check
const backendStatus = ref('checking')

async function checkBackend() {
  try {
    await axios.get('/api/status')
    backendStatus.value = 'running'
  } catch {
    backendStatus.value = 'stopped'
  }
}

onMounted(() => {
  checkBackend()
  setInterval(checkBackend, 30000)
})
</script>

<style scoped>
/* ── Root layout: sidebar + scrollable main ── */
.vyra-app {
  display: flex;
  flex-direction: row;
  min-height: 100vh;
  background: #f5f7fa;
}

.vyra-main {
  flex: 1;
  display: flex;
  flex-direction: column;
  min-width: 0;
  overflow: hidden;
}

/* ── Topbar ── */
.vyra-topbar {
  display: flex;
  align-items: center;
  padding: 0.75rem 2rem;
  border-bottom: 1px solid #e0e0e0;
  background: #fff;
  min-height: 52px;
  flex-shrink: 0;
}

.page-title {
  font-size: 1rem;
  font-weight: 600;
  color: #212121;
}

/* ── Content ── */
.vyra-content {
  flex: 1;
  padding: 2rem;
  overflow: auto;
}

/* ── Footer ── */
.vyra-footer {
  padding: 1rem 2rem;
  text-align: center;
  border-top: 1px solid #e0e0e0;
  color: #607D8B;
  font-size: 0.875rem;
  flex-shrink: 0;
}

.vyra-footer p {
  margin: 0;
}

/* ── Responsive: very small screens ── */
@media (max-width: 480px) {
  .vyra-app {
    flex-direction: column;
  }

  .vyra-main {
    padding-top: 52px;
  }

  .vyra-topbar {
    padding: 0.75rem 1rem;
    gap: 0.75rem;
  }

  .vyra-content {
    padding: 1rem;
  }

  .mobile-menu-btn {
    display: flex !important;
  }
}

/* ── Mobile hamburger (hidden on desktop) ── */
.mobile-menu-btn {
  display: none;
  align-items: center;
  justify-content: center;
  width: 36px;
  height: 36px;
  border: none;
  background: transparent;
  cursor: pointer;
  border-radius: 6px;
  color: var(--text-color, #212121);
  flex-shrink: 0;
  transition: background 0.15s;
}

.mobile-menu-btn:hover {
  background: var(--surface-hover, #f0f0f0);
}
</style>

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

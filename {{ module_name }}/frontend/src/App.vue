<template>
  <div class="vyra-app" :class="{ 'has-sidebar': authStore.isAuthenticated }">
    <!-- Invisible infrastructure plugin slots (rendered at App root, no visual output) -->
    <PluginSlot v-if="authStore.isAuthenticated" slot-id="background" />
    <PluginSlot v-if="authStore.isAuthenticated" slot-id="notification-provider" />
    <PluginSlot v-if="authStore.isAuthenticated" slot-id="component-decorator" />
    <!-- SDP registration wrappers: load at App root so they survive navigation -->
    <PluginSlot v-if="authStore.isAuthenticated" slot-id="side-dock-popup.header" />
    <PluginSlot v-if="authStore.isAuthenticated" slot-id="side-dock-popup.content" />
    <PluginSlot v-if="authStore.isAuthenticated" slot-id="side-dock-popup.footer" />
    <!-- Overlay / popup / context-menu layers -->
    <PluginSlot v-if="authStore.isAuthenticated" slot-id="overlay" />
    <PluginSlot v-if="authStore.isAuthenticated" slot-id="popup" />

    <!-- Side-Dock-Popup floating widgets -->
    <SideDockPopup v-if="authStore.isAuthenticated && uiSettingsStore.sideDockPocketEnabled" />

    <!-- Sidebar navigation (only when authenticated) -->
    <VyraSidebar v-if="authStore.isAuthenticated" />

    <!-- Main content area -->
    <div
      class="vyra-main"
      :class="{ 'sidebar-collapsed': sidebarStore.isCollapsed && authStore.isAuthenticated }"
    >
      <!-- Slim topbar: page title (only when authenticated) -->
      <header v-if="authStore.isAuthenticated" class="vyra-topbar">
        <!-- Mobile hamburger -->
        <button
          class="mobile-menu-btn"
          @click="sidebarStore.toggleCollapse()"
          aria-label="Menü öffnen"
        >
          <i class="pi pi-bars" />
        </button>
        <div class="topbar-title">
          <span class="page-title">{% raw %}{{ pageTitle }}{% endraw %}</span>
        </div>

        <!-- Topbar plugin slots -->
        <PluginSlot slot-id="topbar.menu" />
        <PluginSlot slot-id="topbar.display" />

        <!-- Alarm bell + three-dot menu -->
        <div class="topbar-actions">
          <button
            v-if="bellVisible"
            class="alarm-bell-btn"
            :class="{ 'alarm-bell-btn--active': errorCount > 0 }"
            @click="errorDialogVisible = true"
            :aria-label="`${errorCount} Fehlermeldungen`"
          >
            <i class="pi pi-bell alarm-bell-icon" :class="{ 'bell-ring': errorCount > 0 }" />
            <span v-if="errorCount > 0" class="alarm-badge">{% raw %}{{ errorCount > 99 ? '99+' : errorCount }}{% endraw %}</span>
          </button>
          <button
            class="top-menu-btn"
            @click="(e) => topMenu?.toggle(e)"
            aria-label="Menü"
          >
            <i class="pi pi-ellipsis-v" />
          </button>
          <Menu ref="topMenu" :model="topMenuItems" :popup="true" />
        </div>
      </header>

      <main class="vyra-content">
        <router-view :key="$route.fullPath" />
      </main>

      <!-- Status bar with plugin action slots -->
      <VyraStatusbar v-if="authStore.isAuthenticated" />
    </div>
  </div>

  <!-- Global Toast for plugin notifications and topbar actions -->
  <Toast />

  <!-- Error Feed Dialog -->
  <Dialog
    v-model:visible="errorDialogVisible"
    modal
    header="Fehlermeldungen"
    :style="{ width: '680px', maxWidth: '95vw' }"
    :dismissable-mask="true"
  >
    <div v-if="errorFeeds.length === 0" class="text-center py-5 text-color-secondary">
      <i class="pi pi-check-circle mb-3" style="font-size: 3rem; display:block; color: var(--green-500)"></i>
      <p>Keine Fehlermeldungen vorhanden.</p>
    </div>
    <div v-else class="error-feed-list">
      <div
        v-for="(feed, idx) in [...errorFeeds].reverse()"
        :key="idx"
        class="error-feed-item"
      >
        <div class="error-feed-header">
          <span class="error-feed-module">{% raw %}{{ feed.module_name || feed.module_id }}{% endraw %}</span>
          <span class="error-feed-time">{% raw %}{{ new Date(feed.timestamp).toLocaleString('de-DE') }}{% endraw %}</span>
        </div>
        <p class="error-feed-message">{% raw %}{{ feed.message }}{% endraw %}</p>
      </div>
    </div>
    <template #footer>
      <Button
        label="Alle löschen"
        icon="pi pi-trash"
        severity="danger"
        text
        @click="feedStore.clearFeeds()"
      />
      <Button label="Schließen" @click="errorDialogVisible = false" />
    </template>
  </Dialog>
</template>

<script setup lang="ts">
import { computed, onMounted, onUnmounted, ref, watch } from 'vue'
import { useRoute, useRouter } from 'vue-router'
import { useSidebarStore } from './store/sidebar'
import { useAuthStore } from './store/auth'
import { useSystemStore } from './store/system'
import { useModuleFeedStore } from './store/moduleFeed'
import { usePluginStore } from './store/plugins'
import { useUiSettingsStore } from './store/uiSettings'
import { useSettingsStore } from './store/settings'
import apiClient from './api/http'
import VyraSidebar from './components/layout/VyraSidebar.vue'
import SideDockPopup from './components/layout/SideDockPopup.vue'
import VyraStatusbar from './components/layout/VyraStatusbar.vue'
import PluginSlot from './components/PluginSlot.vue'
import Dialog from 'primevue/dialog'
import Button from 'primevue/button'
import Menu from 'primevue/menu'
import Toast from 'primevue/toast'
import { useToast } from 'primevue/usetoast'
import { providePluginApi } from './composables/usePluginApi'

const route        = useRoute()
const router       = useRouter()
const sidebarStore = useSidebarStore()
const authStore    = useAuthStore()
const systemStore  = useSystemStore()
const feedStore    = useModuleFeedStore()
const toast        = useToast()

// Provide the Global Plugin API to all child components (including plugins)
providePluginApi()

/** Derive the current module name from the API base URL at runtime */
const MODULE_NAME = (apiClient.defaults.baseURL ?? '').replace(/\/api$/, '').replace(/^\//, '')

const pluginStore      = usePluginStore()
const uiSettingsStore  = useUiSettingsStore()
const settingsStore    = useSettingsStore()

// Load plugins as soon as the user is authenticated so that infrastructure
// slots (SDP pockets, background workers, etc.) are active from the start.
watch(
  () => authStore.isAuthenticated,
  async (isAuth) => {
    if (isAuth) {
      await pluginStore.resolvePlugins('MODULE', MODULE_NAME)
    }
  },
  { immediate: true },
)

const topMenu      = ref<InstanceType<typeof Menu> | null>(null)

async function handleTopbarLogout(): Promise<void> {
  try {
    await authStore.logout()
    toast.add({ severity: 'success', summary: 'Abgemeldet', detail: 'Sie wurden erfolgreich abgemeldet', life: 3000 })
    router.push('/{{ module_name }}/login')
  } catch {
    toast.add({ severity: 'error', summary: 'Fehler', detail: 'Abmeldung fehlgeschlagen', life: 3000 })
  }
}

const topMenuItems = computed(() => [
  {
    label: 'Einstellungen',
    icon:  'pi pi-cog',
    command: () => router.push({ name: 'settings' }),
  },
  { separator: true },
  {
    label: 'Abmelden',
    icon:  'pi pi-sign-out',
    command: () => { void handleTopbarLogout() },
  },
])

const errorDialogVisible = ref(false)
const errorFeeds         = computed(() => feedStore.errorFeeds)
const errorCount         = computed(() => feedStore.errorFeeds.length)

/** Bell is visible when notifications are enabled in settings. */
const bellVisible        = computed(() => settingsStore.settings.notifications)

/** Dynamic page title from route meta */
const pageTitle = computed(() => {
  const title = route.meta?.title as string | undefined
  return title ? title.split(' - ')[0] : '{{ module_display_name }}'
})

// ── Backend health check ──────────────────────────────────────────────────────
let _healthTimer: ReturnType<typeof setInterval> | null = null

const checkBackendHealth = async () => {
  try {
    await apiClient.get('/status')
    systemStore.setBackendStatus('running')
  } catch {
    systemStore.setBackendStatus('stopped')
  }
}

onMounted(() => {
  checkBackendHealth()
  _healthTimer = setInterval(checkBackendHealth, 15_000)
  feedStore.connectWs()
})

onUnmounted(() => {
  if (_healthTimer !== null) {
    clearInterval(_healthTimer)
    _healthTimer = null
  }
  feedStore.disconnectWs()
})
</script>

<style scoped>
/* ── Root layout: sidebar (fixed-width) + scrollable main ── */
.vyra-app {
  display: flex;
  flex-direction: row;
  height: 100vh;
  overflow: hidden;
  background: var(--surface-ground, #f5f7fa);
}

/* ── Main area shifts right to make room for the sidebar ── */
.vyra-main {
  flex: 1;
  display: flex;
  flex-direction: column;
  min-width: 0;       /* prevent flex overflow */
  overflow: hidden;
}

/* ── Slim topbar ── */
.vyra-topbar {
  display: flex;
  align-items: center;
  padding: 0.75rem 2rem;
  border-bottom: 1px solid var(--surface-border, #e0e0e0);
  background: var(--surface-card, #fff);
  min-height: 52px;
  flex-shrink: 0;
}

.page-title {
  font-size: 1rem;
  font-weight: 600;
  color: var(--text-color, #212121);
}

/* ── Content ── */
.vyra-content {
  flex: 1;
  padding: 2rem;
  overflow: auto;
}


/* ── Responsive: on very small screens hide the sidebar space offset ── */
@media (max-width: 480px) {
  .vyra-app {
    flex-direction: column;
  }

  .vyra-main {
    padding-top: 52px; /* space for the floating toggle button */
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

/* ── Three-dot menu button ── */
.top-menu-btn {
  display: flex;
  align-items: center;
  justify-content: center;
  width: 36px;
  height: 36px;
  border: none;
  background: transparent;
  cursor: pointer;
  border-radius: 6px;
  color: var(--text-color-secondary, #607D8B);
  transition: background 0.15s;
}

.top-menu-btn:hover {
  background: var(--surface-hover, #f0f0f0);
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

/* ── Topbar actions (right side) ── */
.topbar-actions {
  margin-left: auto;
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

/* ── Alarm bell button ── */
.alarm-bell-btn {
  position: relative;
  display: flex;
  align-items: center;
  justify-content: center;
  width: 36px;
  height: 36px;
  border: none;
  background: transparent;
  cursor: pointer;
  border-radius: 6px;
  color: var(--text-color-secondary, #607D8B);
  transition: background 0.15s, color 0.15s;
}

.alarm-bell-btn:hover {
  background: var(--surface-hover, #f0f0f0);
}

.alarm-bell-btn--active {
  color: var(--red-500, #f44336);
}

.alarm-bell-icon {
  font-size: 1.25rem;
}

@keyframes bell-ring {
  0%   { transform: rotate(0deg); }
  10%  { transform: rotate(18deg); }
  20%  { transform: rotate(-16deg); }
  30%  { transform: rotate(14deg); }
  40%  { transform: rotate(-12deg); }
  50%  { transform: rotate(8deg); }
  60%  { transform: rotate(-6deg); }
  70%  { transform: rotate(4deg); }
  80%  { transform: rotate(-2deg); }
  100% { transform: rotate(0deg); }
}

.bell-ring {
  animation: bell-ring 1.2s ease infinite;
  transform-origin: top center;
}

.alarm-badge {
  position: absolute;
  top: 2px;
  right: 2px;
  min-width: 16px;
  height: 16px;
  padding: 0 3px;
  background: var(--red-500, #f44336);
  color: #fff;
  border-radius: 8px;
  font-size: 0.65rem;
  font-weight: 700;
  line-height: 16px;
  text-align: center;
  pointer-events: none;
}

/* ── Error feed dialog list ── */
.error-feed-list {
  max-height: 440px;
  overflow-y: auto;
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
}

.error-feed-item {
  padding: 0.75rem 1rem;
  background: var(--surface-ground, #f5f7fa);
  border-left: 3px solid var(--red-500, #f44336);
  border-radius: 4px;
}

.error-feed-header {
  display: flex;
  justify-content: space-between;
  margin-bottom: 0.35rem;
  gap: 1rem;
}

.error-feed-module {
  font-weight: 600;
  font-size: 0.85rem;
  color: var(--text-color, #212121);
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}

.error-feed-time {
  font-size: 0.75rem;
  color: var(--text-color-secondary, #607D8B);
  white-space: nowrap;
  flex-shrink: 0;
}

.error-feed-message {
  margin: 0;
  font-size: 0.85rem;
  color: var(--text-color, #212121);
  word-break: break-word;
}
</style>

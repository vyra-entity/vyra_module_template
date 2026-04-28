<template>
  <!-- Overlay backdrop for mobile drawer mode -->
  <Transition name="backdrop-fade">
    <div
      v-if="isMobileDrawerOpen"
      class="sidebar-backdrop"
      @click="closeMobileDrawer"
      aria-hidden="true"
    />
  </Transition>

  <!-- The sidebar itself -->
  <aside
    class="vyra-sidebar"
    :class="{
      'is-collapsed': sidebarStore.isCollapsed,
      'is-mobile-open': isMobileDrawerOpen,
      'is-mobile': isMobile,
    }"
    role="navigation"
    aria-label="Hauptnavigation"
  >
    <!-- ── TOP ZONE: Branding + Toggle ─────────────────────────────────────── -->
    <div class="sidebar-top">
      <div
        class="branding"
        :class="{ 'branding--clickable': sidebarStore.isCollapsed }"
        @click="sidebarStore.isCollapsed && handleToggle()"
      >
        <div class="brand-icon">
          <img src="@/assets/variobotic-kreis-transparent-blaugrau.svg" class="brand-svg" alt="VYRA" />
        </div>
        <span class="brand-label">{{ module_display_name }}</span>
      </div>

      <button
        v-if="!sidebarStore.isCollapsed"
        class="toggle-btn"
        @click="handleToggle"
        title="Sidebar einklappen"
        aria-label="Sidebar einklappen"
        aria-controls="sidebar-nav"
      >
        <i class="pi pi-bars" />
      </button>
    </div>

    <!-- ── MAIN NAVIGATION ZONE ────────────────────────────────────────────── -->
    <!-- Settings sub-nav: shown when inside /settings routes -->
    <nav v-if="isInSettings" class="sidebar-main" aria-label="Einstellungen">
      <button
        class="settings-back-btn"
        @click="goBack"
        title="Zurück zur Hauptnavigation"
        v-tooltip.right="sidebarStore.isCollapsed ? 'Zurück' : undefined"
      >
        <i class="pi pi-arrow-left" />
        <span class="btn-label">Zurück</span>
      </button>
      <div class="settings-nav-group">
        <RouterLink
          v-for="item in sidebarStore.settingsItems"
          :key="item.id"
          :to="{ name: item.routeName }"
          class="settings-nav-item"
          active-class="is-active"
          v-tooltip.right="sidebarStore.isCollapsed ? item.label : undefined"
        >
          <i :class="item.icon" />
          <span class="nav-item-label">{% raw %}{{ item.label }}{% endraw %}</span>
        </RouterLink>
      </div>
    </nav>
    <!-- Normal main nav: shown when NOT in settings -->
    <nav v-else id="sidebar-nav" class="sidebar-main" aria-label="Navigation">
      <SidebarNavGroup
        v-for="group in sidebarStore.groupedItems.filter(g => g.id !== 'system')"
        :key="group.id"
        :group="group"
      />
    </nav>

    <!-- ── BOTTOM ZONE: System Navigation + System Health + User + Settings ── -->
    <div class="sidebar-bottom">
      <!-- System navigation group (fixed at bottom) -->
      <SidebarNavGroup
        v-for="group in sidebarStore.groupedItems.filter(g => g.id === 'system')"
        :key="group.id"
        :group="group"
      />
      <!-- System health indicator -->
      <div
        class="system-health"
        :class="`health-${systemStore.backendStatus}`"
        v-tooltip.right="healthTooltip"
        :title="healthTooltip"
        aria-live="polite"
        :aria-label="`System Status: ${healthLabel}`"
      >
        <span class="health-dot" />
        <span class="health-label">{% raw %}{{ healthLabel }}{% endraw %}</span>
      </div>

      <!-- User panel (clickable → opens dropdown menu) -->
      <Menu ref="userMenu" :model="userMenuItems" popup appendTo="body" id="sidebar-user-menu" />
      <div
        v-if="authStore.isAuthenticated"
        class="user-info user-info--clickable"
        role="button"
        tabindex="0"
        @click="userMenu?.toggle($event)"
        @keydown.enter="userMenu?.toggle($event)"
        aria-label="Benutzermenü"
        v-tooltip.right="sidebarStore.isCollapsed ? authStore.username : undefined"
      >
        <i class="pi pi-user user-icon" />
        <span class="user-name">{% raw %}{{ authStore.username }}{% endraw %}</span>
        <Tag
          v-if="!sidebarStore.isCollapsed && authStore.authMode === 'local'"
          value="lokal"
          severity="warn"
          class="auth-mode-badge"
        />
        <i class="pi pi-ellipsis-v user-menu-icon" v-if="!sidebarStore.isCollapsed" />
      </div>
    </div>
  </aside>
</template>

<script setup lang="ts">
import { computed, onMounted, onUnmounted, ref, watch } from 'vue'
import { useRouter, useRoute } from 'vue-router'
import { useSidebarStore } from '../../store/sidebar'
import { useSystemStore } from '../../store/system'
import { useAuthStore } from '../../store/auth'
import { useToast } from 'primevue/usetoast'
import SidebarNavGroup from './SidebarNavGroup.vue'
import Menu from 'primevue/menu'
import Tag from 'primevue/tag'

const router       = useRouter()
const route        = useRoute()
const sidebarStore = useSidebarStore()
const systemStore  = useSystemStore()
const authStore    = useAuthStore()
const toast        = useToast()

// ─── Settings context detection ───────────────────────────────────────────────
const isInSettings = computed(() => route.path.includes('/settings'))

function goBack(): void {
  router.push('/{{ module_name }}/home')
}

// ─── Mobile detection ──────────────────────────────────────────────────────
const MOBILE_BREAKPOINT  = 768
const DRAWER_BREAKPOINT  = 768

const isMobile          = ref(false)
const isMobileDrawerOpen = ref(false)

function checkViewport(): void {
  const w = window.innerWidth
  isMobile.value = w <= MOBILE_BREAKPOINT
  if (w <= DRAWER_BREAKPOINT) {
    // Drawer mode – sidebar is hidden until opened via mobile toggle
    sidebarStore.setCollapsed(true)
  } else if (w <= MOBILE_BREAKPOINT) {
    sidebarStore.setCollapsed(true)
  }
}

function handleToggle(): void {
  if (window.innerWidth <= DRAWER_BREAKPOINT) {
    // Mobile overlay drawer
    isMobileDrawerOpen.value = !isMobileDrawerOpen.value
  } else {
    sidebarStore.toggleCollapse()
  }
}

function closeMobileDrawer(): void {
  isMobileDrawerOpen.value = false
}

onMounted(() => {
  checkViewport()
  window.addEventListener('resize', checkViewport)
})

onUnmounted(() => {
  window.removeEventListener('resize', checkViewport)
})

watch(
  () => route.fullPath,
  () => {
    isMobileDrawerOpen.value = false
  },
)

// ─── System health ─────────────────────────────────────────────────────────
const healthLabel = computed(() => {
  switch (systemStore.backendStatus) {
    case 'running':  return 'System aktiv'
    case 'stopped':  return 'System gestoppt'
    case 'checking': return 'Verbinde...'
    default:         return 'Unbekannt'
  }
})

const healthTooltip = computed(() =>
  sidebarStore.isCollapsed ? healthLabel.value : undefined
)
// ─── User dropdown menu ─────────────────────────────────────────────────────────
const userMenu = ref<InstanceType<typeof Menu>>()

const userMenuItems = [
  {
    label: 'Benutzerverwaltung',
    icon: 'pi pi-users',
    command: () => { window.location.href = '/v2_usermanager/' },
  },
  { separator: true },
  {
    label: 'Abmelden',
    icon: 'pi pi-sign-out',
    command: () => { void handleLogout() },
  },
]
// ─── Logout ────────────────────────────────────────────────────────────────
async function handleLogout(): Promise<void> {
  try {
    await authStore.logout()
    toast.add({
      severity: 'success',
      summary: 'Abgemeldet',
      detail: 'Sie wurden erfolgreich abgemeldet',
      life: 3000,
    })
    router.push('/{{ module_name }}/login')
  } catch {
    toast.add({
      severity: 'error',
      summary: 'Fehler',
      detail: 'Abmeldung fehlgeschlagen',
      life: 3000,
    })
  }
}
</script>

<style scoped>
/* ── CSS variables (inherit from global :root) ── */
.vyra-sidebar {
  --sb-width:           260px;
  --sb-collapsed-width: 64px;
  --sb-bg:              var(--surface-card, #fff);
  --sb-border:          var(--surface-border, #e0e0e0);
  --sb-transition:      0.25s ease;
}

/* ── Base layout ── */
.vyra-sidebar {
  position: sticky;
  top: 0;
  height: 100dvh;
  width: var(--sb-width);
  min-width: var(--sb-width);
  background: var(--sb-bg);
  border-right: 1px solid var(--sb-border);
  display: flex;
  flex-direction: column;
  overflow: hidden;
  transition: width var(--sb-transition), min-width var(--sb-transition);
  z-index: 100;
}

.vyra-sidebar.is-collapsed {
  width: var(--sb-collapsed-width);
  min-width: var(--sb-collapsed-width);
}

/* ── TOP ZONE ── */
.sidebar-top {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 1rem 0.75rem 0.75rem;
  border-bottom: 1px solid var(--sb-border);
  min-height: 60px;
  gap: 0.5rem;
  flex-shrink: 0;
}

.branding {
  display: flex;
  align-items: center;
  gap: 0.6rem;
  overflow: hidden;
  flex: 1;
  min-width: 0;
}

.brand-icon {
  display: flex;
  align-items: center;
  justify-content: center;
  width: 32px;
  height: 32px;
  border-radius: 8px;
  background: transparent;
  flex-shrink: 0;
}

.brand-svg {
  width: 28px;
  height: 28px;
  display: block;
}

.brand-label {
  font-weight: 700;
  font-size: 0.95rem;
  white-space: nowrap;
  overflow: hidden;
  opacity: 1;
  max-width: 160px;
  transition: opacity var(--sb-transition), max-width var(--sb-transition);
}

.is-collapsed .brand-label {
  opacity: 0;
  max-width: 0;
  pointer-events: none;
}

/* In collapsed state: keep branding visible (icon only), center it */
.is-collapsed .branding {
  cursor: default;
  flex: 1;
}

.is-collapsed .sidebar-top {
  justify-content: center;
}

.toggle-btn {
  display: flex;
  align-items: center;
  justify-content: center;
  width: 28px;
  height: 28px;
  border: none;
  border-radius: 6px;
  background: transparent;
  color: var(--text-color-secondary, #607D8B);
  cursor: pointer;
  flex-shrink: 0;
  transition: background 0.15s ease, color 0.15s ease;
  padding: 0;
}

.toggle-btn:hover {
  background: var(--surface-hover, rgba(33, 150, 243, 0.08));
  color: var(--vyra-primary, #2196F3);
}

.branding--clickable {
  cursor: pointer;
}

.branding--clickable:hover {
  opacity: 0.8;
}

/* ── MAIN NAV ZONE ── */
.sidebar-main {
  flex: 1;
  overflow-y: auto;
  overflow-x: hidden;
  padding: 0.75rem 0;
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  scrollbar-width: thin;
  scrollbar-color: var(--sb-border) transparent;
}

.sidebar-main::-webkit-scrollbar {
  width: 4px;
}

.sidebar-main::-webkit-scrollbar-thumb {
  background: var(--sb-border);
  border-radius: 2px;
}

/* ── BOTTOM ZONE ── */
.sidebar-bottom {
  display: flex;
  flex-direction: column;
  gap: 2px;
  padding: 0.5rem 0.5rem 0.75rem;
  border-top: 1px solid var(--sb-border);
  flex-shrink: 0;
}

/* System health */
.system-health {
  display: flex;
  align-items: center;
  gap: 0.6rem;
  padding: 0.5rem 0.75rem;
  border-radius: 8px;
  overflow: hidden;
  transition: background 0.15s ease;
}

.health-dot {
  width: 8px;
  height: 8px;
  border-radius: 50%;
  flex-shrink: 0;
  background: var(--vyra-secondary, #607D8B);
  transition: background 0.3s ease;
}

.health-running  .health-dot { background: var(--vyra-success, #4CAF50); }
.health-stopped  .health-dot { background: var(--vyra-danger,  #F44336); }
.health-checking .health-dot {
  background: var(--vyra-warning, #FF9800);
  animation: pulse-dot 1.2s ease-in-out infinite;
}

@keyframes pulse-dot {
  0%, 100% { opacity: 1; }
  50%       { opacity: 0.3; }
}

.health-label {
  font-size: 0.75rem;
  color: var(--text-color-secondary, #607D8B);
  white-space: nowrap;
  overflow: hidden;
  opacity: 1;
  max-width: 160px;
  transition: opacity var(--sb-transition), max-width var(--sb-transition);
}

.is-collapsed .health-label {
  opacity: 0;
  max-width: 0;
  pointer-events: none;
}

/* User info */
.user-info {
  display: flex;
  align-items: center;
  gap: 0.6rem;
  padding: 0.4rem 0.75rem;
  overflow: hidden;
}

.user-icon {
  font-size: 0.9rem;
  color: var(--text-color-secondary, #607D8B);
  flex-shrink: 0;
  width: 22px;
  text-align: center;
}

.user-name {
  font-size: 0.75rem;
  color: var(--text-color-secondary, #607D8B);
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
  opacity: 1;
  max-width: 160px;
  transition: opacity var(--sb-transition), max-width var(--sb-transition);
}

.is-collapsed .user-name {
  opacity: 0;
  max-width: 0;
  pointer-events: none;
}

.user-info--clickable {
  cursor: pointer;
  border-radius: 8px;
  transition: background var(--sb-transition);
}

.user-info--clickable:hover {
  background: var(--surface-hover, rgba(0, 0, 0, 0.05));
}

.user-menu-icon {
  font-size: 0.8rem;
  color: var(--text-color-secondary, #607D8B);
  flex-shrink: 0;
  margin-left: auto;
}

.auth-mode-badge {
  font-size: 0.6rem;
  padding: 0.1rem 0.3rem;
  flex-shrink: 0;
}

/* Bottom buttons */
.bottom-btn {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  padding: 0.55rem 0.75rem;
  border-radius: 8px;
  border: none;
  background: transparent;
  color: var(--text-color-secondary, #607D8B);
  cursor: pointer;
  font-size: 0.875rem;
  text-align: left;
  min-height: 48px;
  overflow: hidden;
  transition: background 0.15s ease, color 0.15s ease;
  width: 100%;
}

.bottom-btn:hover {
  background: var(--surface-hover, rgba(244, 67, 54, 0.06));
  color: var(--vyra-danger, #F44336);
}

.bottom-btn .pi {
  font-size: 1rem;
  flex-shrink: 0;
  width: 22px;
  text-align: center;
}

.btn-label {
  white-space: nowrap;
  overflow: hidden;
  opacity: 1;
  max-width: 160px;
  transition: opacity var(--sb-transition), max-width var(--sb-transition);
}

.is-collapsed .btn-label {
  opacity: 0;
  max-width: 0;
  pointer-events: none;
}

/* ── Mobile backdrop ── */
.sidebar-backdrop {
  position: fixed;
  inset: 0;
  background: rgba(0, 0, 0, 0.45);
  z-index: 999;
}

.backdrop-fade-enter-active,
.backdrop-fade-leave-active {
  transition: opacity 0.25s ease;
}
.backdrop-fade-enter-from,
.backdrop-fade-leave-to {
  opacity: 0;
}

/* ── Responsive: mobile drawer ── */
@media (max-width: 768px) {
  .vyra-sidebar {
    position: fixed;
    left: 0;
    top: 0;
    z-index: 1000;
    transform: translateX(calc(-1 * var(--sb-width)));
    transition:
      transform var(--sb-transition),
      width var(--sb-transition),
      min-width var(--sb-transition);
    box-shadow: none;
  }

  .vyra-sidebar.is-mobile-open {
    transform: translateX(0);
    box-shadow: 4px 0 24px rgba(0, 0, 0, 0.15);
    width: var(--sb-width) !important;
    min-width: var(--sb-width) !important;
  }

  /* Show always-visible hamburger strip on mobile */
  .vyra-sidebar .toggle-btn {
    position: fixed;
    top: 12px;
    left: 12px;
    z-index: 101;
    background: var(--sb-bg);
    border-color: var(--sb-border);
    width: 36px;
    height: 36px;
    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.12);
  }
}

/* ── Settings context navigation ────────────────────────────────────────────── */
.settings-back-btn {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  padding: 0.55rem 0.75rem;
  border-radius: 8px;
  border: none;
  background: transparent;
  color: var(--text-color-secondary, #607D8B);
  cursor: pointer;
  font-size: 0.875rem;
  text-align: left;
  min-height: 48px;
  overflow: hidden;
  width: 100%;
  transition: background 0.15s ease, color 0.15s ease;
  margin-bottom: 0.5rem;
}

.settings-back-btn:hover {
  background: var(--surface-hover);
  color: var(--primary-color);
}

.settings-back-btn .btn-label {
  white-space: nowrap;
  overflow: hidden;
  opacity: 1;
  max-width: 160px;
  transition: opacity var(--sb-transition, 0.2s ease), max-width var(--sb-transition, 0.2s ease);
}

.is-collapsed .settings-back-btn .btn-label {
  opacity: 0;
  max-width: 0;
  pointer-events: none;
}

.settings-nav-group {
  display: flex;
  flex-direction: column;
  gap: 2px;
  padding: 0.25rem 0;
}

.settings-nav-item {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  padding: 0.55rem 0.75rem;
  border-radius: 8px;
  color: var(--text-color-secondary, #607D8B);
  cursor: pointer;
  font-size: 0.875rem;
  text-decoration: none;
  min-height: 48px;
  overflow: hidden;
  transition: background 0.15s ease, color 0.15s ease;
}

.settings-nav-item:hover {
  background: var(--surface-hover);
  color: var(--primary-color);
}

.settings-nav-item.is-active {
  background: var(--surface-hover);
  color: var(--primary-color);
  font-weight: 600;
}

.settings-nav-item .pi {
  font-size: 1rem;
  flex-shrink: 0;
  width: 22px;
  text-align: center;
}

.settings-nav-item .nav-item-label {
  white-space: nowrap;
  overflow: hidden;
  opacity: 1;
  max-width: 160px;
  transition: opacity var(--sb-transition, 0.2s ease), max-width var(--sb-transition, 0.2s ease);
}

.is-collapsed .settings-nav-item .nav-item-label {
  opacity: 0;
  max-width: 0;
  pointer-events: none;
}
</style>

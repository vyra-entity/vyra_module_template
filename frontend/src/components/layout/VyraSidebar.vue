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

  <!-- The sidebar -->
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
    <!-- ── TOP ZONE: Branding + Toggle ──────────────────────────────────── -->
    <div class="sidebar-top">
      <!-- Slot: custom branding (icon + title by default) -->
      <slot name="brand">
        <div class="branding">
          <div class="brand-icon">
            <img src="@/assets/variobotic-kreis-transparent-blaugrau.svg" class="brand-svg" alt="VYRA" />
          </div>
          <span class="brand-label">{{ title }}</span>
        </div>
      </slot>

      <button
        class="toggle-btn"
        @click="handleToggle"
        :title="sidebarStore.isCollapsed ? 'Ausklappen' : 'Einklappen'"
        :aria-label="sidebarStore.isCollapsed ? 'Sidebar ausklappen' : 'Sidebar einklappen'"
      >
        <i
          class="pi"
          :class="sidebarStore.isCollapsed ? 'pi-chevron-right' : 'pi-chevron-left'"
        />
      </button>
    </div>

    <!-- ── MAIN NAVIGATION ZONE ─────────────────────────────────────────── -->
    <nav class="sidebar-main" aria-label="Navigation">
      <SidebarNavGroup
        v-for="group in sidebarStore.groupedItems"
        :key="group.id"
        :group="group"
      />
    </nav>

    <!-- ── BOTTOM ZONE: slot for health indicators, user info, etc. ─────── -->
    <div class="sidebar-bottom">
      <!-- Slot: override bottom section entirely -->
      <slot name="bottom">
        <!-- Default: minimal status dot using the backendStatus prop -->
        <div
          v-if="backendStatus"
          class="system-health"
          :class="`health-${backendStatus}`"
          :title="healthLabel"
        >
          <span class="health-dot" />
          <span class="health-label">{{ healthLabel }}</span>
        </div>
      </slot>
    </div>
  </aside>
</template>

<script setup>
import { ref, computed, onMounted, onUnmounted } from 'vue'
import { useSidebarStore } from '../../store/sidebar'
import SidebarNavGroup from './SidebarNavGroup.vue'

const props = defineProps({
  /** Module title shown in the branding area */
  title: {
    type: String,
    default: 'VYRA Module'
  },
  /**
   * System / backend status: 'running' | 'stopped' | 'checking' | null
   * Pass null to hide the health indicator entirely.
   */
  backendStatus: {
    type: String,
    default: null
  }
})

const sidebarStore = useSidebarStore()

// ─── Mobile detection ────────────────────────────────────────────────────────
const isMobile          = ref(false)
const isMobileDrawerOpen = ref(false)

function checkViewport() {
  const w = window.innerWidth
  isMobile.value = w <= 768
  if (w <= 480) sidebarStore.setCollapsed(true)
  else if (w <= 768) sidebarStore.setCollapsed(true)
}

function handleToggle() {
  if (window.innerWidth <= 480) {
    isMobileDrawerOpen.value = !isMobileDrawerOpen.value
  } else {
    sidebarStore.toggleCollapse()
  }
}

function closeMobileDrawer() {
  isMobileDrawerOpen.value = false
}

onMounted(() => {
  checkViewport()
  window.addEventListener('resize', checkViewport)
})

onUnmounted(() => {
  window.removeEventListener('resize', checkViewport)
})

// ─── Health label ─────────────────────────────────────────────────────────────
const healthLabel = computed(() => {
  switch (props.backendStatus) {
    case 'running':  return 'System aktiv'
    case 'stopped':  return 'System gestoppt'
    case 'checking': return 'Verbinde...'
    default:         return 'Status unbekannt'
  }
})
</script>

<style scoped>
.vyra-sidebar {
  --sb-width:           260px;
  --sb-collapsed-width: 64px;
  --sb-bg:              #fff;
  --sb-border:          #e0e0e0;
  --sb-primary:         #2196F3;
  --sb-transition:      0.25s ease;
}

/* ── Base layout ── */
.vyra-sidebar {
  position: sticky;
  top: 0;
  height: 100vh;
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

/* In collapsed state: hide branding entirely, center toggle button */
.is-collapsed .branding {
  opacity: 0;
  flex: 0;
  min-width: 0;
  overflow: hidden;
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
  border: 1px solid var(--sb-border);
  border-radius: 6px;
  background: transparent;
  color: #607D8B;
  cursor: pointer;
  flex-shrink: 0;
  transition: background 0.15s ease, color 0.15s ease;
  padding: 0;
}

.toggle-btn:hover {
  background: rgba(33, 150, 243, 0.08);
  color: #2196F3;
}

/* ── MAIN NAV ── */
.sidebar-main {
  flex: 1;
  overflow-y: auto;
  overflow-x: hidden;
  padding: 0.75rem 0;
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  scrollbar-width: thin;
  scrollbar-color: #e0e0e0 transparent;
}

.sidebar-main::-webkit-scrollbar      { width: 4px; }
.sidebar-main::-webkit-scrollbar-thumb {
  background: #e0e0e0;
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
}

.health-dot {
  width: 8px;
  height: 8px;
  border-radius: 50%;
  flex-shrink: 0;
  background: #607D8B;
  transition: background 0.3s ease;
}

.health-running  .health-dot { background: #4CAF50; }
.health-stopped  .health-dot { background: #F44336; }
.health-checking .health-dot {
  background: #FF9800;
  animation: pulse-dot 1.2s ease-in-out infinite;
}

@keyframes pulse-dot {
  0%, 100% { opacity: 1; }
  50%       { opacity: 0.3; }
}

.health-label {
  font-size: 0.75rem;
  color: #607D8B;
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

/* ── Mobile backdrop ── */
.sidebar-backdrop {
  position: fixed;
  inset: 0;
  background: rgba(0, 0, 0, 0.45);
  z-index: 99;
}

.backdrop-fade-enter-active,
.backdrop-fade-leave-active { transition: opacity 0.25s ease; }
.backdrop-fade-enter-from,
.backdrop-fade-leave-to      { opacity: 0; }

/* ── Mobile drawer ── */
@media (max-width: 480px) {
  .vyra-sidebar {
    position: fixed;
    left: 0;
    top: 0;
    transform: translateX(calc(-1 * var(--sb-width)));
    transition: transform var(--sb-transition), width var(--sb-transition), min-width var(--sb-transition);
  }

  .vyra-sidebar.is-mobile-open {
    transform: translateX(0);
    box-shadow: 4px 0 24px rgba(0, 0, 0, 0.15);
    width: var(--sb-width) !important;
    min-width: var(--sb-width) !important;
  }

  .vyra-sidebar .toggle-btn {
    position: fixed;
    top: 12px;
    left: 12px;
    z-index: 101;
    background: #fff;
    width: 36px;
    height: 36px;
    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.12);
  }
}
</style>

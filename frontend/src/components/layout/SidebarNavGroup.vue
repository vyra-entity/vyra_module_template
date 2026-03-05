<template>
  <div class="sidebar-group">
    <!-- Group label: only visible when expanded -->
    <div
      class="group-header"
      :class="{ hidden: sidebarStore.isCollapsed }"
      aria-hidden="true"
    >
      <span class="group-label">{{ group.label }}</span>
    </div>

    <!-- Divider (always shown, acts as separator in collapsed mode) -->
    <div class="group-divider" :class="{ 'divider-only': sidebarStore.isCollapsed }" />

    <!-- Navigation items -->
    <ul class="group-items" role="menu">
      <SidebarNavItem
        v-for="item in group.items"
        :key="item.id"
        :item="item"
      />
    </ul>
  </div>
</template>

<script setup>
import { useSidebarStore } from '../../store/sidebar'
import SidebarNavItem from './SidebarNavItem.vue'

defineProps({
  group: {
    type: Object,
    required: true
  }
})

const sidebarStore = useSidebarStore()
</script>

<style scoped>
.sidebar-group {
  display: flex;
  flex-direction: column;
}

.group-header {
  padding: 0.4rem 1rem 0.2rem;
  overflow: hidden;
  transition: max-height 0.25s ease, opacity 0.2s ease;
  max-height: 40px;
}

.group-header.hidden {
  max-height: 0;
  opacity: 0;
  padding: 0;
  pointer-events: none;
}

.group-label {
  font-size: 0.65rem;
  font-weight: 700;
  letter-spacing: 0.08em;
  text-transform: uppercase;
  color: #9E9E9E;
  white-space: nowrap;
}

.group-divider {
  height: 1px;
  margin: 0 0.75rem 0.4rem;
  background: #e0e0e0;
  opacity: 0.6;
  transition: margin 0.25s ease;
}

.group-divider.divider-only {
  margin: 0.4rem 0.5rem;
}

.group-items {
  display: flex;
  flex-direction: column;
  gap: 2px;
  padding: 0 0.5rem;
  margin: 0;
}
</style>

<template>
  <li
    class="sidebar-nav-item"
    :class="{ active: isActive, collapsed: sidebarStore.isCollapsed }"
    :title="sidebarStore.isCollapsed ? tooltipText : undefined"
    @click="handleClick"
    role="menuitem"
    :aria-label="item.label"
    :aria-current="isActive ? 'page' : undefined"
  >
    <!-- Active indicator bar -->
    <span class="active-bar" />

    <!-- Icon wrapper with badge -->
    <span class="icon-wrap">
      <i :class="item.icon" class="nav-icon" />
      <span v-if="badgeCount > 0" class="nav-badge">
        {{ badgeCount > 99 ? '99+' : badgeCount }}
      </span>
    </span>

    <!-- Label (hidden via CSS when collapsed) -->
    <span class="nav-label">{{ item.label }}</span>
  </li>
</template>

<script setup>
import { computed } from 'vue'
import { useRoute, useRouter } from 'vue-router'
import { useSidebarStore } from '../../store/sidebar'

const props = defineProps({
  item: {
    type: Object,
    required: true
  }
})

const router       = useRouter()
const route        = useRoute()
const sidebarStore = useSidebarStore()

const isActive    = computed(() => route.name === props.item.routeName)
const tooltipText = computed(() => props.item.tooltip ?? props.item.label)
const badgeCount  = computed(() => props.item.badge ?? 0)

function handleClick() {
  router.push({ name: props.item.routeName })
}
</script>

<style scoped>
.sidebar-nav-item {
  position: relative;
  display: flex;
  align-items: center;
  gap: 0.75rem;
  padding: 0.65rem 1rem;
  border-radius: 8px;
  cursor: pointer;
  list-style: none;
  color: #607D8B;
  transition: background-color 0.18s ease, color 0.18s ease;
  user-select: none;
  min-height: 42px;
  overflow: hidden;
}

.sidebar-nav-item:hover {
  background-color: rgba(33, 150, 243, 0.06);
  color: #212121;
}

/* Active state */
.active-bar {
  position: absolute;
  left: 0;
  top: 50%;
  transform: translateY(-50%);
  width: 3px;
  height: 60%;
  border-radius: 0 3px 3px 0;
  background-color: transparent;
  transition: background-color 0.18s ease;
}

.sidebar-nav-item.active {
  background-color: rgba(33, 150, 243, 0.1);
  color: #2196F3;
  font-weight: 600;
}

.sidebar-nav-item.active .active-bar {
  background-color: #2196F3;
}

/* Icon */
.icon-wrap {
  position: relative;
  display: flex;
  align-items: center;
  justify-content: center;
  flex-shrink: 0;
  width: 22px;
  height: 22px;
}

.nav-icon {
  font-size: 1.1rem;
  line-height: 1;
}

/* Badge */
.nav-badge {
  position: absolute;
  top: -6px;
  right: -8px;
  min-width: 16px;
  height: 16px;
  padding: 0 3px;
  border-radius: 8px;
  background: #F44336;
  color: #fff;
  font-size: 0.6rem;
  font-weight: 700;
  line-height: 16px;
  text-align: center;
  pointer-events: none;
}

/* Label (collapses via CSS) */
.nav-label {
  flex: 1;
  white-space: nowrap;
  overflow: hidden;
  font-size: 0.875rem;
  opacity: 1;
  max-width: 180px;
  transition: opacity 0.2s ease, max-width 0.25s ease;
}

.sidebar-nav-item.collapsed .nav-label {
  opacity: 0;
  max-width: 0;
  pointer-events: none;
}
</style>

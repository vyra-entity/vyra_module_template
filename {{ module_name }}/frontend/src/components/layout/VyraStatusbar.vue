<template>
  <!-- Bottom status bar — renders statusbar.actionbar plugin slots -->
  <footer v-if="authStore.isAuthenticated" class="vyra-statusbar">
    <PluginSlot slot-id="statusbar.actionbar" />
    <div class="statusbar-right">
      <span class="statusbar-copyright">VYRA Industrial Automation © 2025</span>
      <slot />
    </div>
  </footer>
</template>

<script setup lang="ts">
import { useAuthStore } from '../../store/auth'
import PluginSlot from '../PluginSlot.vue'

const authStore = useAuthStore()
</script>

<style scoped>
.vyra-statusbar {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  padding: 0.25rem 1rem calc(0.25rem + var(--safe-area-bottom, 0px));
  min-height: 28px;
  background: var(--surface-ground, #f5f7fa);
  border-top: 1px solid var(--surface-border, #e0e0e0);
  flex-shrink: 0;
  font-size: 0.75rem;
  color: var(--text-color-secondary, #666);
}

.statusbar-right {
  margin-left: auto;
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

@media (max-width: 480px) {
  .statusbar-copyright {
    display: none;
  }
}
</style>

<template>
  <div class="settings-view">
    <div class="flex align-items-center gap-2 mb-4">
      <i class="pi pi-cog text-2xl text-primary" />
      <div>
        <h2 class="m-0">Einstellungen</h2>
        <p class="text-sm text-color-secondary m-0">Globale Anwendungseinstellungen</p>
      </div>
    </div>

    <div class="grid">
      <!-- Side-Dock Widgets -->
      <div class="col-12 md:col-6">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-th-large"></i>
              <span>Side-Dock Widgets</span>
            </div>
          </template>
          <template #content>
            <div class="flex align-items-center justify-content-between gap-3">
              <div>
                <p class="m-0 font-semibold">Show floating widget tabs</p>
                <p class="m-0 text-sm text-color-secondary mt-1">
                  Plugin widgets appear as floating icon tabs on the right edge.
                </p>
              </div>
              <InputSwitch v-model="uiSettingsStore.sideDockPocketEnabled" />
            </div>
          </template>
        </Card>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import Card from 'primevue/card'
import InputSwitch from 'primevue/inputswitch'
import { useUiSettingsStore } from '../../store/uiSettings'

const uiSettingsStore = useUiSettingsStore()
</script>

<style scoped>
.settings-view {
  animation: fadeIn 0.3s ease;
}

@keyframes fadeIn {
  from { opacity: 0; transform: translateY(8px); }
  to   { opacity: 1; transform: translateY(0); }
}
</style>

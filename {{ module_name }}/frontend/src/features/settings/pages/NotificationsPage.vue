<template>
  <div class="settings-page">
    <div class="page-header">
      <i class="pi pi-bell text-primary" />
      <div>
        <h2 class="m-0">Benachrichtigungen</h2>
        <p class="text-sm text-color-secondary m-0">Benachrichtigungseinstellungen</p>
      </div>
    </div>

    <div class="grid">
      <div class="col-12 lg:col-6">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-bell"></i>
              <span>Benachrichtigungen</span>
            </div>
          </template>
          <template #content>
            <div class="flex align-items-center justify-content-between">
              <div>
                <p class="m-0 font-semibold">Benachrichtigungen aktivieren</p>
                <p class="m-0 text-sm text-color-secondary mt-1">
                  System- und Statusbenachrichtigungen anzeigen.
                </p>
              </div>
              <InputSwitch
                v-model="settingsStore.settings.notifications"
                @change="settingsStore.updateSettings({ notifications: settingsStore.settings.notifications })"
              />
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
import { useSettingsStore } from '../../../store/settings'

const settingsStore = useSettingsStore()
</script>

<style scoped>
.settings-page {
  padding: 2rem;
}

.page-header {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  margin-bottom: 2rem;
}

.page-header i {
  font-size: 1.5rem;
}
</style>

<template>
  <div class="settings-page">
    <div class="page-header">
      <i class="pi pi-sliders-h text-primary" />
      <div>
        <h2 class="m-0">Allgemein</h2>
        <p class="text-sm text-color-secondary m-0">Kontoinformationen und allgemeine Optionen</p>
      </div>
    </div>

    <div class="grid">
      <!-- Account Info -->
      <div class="col-12 md:col-6">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-user"></i>
              <span>Kontoinformationen</span>
            </div>
          </template>
          <template #content>
            <div class="flex flex-column gap-3">
              <div>
                <label class="block mb-1 font-semibold text-sm">Benutzername</label>
                <span>{% raw %}{{ authStore.username }}{% endraw %}</span>
              </div>
              <div>
                <label class="block mb-1 font-semibold text-sm">Rollen</label>
                <div class="flex gap-1 flex-wrap">
                  <Tag
                    v-for="role in authStore.roles"
                    :key="role"
                    :value="role"
                    :severity="role === 'Admin' ? 'danger' : role === 'Manager' ? 'warning' : 'info'"
                    size="small"
                  />
                </div>
              </div>
            </div>
          </template>
        </Card>
      </div>

      <!-- Side-Dock -->
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
                <p class="m-0 font-semibold">Schwebende Widget-Tabs anzeigen</p>
                <p class="m-0 text-sm text-color-secondary mt-1">
                  Plugin-Widgets erscheinen als schwebende Tabs am rechten Rand.
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
import Tag from 'primevue/tag'
import InputSwitch from 'primevue/inputswitch'
import { useAuthStore } from '../../../store/auth'
import { useUiSettingsStore } from '../../../store/uiSettings'

const authStore = useAuthStore()
const uiSettingsStore = useUiSettingsStore()
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

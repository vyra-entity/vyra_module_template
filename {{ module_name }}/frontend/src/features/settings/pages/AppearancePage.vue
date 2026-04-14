<template>
  <div class="settings-page">
    <div class="page-header">
      <i class="pi pi-palette text-primary" />
      <div>
        <h2 class="m-0">Darstellung</h2>
        <p class="text-sm text-color-secondary m-0">Theme, Sprache und Anzeigeoptionen</p>
      </div>
    </div>

    <div class="grid">
      <div class="col-12 lg:col-6">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-palette"></i>
              <span>Theme</span>
            </div>
          </template>
          <template #content>
            <SelectButton
              v-model="settingsStore.settings.theme"
              :options="themeOptions"
              option-label="label"
              option-value="value"
              @change="settingsStore.setTheme($event.value)"
            />
          </template>
        </Card>
      </div>

      <div class="col-12 lg:col-6">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-globe"></i>
              <span>Sprache</span>
            </div>
          </template>
          <template #content>
            <Dropdown
              v-model="settingsStore.settings.language"
              :options="languageOptions"
              option-label="label"
              option-value="value"
              @change="settingsStore.setLanguage($event.value)"
              class="w-full"
            />
          </template>
        </Card>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'
import Card from 'primevue/card'
import SelectButton from 'primevue/selectbutton'
import Dropdown from 'primevue/dropdown'
import { useSettingsStore } from '../../../store/settings'

const settingsStore = useSettingsStore()

const themeOptions = ref([
  { label: 'Hell', value: 'light' },
  { label: 'Dunkel', value: 'dark' },
  { label: 'Auto', value: 'auto' },
])

const languageOptions = ref([
  { label: 'Deutsch', value: 'de' },
  { label: 'English', value: 'en' },
])
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

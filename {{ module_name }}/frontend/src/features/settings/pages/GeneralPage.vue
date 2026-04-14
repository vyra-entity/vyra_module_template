<template>
  <div class="settings-page">
    <div class="page-header">
      <i class="pi pi-cog text-primary" />
      <div>
        <h2 class="m-0">GeneralPage</h2>
        <p class="text-sm text-color-secondary m-0">Einstellungen</p>
      </div>
    </div>
    <div class="grid">
      <div class="col-12 md:col-6">
        <Card>
          <template #content>
            <p class="text-color-secondary m-0">Hier werden zukünftig die Einstellungen für diesen Bereich angezeigt.</p>
          </template>
        </Card>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import Card from 'primevue/card'
</script>

<style scoped>
.settings-page { padding: 2rem; }
.page-header { display: flex; align-items: center; gap: 0.75rem; margin-bottom: 2rem; }
.page-header i { font-size: 1.5rem; }
</style>

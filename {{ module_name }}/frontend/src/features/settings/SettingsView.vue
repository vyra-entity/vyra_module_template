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
      <!-- Placeholder: future settings cards go here -->
      <div class="col-12">
        <Card>
          <template #content>
            <div class="text-center py-5 text-color-secondary">
              <i class="pi pi-cog mb-3" style="font-size: 3rem; display: block; opacity: 0.3" />
              <p class="m-0">Einstellungen werden in einer späteren Version verfügbar sein.</p>
            </div>
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
.settings-view {
  animation: fadeIn 0.3s ease;
}

@keyframes fadeIn {
  from { opacity: 0; transform: translateY(8px); }
  to   { opacity: 1; transform: translateY(0); }
}
</style>

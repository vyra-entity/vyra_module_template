<template>
  <div class="home-view">
    <!-- Hero Section -->
    <!-- <Card class="hero-card mb-4">
      <template #content>
        <div class="text-center py-5">
          <i class="pi pi-cog" style="font-size: 4rem; color: var(--primary-color)"></i>
          <h1 class="mt-3 mb-2" style="font-size: 2.5rem">VYRA Module Manager</h1>
          <p class="text-600 text-xl">Zentrale Verwaltung aller VYRA Module und Repositories</p>
        </div>
      </template>
    </Card> -->

    <!-- Summary tiles -->
    <div class="summary-grid mb-4">
      <!-- YOUR CODE HERE -->
    </div>
  </div>
</template>

<script setup lang="ts">

import { onMounted } from 'vue'

onMounted(async () => {
  try {
    // Error feeds are reactive — sync once after load
  } catch (e) { console.error('Failed to update error feeds count:', e) }
})
</script>

<style scoped>
.home-view {
  animation: fadeIn 0.3s ease-in;
}

@keyframes fadeIn {
  from { opacity: 0; transform: translateY(20px); }
  to { opacity: 1; transform: translateY(0); }
}

.hero-card {
  background: linear-gradient(135deg, var(--primary-color) 0%, var(--primary-600) 100%);
  color: white;
}

.hero-card :deep(.p-card-content) {
  padding: 2rem;
}

.quick-action-card {
  transition: all 0.2s;
  height: 100%;
}

.quick-action-card:hover {
  transform: translateY(-4px);
  box-shadow: 0 8px 16px rgba(0,0,0,0.1);
}

/* ── Summary tiles ──────────────────────────────────────────────────── */
.summary-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(220px, 1fr));
  gap: 1rem;
}

.summary-tile {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  padding: 1.25rem;
  border-radius: 0.875rem;
  background: var(--p-surface-card, #fff);
  border: 1px solid var(--p-surface-border, #e5e7eb);
  transition: box-shadow 0.15s, transform 0.15s;
}
.summary-tile:hover {
  box-shadow: 0 6px 20px rgba(0,0,0,.09);
  transform: translateY(-3px);
}

.summary-tile--blue  { border-top: 3px solid var(--p-blue-400, #60a5fa); }
.summary-tile--purple { border-top: 3px solid var(--p-purple-400, #a78bfa); }
.summary-tile--green  { border-top: 3px solid var(--p-green-400, #4ade80); }
.summary-tile--red    { border-top: 3px solid var(--p-red-400, #f87171); }
.summary-tile--neutral { border-top: 3px solid var(--p-surface-400, #9ca3af); }

.summary-tile__icon {
  width: 3rem;
  height: 3rem;
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: 50%;
  margin-bottom: 0.25rem;
}
.summary-tile__content { flex: 1; }
.summary-tile__title   { font-size: 0.85rem; color: var(--p-text-secondary-color, #6b7280); font-weight: 500; }
.summary-tile__number  { font-size: 2.25rem; font-weight: 700; color: var(--p-text-color, #111); line-height: 1; margin: 0.25rem 0; }
.summary-tile__detail  { display: flex; align-items: center; font-size: 0.8rem; }
.summary-tile__sub     { margin-top: auto; }
</style>

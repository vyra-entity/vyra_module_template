<template>
  <div class="plugin-page">
    <div v-if="!component" class="plugin-page-not-found">
      <i class="pi pi-exclamation-circle plugin-page-icon" />
      <h2>Plugin page not found</h2>
      <p>No route-injection plugin is registered for <code>/p/{{ pluginSlug }}</code>.</p>
    </div>
    <component v-else :is="component" />
  </div>
</template>

<script setup lang="ts">
import { computed, defineAsyncComponent } from 'vue'
import { useRoute } from 'vue-router'
import { usePluginStore } from '../../store/plugins'

const route = useRoute()
const pluginStore = usePluginStore()

const pluginSlug = computed(() => String(route.params.pluginSlug ?? ''))

/**
 * Find the first active route-injection plugin whose slug matches the route
 * parameter. The slug is derived from the plugin_id (or component_name) by
 * lower-casing and replacing non-alphanumeric characters with hyphens.
 */
const component = computed(() => {
  const slug = pluginSlug.value
  if (!slug) return null

  const entries = pluginStore.getSlotComponents('route-injection')
  const match = entries.find(({ entry }) => {
    const entrySlug = entry.plugin_id
      .toLowerCase()
      .replace(/[^a-z0-9]+/g, '-')
      .replace(/^-|-$/g, '')
    return entrySlug === slug || entry.plugin_id === slug
  })
  return match?.component ?? null
})
</script>

<style scoped>
.plugin-page {
  width: 100%;
  height: 100%;
}

.plugin-page-not-found {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  padding: 4rem 2rem;
  text-align: center;
  color: var(--text-color-secondary, #666);
}

.plugin-page-icon {
  font-size: 3rem;
  margin-bottom: 1rem;
  color: var(--yellow-500, #f59e0b);
}

.plugin-page-not-found h2 {
  margin: 0 0 0.5rem;
  font-size: 1.25rem;
  color: var(--text-color, #212121);
}

.plugin-page-not-found p {
  margin: 0;
  font-size: 0.9rem;
}

.plugin-page-not-found code {
  background: var(--surface-ground, #f5f7fa);
  padding: 0.1rem 0.4rem;
  border-radius: 4px;
  font-family: monospace;
}
</style>

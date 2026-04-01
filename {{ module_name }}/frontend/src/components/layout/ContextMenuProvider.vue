<template>
  <!-- Aggregates context-menu plugin items via PluginSlot -->
  <ContextMenu ref="ctxMenuRef" :model="contextMenuItems" />
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'
import ContextMenu from 'primevue/contextmenu'
import { usePluginStore } from '../../store/plugins'

const pluginStore = usePluginStore()
const ctxMenuRef = ref<InstanceType<typeof ContextMenu> | null>(null)

/** PrimeVue MenuItem list built from context-menu slot plugin registrations. */
const contextMenuItems = computed(() =>
  pluginStore
    .getSlotComponents('context-menu')
    .map(({ entry }) => ({
      label: entry.component_name,
      icon: entry.icon ?? undefined,
      command: () => {
        // Plugin action dispatched via pluginApi.events or store
        console.debug('[ContextMenuProvider] item clicked:', entry.plugin_id)
      },
    })),
)

/** Open the context menu at a DOM event's position. */
function show(event: MouseEvent) {
  ctxMenuRef.value?.show(event)
}

function hide() {
  ctxMenuRef.value?.hide()
}

defineExpose({ show, hide })
</script>

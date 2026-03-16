<template>
  <!--
    PluginSlot — rendert alle Plugin-Komponenten für einen gegebenen Slot.

    Verwendung:
      <PluginSlot slot-id="home-widget" />
      <PluginSlot slot-id="sidebar-bottom" />

    Das Dashboard (v2_dashboard) ruft `pluginStore.loadUiManifest()` beim Start auf
    und befüllt damit den Pinia-Store. Dieser hier liest den Store aus.
  -->
  <template v-if="components.length > 0">
    <component
      v-for="({ entry, component }, idx) in components"
      :is="component"
      :key="`${entry.plugin_id}-${entry.slot_id}-${idx}`"
      v-bind="componentProps"
    />
  </template>
</template>

<script setup lang="ts">
import { computed } from 'vue'
import { usePluginStore } from '../../store/plugins'

const props = defineProps<{
  slotId:          string
  componentProps?: Record<string, unknown>
}>()

const pluginStore = usePluginStore()
const components  = computed(() => pluginStore.getSlotComponents(props.slotId))
</script>

<template>
  <template
    v-for="item in slotItems"
    :key="item.entry.assignment_id"
  >
    <component
      :is="item.component"
      v-bind="item.entry"
    />
  </template>
</template>

<script setup lang="ts">
import { computed } from 'vue'
import { usePluginStore } from '../../store/plugins'

/**
 * PluginSlotHost
 *
 * Generic container that renders all plugin components assigned to a given slot.
 * Plugin components are loaded lazily via defineAsyncComponent (see plugins store).
 *
 * Usage:
 *   <PluginSlotHost slot-id="sidebar.bottom" />
 *   <PluginSlotHost slot-id="dashboard.header" />
 */
const props = defineProps<{
  /** The slot identifier to render, e.g. 'sidebar.bottom' */
  slotId: string
}>()

const pluginStore = usePluginStore()

const slotItems = computed(() => pluginStore.getSlotComponents(props.slotId))
</script>

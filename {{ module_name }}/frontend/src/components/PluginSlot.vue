<template>
  <!--
    PluginSlot — rendert alle Plugin-Komponenten für einen gegebenen Slot.

    Verwendung:
      <PluginSlot slot-id="home-widget" />
      <PluginSlot slot-id="sidebar-bottom" />

    Fehlerhafte Plugins werden still ausgeklammert (onErrorCaptured) und beeinflussen
    die Host-Applikation nicht.
  -->
  <template v-if="components.length > 0">
    <component
      v-for="({ entry, component }, idx) in components"
      :is="component"
      :key="`${entry.plugin_id}-${entry.slot_id}-${idx}`"
      v-bind="mergedProps"
    />
  </template>
</template>

<script setup lang="ts">
import { computed, inject, onErrorCaptured } from 'vue'
import { usePluginStore } from '../store/plugins'
import { PLUGIN_API_INJECTION_KEY } from '../composables/usePluginApi'

const props = defineProps<{
  slotId:          string
  componentProps?: Record<string, unknown>
}>()

const pluginStore = usePluginStore()
const components  = computed(() => pluginStore.getSlotComponents(props.slotId))

/** Global Plugin API injected from the App root via providePluginApi(). */
const pluginApi = inject(PLUGIN_API_INJECTION_KEY, undefined)

/** Merged props: host componentProps + pluginApi passed to every plugin. */
const mergedProps = computed(() => ({
  ...props.componentProps,
  pluginApi,
}))

/**
 * Catch any runtime error thrown inside a plugin component tree.
 * Returning false prevents the error from propagating further up the host tree,
 * so a broken plugin never crashes or freezes the rest of the UI.
 */
onErrorCaptured((err, _instance, info) => {
  console.error(`[PluginSlot "${props.slotId}"] Plugin runtime error (${info}):`, err)
  return false
})
</script>

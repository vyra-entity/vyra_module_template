<template>
  <div class="plugins-settings">
    <div class="plugins-settings__header">
      <div>
        <h2 class="plugins-settings__title">Aktive Plugins</h2>
        <p class="plugins-settings__subtitle">
          Übersicht aller im aktuellen Webinterface geladenen Plugins und ihrer UI-Slots.
        </p>
      </div>
      <Button
        icon="pi pi-refresh"
        label="Neu laden"
        size="small"
        severity="secondary"
        outlined
        :loading="refreshing"
        @click="doRefresh"
      />
    </div>

    <!-- Empty state -->
    <div v-if="!pluginStore.manifestLoaded" class="plugins-settings__empty">
      <i class="pi pi-spin pi-spinner" style="font-size: 2rem; color: var(--text-color-secondary)" />
      <p>Plugin-Manifest wird geladen…</p>
    </div>

    <div v-else-if="groupedPlugins.length === 0" class="plugins-settings__empty">
      <i class="pi pi-puzzle" style="font-size: 2.5rem; color: var(--text-color-secondary); opacity: 0.4" />
      <p>Keine Plugins aktiv.</p>
      <p class="plugins-settings__empty-hint">
        Installiere Plugins über den v2_modulemanager.
      </p>
    </div>

    <!-- Plugin list -->
    <div v-else class="plugins-settings__list">
      <div
        v-for="plugin in groupedPlugins"
        :key="plugin.pluginId"
        class="plugin-row"
      >
        <!-- Plugin header -->
        <div class="plugin-row__header">
          <div class="plugin-row__icon">
            <img
              v-if="plugin.icon && plugin.icon.startsWith('/')"
              :src="plugin.icon"
              :alt="plugin.title"
              width="32"
              height="32"
            />
            <i
              v-else-if="plugin.icon"
              :class="plugin.icon"
              style="font-size: 1.5rem; color: var(--p-primary-color)"
            />
            <i
              v-else
              class="pi pi-puzzle"
              style="font-size: 1.5rem; color: var(--p-primary-color)"
            />
          </div>
          <div class="plugin-row__meta">
            <div class="plugin-row__name">{%- raw %}{{ plugin.title }}{%- endraw %}</div>
            <div class="plugin-row__id">
              <code>{%- raw %}{{ plugin.pluginId }}{%- endraw %}</code>
              <Tag :value="`v${plugin.version}`" severity="secondary" class="text-xs" />
              <Tag
                :value="plugin.scopeType"
                :severity="plugin.scopeType === 'GLOBAL' ? 'info' : 'secondary'"
                class="text-xs"
                v-tooltip.top="scopeLabel(plugin.scopeType, plugin.scopeTarget)"
              />
              <Tag
                v-if="plugin.scopeTarget"
                :value="plugin.scopeTarget"
                severity="secondary"
                class="text-xs"
              />
            </div>
          </div>
        </div>

        <!-- Slots -->
        <div class="plugin-row__slots">
          <div
            v-for="slot in plugin.slots"
            :key="slot.assignment_id"
            class="slot-row"
          >
            <div class="slot-row__info">
              <i class="pi pi-window-minimize slot-row__icon" />
              <div class="slot-row__ids">
                <span
                  v-for="sid in (slot.slot_ids?.length ? slot.slot_ids : [slot.slot_id])"
                  :key="sid"
                  class="slot-row__label"
                >{%- raw %}{{ sid }}{%- endraw %}</span>
              </div>
              <Tag
                v-if="slot.slot_type"
                :value="slot.slot_type"
                severity="secondary"
                class="text-xs"
              />
              <Tag
                v-if="slot.priority !== undefined && slot.priority !== 50"
                :value="`p:${slot.priority}`"
                severity="secondary"
                class="text-xs"
                v-tooltip.top="'Priorität'"
              />
              <Tag
                v-if="slot.min_user_role && slot.min_user_role !== 'operator'"
                :value="slot.min_user_role"
                severity="warn"
                class="text-xs"
                v-tooltip.top="'Mindest-Rolle'"
              />
            </div>
            <div class="slot-row__actions">
              <span class="slot-row__status" :class="slot.is_active ? 'slot-row__status--active' : 'slot-row__status--inactive'">
                {%- raw %}{{ slot.is_active ? 'Aktiv' : 'Inaktiv' }}{%- endraw %}
              </span>
              <InputSwitch
                v-model="activeMap[slot.assignment_id]"
                :loading="toggling.has(slot.assignment_id)"
                @change="toggleSlot(slot)"
              />
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
/**
 * PluginsPage — Settings page for active plugins in the current web interface.
 * Lists all loaded UI slots with activation status and toggle function.
 */
import { ref, computed, reactive } from 'vue'
import { usePluginStore } from '../../../store/plugins'
import type { UiManifestEntry } from '../../plugins/plugin.api'
import apiClient from '../../../api/http'
import Button from 'primevue/button'
import Tag from 'primevue/tag'
import InputSwitch from 'primevue/inputswitch'

const pluginStore = usePluginStore()
const refreshing  = ref(false)
const toggling    = reactive(new Set<string>())

/** Flat list of all UiManifestEntries across all slots */
const allEntries = computed<UiManifestEntry[]>(() =>
  Object.values(pluginStore.slotComponents).flat().map(sc => sc.entry)
)

interface PluginGroup {
  pluginId:    string
  title:       string
  icon:        string | null
  version:     string
  scopeType:   string
  scopeTarget: string | null
  slots:       UiManifestEntry[]
}

/** Group entries by plugin_id */
const groupedPlugins = computed<PluginGroup[]>(() => {
  const map = new Map<string, PluginGroup>()
  for (const entry of allEntries.value) {
    if (!map.has(entry.plugin_id)) {
      map.set(entry.plugin_id, {
        pluginId:    entry.plugin_id,
        title:       entry.title || entry.plugin_id,
        icon:        entry.icon,
        version:     entry.version,
        scopeType:   entry.scope_type,
        scopeTarget: entry.scope_target,
        slots:       [],
      })
    }
    map.get(entry.plugin_id)!.slots.push(entry)
  }
  return [...map.values()].sort((a, b) => a.title.localeCompare(b.title))
})

/** Local active state mirror for instant UI feedback */
const activeMap = computed<Record<string, boolean>>(() => {
  const result: Record<string, boolean> = {}
  for (const entry of allEntries.value) {
    result[entry.assignment_id] = entry.is_active
  }
  return result
})

function scopeLabel(scopeType: string, scopeTarget: string | null): string {
  if (scopeType === 'GLOBAL') return 'Global — in allen Modulen aktiv'
  if (scopeType === 'MODULE') return `Modul: ${scopeTarget ?? '–'}`
  if (scopeType === 'INSTANCE') return `Instanz: ${scopeTarget ?? '–'}`
  return scopeType
}

async function toggleSlot(slot: UiManifestEntry): Promise<void> {
  if (toggling.has(slot.assignment_id)) return
  toggling.add(slot.assignment_id)
  try {
    await apiClient.patch(`/plugin_admin_service/assignments/${slot.assignment_id}/toggle`)
    // Reload manifest to get fresh state
    await pluginStore.resolvePlugins('MODULE', '{{ module_name }}')
  } catch (e) {
    console.error('[PluginsPage] Toggle failed:', e)
  } finally {
    toggling.delete(slot.assignment_id)
  }
}

async function doRefresh(): Promise<void> {
  refreshing.value = true
  try {
    await pluginStore.resolvePlugins('MODULE', '{{ module_name }}')
  } finally {
    refreshing.value = false
  }
}
</script>

<style scoped>
.plugins-settings {
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
}

.plugins-settings__header {
  display: flex;
  align-items: flex-start;
  justify-content: space-between;
  gap: 1rem;
}

.plugins-settings__title {
  font-size: 1.125rem;
  font-weight: 600;
  color: var(--text-color);
  margin: 0 0 0.25rem 0;
}

.plugins-settings__subtitle {
  font-size: 0.875rem;
  color: var(--text-color-secondary);
  margin: 0;
}

.plugins-settings__empty {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  padding: 3rem 2rem;
  gap: 0.75rem;
  text-align: center;
  color: var(--text-color-secondary);
}

.plugins-settings__empty-hint {
  font-size: 0.875rem;
  opacity: 0.75;
}

.plugins-settings__list {
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
}

.plugin-row {
  background: var(--surface-card);
  border: 1px solid var(--surface-border);
  border-radius: 8px;
  padding: 1rem;
}

.plugin-row__header {
  display: flex;
  align-items: flex-start;
  gap: 0.75rem;
  margin-bottom: 0.75rem;
}

.plugin-row__icon {
  width: 36px;
  height: 36px;
  display: flex;
  align-items: center;
  justify-content: center;
  background: var(--surface-section, var(--surface-hover));
  border-radius: 8px;
  flex-shrink: 0;
}

.plugin-row__meta {
  min-width: 0;
  flex: 1;
}

.plugin-row__name {
  font-weight: 600;
  font-size: 0.95rem;
  color: var(--text-color);
  margin-bottom: 0.25rem;
}

.plugin-row__id {
  display: flex;
  align-items: center;
  gap: 0.4rem;
  flex-wrap: wrap;
}

.plugin-row__id code {
  font-size: 0.75rem;
  color: var(--text-color-secondary);
  background: var(--surface-hover);
  padding: 0.1rem 0.35rem;
  border-radius: 4px;
}

.plugin-row__slots {
  border-top: 1px solid var(--surface-border);
  padding-top: 0.75rem;
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
}

.slot-row {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 0.4rem 0.5rem;
  border-radius: 6px;
  background: var(--surface-section, var(--surface-ground));
}

.slot-row__info {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  min-width: 0;
}

.slot-row__icon {
  color: var(--text-color-secondary);
  font-size: 0.8rem;
}

.slot-row__ids {
  display: flex;
  flex-wrap: wrap;
  gap: 0.25rem;
  align-items: center;
}

.slot-row__label {
  font-size: 0.8rem;
  font-family: monospace;
  color: var(--text-color);
}

.slot-row__actions {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  flex-shrink: 0;
}

.slot-row__status {
  font-size: 0.75rem;
  font-weight: 500;
}

.slot-row__status--active {
  color: var(--p-green-500, #22c55e);
}

.slot-row__status--inactive {
  color: var(--text-color-secondary);
}
</style>

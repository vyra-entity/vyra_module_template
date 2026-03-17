<template>
  <div class="installed-plugins-view">

    <!-- Header bar -->
    <div class="flex align-items-center justify-content-between mb-4">
      <div class="flex align-items-center gap-2">
        <i class="pi pi-puzzle text-primary" style="font-size: 1.5rem"></i>
        <span class="font-semibold text-2xl">Installierte Plugins</span>
        <Tag :value="`${pool.length}`" severity="info" />
      </div>
      <div class="flex gap-2">
        <Button
          icon="pi pi-refresh"
          label="Aktualisieren"
          size="small"
          severity="secondary"
          outlined
          :loading="loading"
          @click="refresh"
        />
        <Button
          icon="pi pi-puzzle"
          label="Repository"
          size="small"
          @click="$router.push('/{{ module_name }}/repository')"
        />
      </div>
    </div>

    <!-- Search + filter -->
    <div class="flex gap-3 mb-4 align-items-center">
      <!-- <span class="p-input-icon-left flex-1">
        <i class="pi pi-search" />
        <InputText v-model="search" placeholder="Plugin suchen…" class="w-full" />
      </span> -->
      <IconField class="flex-1">
        <InputIcon class="pi pi-search" />
        <InputText
          v-model="search"
          placeholder="Plugin suchen…"
          class="w-full"
        />
      </IconField>
      <Select
        v-model="filterActive"
        :options="activeFilterOptions"
        optionLabel="label"
        optionValue="value"
        class="w-12rem"
      />
    </div>

    <!-- Error -->
    <Message v-if="error" severity="error" class="mb-4">{%- raw %}{{ error }}{%- endraw %}</Message>

    <!-- Loading -->
    <div v-if="loading" class="plugin-grid">
      <div v-for="n in 6" :key="n" class="plugin-card plugin-card--skeleton">
        <Skeleton width="56px" height="56px" border-radius="14px" class="mb-3" />
        <Skeleton width="70%" height="1rem" class="mb-2" />
        <Skeleton width="50%" height="0.75rem" />
      </div>
    </div>

    <!-- Empty -->
    <div v-else-if="filtered.length === 0" class="text-center py-10 text-color-secondary">
      <i class="pi pi-inbox mb-3" style="font-size: 3.5rem; display:block"></i>
      <p class="text-lg">Keine installierten Plugins gefunden.</p>
      <Button
        label="Zum Plugin Repository"
        icon="pi pi-puzzle"
        class="mt-3"
        @click="$router.push('/{{ module_name }}/repository')"
      />
    </div>

    <!-- Plugin tiles (grid) -->
    <div v-else class="plugin-grid">
      <div
        v-for="entry in filtered"
        :key="entry.p_id"
        class="plugin-card"
        :class="{ 'plugin-card--inactive': !isActive(entry) }"
      >
        <!-- Top row: icon + name -->
        <div class="plugin-card__header">
          <div class="plugin-card__icon">
            <img
              v-if="iconFor(entry)"
              :src="iconFor(entry)!"
              :alt="entry.plugin_name_id"
              width="40"
              height="40"
            />
            <i v-else class="pi pi-puzzle" style="font-size: 2rem; color: var(--p-primary-color)"></i>
          </div>
          <div class="plugin-card__title">
            <span class="plugin-card__name">{%- raw %}{{ labelFor(entry) }}{%- endraw %}</span>
            <Tag :value="`v${entry.version}`" severity="secondary" class="text-xs mt-1" />
          </div>
          <!-- Active toggle -->
          <ToggleButton
            v-model="activeStates[entry.p_id]"
            onIcon="pi pi-check"
            offIcon="pi pi-times"
            onLabel=""
            offLabel=""
            class="plugin-card__toggle"
            v-tooltip.top="activeStates[entry.p_id] ? 'Plugin aktiv – klicken zum Deaktivieren' : 'Plugin inaktiv – klicken zum Aktivieren'"
            @change="togglePlugin(entry)"
          />
        </div>

        <!-- Verified badge -->
        <div class="flex gap-2 mt-2 flex-wrap">
          <Tag
            v-if="entry.is_verified"
            severity="success"
            value="Verifiziert"
            icon="pi pi-verified"
            class="text-xs"
          />
          <Tag
            v-else
            severity="warn"
            value="Ungeprüft"
            icon="pi pi-exclamation-triangle"
            class="text-xs"
          />
        </div>

        <!-- Assignments: which module →scope info -->
        <div v-if="assignmentsFor(entry).length > 0" class="plugin-card__assignments mt-2">
          <span class="text-xs text-color-secondary font-semibold mb-1 block">Zuweisungen:</span>
          <div
            v-for="a in assignmentsFor(entry)"
            :key="a.assignment_id"
            class="assignment-row"
          >
            <Tag :severity="a.is_active ? 'success' : 'secondary'" :value="a.is_active ? 'Aktiv' : 'Inaktiv'" class="text-xs" />
            <span class="text-xs">{%- raw %}{{ a.scope_type }}{%- endraw %}</span>
            <span v-if="a.scope_target" class="text-xs text-color-secondary">→ {%- raw %}{{ a.scope_target }}{%- endraw %}</span>
          </div>
        </div>
        <div v-else class="text-xs text-color-secondary mt-2 italic">Keine Zuweisungen</div>

        <!-- Installed at -->
        <div class="text-xs text-color-secondary mt-2">
          <i class="pi pi-calendar mr-1"></i>
          {%- raw %}{{ formatDate(entry.installed_at) }}{%- endraw %}
        </div>

        <!-- Actions -->
        <div class="plugin-card__actions mt-3 flex gap-2 flex-wrap">
          <Button
            v-if="hasUpdate(entry)"
            icon="pi pi-refresh"
            label="Update"
            severity="warn"
            size="small"
            outlined
            v-tooltip.top="'Update verfügbar'"
            @click="openUpdateDialog(entry)"
          />
          <Button
            icon="pi pi-trash"
            label="Deinstallieren"
            severity="danger"
            size="small"
            outlined
            :loading="uninstallingId === entry.p_id"
            @click="uninstall(entry)"
          />
        </div>
      </div>
    </div>

    <!-- Update dialog -->
    <Dialog v-model:visible="showUpdateDialog" modal header="Plugin aktualisieren" :style="{ width: '420px' }">
      <div v-if="updateTarget" class="flex flex-column gap-3">
        <p>
          <strong>{%- raw %}{{ labelFor(updateTarget) }}{%- endraw %}</strong> v{%- raw %}{{ updateTarget.version }}{%- endraw %}
          → v{%- raw %}{{ repoVersionFor(updateTarget) }}{%- endraw %}
        </p>
        <Message severity="info">Stellt eine neue Version aus dem Repository bereit.</Message>
      </div>
      <template #footer>
        <Button label="Abbrechen" severity="secondary" @click="showUpdateDialog = false" />
        <Button label="Update starten" icon="pi pi-refresh" :loading="updating" @click="doUpdate" />
      </template>
    </Dialog>

    <Toast />
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import { useToast } from 'primevue/usetoast'
import Button from 'primevue/button'
import InputText from 'primevue/inputtext'
import Select from 'primevue/select'
import Tag from 'primevue/tag'
import Toast from 'primevue/toast'
import Message from 'primevue/message'
import Dialog from 'primevue/dialog'
import Skeleton from 'primevue/skeleton'
import ToggleButton from 'primevue/togglebutton'
import { pluginApi, type PoolEntry, type AssignmentResponse } from '../plugins/plugin.api'
import { usePluginStore } from '../../store/plugins'

const toast = useToast()
const pluginStore = usePluginStore()

// ── State ─────────────────────────────────────────────────────────────────────
const pool        = ref<PoolEntry[]>([])
const assignments = ref<AssignmentResponse[]>([])
const loading     = ref(false)
const error       = ref<string | null>(null)

const search      = ref('')
const filterActive = ref<boolean | null>(null)
const activeStates = ref<Record<string, boolean>>({})

const showUpdateDialog = ref(false)
const updateTarget     = ref<PoolEntry | null>(null)
const updating         = ref(false)
const uninstallingId   = ref<string | null>(null)

const activeFilterOptions = [
  { label: 'Alle', value: null },
  { label: 'Aktiv', value: true },
  { label: 'Inaktiv', value: false },
]

// ── Computed ──────────────────────────────────────────────────────────────────

/** Label: prefer name from repo list, fall back to name_id */
function labelFor(entry: PoolEntry): string {
  const repo = pluginStore.pluginList.find(p => p.id === entry.plugin_name_id)
  return repo?.name ?? entry.plugin_name_id
}

/** Icon URL if the repo entry has an icon field */
function iconFor(entry: PoolEntry): string | null {
  const repo = pluginStore.pluginList.find(p => p.id === entry.plugin_name_id)
  if (!repo?.icon) return null
  return pluginApi.assetUrl(repo.id, repo.version, repo.icon.replace(`plugins/${repo.id}/${repo.version}/`, ''))
}

/** All assignments for this pool entry */
function assignmentsFor(entry: PoolEntry): AssignmentResponse[] {
  return assignments.value.filter(a => a.p_id === entry.p_id)
}

/** Whether at least one assignment is active */
function isActive(entry: PoolEntry): boolean {
  return assignmentsFor(entry).some(a => a.is_active)
}

/** Whether repo has a newer version */
function hasUpdate(entry: PoolEntry): boolean {
  const repo = pluginStore.pluginList.find(p => p.id === entry.plugin_name_id)
  if (!repo) return false
  return semverGt(repo.version, entry.version)
}

function repoVersionFor(entry: PoolEntry): string {
  return pluginStore.pluginList.find(p => p.id === entry.plugin_name_id)?.version ?? entry.version
}

function semverGt(a: string, b: string): boolean {
  const parse = (v: string) => v.replace(/[^0-9.]/g, '').split('.').map(Number)
  const pa = parse(a); const pb = parse(b)
  for (let i = 0; i < Math.max(pa.length, pb.length); i++) {
    if ((pa[i] ?? 0) > (pb[i] ?? 0)) return true
    if ((pa[i] ?? 0) < (pb[i] ?? 0)) return false
  }
  return false
}

function formatDate(iso: string | null): string {
  if (!iso) return 'Unbekannt'
  try {
    return new Date(iso).toLocaleString('de-DE', { day: '2-digit', month: '2-digit', year: 'numeric', hour: '2-digit', minute: '2-digit' })
  } catch { return iso }
}

const filtered = computed(() => {
  let list = pool.value
  if (search.value) {
    const q = search.value.toLowerCase()
    list = list.filter(e => labelFor(e).toLowerCase().includes(q) || e.plugin_name_id.toLowerCase().includes(q))
  }
  if (filterActive.value !== null) {
    list = list.filter(e => isActive(e) === filterActive.value)
  }
  return list
})

// ── Actions ───────────────────────────────────────────────────────────────────

async function refresh() {
  loading.value = true
  error.value   = null
  try {
    const [poolData, assignData] = await Promise.all([
      pluginApi.listPool(),
      pluginApi.listAssignments(),
    ])
    pool.value        = poolData
    assignments.value = assignData

    // Sync active toggle state: active if ANY assignment is active
    const states: Record<string, boolean> = {}
    for (const e of poolData) {
      states[e.p_id] = assignData.filter(a => a.p_id === e.p_id).some(a => a.is_active)
    }
    activeStates.value = states

    // Ensure repo plugin list is loaded
    if (pluginStore.pluginList.length === 0) await pluginStore.fetchPluginList()
  } catch (e: any) {
    error.value = e?.message ?? 'Fehler beim Laden der installierten Plugins'
  } finally {
    loading.value = false
  }
}

async function togglePlugin(entry: PoolEntry) {
  const targetAssignments = assignmentsFor(entry)
  if (targetAssignments.length === 0) return

  try {
    // Toggle the first assignment; others follow
    for (const a of targetAssignments) {
      await pluginApi.toggleAssignment(a.assignment_id)
    }
    toast.add({ severity: 'success', summary: 'Plugin-Status geändert', life: 2500 })
    await refresh()
  } catch (e: any) {
    toast.add({ severity: 'error', summary: 'Fehler', detail: e?.message, life: 5000 })
    // Re-sync toggle to server state
    activeStates.value[entry.p_id] = isActive(entry)
  }
}

async function uninstall(entry: PoolEntry) {
  uninstallingId.value = entry.p_id
  try {
    await pluginApi.uninstallPlugin(entry.plugin_name_id, entry.version)
    toast.add({ severity: 'success', summary: 'Plugin deinstalliert', life: 3000 })
    await refresh()
  } catch (e: any) {
    toast.add({ severity: 'error', summary: 'Fehler', detail: e?.message, life: 5000 })
  } finally {
    uninstallingId.value = null
  }
}

function openUpdateDialog(entry: PoolEntry) {
  updateTarget.value = entry
  showUpdateDialog.value = true
}

async function doUpdate() {
  if (!updateTarget.value) return
  updating.value = true
  try {
    const repo = pluginStore.pluginList.find(p => p.id === updateTarget.value!.plugin_name_id)
    if (!repo) throw new Error('Plugin nicht im Repository gefunden')
    // Install new version with same scope + uninstall old handled by backend
    await pluginApi.installPlugin({ plugin_id: repo.id, version: repo.version })
    showUpdateDialog.value = false
    toast.add({ severity: 'success', summary: 'Update durchgeführt', life: 3000 })
    await refresh()
  } catch (e: any) {
    toast.add({ severity: 'error', summary: 'Update fehlgeschlagen', detail: e?.message, life: 5000 })
  } finally {
    updating.value = false
  }
}

onMounted(refresh)
</script>

<style scoped>
.installed-plugins-view {
  animation: fadeIn 0.3s ease-in;
}

@keyframes fadeIn {
  from { opacity: 0; transform: translateY(20px); }
  to { opacity: 1; transform: translateY(0); }
}

/* ── Grid ─────────────────────────────────────────────────────────────── */
.plugin-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(280px, 1fr));
  gap: 1rem;
}

/* ── Card ─────────────────────────────────────────────────────────────── */
.plugin-card {
  display: flex;
  flex-direction: column;
  padding: 1rem;
  border: 1px solid var(--p-surface-border, #e5e7eb);
  border-radius: 0.875rem;
  background: var(--p-surface-card, #fff);
  transition: box-shadow 0.15s, transform 0.15s;
}
.plugin-card:hover {
  box-shadow: 0 6px 16px rgba(0,0,0,.08);
  transform: translateY(-2px);
}
.plugin-card--inactive {
  opacity: 0.62;
  border-color: var(--p-surface-border, #e5e7eb);
}
.plugin-card--skeleton { align-items: center; }

/* ── Header row ───────────────────────────────────────────────────────── */
.plugin-card__header {
  display: flex;
  align-items: flex-start;
  gap: 0.75rem;
}
.plugin-card__icon {
  flex-shrink: 0;
  width: 52px;
  height: 52px;
  display: flex;
  align-items: center;
  justify-content: center;
  background: var(--p-surface-ground, #f9fafb);
  border-radius: 12px;
  border: 1px solid var(--p-surface-border, #e2e8f0);
}
.plugin-card__title {
  flex: 1;
  display: flex;
  flex-direction: column;
}
.plugin-card__name {
  font-weight: 600;
  font-size: 0.9rem;
  line-height: 1.2;
}
.plugin-card__toggle { margin-left: auto; flex-shrink: 0; }

/* ── Assignments ──────────────────────────────────────────────────────── */
.plugin-card__assignments { display: flex; flex-direction: column; gap: 0.2rem; }
.assignment-row { display: flex; align-items: center; gap: 0.4rem; flex-wrap: wrap; }

/* ── Actions ──────────────────────────────────────────────────────────── */
.plugin-card__actions { margin-top: auto; }
</style>

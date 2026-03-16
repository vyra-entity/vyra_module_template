<template>
  <div class="repository-view">

    <!-- ── Module Repository (collapsible) ──────────────────────────────────── -->
    <div class="section-card mb-4">
      <div class="section-header" @click="moduleCardCollapsed = !moduleCardCollapsed">
        <div class="flex align-items-center gap-2">
          <i class="pi pi-database text-primary" style="font-size: 1.25rem"></i>
          <span class="font-semibold text-lg">Module Repository</span>
          <Button
            icon="pi pi-refresh"
            @click.stop="refreshRepository"
            :loading="loading"
            size="small"
            severity="secondary"
            text
            rounded
            v-tooltip.top="'Repository aktualisieren'"
          />
        </div>
        <i class="pi collapse-icon" :class="moduleCardCollapsed ? 'pi-chevron-down' : 'pi-chevron-up'" />
      </div>

      <div v-show="!moduleCardCollapsed" class="section-body">
        <!-- Repository Selector -->
        <div class="mb-4">
          <label class="block mb-2 font-semibold">Repository auswählen:</label>
          <Select
            v-model="selectedRepository"
            :options="availableRepositories"
            optionLabel="displayName"
            placeholder="Repository wählen..."
            class="w-full"
            @change="onRepositoryChange"
          />
        </div>

        <!-- Filters -->
        <div class="flex gap-3 mb-4 align-items-center">
          <IconField class="flex-1">
            <InputIcon class="pi pi-search" />
            <InputText
              v-model="searchQuery"
              placeholder="Module durchsuchen..."
              class="w-full"
            />
          </IconField>
          <Select
            v-model="statusFilter"
            :options="statusOptions"
            optionLabel="label"
            placeholder="Status"
            class="w-12rem"
          />
        </div>

        <!-- Modules Table -->
        <DataTable
          :value="filteredModules"
          :loading="loading"
          :paginator="true"
          :rows="10"
          stripedRows
        >
          <template #empty>
            <div class="text-center py-5">
              <i class="pi pi-inbox text-4xl text-400 mb-3"></i>
              <p class="text-500">Keine Module im Repository gefunden</p>
            </div>
          </template>

          <Column field="displayName" header="Modul" sortable style="min-width: 200px">
            <template #body="{ data }">
              <div class="flex align-items-center gap-2">
                <i :class="data.icon || 'pi pi-cube'" class="text-primary"></i>
                <span class="font-semibold">{{ data.displayName || data.name }}</span>
              </div>
            </template>
          </Column>
          <Column field="description" header="Beschreibung" style="min-width: 250px" />
          <Column field="author" header="Autor" sortable style="min-width: 150px" />
          <Column field="template" header="Template" sortable style="min-width: 120px">
            <template #body="{ data }">
              <Tag :value="data.template || 'Other'" severity="secondary" />
            </template>
          </Column>
          <Column field="version" header="Version" sortable style="min-width: 100px">
            <template #body="{ data }">
              <Tag :value="`v${data.version}`" severity="info" />
            </template>
          </Column>
          <Column field="status" header="Status" sortable style="min-width: 120px">
            <template #body="{ data }">
              <Tag :value="data.status" :severity="getStatusSeverity(data.status)" />
            </template>
          </Column>
          <Column header="Aktionen" style="min-width: 150px">
            <template #body="{ data }">
              <Button
                v-if="data.status === 'available'"
                label="Installieren"
                icon="pi pi-download"
                severity="success"
                size="small"
                @click="installModule(data)"
              />
              <Button
                v-else-if="data.status === 'update'"
                label="Update"
                icon="pi pi-sync"
                severity="warning"
                size="small"
              />
              <Button
                v-else-if="data.status === 'installed'"
                label="Instanz"
                icon="pi pi-plus-circle"
                severity="success"
                size="small"
                @click="installAdditionalInstance(data)"
                v-tooltip.top="'Zusätzliche Instanz installieren'"
              />
            </template>
          </Column>
        </DataTable>
      </div>
    </div>

    <!-- ── Plugin Repository (collapsible) ──────────────────────────────────── -->
    <div class="section-card mb-4">
      <div class="section-header" @click="pluginCardCollapsed = !pluginCardCollapsed">
        <div class="flex align-items-center gap-2">
          <i class="pi pi-puzzle text-primary" style="font-size: 1.25rem"></i>
          <span class="font-semibold text-lg">Plugin Repository</span>
          <Tag :value="`${pluginStore.pluginList.length}`" severity="secondary" class="text-xs" />
          <Button
            icon="pi pi-refresh"
            @click.stop="pluginStore.fetchPluginList()"
            :loading="pluginStore.loading"
            size="small"
            severity="secondary"
            text
            rounded
            v-tooltip.top="'Plugin-Liste aktualisieren'"
          />
        </div>
        <i class="pi collapse-icon" :class="pluginCardCollapsed ? 'pi-chevron-down' : 'pi-chevron-up'" />
      </div>

      <div v-show="!pluginCardCollapsed" class="section-body">
        <!-- Error -->
        <Message v-if="pluginStore.error" severity="error" class="mb-4">
          {{ pluginStore.error }}
        </Message>

        <!-- Loading skeleton -->
        <div v-if="pluginStore.loading" class="plugin-grid">
          <div v-for="n in 4" :key="n" class="plugin-tile plugin-tile--skeleton">
            <Skeleton width="48px" height="48px" border-radius="12px" />
            <div class="plugin-tile__info">
              <Skeleton width="120px" height="1rem" class="mb-2" />
              <Skeleton width="80px" height="0.75rem" class="mb-2" />
              <Skeleton width="100%" height="0.75rem" />
            </div>
          </div>
        </div>

        <!-- Empty -->
        <div
          v-else-if="pluginStore.pluginList.length === 0"
          class="text-center py-8 text-color-secondary"
        >
          <i class="pi pi-inbox mb-3" style="font-size: 3rem; display:block"></i>
          <p>Keine Plugins im Repository gefunden.</p>
        </div>

        <!-- Plugin tiles -->
        <div v-else class="plugin-grid">
          <div
            v-for="plugin in pluginStore.pluginList"
            :key="plugin.id"
            class="plugin-tile"
            :class="{ 'plugin-tile--installed': plugin.is_installed }"
          >
            <div class="plugin-tile__icon">
              <img
                v-if="plugin.icon"
                :src="pluginAssetUrl(plugin.id, plugin.version ?? '1.0.0', plugin.icon)"
                :alt="plugin.name"
                width="48"
                height="48"
              />
              <i v-else class="pi pi-puzzle" style="font-size: 2.5rem; color: var(--p-primary-color)"></i>
            </div>

            <div class="plugin-tile__info">
              <div class="flex align-items-center gap-2 flex-wrap">
                <h3 class="plugin-tile__name">{{ plugin.name }}</h3>
                <Tag
                  v-if="plugin.is_verified"
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
              <span class="plugin-tile__version text-xs text-color-secondary">v{{ plugin.version }}</span>
              <p class="plugin-tile__desc">{{ plugin.description }}</p>
              <div class="plugin-tile__meta">
                <Tag :severity="pluginStatusSeverity(plugin.status)" :value="plugin.status" class="text-xs" />
                <span class="text-xs text-color-secondary ml-2">{{ plugin.scope?.type }}</span>
              </div>
              <div class="plugin-tile__actions mt-2 flex gap-2 flex-wrap">
                <Button
                  v-if="plugin.is_installed"
                  icon="pi pi-check"
                  label="Installiert"
                  severity="success"
                  size="small"
                  outlined
                  disabled
                />
                <Button
                  v-else
                  icon="pi pi-download"
                  label="Installieren"
                  size="small"
                  @click="openPluginInstallDialog(plugin)"
                  :loading="installingPlugin && pendingPlugin?.id === plugin.id"
                />
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Plugin Install Dialog -->
    <Dialog
      v-model:visible="showPluginInstallDialog"
      modal
      header="Plugin installieren"
      :style="{ width: '480px' }"
    >
      <div v-if="pendingPlugin" class="flex flex-column gap-3">
        <div class="text-sm text-color-secondary">
          <strong>{{ pendingPlugin.name }}</strong> v{{ pendingPlugin.version }}
        </div>
        <div class="field">
          <label class="block font-medium mb-1">Scope-Typ</label>
          <Select
            v-model="pluginInstallForm.scope_type"
            :options="scopeTypes"
            placeholder="Scope-Typ wählen"
            class="w-full"
          />
        </div>
        <div class="field" v-if="pluginInstallForm.scope_type !== 'GLOBAL'">
          <label class="block font-medium mb-1">
            Scope-Target <span class="text-xs text-color-secondary">(kommagetrennte IDs, leer = alle)</span>
          </label>
          <Textarea v-model="pluginInstallForm.scope_target" rows="2" class="w-full" />
        </div>
      </div>
      <template #footer>
        <Button label="Abbrechen" severity="secondary" @click="showPluginInstallDialog = false" />
        <Button label="Installieren" icon="pi pi-download" @click="doPluginInstall" :loading="installingPlugin" />
      </template>
    </Dialog>

    <!-- Task Progress Dialog -->
    <TaskProgressDialog
      v-if="operationStatus"
      :visible="isTracking"
      :title="progressTitle"
      :tasks="operationStatus.tasks"
      :operation-status="operationStatus.status"
      :status-message="operationStatus.message"
      :user-prompt="operationStatus.user_prompt"
      :responding-to-prompt="respondingToPrompt"
      @close="handleProgressClose"
      @cancel="handleProgressCancel"
      @prompt-response="handlePromptResponse"
    />

    <Toast />
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import { useToast } from 'primevue/usetoast'
import { useRouter } from 'vue-router'
import DataTable from 'primevue/datatable'
import Column from 'primevue/column'
import Button from 'primevue/button'
import InputText from 'primevue/inputtext'
import IconField from 'primevue/iconfield'
import InputIcon from 'primevue/inputicon'
import Select from 'primevue/select'
import Tag from 'primevue/tag'
import Toast from 'primevue/toast'
import Message from 'primevue/message'
import Dialog from 'primevue/dialog'
import Textarea from 'primevue/textarea'
import Skeleton from 'primevue/skeleton'
import TaskProgressDialog from '../../components/TaskProgressDialog.vue'
import { repositoryApi } from './repository.api'
import { pluginApi, type PluginListEntry } from '../plugins/plugin.api'
import { usePluginStore } from '../../store/plugins'
import { useOperationTracking } from '../../composables/useOperationTracking'
import type { RepositoryModule, Repository } from '../../types/common'

const toast = useToast()
const router = useRouter()
const pluginStore = usePluginStore()
const {
  isTracking,
  operationStatus,
  respondingToPrompt,
  startTracking,
  stopTracking,
  respondToPrompt,
  cancelOperation
} = useOperationTracking()

// ── Collapse state ────────────────────────────────────────────────────────────
const moduleCardCollapsed = ref(false)
const pluginCardCollapsed = ref(false)

// ── Module repository state ───────────────────────────────────────────────────
const searchQuery = ref('')
const statusFilter = ref<{ label: string; value: string | null } | null>(null)
const selectedRepository = ref<Repository | null>(null)
const availableRepositories = ref<Repository[]>([])
const modules = ref<RepositoryModule[]>([])
const loading = ref(false)

// ── Plugin install state ──────────────────────────────────────────────────────
const showPluginInstallDialog = ref(false)
const pendingPlugin = ref<PluginListEntry | null>(null)
const installingPlugin = ref(false)
const scopeTypes = ['GLOBAL', 'MODULE', 'INSTANCE', 'TEMPLATE']
const pluginInstallForm = ref({ scope_type: 'GLOBAL', scope_target: '' })

function pluginAssetUrl(pluginId: string, version: string, iconPath: string) {
  return pluginApi.assetUrl(pluginId, version, iconPath.replace(`plugins/${pluginId}/${version}/`, ''))
}

function pluginStatusSeverity(status: string) {
  return ({ stable: 'success', development: 'warn', deprecated: 'danger' } as Record<string, string>)[status] ?? 'info'
}

function openPluginInstallDialog(plugin: PluginListEntry) {
  pendingPlugin.value = plugin
  pluginInstallForm.value = { scope_type: 'GLOBAL', scope_target: '' }
  showPluginInstallDialog.value = true
}

async function doPluginInstall() {
  if (!pendingPlugin.value) return
  installingPlugin.value = true
  try {
    await pluginApi.installPlugin({
      plugin_id:    pendingPlugin.value.id,
      version:      pendingPlugin.value.version,
      scope_type:   pluginInstallForm.value.scope_type,
      scope_target: pluginInstallForm.value.scope_target || undefined,
    })
    showPluginInstallDialog.value = false
    toast.add({ severity: 'success', summary: 'Plugin installiert', life: 3000 })
    await pluginStore.fetchPluginList()
  } catch (e: any) {
    toast.add({ severity: 'error', summary: 'Fehler', detail: e?.message ?? 'Installation fehlgeschlagen', life: 5000 })
  } finally {
    installingPlugin.value = false
  }
}

const progressTitle = computed(() => {
  if (!operationStatus.value) return ''
  return `Installation - ${operationStatus.value.module_name || ''}`
})

const statusOptions = [
  { label: 'Alle', value: null },
  { label: 'Verfügbar', value: 'available' },
  { label: 'Installiert', value: 'installed' },
  { label: 'Update', value: 'update' }
]

const filteredModules = computed(() => {
  let result = modules.value
  if (searchQuery.value) {
    const query = searchQuery.value.toLowerCase()
    result = result.filter(m =>
      m.name.toLowerCase().includes(query) ||
      m.displayName.toLowerCase().includes(query) ||
      m.description.toLowerCase().includes(query)
    )
  }
  if (statusFilter.value && statusFilter.value.value) {
    result = result.filter(m => m.status === statusFilter.value!.value)
  }
  return result
})

onMounted(async () => {
  await loadRepositoryList()
  if (availableRepositories.value.length > 0) {
    selectedRepository.value = availableRepositories.value[0]
    await loadRepositoryModules()
  }
  await pluginStore.fetchPluginList()
})

const loadRepositoryList = async () => {
  try {
    loading.value = true
    availableRepositories.value = await repositoryApi.getRepositories()
  } catch (error) {
    console.error('Failed to load repositories:', error)
    toast.add({
      severity: 'error',
      summary: 'Fehler',
      detail: 'Repositories konnten nicht geladen werden',
      life: 5000
    })
  } finally {
    loading.value = false
  }
}

const loadRepositoryModules = async () => {
  if (!selectedRepository.value) return

  try {
    loading.value = true
    modules.value = await repositoryApi.getModules(selectedRepository.value.name)
  } catch (error) {
    console.error('Failed to load modules:', error)
    toast.add({
      severity: 'error',
      summary: 'Fehler',
      detail: 'Module konnten nicht geladen werden',
      life: 5000
    })
    modules.value = []
  } finally {
    loading.value = false
  }
}

const onRepositoryChange = async () => {
  await loadRepositoryModules()
}

const refreshRepository = async () => {
  if (!selectedRepository.value) return
  
  try {
    await repositoryApi.refreshRepository(selectedRepository.value.name)
    toast.add({
      severity: 'success',
      summary: 'Repository aktualisiert',
      detail: 'Lade Module neu...',
      life: 3000
    })
    await loadRepositoryModules()
  } catch (error) {
    console.error('Failed to refresh repository:', error)
  }
}

const installModule = async (module: RepositoryModule) => {
  if (!selectedRepository.value) return

  try {
    // Normalize dependencies: if it's an array, take first element, otherwise use as-is
    let dependencies = module.dependencies || {}
    if (Array.isArray(dependencies) && dependencies.length > 0) {
      dependencies = dependencies[0]
    } else if (Array.isArray(dependencies)) {
      dependencies = {}
    }
    
    const response = await repositoryApi.installModule(
      module.name,
      module.id,
      module.description,
      module.author,
      module.template,
      module.icon,
      dependencies,
      module.version,
      selectedRepository.value.name
    )
    
    await startTracking(response.operation_id, `Installation ${module.displayName}`, {
      statusUrl: response.status_url,
      cancelUrl: `/repository/install/cancel/${response.operation_id}`,
      onComplete: () => {
        loadRepositoryModules()
        router.push('/{{ module_name }}/modules')
      },
      navigateOnSuccess: '/{{ module_name }}/modules'
    })
  } catch (error) {
    console.error('Installation failed:', error)
    toast.add({
      severity: 'error',
      summary: 'Installation fehlgeschlagen',
      detail: error instanceof Error ? error.message : 'Modul konnte nicht installiert werden',
      life: 5000
    })
  }
}

const installAdditionalInstance = async (module: RepositoryModule) => {
  if (!selectedRepository.value) return

  try {
    // Normalize dependencies: if it's an array, take first element, otherwise use as-is
    let dependencies = module.dependencies || {}
    if (Array.isArray(dependencies) && dependencies.length > 0) {
      dependencies = dependencies[0]
    } else if (Array.isArray(dependencies)) {
      dependencies = {}
    }
    
    const response = await repositoryApi.installAdditionalInstance(
      module.name,
      module.id,
      module.description,
      module.author,
      module.template,
      module.icon,
      dependencies,
      module.version,
      selectedRepository.value
    )
    
    await startTracking(response.operation_id, `Installation ${module.displayName}`, {
      statusUrl: response.status_url,
      cancelUrl: `/repository/install/cancel/${response.operation_id}`,
      onComplete: () => {
        loadRepositoryModules()
        router.push('/{{ module_name }}/modules')
      },
      navigateOnSuccess: '/{{ module_name }}/modules'
    })
  } catch (error) {
    console.error('Installation failed:', error)
    toast.add({
      severity: 'error',
      summary: 'Installation fehlgeschlagen',
      detail: error instanceof Error ? error.message : 'Modul konnte nicht installiert werden',
      life: 5000
    })
  }
}

const getStatusSeverity = (status: string) => {
  const severityMap: Record<string, string> = {
    available: 'success',
    installed: 'info',
    update: 'warning'
  }
  return severityMap[status] || 'secondary'
}

const handleProgressClose = () => {
  stopTracking()
}

const handleProgressCancel = () => {
  cancelOperation()
}

const handlePromptResponse = (promptId: string, response: string) => {
  respondToPrompt(promptId, response)
}
</script>

<style scoped>
.repository-view {
  animation: fadeIn 0.3s ease-in;
}

@keyframes fadeIn {
  from { opacity: 0; transform: translateY(20px); }
  to { opacity: 1; transform: translateY(0); }
}

/* ── Collapsible section card ───────────────────────────────────────────── */
.section-card {
  border: 1px solid var(--p-surface-border, #e5e7eb);
  border-radius: 0.75rem;
  background: var(--p-surface-card, #fff);
  overflow: hidden;
  box-shadow: 0 1px 3px rgba(0,0,0,.06);
}

.section-header {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 1rem 1.25rem;
  cursor: pointer;
  user-select: none;
  border-bottom: 1px solid transparent;
  transition: background 0.15s;
}
.section-header:hover { background: var(--p-surface-hover, rgba(0,0,0,.03)); }
.collapse-icon { color: var(--p-text-secondary-color, #6b7280); transition: transform 0.2s; }

.section-body {
  padding: 1.25rem;
  border-top: 1px solid var(--p-surface-border, #e5e7eb);
}

/* ── Plugin tiles ──────────────────────────────────────────────────────── */
.plugin-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(260px, 1fr));
  gap: 1rem;
}

.plugin-tile {
  display: flex;
  gap: 1rem;
  padding: 1rem;
  border: 1px solid var(--p-surface-border, #e5e7eb);
  border-radius: 0.75rem;
  background: var(--p-surface-ground, #f9fafb);
  transition: box-shadow 0.15s, transform 0.15s;
}
.plugin-tile:hover {
  box-shadow: 0 4px 12px rgba(0,0,0,.08);
  transform: translateY(-2px);
}
.plugin-tile--installed { border-color: var(--p-green-400, #4ade80); }
.plugin-tile--skeleton { align-items: center; }

.plugin-tile__icon {
  flex-shrink: 0;
  width: 56px;
  height: 56px;
  display: flex;
  align-items: center;
  justify-content: center;
  background: var(--p-surface-card, #fff);
  border-radius: 12px;
  border: 1px solid var(--p-surface-border, #e5e7eb);
}
.plugin-tile__info { flex: 1; min-width: 0; }
.plugin-tile__name { margin: 0 0 0.125rem; font-size: 0.9rem; font-weight: 600; }
.plugin-tile__desc { margin: 0.25rem 0; font-size: 0.8rem; color: var(--p-text-secondary-color, #6b7280); }
.plugin-tile__meta { display: flex; align-items: center; flex-wrap: wrap; gap: 0.25rem; margin-top: 0.25rem; }
.plugin-tile__actions { display: flex; flex-wrap: wrap; gap: 0.5rem; }
</style>

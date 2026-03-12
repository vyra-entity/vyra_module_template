<template>
  <div class="plugin-repository-view">
    <!-- Unverified install warning dialog -->
    <Dialog
      v-model:visible="showUnverifiedDialog"
      modal
      header="⚠️ Unverified Plugin"
      :style="{ width: '420px' }"
    >
      <p class="mb-3">
        The plugin <strong>{{ pendingInstall?.name }} v{{ selectedVersion }}</strong>
        has <strong>not been verified</strong>. Its signature or checksum could not
        be confirmed.
      </p>
      <p class="text-color-secondary text-sm">
        Only install plugins from trusted sources. Unverified plugins may
        pose security risks.
      </p>
      <template #footer>
        <Button label="Cancel" severity="secondary" @click="showUnverifiedDialog = false" />
        <Button label="Install anyway" severity="danger" @click="confirmInstall" :loading="installing" />
      </template>
    </Dialog>

    <!-- Install / Update dialog -->
    <Dialog
      v-model:visible="showInstallDialog"
      modal
      :header="isUpdate ? 'Update Plugin' : 'Install Plugin'"
      :style="{ width: '500px' }"
    >
      <div v-if="pendingInstall" class="flex flex-column gap-3">
        <div class="text-sm text-color-secondary mb-1">
          <strong>{{ pendingInstall.name }}</strong>
        </div>

        <!-- Version selector -->
        <div class="field">
          <label class="block font-medium mb-1">Version</label>
          <Select
            v-model="selectedVersion"
            :options="availableVersions"
            placeholder="Select version"
            class="w-full"
          />
          <small v-if="isUpdate" class="text-color-secondary">
            Installed: v{{ installedVersionFor(pendingInstall.id) }} &rarr; v{{ selectedVersion }}
          </small>
        </div>

        <!-- Scope type -->
        <div class="field">
          <label class="block font-medium mb-1">Scope Type</label>
          <Select
            v-model="installForm.scope_type"
            :options="scopeTypes"
            placeholder="Select scope type"
            class="w-full"
          />
        </div>

        <!-- Scope targets (not shown for GLOBAL) -->
        <div class="field" v-if="installForm.scope_type !== 'GLOBAL'">
          <label class="block font-medium mb-1">
            Scope Targets
            <span class="text-xs text-color-secondary ml-1">
              (comma-separated IDs, leave empty for all)
            </span>
          </label>
          <Textarea
            v-model="installForm.scope_target"
            rows="2"
            class="w-full"
            placeholder="e.g. v2_dashboard_abc123, v2_dashboard_def456"
          />
          <small v-if="installForm.scope_type === 'TEMPLATE'" class="text-color-secondary">
            TEMPLATE scope allows multiple installed versions with different scope targets.
          </small>
          <small v-else class="text-color-secondary">
            Note: only one version per scope type (GLOBAL / MODULE / INSTANCE). Use TEMPLATE for
            multiple parallel installations.
          </small>
        </div>
      </div>
      <template #footer>
        <Button label="Cancel" severity="secondary" @click="showInstallDialog = false" />
        <Button
          :label="isUpdate ? 'Update' : 'Install'"
          :icon="isUpdate ? 'pi pi-refresh' : 'pi pi-download'"
          @click="startInstall"
          :loading="installing"
        />
      </template>
    </Dialog>

    <Card>
      <template #title>
        <div class="flex align-items-center gap-2">
          <i class="pi pi-puzzle text-primary" style="font-size: 1.5rem"></i>
          <span>Plugin Repository</span>
          <Button
            icon="pi pi-refresh"
            @click="refresh"
            :loading="pluginStore.loading"
            size="small"
            severity="secondary"
            text
            rounded
            v-tooltip.top="'Refresh list'"
          />
        </div>
      </template>

      <template #content>
        <!-- Error -->
        <Message v-if="pluginStore.error" severity="error" class="mb-4">
          {{ pluginStore.error }}
        </Message>

        <!-- Empty state -->
        <div
          v-if="!pluginStore.loading && pluginStore.pluginList.length === 0"
          class="text-center py-8 text-color-secondary"
        >
          <i class="pi pi-inbox mb-3" style="font-size: 3rem; display:block"></i>
          <p>No plugins found in the repository.</p>
        </div>

        <!-- Plugin tiles -->
        <div class="plugin-grid">
          <div
            v-for="plugin in pluginStore.pluginList"
            :key="plugin.id"
            class="plugin-tile"
          >
            <!-- Icon -->
            <div class="plugin-tile__icon">
              <img
                v-if="plugin.icon"
                :src="assetUrl(plugin.id, plugin.version ?? '1.0.0', plugin.icon)"
                :alt="plugin.name"
                width="48"
                height="48"
              />
              <i v-else class="pi pi-puzzle" style="font-size: 2.5rem; color: var(--p-primary-color)"></i>
            </div>

            <!-- Info -->
            <div class="plugin-tile__info">
              <div class="flex align-items-center gap-2">
                <h3 class="plugin-tile__name">{{ plugin.name }}</h3>
                <Tag
                  v-if="plugin.is_verified"
                  severity="success"
                  value="Verified"
                  icon="pi pi-verified"
                  class="text-xs"
                  v-tooltip.top="'Checksum verified'"
                />
                <Tag
                  v-else
                  severity="warn"
                  value="Unverified"
                  icon="pi pi-exclamation-triangle"
                  class="text-xs"
                  v-tooltip.top="'Checksum could not be verified'"
                />
              </div>
              <span class="plugin-tile__version">v{{ plugin.version }}</span>
              <p class="plugin-tile__desc">{{ plugin.description }}</p>

              <div class="plugin-tile__meta">
                <Tag
                  :severity="statusSeverity(plugin.status)"
                  :value="plugin.status"
                  class="text-xs"
                />
                <span class="text-xs text-color-secondary">
                  {{ plugin.scope?.type }}
                  <span v-if="plugin.scope?.target"> → {{ plugin.scope.target }}</span>
                </span>
              </div>

              <!-- Actions -->
              <div class="plugin-tile__actions mt-2 flex gap-2 flex-wrap">
                <!-- Uninstall (installed, not loading update) -->
                <Button
                  v-if="plugin.is_installed"
                  icon="pi pi-trash"
                  label="Uninstall"
                  severity="danger"
                  size="small"
                  outlined
                  @click="doUninstall(plugin)"
                  :loading="uninstalling && pendingInstall?.id === plugin.id"
                />

                <!-- Update (installed + newer version in repo) -->
                <Button
                  v-if="plugin.is_installed && hasUpdate(plugin)"
                  icon="pi pi-refresh"
                  label="Update"
                  severity="warn"
                  size="small"
                  @click="openUpdateDialog(plugin)"
                  :loading="installing && pendingInstall?.id === plugin.id"
                />

                <!-- Install (not installed) -->
                <Button
                  v-if="!plugin.is_installed"
                  icon="pi pi-download"
                  label="Install"
                  size="small"
                  @click="openInstallDialog(plugin)"
                  :loading="installing && pendingInstall?.id === plugin.id"
                />
              </div>
            </div>
          </div>
        </div>
      </template>
    </Card>
  </div>
</template>
      </div>
      <template #footer>
        <Button label="Abbrechen" severity="secondary" @click="showInstallDialog = false" />
        <Button
          label="Installieren"
          icon="pi pi-download"
          @click="startInstall"
          :loading="installing"
        />
      </template>
    </Dialog>

    <Card>
      <template #title>
        <div class="flex align-items-center gap-2">
          <i class="pi pi-puzzle text-primary" style="font-size: 1.5rem"></i>
          <span>Plugin Repository</span>
          <Button
            icon="pi pi-refresh"
            @click="refresh"
            :loading="pluginStore.loading"
            size="small"
            severity="secondary"
            text
            rounded
            v-tooltip.top="'Liste aktualisieren'"
          />
        </div>
      </template>

      <template #content>
        <!-- Fehler -->
        <Message v-if="pluginStore.error" severity="error" class="mb-4">
          {{ pluginStore.error }}
        </Message>

        <!-- Leerer State -->
        <div
          v-if="!pluginStore.loading && pluginStore.pluginList.length === 0"
          class="text-center py-8 text-color-secondary"
        >
          <i class="pi pi-inbox mb-3" style="font-size: 3rem; display:block"></i>
          <p>Keine Plugins im Repository gefunden.</p>
        </div>

        <!-- Plugin-Kacheln -->
        <div class="plugin-grid">
          <div
            v-for="plugin in pluginStore.pluginList"
            :key="plugin.id"
            class="plugin-tile"
          >
            <!-- Icon -->
            <div class="plugin-tile__icon">
              <img
                v-if="plugin.icon"
                :src="assetUrl(plugin.id, plugin.version ?? '1.0.0', plugin.icon)"
                :alt="plugin.name"
                width="48"
                height="48"
              />
              <i v-else class="pi pi-puzzle" style="font-size: 2.5rem; color: var(--p-primary-color)"></i>
            </div>

            <!-- Info -->
            <div class="plugin-tile__info">
              <div class="flex align-items-center gap-2">
                <h3 class="plugin-tile__name">{{ plugin.name }}</h3>
                <Tag
                  v-if="plugin.is_verified"
                  severity="success"
                  value="Verifiziert"
                  icon="pi pi-verified"
                  class="text-xs"
                  v-tooltip.top="'Prüfsumme wurde verifiziert'"
                />
                <Tag
                  v-else
                  severity="warn"
                  value="Nicht verifiziert"
                  icon="pi pi-exclamation-triangle"
                  class="text-xs"
                  v-tooltip.top="'Prüfsumme konnte nicht verifiziert werden'"
                />
              </div>
              <span class="plugin-tile__version">v{{ plugin.version }}</span>
              <p class="plugin-tile__desc">{{ plugin.description }}</p>

              <div class="plugin-tile__meta">
                <Tag
                  :severity="statusSeverity(plugin.status)"
                  :value="plugin.status"
                  class="text-xs"
                />
                <span class="text-xs text-color-secondary">
                  {{ plugin.scope?.type }}
                  <span v-if="plugin.scope?.target"> → {{ plugin.scope.target }}</span>
                </span>
              </div>

              <!-- Install / Installed button -->
              <div class="plugin-tile__actions mt-2">
                <Button
                  v-if="plugin.is_installed"
                  icon="pi pi-check"
                  label="Installiert"
                  severity="success"
                  size="small"
                  disabled
                  outlined
                />
                <Button
                  v-else
                  icon="pi pi-download"
                  label="Installieren"
                  size="small"
                  @click="openInstallDialog(plugin)"
                  :loading="installing && pendingInstall?.id === plugin.id"
                />
              </div>
            </div>
          </div>
        </div>
      </template>
    </Card>
  </div>
</template>

<script setup lang="ts">
import { onMounted, ref, computed } from 'vue'
import { useToast } from 'primevue/usetoast'
import { usePluginStore } from '../../store/plugins'
import { pluginApi, type PluginListEntry, type PoolEntry } from './plugin.api'

const pluginStore = usePluginStore()
const toast = useToast()

const assetUrl = (pluginId: string, version: string, iconPath: string) =>
  pluginApi.assetUrl(pluginId, version, iconPath.replace(`plugins/${pluginId}/${version}/`, ''))

const statusSeverity = (status: string) => {
  return { stable: 'success', development: 'warn', deprecated: 'danger' }[status] ?? 'info'
}

// -------------------------------------------------------------------------
// Pool (installed versions)
// -------------------------------------------------------------------------
const pool = ref<PoolEntry[]>([])

async function fetchPool() {
  try {
    pool.value = await pluginApi.listPool()
  } catch {
    pool.value = []
  }
}

/** Returns the installed version string for a plugin id, or null. */
function installedVersionFor(pluginId: string): string | null {
  const entry = pool.value.find(p => p.plugin_name_id === pluginId)
  return entry?.version ?? null
}

/** True when the repo version is strictly greater than the installed version. */
function hasUpdate(plugin: PluginListEntry): boolean {
  const installed = installedVersionFor(plugin.id)
  if (!installed) return false
  return semverGt(plugin.version, installed)
}

function semverGt(a: string, b: string): boolean {
  const parse = (v: string) => v.replace(/[^0-9.]/g, '').split('.').map(Number)
  const pa = parse(a)
  const pb = parse(b)
  for (let i = 0; i < Math.max(pa.length, pb.length); i++) {
    const diff = (pa[i] ?? 0) - (pb[i] ?? 0)
    if (diff !== 0) return diff > 0
  }
  return false
}

const refresh = async () => {
  await Promise.all([pluginStore.fetchPluginList(), fetchPool()])
}

// -------------------------------------------------------------------------
// Install / Update flow
// -------------------------------------------------------------------------
const scopeTypes = ['GLOBAL', 'TEMPLATE', 'MODULE', 'INSTANCE']

const showInstallDialog    = ref(false)
const showUnverifiedDialog = ref(false)
const installing           = ref(false)
const uninstalling         = ref(false)
const isUpdate             = ref(false)
const pendingInstall       = ref<PluginListEntry | null>(null)
const selectedVersion      = ref('')

const installForm = ref({
  scope_type:   'MODULE',
  scope_target: '',
})

/** All versions available in the repository for the pending plugin.
 *  Currently the API exposes one version per list entry, so we seed the
 *  dropdown with that version and the installed version (if different). */
const availableVersions = computed<string[]>(() => {
  if (!pendingInstall.value) return []
  const versions = new Set<string>()
  versions.add(pendingInstall.value.version)
  const installed = installedVersionFor(pendingInstall.value.id)
  if (installed) versions.add(installed)
  return Array.from(versions).sort((a, b) => (semverGt(a, b) ? -1 : 1))
})

function openInstallDialog(plugin: PluginListEntry) {
  pendingInstall.value  = plugin
  isUpdate.value        = false
  selectedVersion.value = plugin.version
  installForm.value     = { scope_type: 'MODULE', scope_target: '' }
  showInstallDialog.value = true
}

function openUpdateDialog(plugin: PluginListEntry) {
  pendingInstall.value  = plugin
  isUpdate.value        = true
  selectedVersion.value = plugin.version
  installForm.value     = { scope_type: 'MODULE', scope_target: '' }
  showInstallDialog.value = true
}

function startInstall() {
  if (!pendingInstall.value) return
  showInstallDialog.value = false
  if (!pendingInstall.value.is_verified) {
    showUnverifiedDialog.value = true
  } else {
    doInstall()
  }
}

async function confirmInstall() {
  showUnverifiedDialog.value = false
  await doInstall()
}

async function doInstall() {
  if (!pendingInstall.value) return
  installing.value = true
  try {
    await pluginApi.installPlugin({
      plugin_id:    pendingInstall.value.id,
      version:      selectedVersion.value,
      scope_type:   installForm.value.scope_type,
      scope_target: installForm.value.scope_target.trim() || undefined,
    })
    toast.add({
      severity: 'success',
      summary:  isUpdate.value ? 'Plugin updated' : 'Plugin installed',
      detail:   `${pendingInstall.value.name} v${selectedVersion.value} ${isUpdate.value ? 'updated' : 'installed'} successfully.`,
      life:     4000,
    })
    await refresh()
  } catch (err: any) {
    toast.add({
      severity: 'error',
      summary:  isUpdate.value ? 'Update failed' : 'Installation failed',
      detail:   err?.response?.data?.detail ?? String(err),
      life:     6000,
    })
  } finally {
    installing.value    = false
    pendingInstall.value = null
  }
}

async function doUninstall(plugin: PluginListEntry) {
  const version = installedVersionFor(plugin.id) ?? plugin.version
  uninstalling.value  = true
  pendingInstall.value = plugin
  try {
    await pluginApi.uninstallPlugin(plugin.id, version)
    toast.add({
      severity: 'success',
      summary:  'Plugin uninstalled',
      detail:   `${plugin.name} v${version} has been uninstalled.`,
      life:     4000,
    })
    await refresh()
  } catch (err: any) {
    toast.add({
      severity: 'error',
      summary:  'Uninstall failed',
      detail:   err?.response?.data?.detail ?? String(err),
      life:     6000,
    })
  } finally {
    uninstalling.value  = false
    pendingInstall.value = null
  }
}

onMounted(() => refresh())
</script>

<style scoped>
.plugin-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(280px, 1fr));
  gap: 1.25rem;
}

.plugin-tile {
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
  padding: 1.25rem;
  border: 1px solid var(--p-surface-border, #334155);
  border-radius: 12px;
  background: var(--p-surface-card, #1e293b);
  transition: border-color 0.2s, box-shadow 0.2s;
}

.plugin-tile:hover {
  border-color: var(--p-primary-color, #60a5fa);
  box-shadow: 0 0 0 1px var(--p-primary-color, #60a5fa22);
}

.plugin-tile__icon {
  display: flex;
  align-items: center;
  justify-content: center;
  width: 56px;
  height: 56px;
  border-radius: 10px;
  background: var(--p-surface-section, #0f172a);
  flex-shrink: 0;
}

.plugin-tile__info {
  flex: 1;
  display: flex;
  flex-direction: column;
  gap: 4px;
}

.plugin-tile__name {
  margin: 0;
  font-size: 1rem;
  font-weight: 600;
}

.plugin-tile__version {
  font-size: 0.75rem;
  color: var(--p-text-muted-color, #94a3b8);
  font-family: monospace;
}

.plugin-tile__desc {
  font-size: 0.8rem;
  color: var(--p-text-secondary-color, #cbd5e1);
  margin: 4px 0 0;
  line-height: 1.4;
}

.plugin-tile__meta {
  display: flex;
  align-items: center;
  gap: 8px;
  margin-top: 8px;
}

.plugin-tile__demo {
  margin-top: 4px;
}
</style>

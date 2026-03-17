<template>
  <div class="monitoring-view">
    <!-- Hardware Selection -->
    <Card class="mb-4">
      <template #title>
        <div class="flex align-items-center justify-content-between">
          <div class="flex align-items-center gap-2">
            <i class="pi pi-server text-primary"></i>
            <span>Hardware Monitoring</span>
          </div>
          <div class="flex align-items-center gap-3">
            <span class="text-sm text-500">Auto-Update: 5s</span>
            <Tag v-if="isLive" severity="success" value="LIVE" icon="pi pi-circle-fill" class="pulse-animation" />
            <Tag v-else severity="danger" value="OFFLINE" icon="pi pi-times-circle" />
          </div>
        </div>
      </template>
      <template #content>
        <div class="flex align-items-center gap-3">
          <span class="font-semibold">Hardware Node:</span>
          <Select 
            v-model="selectedNode" 
            :options="hardwareNodes" 
            optionLabel="label"
            optionValue="value"
            placeholder="Wähle Hardware Node"
            class="flex-1"
            @change="onNodeChange"
            :loading="loadingNodes"
          />
          <Button 
            icon="pi pi-refresh" 
            label="Refresh" 
            @click="fetchHardwareNodes"
            :loading="loadingNodes"
            size="small"
          />
        </div>
      </template>
    </Card>

    <!-- System Ressourcen -->
    <div class="grid">
      <div class="col-12 md:col-6 lg:col-3">
        <Card>
          <template #content>
            <div class="flex flex-column gap-2">
              <div class="flex align-items-center justify-content-between">
                <span class="text-600 font-semibold">CPU Auslastung</span>
                <Tag :value="`${systemStats.cpu}%`" :severity="getCpuSeverity(systemStats.cpu)" />
              </div>
              <ProgressBar :value="systemStats.cpu" :showValue="false" />
            </div>
          </template>
        </Card>
      </div>
      <div class="col-12 md:col-6 lg:col-3">
        <Card>
          <template #content>
            <div class="flex flex-column gap-2">
              <div class="flex align-items-center justify-content-between">
                <span class="text-600 font-semibold">RAM Auslastung</span>
                <Tag :value="`${systemStats.memory}%`" :severity="getMemorySeverity(systemStats.memory)" />
              </div>
              <ProgressBar :value="systemStats.memory" :showValue="false" />
              <div class="text-xs text-500">{%- raw %}{{ systemStats.memoryUsed }}{%- endraw %} / {%- raw %}{{ systemStats.memoryTotal }}{%- endraw %} GB</div>
            </div>
          </template>
        </Card>
      </div>
      <div class="col-12 md:col-6 lg:col-3">
        <Card>
          <template #content>
            <div class="flex flex-column gap-2">
              <div class="flex align-items-center justify-content-between">
                <span class="text-600 font-semibold">Festplatte</span>
                <Tag :value="`${systemStats.disk}%`" severity="info" />
              </div>
              <ProgressBar :value="systemStats.disk" :showValue="false" />
              <div class="text-xs text-500">{%- raw %}{{ systemStats.diskUsed }}{%- endraw %} / {%- raw %}{{ systemStats.diskTotal }}{%- endraw %} GB</div>
            </div>
          </template>
        </Card>
      </div>
      <div class="col-12 md:col-6 lg:col-3">
        <Card>
          <template #content>
            <div class="flex flex-column gap-2">
              <span class="text-600 font-semibold">Network</span>
              <div class="flex justify-content-between text-sm">
                <span>↓ {%- raw %}{{ systemStats.networkRx }}{%- endraw %} MB/s</span>
                <span>↑ {%- raw %}{{ systemStats.networkTx }}{%- endraw %} MB/s</span>
              </div>
              <ProgressBar :value="systemStats.networkPercent" :showValue="false" severity="success" />
            </div>
          </template>
        </Card>
      </div>
    </div>

    <!-- Module Feeds Tabs -->
    <Tabs value="0" class="mt-4">
      <TabList>
        <Tab value="0">Fehler</Tab>
        <Tab value="1">Neuigkeiten</Tab>
        <Tab value="2">Status</Tab>
        <Tab value="3">Alle Feeds</Tab>
      </TabList>
      <TabPanels>
        <TabPanel value="0">
          <ModuleFeedPanel
            :feeds="errorFeeds"
            title="Fehler-Meldungen"
            titleIcon="pi-times-circle"
            titleIconColor="text-red-500"
            badgeSeverity="danger"
            feedTypeLabel="Fehler"
          />
        </TabPanel>
        
        <TabPanel value="1">
          <ModuleFeedPanel
            :feeds="newsFeeds"
            title="Neuigkeiten"
            titleIcon="pi-bell"
            titleIconColor="text-green-500"
            badgeSeverity="success"
            feedTypeLabel="Neuigkeiten"
          />
        </TabPanel>
        
        <TabPanel value="2">
          <ModuleFeedPanel
            :feeds="stateFeeds"
            title="Status-Änderungen"
            titleIcon="pi-info-circle"
            titleIconColor="text-blue-500"
            badgeSeverity="info"
            feedTypeLabel="Status-Änderungen"
          />
        </TabPanel>
        
        <TabPanel value="3">
          <ModuleFeedPanel
            :feeds="allFeeds"
            title="Alle Module-Feeds"
            titleIcon="pi-list"
            titleIconColor="text-primary"
            badgeSeverity="info"
            feedTypeLabel="Feeds"
          />
        </TabPanel>
      </TabPanels>
    </Tabs>

    <!-- Module Status -->
    <div class="grid mt-4">
      <div class="col-12 lg:col-4">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-box"></i>
              <span>Module Status</span>
            </div>
          </template>
          <template #content>
            <div class="flex flex-column gap-3">
              <!-- Docker-level status rows -->
              <div class="flex align-items-center justify-content-between p-3 surface-100 border-round">
                <div class="flex align-items-center gap-2">
                  <i class="pi pi-check-circle text-green-500"></i>
                  <span>Laufend</span>
                </div>
                <Tag :value="containerStats.running" severity="success" />
              </div>
              <div class="flex align-items-center justify-content-between p-3 surface-100 border-round">
                <div class="flex align-items-center gap-2">
                  <i class="pi pi-pause text-orange-500"></i>
                  <span>Gestoppt</span>
                </div>
                <Tag :value="containerStats.stopped" severity="warning" />
              </div>
              <div class="flex align-items-center justify-content-between p-3 surface-100 border-round">
                <div class="flex align-items-center gap-2">
                  <i class="pi pi-times-circle text-red-500"></i>
                  <span>Fehler</span>
                </div>
                <Tag :value="containerStats.error" severity="danger" />
              </div>

              <!-- Live lifecycle / operational / health state counters -->
              <div class="border-top-1 surface-border pt-2">
                <div
                  class="flex align-items-center justify-content-between cursor-pointer py-1"
                  @click="showStateCounters = !showStateCounters"
                >
                  <span class="text-sm font-medium text-color-secondary">
                    <i class="pi pi-chart-bar mr-1" />
                    Live-Zustandszähler
                  </span>
                  <i :class="['pi', showStateCounters ? 'pi-chevron-up' : 'pi-chevron-down']" style="font-size: 0.75rem" />
                </div>

                <div v-if="showStateCounters" class="flex flex-column gap-2 mt-2">
                  <!-- Lifecycle -->
                  <span class="text-xs font-semibold text-color-secondary uppercase">Lifecycle</span>
                  <div
                    v-for="(count, state) in lifecycleCounters"
                    :key="'lc-' + state"
                    class="flex align-items-center justify-content-between px-2 py-1 surface-50 border-round"
                  >
                    <span class="text-sm">{%- raw %}{{ state }}{%- endraw %}</span>
                    <Tag :value="count" :severity="lifecycleSeverityMap[state] ?? 'secondary'" size="small" />
                  </div>

                  <!-- Operational -->
                  <span class="text-xs font-semibold text-color-secondary uppercase mt-1">Operational</span>
                  <div
                    v-for="(count, state) in operationalCounters"
                    :key="'op-' + state"
                    class="flex align-items-center justify-content-between px-2 py-1 surface-50 border-round"
                  >
                    <span class="text-sm">{%- raw %}{{ state }}{%- endraw %}</span>
                    <Tag :value="count" severity="secondary" size="small" />
                  </div>

                  <!-- Health -->
                  <span class="text-xs font-semibold text-color-secondary uppercase mt-1">Health</span>
                  <div
                    v-for="(count, state) in healthCounters"
                    :key="'h-' + state"
                    class="flex align-items-center justify-content-between px-2 py-1 surface-50 border-round"
                  >
                    <span class="text-sm">{%- raw %}{{ state }}{%- endraw %}</span>
                    <Tag
                      :value="count"
                      :severity="state === 'HEALTHY' ? 'success' : state === 'WARNING' ? 'warn' : 'danger'"
                      size="small"
                    />
                  </div>

                  <span v-if="stateFeeds.length === 0" class="text-sm text-color-secondary italic">
                    Keine Live-Daten verfügbar
                  </span>
                </div>
              </div>
            </div>
          </template>
        </Card>
      </div>

      <div class="col-12 lg:col-8">
        <Card>
          <template #title>
            <div class="flex align-items-center justify-content-between">
              <div class="flex align-items-center gap-2">
                <i class="pi pi-list"></i>
                <span>System Events</span>
              </div>
              <div class="flex gap-2">
                <Badge :value="errorFeeds.length" v-if="errorFeeds.length > 0" severity="danger" />
                <Badge :value="newsFeeds.length" v-if="newsFeeds.length > 0" severity="success" />
              </div>
            </div>
          </template>
          <template #content>
            <DataTable 
              :value="combinedLogs" 
              :paginator="true" 
              :rows="10" 
              stripedRows
              class="p-datatable-sm"
              sortField="timestamp" 
              :sortOrder="-1"
            >
              <Column field="timestamp" header="Zeit" sortable style="width: 12rem">
                <template #body="{ data }">
                  <span class="text-sm">{%- raw %}{{ formatLogTimestamp(data.timestamp) }}{%- endraw %}</span>
                </template>
              </Column>
              <Column field="type" header="Typ" sortable style="width: 8rem">
                <template #body="{ data }">
                  <Tag :value="data.type" :severity="getFeedTypeSeverity(data.type)" size="small" />
                </template>
              </Column>
              <Column field="module" header="Modul" sortable style="width: 12rem" />
              <Column field="message" header="Nachricht" />
            </DataTable>
          </template>
        </Card>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted, onUnmounted } from 'vue'
import Card from 'primevue/card'
import ProgressBar from 'primevue/progressbar'
import DataTable from 'primevue/datatable'
import Column from 'primevue/column'
import Button from 'primevue/button'
import Tag from 'primevue/tag'
import Badge from 'primevue/badge'
import Select from 'primevue/select'
import Tabs from 'primevue/tabs'
import TabList from 'primevue/tablist'
import Tab from 'primevue/tab'
import TabPanels from 'primevue/tabpanels'
import TabPanel from 'primevue/tabpanel'
import ModuleFeedPanel from '../../components/ModuleFeedPanel.vue'
import { useModuleFeed } from '../../composables/useModuleFeed'
import { lifecycleSeverity as lifecycleSeverityExport } from '../modules/useModuleActions'
import { monitoringApi } from './monitoring.api'
import type { ModuleFeed } from '../../types/common'

// Initialize WebSocket for feeds
const { 
  errorFeeds, 
  newsFeeds, 
  stateFeeds, 
  allFeeds, 
  connected: feedConnected 
} = useModuleFeed()

const selectedNode = ref<string | null>(null)
const hardwareNodes = ref<any[]>([])
const loadingNodes = ref(false)
const isLive = ref(false)
const showStateCounters = ref(false)

// Map lifecycle state (UPPERCASE) → PrimeVue Tag severity
const lifecycleSeverityMap = Object.fromEntries(
  Object.entries(lifecycleSeverityExport).map(([k, v]) => [k.toUpperCase(), v])
)

/** Count modules by lifecycle state from live feed (latest per module_id). */
const lifecycleCounters = computed<Record<string, number>>(() => {
  const latest: Record<string, string> = {}
  for (const feed of stateFeeds.value) {
    const lc = feed.data?.lifecycle ?? feed.data?.lifecycle_state
    if (lc && feed.module_id) latest[feed.module_id] = String(lc).toUpperCase()
  }
  const counts: Record<string, number> = {}
  for (const state of Object.values(latest)) {
    counts[state] = (counts[state] ?? 0) + 1
  }
  return counts
})

/** Count modules by operational state from live feed. */
const operationalCounters = computed<Record<string, number>>(() => {
  const latest: Record<string, string> = {}
  for (const feed of stateFeeds.value) {
    const op = feed.data?.operational ?? feed.data?.operational_state ?? feed.data?.current
    if (op && feed.module_id) latest[feed.module_id] = String(op).toUpperCase()
  }
  const counts: Record<string, number> = {}
  for (const state of Object.values(latest)) {
    counts[state] = (counts[state] ?? 0) + 1
  }
  return counts
})

/** Count modules by health state from live feed. */
const healthCounters = computed<Record<string, number>>(() => {
  const latest: Record<string, string> = {}
  for (const feed of stateFeeds.value) {
    const h = feed.data?.health ?? feed.data?.health_state
    if (h && feed.module_id) latest[feed.module_id] = String(h).toUpperCase()
  }
  const counts: Record<string, number> = {}
  for (const state of Object.values(latest)) {
    counts[state] = (counts[state] ?? 0) + 1
  }
  return counts
})

const systemStats = ref({
  cpu: 0,
  memory: 0,
  memoryUsed: 0,
  memoryTotal: 0,
  disk: 0,
  diskUsed: 0,
  diskTotal: 0,
  networkRx: 0,
  networkTx: 0,
  networkPercent: 0
})

const containerStats = ref({
  running: 0,
  stopped: 0,
  error: 0
})

const logs = ref<any[]>([])

// Combined logs from feeds and system logs
const combinedLogs = computed(() => {
  const feedLogs = [
    ...errorFeeds.value.map(f => ({
      timestamp: f.timestamp,
      type: 'ERROR',
      module: f.module_name || f.module_id,
      message: f.message,
      sortKey: new Date(f.timestamp).getTime()
    })),
    ...newsFeeds.value.map(f => ({
      timestamp: f.timestamp,
      type: 'NEWS',
      module: f.module_name || f.module_id,
      message: f.message,
      sortKey: new Date(f.timestamp).getTime()
    })),
    ...stateFeeds.value.map(f => ({
      timestamp: f.timestamp,
      type: 'STATE',
      module: f.module_name || f.module_id,
      message: f.message,
      sortKey: new Date(f.timestamp).getTime()
    }))
  ]
  
  // Sort by timestamp descending
  return feedLogs.sort((a, b) => b.sortKey - a.sortKey)
})

let updateInterval: NodeJS.Timeout | null = null

const fetchHardwareNodes = async () => {
  loadingNodes.value = true
  try {
    const nodes = await monitoringApi.getHardwareNodes()
    hardwareNodes.value = nodes.map(node => ({
      label: `${node.hostname} (${node.role}) - CPU: ${node.cpu_cores} cores, RAM: ${node.memory_total_gb}GB`,
      value: node.node_id,
      ...node
    }))
    
    // Auto-select first node if none selected
    if (!selectedNode.value && hardwareNodes.value.length > 0) {
      selectedNode.value = hardwareNodes.value[0].value
      await fetchNodeStats()
      await fetchModuleStats()
    }
  } catch (error) {
    console.error('Failed to fetch hardware nodes:', error)
  } finally {
    loadingNodes.value = false
  }
}

const fetchNodeStats = async () => {
  if (!selectedNode.value) return
  
  try {
    const stats = await monitoringApi.getNodeStats(selectedNode.value)
    
    // Update system stats
    systemStats.value.cpu = Math.round(stats.cpu?.percent || 0)
    systemStats.value.memory = Math.round(stats.memory?.percent || 0)
    systemStats.value.memoryUsed = ((stats.memory?.usage_mb || 0) / 1024).toFixed(1) as any
    systemStats.value.memoryTotal = ((stats.memory?.limit_mb || 0) / 1024).toFixed(1) as any
    systemStats.value.disk = Math.round(stats.disk?.percent || 0)
    systemStats.value.diskUsed = (((stats.disk?.total_mb || 0) - (stats.disk?.available_mb || 0)) / 1024).toFixed(1) as any
    systemStats.value.diskTotal = ((stats.disk?.total_mb || 0) / 1024).toFixed(1) as any
    systemStats.value.networkRx = (stats.network?.rx_mb_per_sec || 0).toFixed(1) as any
    systemStats.value.networkTx = (stats.network?.tx_mb_per_sec || 0).toFixed(1) as any
    systemStats.value.networkPercent = Math.min(100, Math.round((systemStats.value.networkRx + systemStats.value.networkTx) * 5))
    
    isLive.value = true
  } catch (error) {
    console.error('Failed to fetch node stats:', error)
    isLive.value = false
  }
}

const fetchModuleStats = async () => {
  if (!selectedNode.value) return
  
  try {
    const modules = await monitoringApi.getAllModuleStats()
    
    // Calculate module status
    const stats = {
      running: modules.filter(m => m.status === 'running').length,
      stopped: modules.filter(m => m.status === 'stopped' || m.status === 'exited').length,
      error: modules.filter(m => m.status === 'error' || m.status === 'failed').length
    }
    
    containerStats.value = stats
  } catch (error) {
    console.error('Failed to fetch module stats:', error)
  }
}

const onNodeChange = async () => {
  if (selectedNode.value) {
    await fetchNodeStats()
    await fetchModuleStats()
  }
}

const formatLogTimestamp = (timestamp: string): string => {
  try {
    const date = new Date(timestamp)
    return date.toLocaleString('de-DE', {
      day: '2-digit',
      month: '2-digit',
      hour: '2-digit',
      minute: '2-digit',
      second: '2-digit'
    })
  } catch (e) {
    return timestamp
  }
}

const getCpuSeverity = (value: number) => {
  if (value > 80) return 'danger'
  if (value > 60) return 'warning'
  return 'success'
}

const getMemorySeverity = (value: number) => {
  if (value > 85) return 'danger'
  if (value > 70) return 'warning'
  return 'info'
}

const getFeedTypeSeverity = (type: string) => {
  const severityMap: Record<string, string> = {
    ERROR: 'danger',
    NEWS: 'success',
    STATE: 'info'
  }
  return severityMap[type] || 'info'
}

const getLogSeverity = (level: string) => {
  const severityMap: Record<string, string> = {
    ERROR: 'danger',
    WARNING: 'warning',
    INFO: 'info',
    DEBUG: 'secondary'
  }
  return severityMap[level] || 'info'
}

onMounted(async () => {
  // Fetch hardware nodes on mount
  await fetchHardwareNodes()
  
  // Auto-update every 5 seconds
  updateInterval = setInterval(async () => {
    if (selectedNode.value) {
      await fetchNodeStats()
      await fetchModuleStats()
    }
  }, 5000)
})

onUnmounted(() => {
  if (updateInterval) {
    clearInterval(updateInterval)
  }
})
</script>

<style scoped>
.monitoring-view {
  animation: fadeIn 0.3s ease-in;
}

@keyframes fadeIn {
  from { opacity: 0; transform: translateY(20px); }
  to { opacity: 1; transform: translateY(0); }
}

.pulse-animation {
  animation: pulse 2s cubic-bezier(0.4, 0, 0.6, 1) infinite;
}

@keyframes pulse {
  0%, 100% { opacity: 1; }
  50% { opacity: 0.5; }
}
</style>

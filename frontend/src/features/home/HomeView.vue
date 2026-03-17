<template>
  <div class="home-view">
    <!-- Hero Section -->
    <!-- <Card class="hero-card mb-4">
      <template #content>
        <div class="text-center py-5">
          <i class="pi pi-cog" style="font-size: 4rem; color: var(--primary-color)"></i>
          <h1 class="mt-3 mb-2" style="font-size: 2.5rem">VYRA Module Manager</h1>
          <p class="text-600 text-xl">Zentrale Verwaltung aller VYRA Module und Repositories</p>
        </div>
      </template>
    </Card> -->

    <!-- Summary tiles -->
    <div class="summary-grid mb-4">

      <!-- Modules tile -->
      <div class="summary-tile summary-tile--blue cursor-pointer" @click="$router.push('/{{ module_name }}/modules')">
        <div class="summary-tile__icon bg-blue-100">
          <i class="pi pi-box text-blue-500 text-2xl"></i>
        </div>
        <div class="summary-tile__content">
          <div class="summary-tile__title">Module</div>
          <div class="summary-tile__number">{%- raw %}{{ stats.installed }}{%- endraw %}</div>
          <div class="summary-tile__detail">
            <span class="text-500 text-sm">Instanzen</span>
            <Divider layout="vertical" class="mx-2" style="height: 1rem" />
            <span class="text-cyan-600 font-semibold">{%- raw %}{{ stats.moduleTypes }}{%- endraw %}</span>
            <span class="text-500 text-sm ml-1">Typen</span>
          </div>
        </div>
        <div class="summary-tile__sub">
          <Tag :value="`${stats.active} aktiv`" severity="success" class="text-xs" />
        </div>
      </div>

      <!-- Plugins tile -->
      <div class="summary-tile summary-tile--purple cursor-pointer" @click="$router.push('/{{ module_name }}/installed-plugins')">
        <div class="summary-tile__icon bg-purple-100">
          <i class="pi pi-th-large text-purple-500 text-2xl"></i>
        </div>
        <div class="summary-tile__content">
          <div class="summary-tile__title">Plugins</div>
          <div class="summary-tile__number">{%- raw %}{{ stats.plugins }}{%- endraw %}</div>
          <div class="summary-tile__detail">
            <span class="text-500 text-sm">installiert</span>
          </div>
        </div>
        <div class="summary-tile__sub">
          <Tag :value="`${stats.pluginsActive} aktiv`" severity="success" class="text-xs" />
        </div>
      </div>

      <!-- Hardware tile -->
      <div class="summary-tile summary-tile--green cursor-pointer" @click="$router.push('/{{ module_name }}/monitoring')">
        <div class="summary-tile__icon bg-green-100">
          <i class="pi pi-server text-green-500 text-2xl"></i>
        </div>
        <div class="summary-tile__content">
          <div class="summary-tile__title">Hardware</div>
          <div class="summary-tile__number">{%- raw %}{{ stats.hardware }}{%- endraw %}</div>
          <div class="summary-tile__detail">
            <span class="text-500 text-sm">Nodes</span>
          </div>
        </div>
        <div class="summary-tile__sub">
          <Tag
            :value="stats.hardware > 0 ? `${stats.hardwareHealthy} gesund` : 'Keine'"
            :severity="stats.hardware > 0 ? 'success' : 'secondary'"
            class="text-xs"
          />
        </div>
      </div>

      <!-- Error Feeds tile -->
      <div
        class="summary-tile cursor-pointer"
        :class="stats.errorFeeds > 0 ? 'summary-tile--red' : 'summary-tile--neutral'"
        @click="$router.push('/{{ module_name }}/monitoring')"
      >
        <div class="summary-tile__icon" :class="stats.errorFeeds > 0 ? 'bg-red-100' : 'bg-surface-200'">
          <i
            class="pi pi-exclamation-triangle text-2xl"
            :class="stats.errorFeeds > 0 ? 'text-red-500' : 'text-500'"
          ></i>
        </div>
        <div class="summary-tile__content">
          <div class="summary-tile__title">Error Feeds</div>
          <div class="summary-tile__number" :class="stats.errorFeeds > 0 ? 'text-red-500' : ''">
            {%- raw %}{{ stats.errorFeeds }}{%- endraw %}
          </div>
          <div class="summary-tile__detail">
            <span class="text-500 text-sm">aktive Fehler</span>
          </div>
        </div>
        <div class="summary-tile__sub">
          <Tag
            :value="stats.errorFeeds > 0 ? 'Fehler vorhanden' : 'Alles ok'"
            :severity="stats.errorFeeds > 0 ? 'danger' : 'success'"
            class="text-xs"
          />
        </div>
      </div>

    </div>

    <!-- Quick Actions -->
    <!-- <Card class="mb-4">
      <template #title>
        <div class="flex align-items-center gap-2">
          <i class="pi pi-bolt"></i>
          <span>Schnellzugriff</span>
        </div>
      </template>
      <template #content>
        <div class="grid">
          <div class="col-12 md:col-4">
            <Card class="quick-action-card cursor-pointer hover:surface-hover" @click="$router.push('/{{ module_name }}/modules')">
              <template #content>
                <div class="text-center py-4">
                  <i class="pi pi-box" style="font-size: 3rem; color: var(--primary-color)"></i>
                  <h3 class="mt-3 mb-2">Module verwalten</h3>
                  <p class="text-600">Installierte Module starten, stoppen und konfigurieren</p>
                </div>
              </template>
            </Card>
          </div>

          <div class="col-12 md:col-4">
            <Card class="quick-action-card cursor-pointer hover:surface-hover" @click="$router.push('/{{ module_name }}/repository')">
              <template #content>
                <div class="text-center py-4">
                  <i class="pi pi-cloud-download" style="font-size: 3rem; color: var(--primary-color)"></i>
                  <h3 class="mt-3 mb-2">Repository</h3>
                  <p class="text-600">Neue Module & Plugins aus dem Repository installieren</p>
                </div>
              </template>
            </Card>
          </div>

          <div class="col-12 md:col-4">
            <Card class="quick-action-card cursor-pointer hover:surface-hover" @click="$router.push('/{{ module_name }}/monitoring')">
              <template #content>
                <div class="text-center py-4">
                  <i class="pi pi-chart-line" style="font-size: 3rem; color: var(--primary-color)"></i>
                  <h3 class="mt-3 mb-2">System-Monitoring</h3>
                  <p class="text-600">Performance und Logs überwachen</p>
                </div>
              </template>
            </Card>
          </div>
        </div>
      </template>
    </Card> -->

    <!-- Recent Errors -->
    <Card class="mb-4">
      <template #title>
        <div class="flex align-items-center gap-2">
          <i class="pi pi-exclamation-triangle text-red-500"></i>
          <span>Aktuelle Fehler</span>
          <Badge :value="recentErrors.length" severity="danger" />
        </div>
      </template>
      <template #content>
        <Timeline :value="recentErrors" align="left" class="customized-timeline">
          <template #marker>
            <span class="flex w-2rem h-2rem align-items-center justify-content-center text-white border-circle z-1 shadow-1"
                  :style="{ backgroundColor: 'var(--red-500)' }">
              <i class="pi pi-times"></i>
            </span>
          </template>
          <template #content="{ item }">
            <Card>
              <template #title>
                <div class="flex align-items-center justify-content-between">
                  <span class="text-lg">{%- raw %}{{ item.module_name }}{%- endraw %}</span>
                  <small class="text-500">{%- raw %}{{ formatTimestamp(item.timestamp) }}{%- endraw %}</small>
                </div>
              </template>
              <template #content>
                <p class="m-0 text-sm">{%- raw %}{{ item.message }}{%- endraw %}</p>
                <div v-if="item.feed_type" class="mt-2">
                  <Tag :value="item.feed_type" severity="danger" size="small" />
                </div>
              </template>
            </Card>
          </template>
        </Timeline>
      </template>
    </Card>
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import Card from 'primevue/card'
import Badge from 'primevue/badge'
import Tag from 'primevue/tag'
import Timeline from 'primevue/timeline'
import Divider from 'primevue/divider'
import { moduleInstanceApi } from '../modules/module.api'
import { pluginApi } from '../plugins/plugin.api'
import { monitoringApi } from '../monitoring/monitoring.api'
import { useModuleFeed } from '../../composables/useModuleFeed'

// Initialize WebSocket for feeds
const { errorFeeds } = useModuleFeed()

const stats = ref({
  installed:      0,
  active:         0,
  moduleTypes:    0,
  plugins:        0,
  pluginsActive:  0,
  hardware:       0,
  hardwareHealthy: 0,
  errorFeeds:     0,
})

// Get recent error feeds (last 10)
const recentErrors = computed(() => errorFeeds.value.slice(-10).reverse())

// Keep errorFeeds count in sync
const errorFeedsCount = computed(() => errorFeeds.value.length)

const formatTimestamp = (timestamp: string): string => {
  try {
    const date = new Date(timestamp)
    const now = new Date()
    const diff = now.getTime() - date.getTime()
    if (diff < 60000) return 'gerade eben'
    if (diff < 3600000) { const m = Math.floor(diff / 60000); return `vor ${m} Minute${m > 1 ? 'n' : ''}` }
    if (diff < 86400000) { const h = Math.floor(diff / 3600000); return `vor ${h} Stunde${h > 1 ? 'n' : ''}` }
    return date.toLocaleString('de-DE', { day: '2-digit', month: '2-digit', year: 'numeric', hour: '2-digit', minute: '2-digit' })
  } catch (e) { return timestamp }
}

onMounted(async () => {
  try {
    // Modules
    const modules = await moduleInstanceApi.getInstances(false)
    stats.value.moduleTypes = Object.keys(modules).length
    const allInstances = Object.values(modules).flat()
    stats.value.installed   = allInstances.length
    stats.value.active      = allInstances.filter(m => m.status === 'running').length
  } catch (e) { console.error('Failed to load module stats:', e) }

  try {
    // Plugins
    const pool        = await pluginApi.listPool()
    const assignments = await pluginApi.listAssignments()
    stats.value.plugins       = pool.length
    stats.value.pluginsActive = pool.filter(pe =>
      assignments.filter(a => a.p_id === pe.p_id).some(a => a.is_active)
    ).length
  } catch (e) { console.error('Failed to load plugin stats:', e) }

  try {
    // Hardware
    const nodes = await monitoringApi.getHardwareNodes()
    stats.value.hardware        = nodes.length
    stats.value.hardwareHealthy = nodes.filter(n => n.is_healthy).length
  } catch (e) { console.error('Failed to load hardware stats:', e) }

  // Error feeds are reactive — sync once after load
  stats.value.errorFeeds = errorFeedsCount.value
})
</script>

<style scoped>
.home-view {
  animation: fadeIn 0.3s ease-in;
}

@keyframes fadeIn {
  from { opacity: 0; transform: translateY(20px); }
  to { opacity: 1; transform: translateY(0); }
}

.hero-card {
  background: linear-gradient(135deg, var(--primary-color) 0%, var(--primary-600) 100%);
  color: white;
}

.hero-card :deep(.p-card-content) {
  padding: 2rem;
}

.quick-action-card {
  transition: all 0.2s;
  height: 100%;
}

.quick-action-card:hover {
  transform: translateY(-4px);
  box-shadow: 0 8px 16px rgba(0,0,0,0.1);
}

/* ── Summary tiles ──────────────────────────────────────────────────── */
.summary-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(220px, 1fr));
  gap: 1rem;
}

.summary-tile {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  padding: 1.25rem;
  border-radius: 0.875rem;
  background: var(--p-surface-card, #fff);
  border: 1px solid var(--p-surface-border, #e5e7eb);
  transition: box-shadow 0.15s, transform 0.15s;
}
.summary-tile:hover {
  box-shadow: 0 6px 20px rgba(0,0,0,.09);
  transform: translateY(-3px);
}

.summary-tile--blue  { border-top: 3px solid var(--p-blue-400, #60a5fa); }
.summary-tile--purple { border-top: 3px solid var(--p-purple-400, #a78bfa); }
.summary-tile--green  { border-top: 3px solid var(--p-green-400, #4ade80); }
.summary-tile--red    { border-top: 3px solid var(--p-red-400, #f87171); }
.summary-tile--neutral { border-top: 3px solid var(--p-surface-400, #9ca3af); }

.summary-tile__icon {
  width: 3rem;
  height: 3rem;
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: 50%;
  margin-bottom: 0.25rem;
}
.summary-tile__content { flex: 1; }
.summary-tile__title   { font-size: 0.85rem; color: var(--p-text-secondary-color, #6b7280); font-weight: 500; }
.summary-tile__number  { font-size: 2.25rem; font-weight: 700; color: var(--p-text-color, #111); line-height: 1; margin: 0.25rem 0; }
.summary-tile__detail  { display: flex; align-items: center; font-size: 0.8rem; }
.summary-tile__sub     { margin-top: auto; }
</style>

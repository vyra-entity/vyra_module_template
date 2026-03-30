<template>
  <Card>
    <template #title>
      <div class="flex align-items-center justify-content-between">
        <div class="flex align-items-center gap-2">
          <i :class="['pi', titleIcon, titleIconColor]"></i>
          <span>{%- raw %}{{ title }}{%- endraw %}</span>
          <Badge v-if="feeds.length > 0" :value="feeds.length" :severity="badgeSeverity" />
        </div>
        <div class="flex gap-2">
          <Select 
            v-if="showModuleFilter"
            v-model="selectedModule" 
            :options="moduleOptions" 
            optionLabel="label"
            optionValue="value"
            placeholder="Alle Module"
            class="w-12rem"
          />
          <Button 
            icon="pi pi-trash" 
            text 
            severity="secondary"
            size="small"
            @click="clearFeeds"
            v-tooltip.top="'Alle löschen'"
          />
        </div>
      </div>
    </template>
    <template #content>
      <div class="feed-scroll-container">
        <div v-if="filteredFeeds.length === 0" class="text-center py-5 text-500">
          <i class="pi pi-inbox text-4xl mb-3 block"></i>
          <p>Keine {%- raw %}{{ feedTypeLabel }}{%- endraw %} vorhanden</p>
        </div>
        
        <Timeline 
          v-else
          :value="filteredFeeds" 
          align="left"
          class="customized-timeline"
        >
          <template #marker="{ item }">
            <span class="flex w-2rem h-2rem align-items-center justify-content-center text-white border-circle z-1 shadow-1"
                  :style="{ backgroundColor: getMarkerColor(item) }">
              <i :class="['pi', getMarkerIcon(item)]"></i>
            </span>
          </template>
          <template #content="{ item }">
            <Card class="mb-2">
              <template #title>
                <div class="flex align-items-center justify-content-between">
                  <span class="text-base">{%- raw %}{{ item.module_name }}{%- endraw %}</span>
                  <small class="text-500 font-normal">{%- raw %}{{ formatTimestamp(item.timestamp) }}{%- endraw %}</small>
                </div>
              </template>
              <template #content>
                <p class="m-0 text-sm">
                  {%- raw %}{{ item.message || getFallbackMessage(item) }}{%- endraw %}
                </p>
                <div class="mt-2 flex gap-2">
                  <Tag :value="item.feed_type" :severity="getTagSeverity(item.feed_type)" size="small" />
                  <Tag v-if="item.module_id" :value="item.module_id.substring(0, 8)" severity="info" size="small" />
                </div>
              </template>
            </Card>
          </template>
        </Timeline>
      </div>
    </template>
  </Card>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'
import Card from 'primevue/card'
import Badge from 'primevue/badge'
import Tag from 'primevue/tag'
import Button from 'primevue/button'
import Select from 'primevue/select'
import Timeline from 'primevue/timeline'
import type { ModuleFeed } from '../types/common'

interface Props {
  feeds: ModuleFeed[]
  title?: string
  titleIcon?: string
  titleIconColor?: string
  badgeSeverity?: 'success' | 'info' | 'warning' | 'danger' | 'secondary'
  feedTypeLabel?: string
  showModuleFilter?: boolean
}

const props = withDefaults(defineProps<Props>(), {
  title: 'Module Feeds',
  titleIcon: 'pi-bell',
  titleIconColor: 'text-primary',
  badgeSeverity: 'info',
  feedTypeLabel: 'Feeds',
  showModuleFilter: true
})

const emit = defineEmits<{
  clear: []
}>()

const selectedModule = ref<string | null>(null)

const moduleOptions = computed(() => {
  const modules = new Set(props.feeds.map(f => f.module_name))
  return [
    { label: 'Alle Module', value: null },
    ...Array.from(modules).map(m => ({ label: m, value: m }))
  ]
})

const filteredFeeds = computed(() => {
  if (!selectedModule.value) {
    return props.feeds
  }
  return props.feeds.filter(f => f.module_name === selectedModule.value)
})

const clearFeeds = () => {
  emit('clear')
}

const getFallbackMessage = (item: ModuleFeed): string => {
  if (!item.data) return ''
  // Try common field names from different feeder types
  return (
    (item.data.current as string) ||
    (item.data.lifecycle_state as string) ||
    (item.data.status as string) ||
    (item.data.error as string) ||
    (item.data.news as string) ||
    (item.data.content as string) ||
    ''
  )
}

const formatTimestamp = (timestamp: string): string => {
  try {
    const date = new Date(timestamp)
    const now = new Date()
    const diff = now.getTime() - date.getTime()
    
    if (diff < 60000) return 'gerade eben'
    if (diff < 3600000) {
      const minutes = Math.floor(diff / 60000)
      return `vor ${minutes}min`
    }
    if (diff < 86400000) {
      const hours = Math.floor(diff / 3600000)
      return `vor ${hours}h`
    }
    return date.toLocaleString('de-DE', {
      day: '2-digit',
      month: '2-digit',
      hour: '2-digit',
      minute: '2-digit'
    })
  } catch (e) {
    return timestamp
  }
}

const getMarkerColor = (item: ModuleFeed): string => {
  const colorMap: Record<string, string> = {
    error: 'var(--red-500)',
    warning: 'var(--yellow-500)',
    state: 'var(--blue-500)',
    news: 'var(--green-500)'
  }
  return colorMap[item.feed_type] || 'var(--gray-500)'
}

const getMarkerIcon = (item: ModuleFeed): string => {
  const iconMap: Record<string, string> = {
    error: 'pi-times',
    warning: 'pi-exclamation-triangle',
    state: 'pi-info-circle',
    news: 'pi-bell'
  }
  return iconMap[item.feed_type] || 'pi-circle'
}

const getTagSeverity = (feedType: string): 'success' | 'info' | 'warning' | 'danger' => {
  const severityMap: Record<string, 'success' | 'info' | 'warning' | 'danger'> = {
    error: 'danger',
    warning: 'warning',
    state: 'info',
    news: 'success'
  }
  return severityMap[feedType] || 'info'
}
</script>

<style scoped>
.feed-scroll-container {
  max-height: 420px;
  overflow-y: auto;
  overflow-x: hidden;
  padding-right: 0.25rem;
}

.feed-scroll-container::-webkit-scrollbar {
  width: 6px;
}

.feed-scroll-container::-webkit-scrollbar-track {
  background: var(--surface-ground);
  border-radius: 3px;
}

.feed-scroll-container::-webkit-scrollbar-thumb {
  background: var(--surface-400);
  border-radius: 3px;
}

.customized-timeline :deep(.p-timeline-event-content) {
  width: 100%;
}

.customized-timeline :deep(.p-timeline-event-opposite) {
  display: none;
}
</style>

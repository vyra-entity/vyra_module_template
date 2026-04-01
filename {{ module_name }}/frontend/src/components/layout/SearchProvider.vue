<template>
  <!-- Global search dialog (CMD+K) aggregating search-provider plugin results -->
  <Dialog
    v-model:visible="isOpen"
    modal
    :closable="false"
    :show-header="false"
    class="search-dialog"
    :pt="{ root: { class: 'search-dialog-root' } }"
    @keydown.escape="close()"
  >
    <div class="search-container">
      <div class="search-input-row">
        <i class="pi pi-search search-icon" />
        <input
          ref="inputRef"
          v-model="query"
          type="text"
          class="search-input"
          placeholder="Search…"
          @keydown.enter="executeFirst()"
          @keydown.escape="close()"
          @keydown.up.prevent="moveCursor(-1)"
          @keydown.down.prevent="moveCursor(1)"
        />
        <kbd class="search-kbd">ESC</kbd>
      </div>

      <!-- Plugin-provided results -->
      <ul v-if="results.length > 0" class="search-results">
        <li
          v-for="(result, idx) in results"
          :key="result.id"
          class="search-result-item"
          :class="{ active: cursor === idx }"
          @click="executeResult(result)"
          @mouseenter="cursor = idx"
        >
          <i v-if="result.icon" :class="result.icon" class="result-icon" />
          <div class="result-text">
            <span class="result-title">{{ result.title }}</span>
            <span v-if="result.description" class="result-desc">{{ result.description }}</span>
          </div>
        </li>
      </ul>

      <div v-else-if="query.length > 0" class="search-empty">No results</div>
    </div>
  </Dialog>
</template>

<script setup lang="ts">
import { ref, watch, nextTick } from 'vue'
import { useRouter } from 'vue-router'
import Dialog from 'primevue/dialog'
import type { SearchResult } from '../../types/plugin_slots'

const router = useRouter()
const isOpen = ref(false)
const query = ref('')
const results = ref<SearchResult[]>([])
const cursor = ref(0)
const inputRef = ref<HTMLInputElement | null>(null)

/** Open the search dialog. Called externally or via the keyboard shortcut. */
function open() {
  isOpen.value = true
  query.value = ''
  results.value = []
  cursor.value = 0
  nextTick(() => inputRef.value?.focus())
}

function close() {
  isOpen.value = false
  query.value = ''
  results.value = []
}

function moveCursor(delta: number) {
  cursor.value = Math.max(0, Math.min(results.value.length - 1, cursor.value + delta))
}

function executeResult(result: SearchResult) {
  if (typeof result.action === 'function') {
    result.action()
  } else {
    router.push(result.action)
  }
  close()
}

function executeFirst() {
  if (results.value[cursor.value]) executeResult(results.value[cursor.value])
}

/**
 * Receive results pushed by a search-provider plugin.
 * Plugin call: `pluginApi.events.searchResults(results)` (future extension point).
 */
function receiveResults(newResults: SearchResult[]) {
  results.value = [...newResults]
  cursor.value = 0
}

// ── Global keyboard shortcut (Ctrl+K / Cmd+K) ─────────────────────────────
function _handleKeydown(e: KeyboardEvent) {
  if ((e.ctrlKey || e.metaKey) && e.key === 'k') {
    e.preventDefault()
    isOpen.value ? close() : open()
  }
}
// Register on mount; call this component from App.vue via ref if needed.
import { onMounted, onUnmounted } from 'vue'
onMounted(() => window.addEventListener('keydown', _handleKeydown))
onUnmounted(() => window.removeEventListener('keydown', _handleKeydown))

defineExpose({ open, close, receiveResults })
</script>

<style>
/* global (not scoped) so the PrimeVue dialog root is styled */
.search-dialog-root {
  width: 560px;
  max-width: 95vw;
  border-radius: 12px;
  overflow: hidden;
  padding: 0 !important;
}
</style>

<style scoped>
.search-container {
  display: flex;
  flex-direction: column;
}

.search-input-row {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  padding: 0.75rem 1rem;
  border-bottom: 1px solid var(--surface-border, #e0e0e0);
}

.search-icon {
  color: var(--text-color-secondary, #999);
  font-size: 1rem;
  flex-shrink: 0;
}

.search-input {
  flex: 1;
  border: none;
  outline: none;
  background: transparent;
  font-size: 1rem;
  color: var(--text-color, #212121);
}

.search-kbd {
  font-size: 0.7rem;
  background: var(--surface-border, #e0e0e0);
  border-radius: 4px;
  padding: 0.15rem 0.4rem;
  color: var(--text-color-secondary, #777);
  flex-shrink: 0;
}

.search-results {
  list-style: none;
  margin: 0;
  padding: 0.5rem 0;
  max-height: 360px;
  overflow-y: auto;
}

.search-result-item {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  padding: 0.6rem 1rem;
  cursor: pointer;
  border-radius: 6px;
  margin: 0 0.5rem;
}
.search-result-item.active,
.search-result-item:hover {
  background: var(--primary-50, #eff6ff);
}

.result-icon { font-size: 1rem; color: var(--text-color-secondary, #666); }

.result-text {
  display: flex;
  flex-direction: column;
  gap: 0.15rem;
}
.result-title { font-size: 0.9rem; font-weight: 500; color: var(--text-color, #212121); }
.result-desc { font-size: 0.78rem; color: var(--text-color-secondary, #777); }

.search-empty {
  padding: 1.5rem 1rem;
  text-align: center;
  color: var(--text-color-secondary, #999);
  font-size: 0.9rem;
}
</style>

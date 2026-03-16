/**
 * Pinia Store for Module Feeds
 *
 * Manages state, error, and news feeds from registered modules.
 * Owns the single WebSocket connection to /ws/module_feed so that multiple
 * components using useModuleFeed() never create duplicate connections.
 *
 * Connection life-cycle uses ref-counting:
 *   Component mounts  → connectWs()  → consumerCount++, opens WS if not open
 *   Component unmounts → disconnectWs() → consumerCount--, closes WS when 0
 */
import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import type { ModuleFeed } from '../types/common'

// ─── Helpers ──────────────────────────────────────────────────────────────────

function buildWsUrl(): string {
  const isViteDevServer = window.location.port === '3001' || window.location.port === '3000'
  if (isViteDevServer) {
    return `ws://${window.location.hostname}:${window.location.port}/{{ module_name }}/ws/module_feed`
  }
  const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:'
  return `${protocol}//${window.location.host}/{{ module_name }}/ws/module_feed`
}

// ─── Store ─────────────────────────────────────────────────────────────────────

export const useModuleFeedStore = defineStore('moduleFeed', () => {
  // ── Feed state ──────────────────────────────────────────────────────────────
  const feeds = ref<ModuleFeed[]>([])
  const maxFeeds = ref(1000)

  // ── WS connection state ────────────────────────────────────────────────────
  const wsConnected = ref(false)
  let _ws: WebSocket | null = null
  let _reconnectTimer: ReturnType<typeof setTimeout> | null = null
  let _pingInterval: ReturnType<typeof setInterval> | null = null
  let _consumerCount = 0

  // ── Feed computed ──────────────────────────────────────────────────────────
  const stateFeeds = computed(() => feeds.value.filter(f => f.feed_type === 'state'))
  const errorFeeds = computed(() => feeds.value.filter(f => f.feed_type === 'error'))
  const newsFeeds  = computed(() => feeds.value.filter(f => f.feed_type === 'news'))
  const allFeeds   = computed(() => feeds.value)

  const latestState = computed(() => stateFeeds.value.at(-1) ?? null)
  const latestError = computed(() => errorFeeds.value.at(-1) ?? null)
  const latestNews  = computed(() => newsFeeds.value.at(-1) ?? null)

  const getLatestStateByModule = computed(() => (moduleId: string) => {
    const s = stateFeeds.value.filter(f => f.module_id === moduleId)
    return s.at(-1) ?? null
  })

  const getFeedsByModule = computed(() => (moduleId: string) =>
    feeds.value.filter(f => f.module_id === moduleId)
  )

  // ── Feed actions ───────────────────────────────────────────────────────────
  function addFeed(feed: ModuleFeed) {
    feeds.value.push(feed)
    if (feeds.value.length > maxFeeds.value) {
      feeds.value = feeds.value.slice(-maxFeeds.value)
    }
  }

  /** Add many feeds at once (history_batch). */
  function addFeedBatch(batch: ModuleFeed[]) {
    feeds.value.push(...batch)
    if (feeds.value.length > maxFeeds.value) {
      feeds.value = feeds.value.slice(-maxFeeds.value)
    }
  }

  function clearFeeds() { feeds.value = [] }
  function clearFeedsByModule(moduleId: string) {
    feeds.value = feeds.value.filter(f => f.module_id !== moduleId)
  }
  function clearFeedsByType(feedType: 'state' | 'error' | 'news') {
    feeds.value = feeds.value.filter(f => f.feed_type !== feedType)
  }

  // ── WS message handler ─────────────────────────────────────────────────────
  function _handleMessage(event: MessageEvent) {
    try {
      const msg = JSON.parse(event.data as string)

      if (msg.type === 'pong') return

      if (msg.type === 'module_feed' && msg.data) {
        addFeed(msg.data as ModuleFeed)
        return
      }

      // history_batch: server sends all history items in one frame
      if (msg.type === 'history_batch' && Array.isArray(msg.items)) {
        addFeedBatch(msg.items as ModuleFeed[])
        console.log(`📚 Received history_batch: ${msg.items.length} items`)
        return
      }

      // state_snapshot: current state of all installed modules
      if (msg.type === 'state_snapshot' && msg.states) {
        const now = new Date().toISOString()
        for (const [moduleId, stateData] of Object.entries(msg.states as Record<string, Record<string, unknown>>)) {
          // Only add if we don't already have a recent state for this module
          const existing = getLatestStateByModule.value(moduleId)
          if (!existing) {
            addFeed({
              module_id: moduleId,
              module_name: (stateData.module_name as string) || moduleId,
              feed_type: 'state',
              message: (stateData.current as string) || (stateData.status as string) || 'unknown',
              timestamp: (stateData.timestamp as string) || now,
              data: stateData as Record<string, unknown>,
            } as ModuleFeed)
          }
        }
        return
      }
    } catch (e) {
      console.error('moduleFeed store: failed to parse WS message', e)
    }
  }

  // ── WS connection management ───────────────────────────────────────────────
  function _openConnection() {
    if (_ws && _ws.readyState <= WebSocket.OPEN) return

    const url = buildWsUrl()
    console.log('📡 moduleFeed: opening WS connection to', url)
    _ws = new WebSocket(url)

    _ws.onopen = () => {
      wsConnected.value = true
      console.log('✅ moduleFeed WS connected')
      _pingInterval = setInterval(() => {
        if (_ws?.readyState === WebSocket.OPEN) {
          _ws.send(JSON.stringify({ type: 'ping' }))
        }
      }, 30_000)
    }

    _ws.onmessage = _handleMessage

    _ws.onerror = () => console.error('moduleFeed WS error')

    _ws.onclose = () => {
      wsConnected.value = false
      if (_pingInterval) { clearInterval(_pingInterval); _pingInterval = null }
      console.log('❌ moduleFeed WS closed')
      if (_consumerCount > 0) {
        _reconnectTimer = setTimeout(() => {
          console.log('🔄 moduleFeed WS reconnecting…')
          _openConnection()
        }, 5_000)
      }
    }
  }

  function _closeConnection() {
    if (_reconnectTimer) { clearTimeout(_reconnectTimer); _reconnectTimer = null }
    if (_pingInterval)   { clearInterval(_pingInterval);  _pingInterval = null }
    if (_ws) { _ws.close(); _ws = null }
    wsConnected.value = false
  }

  /** Called by each consuming component on mount. */
  function connectWs() {
    _consumerCount++
    _openConnection()
  }

  /** Called by each consuming component on unmount. */
  function disconnectWs() {
    _consumerCount = Math.max(0, _consumerCount - 1)
    if (_consumerCount === 0) {
      _closeConnection()
    }
  }

  // ── Expose ─────────────────────────────────────────────────────────────────
  return {
    // Feed state
    feeds,
    maxFeeds,

    // Feed computed
    stateFeeds,
    errorFeeds,
    newsFeeds,
    allFeeds,
    latestState,
    latestError,
    latestNews,
    getLatestStateByModule,
    getFeedsByModule,

    // Feed actions
    addFeed,
    addFeedBatch,
    clearFeeds,
    clearFeedsByModule,
    clearFeedsByType,

    // WS
    wsConnected,
    connectWs,
    disconnectWs,
  }
})


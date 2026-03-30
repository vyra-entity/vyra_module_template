/**
 * Composable for receiving real-time module feed updates via WebSocket.
 *
 * The WebSocket connection is managed as a SINGLETON inside the Pinia store
 * (useModuleFeedStore). This composable is a thin convenience wrapper:
 *   - Calls store.connectWs() on mount (ref-counted — no duplicate connections)
 *   - Calls store.disconnectWs() on unmount
 *   - Exposes the same API as before for backwards-compatible usage
 */
import { computed, onMounted, onUnmounted } from 'vue'
import { useModuleFeedStore } from '../store/moduleFeed'

export function useModuleFeed() {
  const feedStore = useModuleFeedStore()

  onMounted(() => feedStore.connectWs())
  onUnmounted(() => feedStore.disconnectWs())

  return {
    connected: computed(() => feedStore.wsConnected),

    // Feed data (computed from store)
    stateFeeds: computed(() => feedStore.stateFeeds),
    errorFeeds: computed(() => feedStore.errorFeeds),
    newsFeeds:  computed(() => feedStore.newsFeeds),
    allFeeds:   computed(() => feedStore.allFeeds),

    // Store getters
    getLatestStateByModule: feedStore.getLatestStateByModule,
    getFeedsByModule:       feedStore.getFeedsByModule,

    // Actions
    connect:             () => feedStore.connectWs(),
    disconnect:          () => feedStore.disconnectWs(),
    clearFeeds:          feedStore.clearFeeds,
    clearFeedsByModule:  feedStore.clearFeedsByModule,
  }
}


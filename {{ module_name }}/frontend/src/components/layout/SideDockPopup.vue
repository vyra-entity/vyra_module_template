<template>
  <!-- Side-Dock-Popup (SDP): right-side fly-in panel -->
  <Teleport to="body">
    <Transition name="sdp-slide">
      <aside
        v-if="sdpStore.isPanelOpen"
        class="sdp-panel"
        role="complementary"
        aria-label="Side Dock Popup"
      >
        <!-- Panel header -->
        <div class="sdp-panel-header">
          <span class="sdp-panel-title">Plugins</span>
          <button
            class="sdp-close-btn"
            @click="sdpStore.closePanel()"
            aria-label="Panel schließen"
          >
            <i class="pi pi-times" />
          </button>
        </div>

        <!-- Sections: header → content → footer -->
        <div class="sdp-sections">
          <template v-for="section in SECTIONS" :key="section">
            <template v-if="pocketsFor(section).length > 0">
              <div class="sdp-section">
                <div
                  v-for="pocket in pocketsFor(section)"
                  :key="pocket.id"
                  class="sdp-pocket"
                  :class="{
                    'sdp-pocket--open': pocket.isOpen,
                    'sdp-pocket--pinned': pocket.isPinned,
                  }"
                >
                  <!-- Trigger row -->
                  <div
                    class="sdp-pocket-trigger"
                    @click="pocket.isOpen ? sdpStore.closePocket(pocket.id) : sdpStore.openPocket(pocket.id)"
                  >
                    <i :class="pocket.icon" class="sdp-pocket-icon" />
                    <span class="sdp-pocket-title">{{ pocket.title }}</span>
                    <div class="sdp-pocket-actions">
                      <button
                        v-if="pocket.isPinnable"
                        class="sdp-pin-btn"
                        :class="{ active: pocket.isPinned }"
                        @click.stop="pocket.isPinned ? sdpStore.unpinPocket(pocket.id) : sdpStore.pinPocket(pocket.id)"
                        :aria-label="pocket.isPinned ? 'Unpin' : 'Pin'"
                      >
                        <i :class="pocket.isPinned ? 'pi pi-lock' : 'pi pi-lock-open'" />
                      </button>
                      <i
                        :class="pocket.isOpen ? 'pi pi-chevron-up' : 'pi pi-chevron-down'"
                        class="sdp-chevron"
                      />
                    </div>
                  </div>
                  <!-- Pocket body -->
                  <div v-if="pocket.isOpen" class="sdp-pocket-body">
                    <component
                      :is="pocket.component"
                      :sdpApi="sdpStore.getPocketApi(pocket.id)"
                    />
                  </div>
                </div>
                <!-- Overflow indicator -->
                <div v-if="overflowFor(section) > 0" class="sdp-overflow">
                  +{{ overflowFor(section) }} more
                </div>
              </div>
            </template>
          </template>
        </div>
      </aside>
    </Transition>

    <!-- Backdrop (click-outside to close) -->
    <Transition name="sdp-fade">
      <div
        v-if="sdpStore.isPanelOpen"
        class="sdp-backdrop"
        @click="sdpStore.closePanel()"
      />
    </Transition>
  </Teleport>
</template>

<script setup lang="ts">
import { computed } from 'vue'
import { useRoute } from 'vue-router'
import {
  useSideDockPopupStore,
  SDP_MAX_POCKETS_PER_SECTION,
} from '../../store/sideDockPopup'
import type { SdpSection, SdpPocket } from '../../store/sideDockPopup'

const SECTIONS: SdpSection[] = ['header', 'content', 'footer']

const sdpStore = useSideDockPopupStore()
const route = useRoute()
const activeContext = computed(() => String(route.name ?? route.path))

function pocketsFor(section: SdpSection): SdpPocket[] {
  return sdpStore
    .pocketsInSection(section, activeContext.value)
    .slice(0, SDP_MAX_POCKETS_PER_SECTION)
}

function overflowFor(section: SdpSection): number {
  return sdpStore.overflowCount(section, activeContext.value)
}
</script>

<style scoped>
/* ── Panel ── */
.sdp-panel {
  position: fixed;
  top: 0;
  right: 0;
  width: 320px;
  height: 100vh;
  background: var(--surface-card, #fff);
  border-left: 1px solid var(--surface-border, #e0e0e0);
  box-shadow: -4px 0 24px rgba(0, 0, 0, 0.12);
  z-index: 1200;
  display: flex;
  flex-direction: column;
  overflow: hidden;
}

.sdp-panel-header {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 0.75rem 1rem;
  border-bottom: 1px solid var(--surface-border, #e0e0e0);
  flex-shrink: 0;
}

.sdp-panel-title {
  font-weight: 600;
  font-size: 0.9rem;
  color: var(--text-color, #212121);
}

.sdp-close-btn {
  background: none;
  border: none;
  cursor: pointer;
  color: var(--text-color-secondary, #666);
  padding: 0.25rem;
  border-radius: 4px;
  display: flex;
  align-items: center;
}
.sdp-close-btn:hover {
  background: var(--surface-hover, #f5f5f5);
}

/* ── Sections ── */
.sdp-sections {
  flex: 1;
  overflow-y: auto;
  padding: 0.5rem 0;
}

.sdp-section {
  padding: 0 0.5rem;
}

/* ── Pocket ── */
.sdp-pocket {
  border-radius: 6px;
  margin-bottom: 2px;
  overflow: hidden;
}

.sdp-pocket-trigger {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  padding: 0.6rem 0.75rem;
  cursor: pointer;
  border-radius: 6px;
  user-select: none;
}
.sdp-pocket-trigger:hover {
  background: var(--surface-hover, #f5f5f5);
}

.sdp-pocket--open > .sdp-pocket-trigger {
  background: var(--primary-50, #eff6ff);
  color: var(--primary-color, #3b82f6);
}

.sdp-pocket-icon {
  font-size: 1rem;
  flex-shrink: 0;
}
.sdp-pocket-title {
  flex: 1;
  font-size: 0.85rem;
  font-weight: 500;
}
.sdp-pocket-actions {
  display: flex;
  align-items: center;
  gap: 0.25rem;
}

.sdp-pin-btn {
  background: none;
  border: none;
  cursor: pointer;
  padding: 0.2rem;
  border-radius: 4px;
  color: var(--text-color-secondary, #999);
  font-size: 0.75rem;
  display: flex;
}
.sdp-pin-btn.active {
  color: var(--primary-color, #3b82f6);
}
.sdp-chevron {
  font-size: 0.7rem;
  color: var(--text-color-secondary, #999);
}

.sdp-pocket-body {
  padding: 0.5rem 0.75rem 0.75rem;
  border-top: 1px solid var(--surface-border, #e0e0e0);
}

.sdp-pocket--pinned {
  border: 1px solid var(--primary-200, #bfdbfe);
  border-radius: 6px;
}

.sdp-overflow {
  font-size: 0.75rem;
  color: var(--text-color-secondary, #999);
  padding: 0.25rem 0.75rem;
  text-align: center;
}

/* ── Backdrop ── */
.sdp-backdrop {
  position: fixed;
  inset: 0;
  z-index: 1199;
  background: rgba(0, 0, 0, 0.2);
}

/* ── Transitions ── */
.sdp-slide-enter-active,
.sdp-slide-leave-active {
  transition: transform 0.25s ease;
}
.sdp-slide-enter-from,
.sdp-slide-leave-to {
  transform: translateX(100%);
}

.sdp-fade-enter-active,
.sdp-fade-leave-active {
  transition: opacity 0.2s ease;
}
.sdp-fade-enter-from,
.sdp-fade-leave-to {
  opacity: 0;
}
</style>

<template>
  <!-- Side-Dock-Popup (SDP): floating icon tabs pinned to the right edge.
       Each registered pocket becomes an independent floating widget:
       - Icon tab always visible on the right edge.
       - Hover: label slides out to the left.
       - Click: popup panel opens to the left of the strip.
       - Pinned: popup stays open; main content remains fully accessible.
       - Not pinned + click outside: backdrop catches clicks → close all unpinned. -->
  <Teleport to="body">
    <!-- Global backdrop — semi-transparent, only when an unpinned pocket is open -->
    <Transition name="sdp-fade">
      <div
        v-if="hasUnpinnedOpen"
        class="sdp-backdrop"
        @click="sdpStore.closeAllUnpinned()"
        aria-hidden="true"
      />
    </Transition>

    <!-- Right-edge strip: one widget per visible pocket -->
    <div class="sdp-strip" role="complementary" aria-label="Side Dock Widgets">
      <div
        v-for="pocket in visiblePockets"
        :key="pocket.id"
        class="sdp-widget"
        :class="{
          'sdp-widget--open': pocket.isOpen,
          'sdp-widget--pinned': pocket.isPinned,
        }"
      >
        <!-- Always-visible tab (icon + slide-out label) -->
        <button
          class="sdp-tab"
          @click="togglePocket(pocket)"
          :aria-label="pocket.title"
          :title="pocket.title"
          :aria-expanded="pocket.isOpen"
        >
          <i :class="pocket.icon" class="sdp-tab-icon" aria-hidden="true" />
          <span class="sdp-tab-label">{{ pocket.title }}</span>
        </button>

        <!-- Popup panel — appears to the left of the strip -->
        <Transition name="sdp-popup">
          <div
            v-if="pocket.isOpen"
            class="sdp-popup"
            :class="{ 'sdp-popup--dragging': isDragging(pocket.id) }"
            :style="popupStyle(pocket.id)"
            role="dialog"
            :aria-label="pocket.title"
            @click.stop
          >
            <div
              class="sdp-popup-header"
              @mousedown.prevent="startDrag($event, pocket.id)"
            >
              <i :class="pocket.icon" class="sdp-popup-header-icon" aria-hidden="true" />
              <span class="sdp-popup-title">{{ pocket.title }}</span>
              <div class="sdp-popup-header-actions">
                <button
                  v-if="pocket.isPinnable"
                  class="sdp-icon-btn"
                  :class="{ 'sdp-icon-btn--active': pocket.isPinned }"
                  @click.stop="pocket.isPinned ? sdpStore.unpinPocket(pocket.id) : sdpStore.pinPocket(pocket.id)"
                  :title="pocket.isPinned ? 'Floating (unpin)' : 'Pinned (pin)'"
                  :aria-label="pocket.isPinned ? 'Unpin panel' : 'Pin panel open'"
                >
                  <i :class="pocket.isPinned ? 'pi pi-lock' : 'pi pi-lock-open'" aria-hidden="true" />
                </button>
                <button
                  class="sdp-icon-btn"
                  @click.stop="closePocket(pocket)"
                  title="Schließen"
                  aria-label="Panel schließen"
                >
                  <i class="pi pi-times" aria-hidden="true" />
                </button>
              </div>
            </div>
            <div class="sdp-popup-body">
              <component
                :is="pocket.component"
                :sdpApi="sdpStore.getPocketApi(pocket.id)"
              />
            </div>
          </div>
        </Transition>
      </div>
    </div>
  </Teleport>
</template>

<script setup lang="ts">
import { computed, ref } from 'vue'
import { useRoute } from 'vue-router'
import { useSideDockPopupStore } from '../../store/sideDockPopup'
import type { SdpPocket } from '../../store/sideDockPopup'

const sdpStore = useSideDockPopupStore()
const route = useRoute()
const activeContext = computed(() => String(route.name ?? route.path))

/** All pockets that pass the current context scope filter, sorted by priority. */
const visiblePockets = computed((): SdpPocket[] =>
  sdpStore.sortedPockets.filter(
    (p) =>
      p.contextScope.length === 0 ||
      p.contextScope.some((s) => activeContext.value.includes(s)),
  ),
)

/** True when at least one unpinned pocket is open → show the backdrop. */
const hasUnpinnedOpen = computed(() =>
  sdpStore.pockets.some((p) => p.isOpen && !p.isPinned),
)

// ── Drag state ──────────────────────────────────────────────────────────────
/** Per-pocket accumulated drag offset (x = horizontal, y = vertical). */
const dragOffsets = ref<Record<string, { x: number; y: number }>>({})

/** ID of the pocket currently being dragged, or null. */
const draggingId = ref<string | null>(null)

/** Whether a given pocket popup is being dragged right now. */
function isDragging(id: string): boolean {
  return draggingId.value === id
}

/** Inline style for the popup — applies accumulated drag transform. */
function popupStyle(id: string): Record<string, string> {
  const off = dragOffsets.value[id]
  if (!off) return {}
  return { transform: `translate(${off.x}px, ${off.y}px)` }
}

/**
 * Initiate a drag on mousedown inside the popup header.
 * Listens on the window so the pointer can move outside the panel.
 */
function startDrag(e: MouseEvent, id: string): void {
  const startX = e.clientX
  const startY = e.clientY
  const init = dragOffsets.value[id] ?? { x: 0, y: 0 }

  draggingId.value = id

  const onMove = (ev: MouseEvent) => {
    dragOffsets.value[id] = {
      x: init.x + (ev.clientX - startX),
      y: init.y + (ev.clientY - startY),
    }
  }

  const onUp = () => {
    draggingId.value = null
    window.removeEventListener('mousemove', onMove)
    window.removeEventListener('mouseup', onUp)
  }

  window.addEventListener('mousemove', onMove)
  window.addEventListener('mouseup', onUp)
}

/** Close a pocket and reset its drag offset so it reopens at the default position. */
function closePocket(pocket: SdpPocket): void {
  delete dragOffsets.value[pocket.id]
  sdpStore.closePocketForcefully(pocket.id)
}

/** Toggle a pocket open / closed on tab click. */
function togglePocket(pocket: SdpPocket): void {
  if (pocket.isOpen) {
    closePocket(pocket)
  } else {
    sdpStore.openPocket(pocket.id)
  }
}
</script>

<style scoped>
/* ───────────────────────────────────────────────
   Backdrop — semi-transparent, behind popups
──────────────────────────────────────────────── */
.sdp-backdrop {
  position: fixed;
  inset: 0;
  z-index: 1099;
  background: rgba(0, 0, 0, 0.18);
}

/* ───────────────────────────────────────────────
   Strip — fixed container on the right edge
──────────────────────────────────────────────── */
.sdp-strip {
  position: fixed;
  right: 0;
  top: 50%;
  transform: translateY(-50%);
  z-index: 1100;
  display: flex;
  flex-direction: column;
  gap: 6px;
  /* Let click events pass through the strip background to the page */
  pointer-events: none;
}

/* ───────────────────────────────────────────────
   Widget wrapper
──────────────────────────────────────────────── */
.sdp-widget {
  position: relative;
  pointer-events: all;
  display: flex;
  align-items: center;
  justify-content: flex-end;
}

/* ───────────────────────────────────────────────
   Tab button (icon + slide-out label)
──────────────────────────────────────────────── */
.sdp-tab {
  display: flex;
  align-items: center;
  /* Collapsed state: only wide enough for the icon (icon 22px + padding 2×10px = 42px) */
  max-width: 42px;
  min-width: 42px;
  height: 42px;
  padding: 0 10px;
  overflow: hidden;
  white-space: nowrap;

  background: var(--surface-card, #fff);
  border: 1px solid var(--surface-border, #e0e0e0);
  border-right: none;
  border-radius: 8px 0 0 8px;
  cursor: pointer;
  color: var(--text-color-secondary, #607d8b);
  box-shadow: -2px 0 6px rgba(0, 0, 0, 0.06);

  transition:
    max-width 0.25s cubic-bezier(0.4, 0, 0.2, 1),
    background 0.15s ease,
    color 0.15s ease,
    box-shadow 0.15s ease;
}

/* Expanded on hover or when the popup is open */
.sdp-widget:hover .sdp-tab,
.sdp-widget--open .sdp-tab {
  max-width: 200px;
  background: var(--surface-hover, #f5f5f5);
  color: var(--primary-color, #6366f1);
  box-shadow: -3px 0 10px rgba(0, 0, 0, 0.1);
}

/* Pinned state: accent styling */
.sdp-widget--pinned .sdp-tab {
  background: var(--primary-50, #eef2ff);
  border-color: var(--primary-200, #c7d2fe);
  color: var(--primary-color, #6366f1);
}

.sdp-tab-icon {
  font-size: 1.05rem;
  flex-shrink: 0;
  width: 22px;
  text-align: center;
}

.sdp-tab-label {
  font-size: 0.78rem;
  font-weight: 500;
  padding-left: 7px;
  padding-right: 4px;
  /* Fade in / out alongside the width expansion */
  opacity: 0;
  transition: opacity 0.15s ease;
}

.sdp-widget:hover .sdp-tab .sdp-tab-label,
.sdp-widget--open .sdp-tab .sdp-tab-label {
  opacity: 1;
}

/* ───────────────────────────────────────────────
   Popup panel — appears to the left of the tab
──────────────────────────────────────────────── */
.sdp-popup {
  position: absolute;
  /* Double the original gap: tab width (42px) × 2 + 2px ≈ 86px */
  right: 130px;
  top: 0;
  width: 300px;
  max-height: min(420px, 80vh);
  display: flex;
  flex-direction: column;

  background: var(--surface-card, #fff);
  border: 1px solid var(--surface-border, #e0e0e0);
  border-radius: 10px;
  box-shadow: -4px 4px 24px rgba(0, 0, 0, 0.16);
  z-index: 1101;
  overflow: hidden;
}

.sdp-popup-header {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  padding: 0.65rem 0.85rem;
  border-bottom: 1px solid var(--surface-border, #e0e0e0);
  flex-shrink: 0;
  background: var(--surface-section, #fafafa);
  cursor: move;
}

.sdp-popup-header:active {
  cursor: grabbing;
}

.sdp-popup--dragging {
  user-select: none;
  cursor: grabbing;
}

.sdp-popup-header-icon {
  font-size: 0.95rem;
  color: var(--primary-color, #6366f1);
  flex-shrink: 0;
}

.sdp-popup-title {
  flex: 1;
  font-size: 0.85rem;
  font-weight: 600;
  color: var(--text-color, #212121);
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}

.sdp-popup-header-actions {
  display: flex;
  align-items: center;
  gap: 2px;
  flex-shrink: 0;
}

.sdp-icon-btn {
  display: flex;
  align-items: center;
  justify-content: center;
  width: 28px;
  height: 28px;
  border: none;
  background: transparent;
  cursor: pointer;
  border-radius: 5px;
  color: var(--text-color-secondary, #607d8b);
  font-size: 0.8rem;
  transition: background 0.12s, color 0.12s;
}

.sdp-icon-btn:hover {
  background: var(--surface-hover, #f0f0f0);
  color: var(--text-color, #212121);
}

.sdp-icon-btn--active {
  color: var(--primary-color, #6366f1);
  background: var(--primary-50, #eef2ff);
}

.sdp-icon-btn--active:hover {
  background: var(--primary-100, #e0e7ff);
}

.sdp-popup-body {
  flex: 1;
  overflow-y: auto;
  padding: 0.75rem;
}

/* ───────────────────────────────────────────────
   Transitions
──────────────────────────────────────────────── */
.sdp-popup-enter-active {
  transition: opacity 0.15s ease, transform 0.2s ease;
}
.sdp-popup-leave-active {
  transition: opacity 0.1s ease, transform 0.15s ease;
}
.sdp-popup-enter-from,
.sdp-popup-leave-to {
  opacity: 0;
  transform: translateX(8px);
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

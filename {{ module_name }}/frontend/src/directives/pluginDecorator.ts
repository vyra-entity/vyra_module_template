/**
 * v-plugin-decorator directive
 *
 * Applied to a host element to signal that `component-decorator` plugins
 * may inject extra UI adjacent to it.
 *
 * The directive sets a `data-plugin-decorator` attribute on the element.
 * Decorator plugins can query `document.querySelectorAll('[data-plugin-decorator="<key>"]')`
 * to locate valid mount targets.
 *
 * @example
 *   <div v-plugin-decorator="'module-header'">…</div>
 *   <!-- renders as: <div data-plugin-decorator="module-header">…</div> -->
 */

import type { Directive } from 'vue'

export const vPluginDecorator: Directive<HTMLElement, string | undefined> = {
  mounted(el, binding) {
    el.setAttribute('data-plugin-decorator', binding.value ?? '')
  },
  updated(el, binding) {
    el.setAttribute('data-plugin-decorator', binding.value ?? '')
  },
  unmounted(el) {
    el.removeAttribute('data-plugin-decorator')
  },
}

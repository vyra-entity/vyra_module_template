<template>
  <div class="settings-page">
    <div class="page-header">
      <i class="pi pi-sliders-h text-primary" />
      <div>
        <h2 class="m-0">Allgemein</h2>
        <p class="text-sm text-color-secondary m-0">Kontoinformationen und allgemeine Optionen</p>
      </div>
    </div>

    <div class="grid">
      <!-- Account Info -->
      <div class="col-12 md:col-6">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-user"></i>
              <span>Kontoinformationen</span>
            </div>
          </template>
          <template #content>
            <div class="flex flex-column gap-3">
              <div>
                <label class="block mb-1 font-semibold text-sm">Benutzername</label>
                <span>{% raw %}{{ authStore.username }}{% endraw %}</span>
              </div>
              <div>
                <label class="block mb-1 font-semibold text-sm">Rollen</label>
                <div class="flex gap-1 flex-wrap">
                  <Tag
                    v-for="role in authStore.roles"
                    :key="role"
                    :value="role"
                    :severity="role === 'Admin' ? 'danger' : role === 'Manager' ? 'warning' : 'info'"
                    size="small"
                  />
                </div>
              </div>
            </div>
          </template>
        </Card>
      </div>

      <!-- Side-Dock -->
      <div class="col-12 md:col-6">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-th-large"></i>
              <span>Side-Dock Widgets</span>
            </div>
          </template>
          <template #content>
            <div class="flex align-items-center justify-content-between gap-3">
              <div>
                <p class="m-0 font-semibold">Schwebende Widget-Tabs anzeigen</p>
                <p class="m-0 text-sm text-color-secondary mt-1">
                  Plugin-Widgets erscheinen als schwebende Tabs am rechten Rand.
                </p>
              </div>
              <InputSwitch v-model="uiSettingsStore.sideDockPocketEnabled" />
            </div>
          </template>
        </Card>
      </div>

      <div class="col-12">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-shield" />
              <span>Modul-Parameter (Permissions)</span>
            </div>
          </template>
          <template #content>
            <p class="text-sm text-color-secondary mt-0 mb-3">
              Werte aus <code>.module/module_params.yaml</code>. Nur Admins duerfen speichern.
            </p>

            <Message v-if="permissionError" severity="error" :closable="false" class="mb-3">
              <span v-text="permissionError" />
            </Message>
            <Message v-if="permissionSuccess" severity="success" :closable="false" class="mb-3">
              <span v-text="permissionSuccess" />
            </Message>

            <div class="permissions-table">
              <div v-for="([key, value]) in permissionEntries" :key="key" class="permissions-row">
                <div class="permissions-key"><span v-text="key" /></div>
                <div class="permissions-value">
                  <InputSwitch
                    v-if="typeof value === 'boolean'"
                    :modelValue="Boolean(value)"
                    :disabled="!authStore.isAdmin"
                    @update:modelValue="(v) => updateBoolPermission(key, v)"
                  />
                  <InputText
                    v-else
                    :modelValue="permissionText[key] ?? stringifyPermissionValue(value)"
                    :disabled="!authStore.isAdmin"
                    class="w-full"
                    @update:modelValue="(v) => updateTextPermission(key, String(v))"
                  />
                </div>
              </div>
            </div>

            <div v-if="hasPermissionChanges" class="flex justify-content-end mt-3">
              <Button
                label="Speichern"
                icon="pi pi-save"
                :loading="savingPermissions"
                :disabled="!authStore.isAdmin || loadingPermissions || !hasPermissionChanges"
                @click="savePermissions"
              />
            </div>
          </template>
        </Card>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { computed, onMounted, ref } from 'vue'
import Card from 'primevue/card'
import Tag from 'primevue/tag'
import InputSwitch from 'primevue/inputswitch'
import InputText from 'primevue/inputtext'
import Button from 'primevue/button'
import Message from 'primevue/message'
import { useAuthStore } from '../../../store/auth'
import { useUiSettingsStore } from '../../../store/uiSettings'
import { settingsApi } from '../../../api/settings.api'

const authStore = useAuthStore()
const uiSettingsStore = useUiSettingsStore()

const loadingPermissions = ref(false)
const savingPermissions = ref(false)
const permissionError = ref('')
const permissionSuccess = ref('')
const permissions = ref<Record<string, unknown>>({})
const permissionText = ref<Record<string, string>>({})
const permissionsLoaded = ref(false)
const initialPermissionsSnapshot = ref('')

const permissionEntries = computed<[string, unknown][]>(() => Object.entries(permissions.value))
const hasPermissionChanges = computed(() => {
  if (!permissionsLoaded.value) return false
  return JSON.stringify(permissions.value) !== initialPermissionsSnapshot.value
})

function stringifyPermissionValue(value: unknown): string {
  if (value === null || value === undefined) return ''
  if (typeof value === 'object') return JSON.stringify(value)
  return String(value)
}

function parsePermissionValue(raw: string): unknown {
  const value = raw.trim()
  if (value === '') return ''
  if (value.toLowerCase() === 'true') return true
  if (value.toLowerCase() === 'false') return false
  if (value.toLowerCase() === 'null') return null
  if (/^-?\d+(\.\d+)?$/.test(value)) return Number(value)
  if ((value.startsWith('{') && value.endsWith('}')) || (value.startsWith('[') && value.endsWith(']'))) {
    try {
      return JSON.parse(value)
    } catch {
      return raw
    }
  }
  return raw
}

function updateBoolPermission(key: string, value: boolean): void {
  permissions.value[key] = value
}

function updateTextPermission(key: string, value: string): void {
  permissionText.value[key] = value
  permissions.value[key] = parsePermissionValue(value)
}

async function loadPermissions(): Promise<void> {
  loadingPermissions.value = true
  permissionsLoaded.value = false
  permissionError.value = ''
  try {
    const response = await settingsApi.getModulePermissions()
    permissions.value = { ...response.permissions }
    permissionText.value = {}
    initialPermissionsSnapshot.value = JSON.stringify(permissions.value)
    permissionsLoaded.value = true
    permissionSuccess.value = ''
  } catch (error) {
    permissionError.value = (error as Error).message || 'Permissions konnten nicht geladen werden'
  } finally {
    loadingPermissions.value = false
  }
}

async function savePermissions(): Promise<void> {
  if (!authStore.isAdmin) return
  savingPermissions.value = true
  permissionError.value = ''
  permissionSuccess.value = ''
  try {
    const response = await settingsApi.updateModulePermissions(permissions.value)
    permissions.value = { ...response.permissions }
    initialPermissionsSnapshot.value = JSON.stringify(permissions.value)
    permissionSuccess.value = 'Permissions wurden gespeichert.'
  } catch (error) {
    permissionError.value = (error as Error).message || 'Permissions konnten nicht gespeichert werden'
  } finally {
    savingPermissions.value = false
  }
}

onMounted(async () => {
  await loadPermissions()
})
</script>

<style scoped>
.settings-page {
  padding: 2rem;
}

.page-header {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  margin-bottom: 2rem;
}

.page-header i {
  font-size: 1.5rem;
}

.permissions-table {
  display: flex;
  flex-direction: column;
  border: 1px solid var(--surface-border);
  border-radius: 8px;
  overflow: hidden;
}

.permissions-row {
  display: grid;
  grid-template-columns: minmax(10rem, 16rem) 1fr;
  gap: 1rem;
  padding: 0.75rem 1rem;
  border-bottom: 1px solid var(--surface-border);
}

.permissions-row:last-child {
  border-bottom: none;
}

.permissions-key {
  font-family: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, monospace;
  font-size: 0.9rem;
  align-self: center;
}

.permissions-value {
  display: flex;
  align-items: center;
}
</style>

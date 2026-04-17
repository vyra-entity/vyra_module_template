<template>
  <div class="settings-page">
    <div class="page-header">
      <i class="pi pi-lock text-primary" />
      <div>
        <h2 class="m-0">Authentifizierung</h2>
        <p class="text-sm text-color-secondary m-0">Authentifizierungseinstellungen &amp; Passwort</p>
      </div>
    </div>
    <div class="grid">
      <!-- Auth Mode Info -->
      <div class="col-12 md:col-6">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-info-circle"></i>
              <span>Authentifizierungsmodus</span>
            </div>
          </template>
          <template #content>
            <div class="flex flex-column gap-3">
              <div class="flex align-items-center gap-2">
                <i :class="['pi', authStore.authMode === 'local' ? 'pi-check-circle text-green-500' : 'pi-circle text-color-secondary']"></i>
                <span><strong>Lokal:</strong> Integrierte Benutzerdatenbank</span>
              </div>
              <div class="flex align-items-center gap-2">
                <i :class="['pi', userManagerAvailable ? 'pi-check-circle text-green-500' : 'pi-times-circle text-red-400']"></i>
                <span>
                  <strong>UserManager:</strong>
                  {% raw %}{{ userManagerAvailable ? 'Externer UserManager verfügbar' : 'Kein UserManager erreichbar' }}{% endraw %}
                </span>
              </div>
            </div>
          </template>
        </Card>
      </div>

      <!-- Local User Management (local auth mode or admin via UserManager) -->
      <div v-if="authStore.authMode === 'local' || isAdmin" class="col-12">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-users"></i>
              <span>Lokale Benutzerverwaltung</span>
            </div>
          </template>
          <template #content>
            <div class="grid">
              <!-- Password Change Section -->
              <div class="col-12 md:col-6">
                <h3 class="text-lg font-semibold mb-3">
                  <i class="pi pi-key mr-2"></i>Passwort ändern
                </h3>
                <form @submit.prevent="handleChangePassword" class="flex flex-column gap-3">
                  <div class="field">
                    <label for="oldPw" class="block mb-2 font-semibold">Aktuelles Passwort</label>
                    <Password id="oldPw" v-model="oldPassword" :feedback="false" toggleMask class="w-full" :inputStyle="{ width: '100%' }" :pt="{ input: { autocomplete: 'current-password' } }" />
                  </div>
                  <div class="field">
                    <label for="newPw" class="block mb-2 font-semibold">Neues Passwort (min. 8 Zeichen)</label>
                    <Password id="newPw" v-model="newPassword" toggleMask class="w-full" :inputStyle="{ width: '100%' }" :pt="{ input: { autocomplete: 'new-password' } }" />
                  </div>
                  <div class="field">
                    <label for="confirmPw" class="block mb-2 font-semibold">Passwort bestätigen</label>
                    <Password id="confirmPw" v-model="confirmPassword" :feedback="false" toggleMask class="w-full" :inputStyle="{ width: '100%' }" :pt="{ input: { autocomplete: 'new-password' } }" />
                  </div>
                  <Message v-if="passwordError" severity="error" :closable="false">{% raw %}{{ passwordError }}{% endraw %}</Message>
                  <Button
                    type="submit"
                    label="Passwort ändern"
                    icon="pi pi-check"
                    :loading="changingPassword"
                    :disabled="!oldPassword || newPassword.length < 8 || newPassword !== confirmPassword"
                  />
                </form>
              </div>

              <!-- Create User Section (admin only) -->
              <div class="col-12 md:col-6">
                <h3 class="text-lg font-semibold mb-3">
                  <i class="pi pi-user-plus mr-2"></i>Neuen Benutzer anlegen
                  <Tag v-if="!isAdmin" value="Nur für Admin" severity="warn" class="ml-2 text-xs" />
                </h3>
                <form @submit.prevent="handleCreateUser" class="flex flex-column gap-3">
                  <div class="field">
                    <label for="newUsername" class="block mb-2 font-semibold">Benutzername</label>
                    <InputText
                      id="newUsername"
                      v-model="newUsername"
                      class="w-full"
                      :disabled="!isAdmin"
                      placeholder="Benutzername eingeben"
                    />
                  </div>
                  <div class="field">
                    <label for="newUserPw" class="block mb-2 font-semibold">Passwort (min. 8 Zeichen)</label>
                    <Password
                      id="newUserPw"
                      v-model="newUserPassword"
                      toggleMask
                      class="w-full"
                      :inputStyle="{ width: '100%' }"
                      :disabled="!isAdmin"
                    />
                  </div>
                  <div class="field">
                    <label for="newUserRole" class="block mb-2 font-semibold">Rolle</label>
                    <Select
                      id="newUserRole"
                      v-model="newUserRole"
                      :options="roleOptions"
                      optionLabel="label"
                      optionValue="value"
                      class="w-full"
                      :disabled="!isAdmin"
                    />
                  </div>
                  <Message v-if="createUserError" severity="error" :closable="false">{% raw %}{{ createUserError }}{% endraw %}</Message>
                  <Button
                    type="submit"
                    label="Benutzer anlegen"
                    icon="pi pi-user-plus"
                    :loading="creatingUser"
                    :disabled="!isAdmin || !newUsername || newUserPassword.length < 8"
                  />
                </form>
              </div>

              <!-- Local User List -->
              <div class="col-12 mt-3">
                <h3 class="text-lg font-semibold mb-3">
                  <i class="pi pi-list mr-2"></i>Lokale Benutzer
                </h3>
                <DataTable
                  :value="localUsers"
                  :loading="loadingUsers"
                  stripedRows
                  class="p-datatable-sm"
                >
                  <template #empty>
                    <div class="text-center py-3 text-color-secondary">
                      <span v-if="!isAdmin">Nur für Administratoren sichtbar.</span>
                      <span v-else>Keine lokalen Benutzer gefunden.</span>
                    </div>
                  </template>
                  <Column field="username" header="Benutzername" sortable />
                  <Column field="role" header="Rolle" sortable>
                    <template #body="{ data }">
                      <Tag
                        :value="data.role ?? '–'"
                        :severity="data.role === 'admin' ? 'danger' : data.role === 'manager' ? 'secondary' : data.role === 'operator' ? 'warn' : 'info'"
                        size="small"
                      />
                    </template>
                  </Column>
                  <Column field="created_at" header="Erstellt am">
                    <template #body="{ data }">
                      {% raw %}{{ data.created_at ? formatDate(data.created_at) : '–' }}{% endraw %}
                    </template>
                  </Column>
                  <Column header="" style="width: 4rem">
                    <template #body="{ data }">
                      <Button
                        v-if="isAdmin && data.username !== 'admin' && !data.lock_edit"
                        icon="pi pi-trash"
                        severity="danger"
                        text
                        rounded
                        size="small"
                        v-tooltip.top="'Delete'"
                        @click="confirmDeleteUser(data.username)"
                      />
                      <span
                        v-else-if="data.lock_edit"
                        v-tooltip.top="'Locked — cannot be deleted'"
                        class="pi pi-lock text-400"
                        style="font-size: 0.9rem; padding: 0.5rem"
                      />
                    </template>
                  </Column>
                </DataTable>
              </div>
            </div>
          </template>
        </Card>
      </div>

      <!-- UserManager info (usermanager auth mode) -->
      <div v-else class="col-12">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-shield"></i>
              <span>Benutzerverwaltung</span>
            </div>
          </template>
          <template #content>
            <Message severity="info" :closable="false">
              <strong>UserManager-Modus aktiv:</strong> Benutzer, Rollen und Zugriffsrechte werden
              zentral im <strong>UserManager</strong> verwaltet. Bitte melde dich dort an, um
              Benutzer zu verwalten.
            </Message>
          </template>
        </Card>
      </div>
    </div>

    <ConfirmDialog />
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted } from 'vue'
import Card from 'primevue/card'
import DataTable from 'primevue/datatable'
import Column from 'primevue/column'
import Button from 'primevue/button'
import Tag from 'primevue/tag'
import Message from 'primevue/message'
import Password from 'primevue/password'
import InputText from 'primevue/inputtext'
import Select from 'primevue/select'
import ConfirmDialog from 'primevue/confirmdialog'
import { useConfirm } from 'primevue/useconfirm'
import { useToast } from 'primevue/usetoast'
import { authApi, type LocalUser } from '../../../api/auth.api'
import { useAuthStore } from '../../../store/auth'

const confirm = useConfirm()
const toast = useToast()
const authStore = useAuthStore()

const userManagerAvailable = ref(false)
const isAdmin = computed(() => authStore.user?.username === 'admin')

// ─── Password change ─────────────────────────────────────────────────────────
const oldPassword = ref('')
const newPassword = ref('')
const confirmPassword = ref('')
const changingPassword = ref(false)
const passwordError = ref('')

async function handleChangePassword() {
  passwordError.value = ''
  if (newPassword.value.length < 8) {
    passwordError.value = 'Neues Passwort muss mindestens 8 Zeichen haben'
    return
  }
  if (newPassword.value !== confirmPassword.value) {
    passwordError.value = 'Passwörter stimmen nicht überein'
    return
  }
  changingPassword.value = true
  try {
    await authStore.changePassword(oldPassword.value, newPassword.value)
    toast.add({ severity: 'success', summary: 'Passwort geändert', life: 3000 })
    oldPassword.value = ''
    newPassword.value = ''
    confirmPassword.value = ''
  } catch (e: any) {
    passwordError.value = e.message || 'Passwortänderung fehlgeschlagen'
  } finally {
    changingPassword.value = false
  }
}

// ─── Create user ─────────────────────────────────────────────────────────────
const newUsername = ref('')
const newUserPassword = ref('')
const newUserRole = ref(authStore.user?.role ?? 'viewer')
const creatingUser = ref(false)
const createUserError = ref('')

const roleOptions = [
  { label: 'Viewer', value: 'viewer' },
  { label: 'Operator', value: 'operator' },
  { label: 'Manager', value: 'manager' },
  { label: 'Admin', value: 'admin' },
]

async function handleCreateUser() {
  createUserError.value = ''
  if (newUserPassword.value.length < 8) {
    createUserError.value = 'Passwort muss mindestens 8 Zeichen haben'
    return
  }
  creatingUser.value = true
  try {
    await authApi.createLocalUser(newUsername.value, newUserPassword.value, newUserRole.value)
    toast.add({ severity: 'success', summary: 'Benutzer angelegt', detail: `${newUsername.value} wurde erstellt`, life: 3000 })
    newUsername.value = ''
    newUserPassword.value = ''
    newUserRole.value = 'viewer'
    await loadLocalUsers()
  } catch (e: any) {
    createUserError.value = e.message || 'Benutzer konnte nicht angelegt werden'
  } finally {
    creatingUser.value = false
  }
}

// ─── Delete user ─────────────────────────────────────────────────────────────
function confirmDeleteUser(username: string) {
  confirm.require({
    message: `Benutzer "${username}" wirklich löschen?`,
    header: 'Löschen bestätigen',
    icon: 'pi pi-exclamation-triangle',
    acceptClass: 'p-button-danger',
    accept: async () => {
      try {
        await authApi.deleteLocalUser(username)
        toast.add({ severity: 'success', summary: 'Benutzer gelöscht', life: 3000 })
        await loadLocalUsers()
      } catch (e: any) {
        toast.add({ severity: 'error', summary: 'Löschen fehlgeschlagen', detail: e.message, life: 5000 })
      }
    },
  })
}

// ─── Local user list ─────────────────────────────────────────────────────────
const localUsers = ref<LocalUser[]>([])
const loadingUsers = ref(false)

async function loadLocalUsers() {
  if (!isAdmin.value) return
  loadingUsers.value = true
  try {
    localUsers.value = await authApi.listLocalUsers()
  } catch {
    // silently fail for non-admin
  } finally {
    loadingUsers.value = false
  }
}

function formatDate(iso: string): string {
  try {
    return new Date(iso).toLocaleDateString('de-DE', { day: '2-digit', month: 'short', year: 'numeric' })
  } catch {
    return iso
  }
}

onMounted(async () => {
  const status = await authApi.checkUserManagerAvailable()
  userManagerAvailable.value = status.available
  await loadLocalUsers()
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
</style>


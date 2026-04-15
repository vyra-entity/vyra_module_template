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
          <template #content>
            <p class="text-color-secondary m-0">Hier werden zukünftig die Authentifizierungseinstellungen angezeigt.</p>
          </template>
        </Card>
      </div>

      <!-- Password Change -->
      <div class="col-12 md:col-6">
        <Card>
          <template #title>
            <div class="flex align-items-center gap-2">
              <i class="pi pi-key"></i>
              <span>Passwort ändern</span>
            </div>
          </template>
          <template #content>
            <form @submit.prevent="handleChangePassword" class="flex flex-column gap-3">
              <div class="field">
                <label for="oldPw" class="block mb-2 font-semibold">Aktuelles Passwort</label>
                <Password id="oldPw" v-model="oldPassword" :feedback="false" toggleMask class="w-full" :inputStyle="{ width: '100%' }" />
              </div>
              <div class="field">
                <label for="newPw" class="block mb-2 font-semibold">Neues Passwort (min. 8 Zeichen)</label>
                <Password id="newPw" v-model="newPassword" toggleMask class="w-full" :inputStyle="{ width: '100%' }" />
              </div>
              <div class="field">
                <label for="confirmPw" class="block mb-2 font-semibold">Passwort bestätigen</label>
                <Password id="confirmPw" v-model="confirmPassword" :feedback="false" toggleMask class="w-full" :inputStyle="{ width: '100%' }" />
              </div>
              <Message v-if="passwordError" severity="error" :closable="false">{{ passwordError }}</Message>
              <Button
                type="submit"
                label="Passwort ändern"
                icon="pi pi-check"
                :loading="changingPassword"
                :disabled="!oldPassword || newPassword.length < 8 || newPassword !== confirmPassword"
              />
            </form>
          </template>
        </Card>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'
import Card from 'primevue/card'
import Button from 'primevue/button'
import Message from 'primevue/message'
import Password from 'primevue/password'
import { useToast } from 'primevue/usetoast'
import { useAuthStore } from '../../../store/auth'

const toast = useToast()
const authStore = useAuthStore()

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
</script>

<style scoped>
.settings-page { padding: 2rem; }
.page-header { display: flex; align-items: center; gap: 0.75rem; margin-bottom: 2rem; }
.page-header i { font-size: 1.5rem; }
</style>


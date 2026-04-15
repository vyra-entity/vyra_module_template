<template>
  <div class="login-view">
    <Card class="login-card">
      <template #header>
        <div class="login-header">
          <img :src="logo" alt="VYRA Logo" class="login-logo mb-3" />
          <h2 class="m-0">VYRA {{ module_name }}</h2>
          <p class="text-600 mt-2">Bitte melden Sie sich an</p>
        </div>
      </template>
      <template #content>
        <form @submit.prevent="handleLogin" class="login-form">
          <div class="flex flex-column gap-3">
            <!-- Username -->
            <div class="field">
              <label for="username" class="block mb-2 font-semibold">Benutzername</label>
              <InputText
                id="username"
                v-model="username"
                placeholder="Benutzername eingeben"
                class="w-full"
                :disabled="isLoading"
                autocomplete="username"
              />
            </div>

            <!-- Password -->
            <div class="field">
              <label for="password" class="block mb-2 font-semibold">Passwort</label>
              <Password
                id="password"
                v-model="password"
                placeholder="Passwort eingeben"
                :feedback="false"
                toggleMask
                class="w-full"
                :disabled="isLoading"
                :inputStyle="{ width: '100%' }"
                autocomplete="current-password"
              />
            </div>

            <!-- Auth Mode Selection -->
            <div class="field">
              <label for="authMode" class="block mb-2 font-semibold">
                Authentifizierungsmodus
              </label>
              <Select
                v-if="authModeOptions.length > 1"
                id="authMode"
                v-model="authMode"
                :options="authModeOptions"
                optionLabel="label"
                optionValue="value"
                placeholder="Modus wählen"
                class="w-full"
                :disabled="isLoading"
              />
              <div v-else class="auth-mode-info">
                <i class="pi pi-info-circle mr-2"></i>
                <span>Anmeldung erfolgt lokal</span>
              </div>
            </div>

            <!-- Error Message -->
            <Message v-if="errorMessage" severity="error" :closable="false">
              {%- raw %}{{ errorMessage }}{%- endraw %}
            </Message>

            <!-- Login Button -->
            <Button
              type="submit"
              label="Anmelden"
              icon="pi pi-sign-in"
              class="w-full"
              :loading="isLoading"
              :disabled="!username || !password"
            />

            <!-- Info about default credentials -->
            <div class="text-center text-sm text-600 mt-3">
              <p class="m-0">Standard-Anmeldedaten:</p>
              <p class="m-0"><strong>Benutzername:</strong> admin</p>
              <p class="m-0"><strong>Passwort:</strong> admin</p>
            </div>
          </div>
        </form>
      </template>
    </Card>
  </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from 'vue'
import { useRouter } from 'vue-router'
import Card from 'primevue/card'
import InputText from 'primevue/inputtext'
import Password from 'primevue/password'
import Button from 'primevue/button'
import Select from 'primevue/select'
import Message from 'primevue/message'
import { useAuthStore } from '../../store/auth'
import { useToast } from 'primevue/usetoast'
import logo from '../../assets/logo.svg'
// Alternative: Variobotic logo as placeholder
// import logo from '../../assets/variobotic-kreis-transparent-blaugrau.svg'

const router = useRouter()
const authStore = useAuthStore()
const toast = useToast()

const username = ref('')
const password = ref('')
const authMode = ref<'local' | 'usermanager'>('local')
const isLoading = ref(false)
const errorMessage = ref('')
const userManagerAvailable = ref(false)

const authModeOptions = ref([
  { label: 'Lokal', value: 'local' }
])

const handleLogin = async () => {
  errorMessage.value = ''
  isLoading.value = true

  try {
    await authStore.login(username.value, password.value, authMode.value)
    
    toast.add({
      severity: 'success',
      summary: 'Anmeldung erfolgreich',
      detail: `Willkommen, ${username.value}!`,
      life: 3000
    })

    router.push('/{{ module_name }}/home')
  } catch (error: any) {
    errorMessage.value = error.message || 'Anmeldung fehlgeschlagen'
    toast.add({
      severity: 'error',
      summary: 'Anmeldung fehlgeschlagen',
      detail: errorMessage.value,
      life: 5000
    })
  } finally {
    isLoading.value = false
  }
}

onMounted(async () => {
  // Check if user manager is available
  await authStore.checkUserManager()
  userManagerAvailable.value = authStore.userManagerAvailable
  
  // Update auth mode options based on availability
  if (userManagerAvailable.value) {
    authModeOptions.value = [
      { label: 'User Manager', value: 'usermanager' },
      { label: 'Lokal', value: 'local' }
    ]
    authMode.value = 'usermanager'
  } else {
    authModeOptions.value = [
      { label: 'Lokal', value: 'local' }
    ]
  }
})
</script>

<style scoped>
.login-view {
  min-height: 100vh;
  display: flex;
  align-items: center;
  justify-content: center;
  background: linear-gradient(135deg, var(--primary-color) 0%, var(--primary-600) 100%);
  padding: 2rem;
}

.login-card {
  width: 100%;
  max-width: 450px;
  box-shadow: 0 8px 32px rgba(0, 0, 0, 0.1);
}

.login-header {
  text-align: center;
  padding: 2rem 2rem 1rem;
  background: var(--surface-ground);
}

.login-logo {
  width: 80px;
  height: 80px;
}

.login-form {
  padding: 0 1rem 1rem;
}

.auth-mode-info {
  display: flex;
  align-items: center;
  padding: 0.75rem 1rem;
  background-color: var(--surface-100);
  border: 1px solid var(--surface-300);
  border-radius: var(--border-radius);
  color: var(--text-color-secondary);
  font-size: 0.95rem;
}

:deep(.p-password-input) {
  width: 100%;
}
</style>

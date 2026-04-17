<template>
  <Dialog 
    v-model:visible="isVisible" 
    :header="`Update: ${moduleName}`" 
    :modal="true" 
    :style="{ width: '600px' }"
    :closable="true"
    @update:visible="handleClose"
  >
    <div class="update-modal-content">
      <div class="flex flex-column gap-4">
        <!-- Current Version -->
        <div class="version-info">
          <div class="flex align-items-center gap-2 mb-2">
            <i class="pi pi-box text-600"></i>
            <span class="text-600 font-semibold">Aktuelle Version:</span>
          </div>
          <Tag :value="currentVersion" severity="info" class="text-lg px-3 py-2" />
        </div>

        <!-- Available Updates -->
        <div class="available-updates">
          <div class="flex align-items-center gap-2 mb-3">
            <i class="pi pi-download text-primary"></i>
            <span class="text-primary font-semibold">Verfügbare Updates:</span>
          </div>

          <div v-if="availableUpdates && availableUpdates.length > 0" class="flex flex-column gap-2">
            <div 
              v-for="update in availableUpdates" 
              :key="`${update.repository_id}_${update.available_version}`"
              class="update-option p-3 border-round cursor-pointer transition-all"
              :class="{ 'update-option-selected': selectedUpdate?.repository_id === update.repository_id }"
              @click="selectUpdate(update)"
            >
              <div class="flex align-items-center justify-content-between">
                <div class="flex-1">
                  <div class="flex align-items-center gap-2 mb-2">
                    <RadioButton 
                      :value="update" 
                      v-model="selectedUpdate" 
                      :inputId="`update_${update.repository_id}`"
                    />
                    <label :for="`update_${update.repository_id}`" class="font-semibold cursor-pointer">
                      {% raw %}{{ update.repository_name }}{% endraw %}
                    </label>
                  </div>
                  
                  <div class="flex align-items-center gap-3 ml-4">
                    <Tag :value="`v${update.available_version}`" severity="success" />
                    <Tag :value="update.repository_type" severity="secondary" />
                  </div>
                  
                  <div v-if="update.description" class="ml-4 mt-2 text-sm text-600">
                    {% raw %}{{ update.description }}{% endraw %}
                  </div>
                </div>
                
                <div class="version-arrow flex align-items-center gap-2">
                  <i class="pi pi-arrow-right text-success"></i>
                </div>
              </div>
            </div>
          </div>

          <div v-else class="text-center text-600 py-4">
            <i class="pi pi-info-circle mr-2"></i>
            Keine Updates verfügbar
          </div>
        </div>

        <!-- Update All Instances Option -->
        <div class="update-all-option border-top-1 border-200 pt-3">
          <div class="flex align-items-center gap-2">
            <Checkbox v-model="updateAllInstances" :binary="true" inputId="updateAll" />
            <label for="updateAll" class="cursor-pointer">
              Alle Instanzen aktualisieren
            </label>
          </div>
          <div class="text-sm text-600 ml-4 mt-1">
            Wenn aktiviert, werden alle Instanzen dieses Moduls aktualisiert
          </div>
        </div>
      </div>
    </div>

    <template #footer>
      <div class="flex justify-content-end gap-2">
        <Button 
          label="Abbrechen" 
          icon="pi pi-times" 
          severity="secondary"
          @click="handleClose" 
        />
        <Button 
          label="Update starten" 
          icon="pi pi-download" 
          severity="success"
          :disabled="!selectedUpdate"
          @click="handleUpdate" 
        />
      </div>
    </template>
  </Dialog>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'
import Dialog from 'primevue/dialog'
import Button from 'primevue/button'
import Tag from 'primevue/tag'
import RadioButton from 'primevue/radiobutton'
import Checkbox from 'primevue/checkbox'

interface UpdateInfo {
  repository_id: string
  repository_name: string
  repository_type: string
  available_version: string
  module_hash: string
  description?: string
}

interface Props {
  visible: boolean
  moduleName: string
  instanceId: string
  currentVersion: string
  availableUpdates?: UpdateInfo[]
}

interface Emits {
  (e: 'update:visible', value: boolean): void
  (e: 'confirm', data: { repository: any; version: string; updateAll: boolean }): void
}

const props = defineProps<Props>()
const emit = defineEmits<Emits>()

const isVisible = computed({
  get: () => props.visible,
  set: (value) => emit('update:visible', value)
})

const selectedUpdate = ref<UpdateInfo | null>(null)
const updateAllInstances = ref(false)

const selectUpdate = (update: UpdateInfo) => {
  selectedUpdate.value = update
}

const handleClose = () => {
  emit('update:visible', false)
  selectedUpdate.value = null
  updateAllInstances.value = false
}

const handleUpdate = () => {
  if (!selectedUpdate.value) return

  const repository = {
    id: selectedUpdate.value.repository_id,
    name: selectedUpdate.value.repository_name,
    type: selectedUpdate.value.repository_type
  }

  emit('confirm', {
    repository,
    version: selectedUpdate.value.available_version,
    updateAll: updateAllInstances.value
  })

  handleClose()
}
</script>

<style scoped>
.update-modal-content {
  padding: 0.5rem 0;
}

.version-info {
  background-color: rgba(0, 0, 0, 0.02);
  padding: 1rem;
  border-radius: 8px;
}

.update-option {
  background-color: rgba(0, 0, 0, 0.02);
  border: 2px solid transparent;
  transition: all 0.2s ease;
}

.update-option:hover {
  background-color: rgba(0, 0, 0, 0.04);
  border-color: var(--primary-color);
  transform: translateX(4px);
}

.update-option-selected {
  background-color: rgba(var(--primary-color-rgb), 0.1);
  border-color: var(--primary-color);
}

.version-arrow {
  opacity: 0.5;
  transition: opacity 0.2s ease;
}

.update-option:hover .version-arrow {
  opacity: 1;
}

:deep(.p-tag) {
  font-weight: 600;
}

:deep(.p-radiobutton) {
  flex-shrink: 0;
}
</style>

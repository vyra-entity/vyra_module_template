<template>
  <Dialog 
    v-model:visible="isVisible" 
    :header="dialogTitle" 
    :modal="true" 
    :closable="canClose"
    :draggable="false"
    :style="{ width: '600px' }"
    @update:visible="$emit('update:visible', $event)"
  >
    <!-- Task List -->
    <div class="task-progress-container">
      
      <div 
        v-for="task in tasks" 
        :key="task.id"
        class="task-item"
        :class="{ 'task-active': task.status === 'running' }"
      >
        <!-- Status Icon -->
        <div class="task-icon">
          <!-- Pending: Empty Circle -->
          <i v-if="task.status === 'pending'" class="pi pi-circle task-icon-pending" />
          
          <!-- Running: Spinner -->
          <i v-else-if="task.status === 'running'" class="pi pi-spin pi-spinner task-icon-running" />
          
          <!-- Completed: Check Circle -->
          <i v-else-if="task.status === 'completed'" class="pi pi-check-circle task-icon-completed" />
          
          <!-- Failed: Times Circle -->
          <i v-else-if="task.status === 'failed'" class="pi pi-times-circle task-icon-failed" />
          
          <!-- Skipped: Info Circle -->
          <i v-else-if="task.status === 'skipped'" class="pi pi-info-circle task-icon-skipped" />
        </div>

        <!-- Task Info -->
        <div class="task-content">
          <div class="task-title">{{ task.title }}</div>
          <div v-if="task.description" class="task-description">{{ task.description }}</div>
          <div v-if="task.error" class="task-error">{{ task.error }}</div>
        </div>
      </div>

      <!-- User Prompt Section -->
      <div v-if="userPrompt" class="user-prompt-section">
        <Divider />
        
        <div class="prompt-content">
          <div class="prompt-icon">
            <i 
              class="prompt-icon-symbol"
              :class="{
                'pi pi-exclamation-triangle': userPrompt.type === 'warning',
                'pi pi-times-circle': userPrompt.type === 'error',
                'pi pi-info-circle': userPrompt.type === 'info',
                'pi pi-question-circle': userPrompt.type === 'question'
              }"
            />
          </div>
          
          <div class="prompt-body">
            <h3 class="prompt-title">{{ userPrompt.title }}</h3>
            <p class="prompt-message">{{ userPrompt.message }}</p>
            
            <div class="prompt-actions">
              <Button
                v-for="option in userPrompt.options"
                :key="option.value"
                :label="option.label"
                :severity="getButtonSeverity(option.variant)"
                @click="handlePromptResponse(option.value)"
                :disabled="respondingToPrompt"
              />
            </div>
          </div>
        </div>
      </div>

      <!-- Overall Status Message -->
      <div v-if="statusMessage" class="status-message" :class="`status-${operationStatus}`">
        <i class="pi" :class="getStatusIcon()" />
        <span>{{ statusMessage }}</span>
      </div>
    </div>

    <template #footer>
      <Button 
        v-if="canClose"
        label="Schließen" 
        @click="$emit('close')" 
        severity="secondary"
      />
      <Button 
        v-if="canCancel"
        label="Abbrechen" 
        @click="$emit('cancel')" 
        severity="danger"
        outlined
      />
    </template>
  </Dialog>
</template>

<script setup lang="ts">
import { computed } from 'vue'
import Dialog from 'primevue/dialog'
import Button from 'primevue/button'
import Divider from 'primevue/divider'
import type { OperationTask, UserPrompt } from '../types/common'
import { TaskStatus } from '../types/common'

interface Props {
  visible: boolean
  title?: string
  tasks: OperationTask[]
  operationStatus: 'pending' | 'running' | 'success' | 'failed' | 'waiting_for_user'
  statusMessage?: string
  userPrompt?: UserPrompt
  respondingToPrompt?: boolean
  hideCancel?: boolean
}

const props = withDefaults(defineProps<Props>(), {
  title: 'Operation',
  statusMessage: '',
  respondingToPrompt: false,
  hideCancel: false
})

const emit = defineEmits<{
  'update:visible': [value: boolean]
  'close': []
  'cancel': []
  'promptResponse': [promptId: string, response: string]
}>()

const isVisible = computed({
  get: () => props.visible,
  set: (value) => emit('update:visible', value)
})

const dialogTitle = computed(() => props.title)

const canClose = computed(() => {
  return props.operationStatus === 'success' || props.operationStatus === 'failed'
})

const canCancel = computed(() => {
  if (props.hideCancel) return false
  return props.operationStatus === 'running' || props.operationStatus === 'pending'
})

const getStatusIcon = () => {
  switch (props.operationStatus) {
    case 'success': return 'pi-check-circle'
    case 'failed': return 'pi-times-circle'
    case 'running': return 'pi-spin pi-spinner'
    case 'waiting_for_user': return 'pi-pause-circle'
    default: return 'pi-info-circle'
  }
}

const getButtonSeverity = (variant?: string) => {
  switch (variant) {
    case 'primary': return 'primary'
    case 'danger': return 'danger'
    case 'secondary': return 'secondary'
    default: return 'secondary'
  }
}

const handlePromptResponse = (response: string) => {
  if (props.userPrompt) {
    emit('promptResponse', props.userPrompt.id, response)
  }
}
</script>

<style scoped>
.task-progress-container {
  display: flex;
  flex-direction: column;
  gap: 1rem;
  min-height: 200px;
  max-height: 500px;
  overflow-y: auto;
}

.task-item {
  display: flex;
  gap: 1rem;
  align-items: flex-start;
  padding: 0.75rem;
  border-radius: 6px;
  transition: background-color 0.2s;
}

.task-item.task-active {
  background-color: rgba(var(--primary-500), 0.1);
}

.task-icon {
  flex-shrink: 0;
  width: 24px;
  height: 24px;
  display: flex;
  align-items: center;
  justify-content: center;
}

.task-icon i {
  font-size: 1.5rem;
}

.task-icon-pending {
  color: var(--gray-400);
}

.task-icon-running {
  color: var(--primary-500);
}

.task-icon-completed {
  color: var(--green-500);
}

.task-icon-failed {
  color: var(--red-500);
}

.task-icon-skipped {
  color: var(--orange-500);
}

.task-content {
  flex: 1;
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
}

.task-title {
  font-weight: 600;
  font-size: 0.95rem;
  color: var(--text-color);
}

.task-description {
  font-size: 0.85rem;
  color: var(--text-color-secondary);
}

.task-error {
  font-size: 0.85rem;
  color: var(--red-500);
  padding: 0.5rem;
  background-color: rgba(var(--red-500), 0.1);
  border-radius: 4px;
}

.task-progress-bar {
  margin-top: 0.5rem;
  height: 0.5rem;
}

.user-prompt-section {
  margin-top: 1rem;
}

.prompt-content {
  display: flex;
  gap: 1rem;
  padding: 1rem;
  background-color: var(--surface-50);
  border-radius: 8px;
  border: 1px solid var(--surface-200);
}

.prompt-icon {
  flex-shrink: 0;
}

.prompt-icon-symbol {
  font-size: 2rem;
  color: var(--orange-500);
}

.prompt-body {
  flex: 1;
}

.prompt-title {
  font-size: 1.1rem;
  font-weight: 600;
  margin: 0 0 0.5rem 0;
  color: var(--text-color);
}

.prompt-message {
  font-size: 0.9rem;
  color: var(--text-color-secondary);
  margin: 0 0 1rem 0;
  line-height: 1.5;
}

.prompt-actions {
  display: flex;
  gap: 0.5rem;
  flex-wrap: wrap;
}

.status-message {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  padding: 0.75rem;
  border-radius: 6px;
  font-weight: 500;
  margin-top: 1rem;
}

.status-success {
  background-color: rgba(var(--green-500), 0.1);
  color: var(--green-700);
}

.status-failed {
  background-color: rgba(var(--red-500), 0.1);
  color: var(--red-700);
}

.status-running {
  background-color: rgba(var(--primary-500), 0.1);
  color: var(--primary-700);
}

.status-waiting_for_user {
  background-color: rgba(var(--orange-500), 0.1);
  color: var(--orange-700);
}
</style>

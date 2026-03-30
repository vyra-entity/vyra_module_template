import { ref } from 'vue'
import { operationApi } from '../features/operations/operation.api'
import type { OperationStatus } from '../types/common'
import { useToast } from 'primevue/usetoast'
import { useRouter } from 'vue-router'

export function useOperationTracking() {
  const toast = useToast()
  const router = useRouter()

  const isTracking = ref(false)
  const operationStatus = ref<OperationStatus | null>(null)
  const respondingToPrompt = ref(false)

  let pollInterval: number | null = null
  let onCompleteCallback: (() => void) | null = null
  let currentCancelUrl: string | null = null

  /**
   * Start tracking an operation
   * @param operationId - The operation ID to track
   * @param operationType - Description of operation for user messages
   * @param options - Optional configuration including statusUrl and initialStatus
   */
  const startTracking = async (
    operationId: string,
    operationType: string,
    options?: {
      pollIntervalMs?: number
      maxAttempts?: number
      onComplete?: () => void
      navigateOnSuccess?: string
      statusUrl?: string
      initialStatus?: OperationStatus
      cancelUrl?: string
    }
  ) => {
    const pollIntervalMs = options?.pollIntervalMs || 2000
    const maxAttempts = options?.maxAttempts || 300 // 10 minutes at 2s interval
    const statusUrl = options?.statusUrl
    const cancelUrl = options?.cancelUrl
    let attempts = 0

    isTracking.value = true
    onCompleteCallback = options?.onComplete || null
    currentCancelUrl = cancelUrl || null

    // Set initial status if provided (sofort anzeigen!)
    if (options?.initialStatus) {
      operationStatus.value = options.initialStatus
    }

    const checkStatus = async () => {
      try {
        attempts++

        const status = await operationApi.getStatus(operationId, statusUrl)
        operationStatus.value = status

        // Check if finished
        if (status.status === 'success') {
          stopTracking()
          
          toast.add({
            severity: 'success',
            summary: `${operationType} abgeschlossen`,
            detail: status.message || 'Operation erfolgreich abgeschlossen',
            life: 5000
          })

          if (onCompleteCallback) {
            onCompleteCallback()
          }

          if (options?.navigateOnSuccess) {
            setTimeout(() => {
              router.push(options.navigateOnSuccess!)
            }, 1000)
          }

          return
        } else if (status.status === 'failed') {
          stopTracking()
          
          toast.add({
            severity: 'error',
            summary: `${operationType} fehlgeschlagen`,
            detail: status.error || status.message || 'Operation fehlgeschlagen',
            life: 7000
          })

          return
        }

        // Continue tracking if not finished
        if (attempts < maxAttempts && !['success', 'failed'].includes(status.status)) {
          pollInterval = window.setTimeout(checkStatus, pollIntervalMs)
        } else if (attempts >= maxAttempts) {
          stopTracking()
          toast.add({
            severity: 'warn',
            summary: 'Tracking-Timeout',
            detail: `${operationType} läuft noch, aber Status-Tracking wurde beendet.`,
            life: 5000
          })
        }

      } catch (error) {
        console.error('Status tracking error:', error)

        if (attempts < 5) {
          // Retry on error
          pollInterval = window.setTimeout(checkStatus, pollIntervalMs * 2)
        } else {
          stopTracking()
          toast.add({
            severity: 'error',
            summary: 'Tracking fehlgeschlagen',
            detail: 'Konnte Status nicht abrufen. Bitte prüfen Sie manuell.',
            life: 5000
          })
        }
      }
    }

    // Start immediately
    setTimeout(checkStatus, 1000)
  }

  /**
   * Stop tracking
   */
  const stopTracking = () => {
    if (pollInterval) {
      clearTimeout(pollInterval)
      pollInterval = null
    }
    isTracking.value = false
  }

  /**
   * Respond to user prompt
   */
  const respondToPrompt = async (promptId: string, response: string) => {
    if (!operationStatus.value) return

    try {
      respondingToPrompt.value = true
      await operationApi.respondToPrompt(operationStatus.value.operation_id, promptId, response)
      
      toast.add({
        severity: 'info',
        summary: 'Antwort gesendet',
        detail: 'Operation wird fortgesetzt...',
        life: 3000
      })

      // Clear the prompt from UI
      if (operationStatus.value) {
        operationStatus.value.user_prompt = undefined
        operationStatus.value.status = 'running'
      }

    } catch (error) {
      console.error('Failed to respond to prompt:', error)
      toast.add({
        severity: 'error',
        summary: 'Fehler',
        detail: 'Konnte Antwort nicht senden',
        life: 5000
      })
    } finally {
      respondingToPrompt.value = false
    }
  }

  /**
   * Cancel operation
   */
  const cancelOperation = async () => {
    if (!operationStatus.value) return

    try {
      await operationApi.cancelOperation(operationStatus.value.operation_id, currentCancelUrl || undefined)
      stopTracking()
      
      toast.add({
        severity: 'info',
        summary: 'Operation abgebrochen',
        detail: 'Die Operation wurde abgebrochen',
        life: 3000
      })

    } catch (error) {
      console.error('Failed to cancel operation:', error)
      toast.add({
        severity: 'error',
        summary: 'Fehler',
        detail: 'Konnte Operation nicht abbrechen',
        life: 5000
      })
    }
  }

  return {
    isTracking,
    operationStatus,
    respondingToPrompt,
    startTracking,
    stopTracking,
    respondToPrompt,
    cancelOperation
  }
}

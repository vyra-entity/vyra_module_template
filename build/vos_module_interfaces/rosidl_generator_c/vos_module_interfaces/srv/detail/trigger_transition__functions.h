// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vos_module_interfaces:srv/TriggerTransition.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__FUNCTIONS_H_
#define VOS_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "vos_module_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "vos_module_interfaces/srv/detail/trigger_transition__struct.h"

/// Initialize srv/TriggerTransition message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vos_module_interfaces__srv__TriggerTransition_Request
 * )) before or use
 * vos_module_interfaces__srv__TriggerTransition_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Request__init(vos_module_interfaces__srv__TriggerTransition_Request * msg);

/// Finalize srv/TriggerTransition message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__srv__TriggerTransition_Request__fini(vos_module_interfaces__srv__TriggerTransition_Request * msg);

/// Create srv/TriggerTransition message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vos_module_interfaces__srv__TriggerTransition_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
vos_module_interfaces__srv__TriggerTransition_Request *
vos_module_interfaces__srv__TriggerTransition_Request__create();

/// Destroy srv/TriggerTransition message.
/**
 * It calls
 * vos_module_interfaces__srv__TriggerTransition_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__srv__TriggerTransition_Request__destroy(vos_module_interfaces__srv__TriggerTransition_Request * msg);

/// Check for srv/TriggerTransition message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Request__are_equal(const vos_module_interfaces__srv__TriggerTransition_Request * lhs, const vos_module_interfaces__srv__TriggerTransition_Request * rhs);

/// Copy a srv/TriggerTransition message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Request__copy(
  const vos_module_interfaces__srv__TriggerTransition_Request * input,
  vos_module_interfaces__srv__TriggerTransition_Request * output);

/// Initialize array of srv/TriggerTransition messages.
/**
 * It allocates the memory for the number of elements and calls
 * vos_module_interfaces__srv__TriggerTransition_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Request__Sequence__init(vos_module_interfaces__srv__TriggerTransition_Request__Sequence * array, size_t size);

/// Finalize array of srv/TriggerTransition messages.
/**
 * It calls
 * vos_module_interfaces__srv__TriggerTransition_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__srv__TriggerTransition_Request__Sequence__fini(vos_module_interfaces__srv__TriggerTransition_Request__Sequence * array);

/// Create array of srv/TriggerTransition messages.
/**
 * It allocates the memory for the array and calls
 * vos_module_interfaces__srv__TriggerTransition_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
vos_module_interfaces__srv__TriggerTransition_Request__Sequence *
vos_module_interfaces__srv__TriggerTransition_Request__Sequence__create(size_t size);

/// Destroy array of srv/TriggerTransition messages.
/**
 * It calls
 * vos_module_interfaces__srv__TriggerTransition_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__srv__TriggerTransition_Request__Sequence__destroy(vos_module_interfaces__srv__TriggerTransition_Request__Sequence * array);

/// Check for srv/TriggerTransition message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Request__Sequence__are_equal(const vos_module_interfaces__srv__TriggerTransition_Request__Sequence * lhs, const vos_module_interfaces__srv__TriggerTransition_Request__Sequence * rhs);

/// Copy an array of srv/TriggerTransition messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Request__Sequence__copy(
  const vos_module_interfaces__srv__TriggerTransition_Request__Sequence * input,
  vos_module_interfaces__srv__TriggerTransition_Request__Sequence * output);

/// Initialize srv/TriggerTransition message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vos_module_interfaces__srv__TriggerTransition_Response
 * )) before or use
 * vos_module_interfaces__srv__TriggerTransition_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Response__init(vos_module_interfaces__srv__TriggerTransition_Response * msg);

/// Finalize srv/TriggerTransition message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__srv__TriggerTransition_Response__fini(vos_module_interfaces__srv__TriggerTransition_Response * msg);

/// Create srv/TriggerTransition message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vos_module_interfaces__srv__TriggerTransition_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
vos_module_interfaces__srv__TriggerTransition_Response *
vos_module_interfaces__srv__TriggerTransition_Response__create();

/// Destroy srv/TriggerTransition message.
/**
 * It calls
 * vos_module_interfaces__srv__TriggerTransition_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__srv__TriggerTransition_Response__destroy(vos_module_interfaces__srv__TriggerTransition_Response * msg);

/// Check for srv/TriggerTransition message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Response__are_equal(const vos_module_interfaces__srv__TriggerTransition_Response * lhs, const vos_module_interfaces__srv__TriggerTransition_Response * rhs);

/// Copy a srv/TriggerTransition message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Response__copy(
  const vos_module_interfaces__srv__TriggerTransition_Response * input,
  vos_module_interfaces__srv__TriggerTransition_Response * output);

/// Initialize array of srv/TriggerTransition messages.
/**
 * It allocates the memory for the number of elements and calls
 * vos_module_interfaces__srv__TriggerTransition_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Response__Sequence__init(vos_module_interfaces__srv__TriggerTransition_Response__Sequence * array, size_t size);

/// Finalize array of srv/TriggerTransition messages.
/**
 * It calls
 * vos_module_interfaces__srv__TriggerTransition_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__srv__TriggerTransition_Response__Sequence__fini(vos_module_interfaces__srv__TriggerTransition_Response__Sequence * array);

/// Create array of srv/TriggerTransition messages.
/**
 * It allocates the memory for the array and calls
 * vos_module_interfaces__srv__TriggerTransition_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
vos_module_interfaces__srv__TriggerTransition_Response__Sequence *
vos_module_interfaces__srv__TriggerTransition_Response__Sequence__create(size_t size);

/// Destroy array of srv/TriggerTransition messages.
/**
 * It calls
 * vos_module_interfaces__srv__TriggerTransition_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__srv__TriggerTransition_Response__Sequence__destroy(vos_module_interfaces__srv__TriggerTransition_Response__Sequence * array);

/// Check for srv/TriggerTransition message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Response__Sequence__are_equal(const vos_module_interfaces__srv__TriggerTransition_Response__Sequence * lhs, const vos_module_interfaces__srv__TriggerTransition_Response__Sequence * rhs);

/// Copy an array of srv/TriggerTransition messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__srv__TriggerTransition_Response__Sequence__copy(
  const vos_module_interfaces__srv__TriggerTransition_Response__Sequence * input,
  vos_module_interfaces__srv__TriggerTransition_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VOS_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__FUNCTIONS_H_

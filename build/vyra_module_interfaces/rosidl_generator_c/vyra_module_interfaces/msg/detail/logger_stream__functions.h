// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vyra_module_interfaces:msg/LoggerStream.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__FUNCTIONS_H_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "vyra_module_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "vyra_module_interfaces/msg/detail/logger_stream__struct.h"

/// Initialize msg/LoggerStream message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vyra_module_interfaces__msg__LoggerStream
 * )) before or use
 * vyra_module_interfaces__msg__LoggerStream__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
bool
vyra_module_interfaces__msg__LoggerStream__init(vyra_module_interfaces__msg__LoggerStream * msg);

/// Finalize msg/LoggerStream message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
void
vyra_module_interfaces__msg__LoggerStream__fini(vyra_module_interfaces__msg__LoggerStream * msg);

/// Create msg/LoggerStream message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vyra_module_interfaces__msg__LoggerStream__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
vyra_module_interfaces__msg__LoggerStream *
vyra_module_interfaces__msg__LoggerStream__create();

/// Destroy msg/LoggerStream message.
/**
 * It calls
 * vyra_module_interfaces__msg__LoggerStream__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
void
vyra_module_interfaces__msg__LoggerStream__destroy(vyra_module_interfaces__msg__LoggerStream * msg);

/// Check for msg/LoggerStream message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
bool
vyra_module_interfaces__msg__LoggerStream__are_equal(const vyra_module_interfaces__msg__LoggerStream * lhs, const vyra_module_interfaces__msg__LoggerStream * rhs);

/// Copy a msg/LoggerStream message.
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
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
bool
vyra_module_interfaces__msg__LoggerStream__copy(
  const vyra_module_interfaces__msg__LoggerStream * input,
  vyra_module_interfaces__msg__LoggerStream * output);

/// Initialize array of msg/LoggerStream messages.
/**
 * It allocates the memory for the number of elements and calls
 * vyra_module_interfaces__msg__LoggerStream__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
bool
vyra_module_interfaces__msg__LoggerStream__Sequence__init(vyra_module_interfaces__msg__LoggerStream__Sequence * array, size_t size);

/// Finalize array of msg/LoggerStream messages.
/**
 * It calls
 * vyra_module_interfaces__msg__LoggerStream__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
void
vyra_module_interfaces__msg__LoggerStream__Sequence__fini(vyra_module_interfaces__msg__LoggerStream__Sequence * array);

/// Create array of msg/LoggerStream messages.
/**
 * It allocates the memory for the array and calls
 * vyra_module_interfaces__msg__LoggerStream__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
vyra_module_interfaces__msg__LoggerStream__Sequence *
vyra_module_interfaces__msg__LoggerStream__Sequence__create(size_t size);

/// Destroy array of msg/LoggerStream messages.
/**
 * It calls
 * vyra_module_interfaces__msg__LoggerStream__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
void
vyra_module_interfaces__msg__LoggerStream__Sequence__destroy(vyra_module_interfaces__msg__LoggerStream__Sequence * array);

/// Check for msg/LoggerStream message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
bool
vyra_module_interfaces__msg__LoggerStream__Sequence__are_equal(const vyra_module_interfaces__msg__LoggerStream__Sequence * lhs, const vyra_module_interfaces__msg__LoggerStream__Sequence * rhs);

/// Copy an array of msg/LoggerStream messages.
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
ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
bool
vyra_module_interfaces__msg__LoggerStream__Sequence__copy(
  const vyra_module_interfaces__msg__LoggerStream__Sequence * input,
  vyra_module_interfaces__msg__LoggerStream__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__FUNCTIONS_H_

// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vos_module_interfaces:msg/NewsFeed.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__FUNCTIONS_H_
#define VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "vos_module_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "vos_module_interfaces/msg/detail/news_feed__struct.h"

/// Initialize msg/NewsFeed message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vos_module_interfaces__msg__NewsFeed
 * )) before or use
 * vos_module_interfaces__msg__NewsFeed__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__msg__NewsFeed__init(vos_module_interfaces__msg__NewsFeed * msg);

/// Finalize msg/NewsFeed message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__msg__NewsFeed__fini(vos_module_interfaces__msg__NewsFeed * msg);

/// Create msg/NewsFeed message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vos_module_interfaces__msg__NewsFeed__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
vos_module_interfaces__msg__NewsFeed *
vos_module_interfaces__msg__NewsFeed__create();

/// Destroy msg/NewsFeed message.
/**
 * It calls
 * vos_module_interfaces__msg__NewsFeed__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__msg__NewsFeed__destroy(vos_module_interfaces__msg__NewsFeed * msg);

/// Check for msg/NewsFeed message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__msg__NewsFeed__are_equal(const vos_module_interfaces__msg__NewsFeed * lhs, const vos_module_interfaces__msg__NewsFeed * rhs);

/// Copy a msg/NewsFeed message.
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
vos_module_interfaces__msg__NewsFeed__copy(
  const vos_module_interfaces__msg__NewsFeed * input,
  vos_module_interfaces__msg__NewsFeed * output);

/// Initialize array of msg/NewsFeed messages.
/**
 * It allocates the memory for the number of elements and calls
 * vos_module_interfaces__msg__NewsFeed__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__msg__NewsFeed__Sequence__init(vos_module_interfaces__msg__NewsFeed__Sequence * array, size_t size);

/// Finalize array of msg/NewsFeed messages.
/**
 * It calls
 * vos_module_interfaces__msg__NewsFeed__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__msg__NewsFeed__Sequence__fini(vos_module_interfaces__msg__NewsFeed__Sequence * array);

/// Create array of msg/NewsFeed messages.
/**
 * It allocates the memory for the array and calls
 * vos_module_interfaces__msg__NewsFeed__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
vos_module_interfaces__msg__NewsFeed__Sequence *
vos_module_interfaces__msg__NewsFeed__Sequence__create(size_t size);

/// Destroy array of msg/NewsFeed messages.
/**
 * It calls
 * vos_module_interfaces__msg__NewsFeed__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
void
vos_module_interfaces__msg__NewsFeed__Sequence__destroy(vos_module_interfaces__msg__NewsFeed__Sequence * array);

/// Check for msg/NewsFeed message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vos_module_interfaces
bool
vos_module_interfaces__msg__NewsFeed__Sequence__are_equal(const vos_module_interfaces__msg__NewsFeed__Sequence * lhs, const vos_module_interfaces__msg__NewsFeed__Sequence * rhs);

/// Copy an array of msg/NewsFeed messages.
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
vos_module_interfaces__msg__NewsFeed__Sequence__copy(
  const vos_module_interfaces__msg__NewsFeed__Sequence * input,
  vos_module_interfaces__msg__NewsFeed__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__FUNCTIONS_H_

// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vyra_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "vyra_module_interfaces/srv/detail/get_logs__struct.h"
#include "vyra_module_interfaces/srv/detail/get_logs__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vyra_module_interfaces__srv__get_logs__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
    if (class_attr == NULL) {
      return false;
    }
    PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
    if (name_attr == NULL) {
      Py_DECREF(class_attr);
      return false;
    }
    PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
    if (module_attr == NULL) {
      Py_DECREF(name_attr);
      Py_DECREF(class_attr);
      return false;
    }

    // PyUnicode_1BYTE_DATA is just a cast
    assert(strncmp("vyra_module_interfaces.srv._get_logs", (char *)PyUnicode_1BYTE_DATA(module_attr), 36) == 0);
    assert(strncmp("GetLogs_Request", (char *)PyUnicode_1BYTE_DATA(name_attr), 15) == 0);

    Py_DECREF(module_attr);
    Py_DECREF(name_attr);
    Py_DECREF(class_attr);
  }
  vyra_module_interfaces__srv__GetLogs_Request * ros_message = _ros_message;
  {  // log_lines
    PyObject * field = PyObject_GetAttrString(_pymsg, "log_lines");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->log_lines = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // log_level
    PyObject * field = PyObject_GetAttrString(_pymsg, "log_level");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->log_level = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vyra_module_interfaces__srv__get_logs__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetLogs_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vyra_module_interfaces.srv._get_logs");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetLogs_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vyra_module_interfaces__srv__GetLogs_Request * ros_message = (vyra_module_interfaces__srv__GetLogs_Request *)raw_ros_message;
  {  // log_lines
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->log_lines);
    {
      int rc = PyObject_SetAttrString(_pymessage, "log_lines", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // log_level
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->log_level);
    {
      int rc = PyObject_SetAttrString(_pymessage, "log_level", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
// already included above
// #include <Python.h>
// already included above
// #include <stdbool.h>
// already included above
// #include "numpy/ndarrayobject.h"
// already included above
// #include "rosidl_runtime_c/visibility_control.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_logs__struct.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_logs__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes
#include "vyra_module_interfaces/msg/detail/logger_stream__functions.h"
// end nested array functions include
bool vyra_module_interfaces__msg__logger_stream__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vyra_module_interfaces__msg__logger_stream__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vyra_module_interfaces__srv__get_logs__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
    if (class_attr == NULL) {
      return false;
    }
    PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
    if (name_attr == NULL) {
      Py_DECREF(class_attr);
      return false;
    }
    PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
    if (module_attr == NULL) {
      Py_DECREF(name_attr);
      Py_DECREF(class_attr);
      return false;
    }

    // PyUnicode_1BYTE_DATA is just a cast
    assert(strncmp("vyra_module_interfaces.srv._get_logs", (char *)PyUnicode_1BYTE_DATA(module_attr), 36) == 0);
    assert(strncmp("GetLogs_Response", (char *)PyUnicode_1BYTE_DATA(name_attr), 16) == 0);

    Py_DECREF(module_attr);
    Py_DECREF(name_attr);
    Py_DECREF(class_attr);
  }
  vyra_module_interfaces__srv__GetLogs_Response * ros_message = _ros_message;
  {  // log_messages
    PyObject * field = PyObject_GetAttrString(_pymsg, "log_messages");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'log_messages'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!vyra_module_interfaces__msg__LoggerStream__Sequence__init(&(ros_message->log_messages), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create vyra_module_interfaces__msg__LoggerStream__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    vyra_module_interfaces__msg__LoggerStream * dest = ros_message->log_messages.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!vyra_module_interfaces__msg__logger_stream__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vyra_module_interfaces__srv__get_logs__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetLogs_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vyra_module_interfaces.srv._get_logs");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetLogs_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vyra_module_interfaces__srv__GetLogs_Response * ros_message = (vyra_module_interfaces__srv__GetLogs_Response *)raw_ros_message;
  {  // log_messages
    PyObject * field = NULL;
    size_t size = ros_message->log_messages.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    vyra_module_interfaces__msg__LoggerStream * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->log_messages.data[i]);
      PyObject * pyitem = vyra_module_interfaces__msg__logger_stream__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "log_messages", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
// already included above
// #include <Python.h>
// already included above
// #include <stdbool.h>
// already included above
// #include "numpy/ndarrayobject.h"
// already included above
// #include "rosidl_runtime_c/visibility_control.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_logs__struct.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_logs__functions.h"

// already included above
// #include "rosidl_runtime_c/primitives_sequence.h"
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes


// end nested array functions include
ROSIDL_GENERATOR_C_IMPORT
bool service_msgs__msg__service_event_info__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * service_msgs__msg__service_event_info__convert_to_py(void * raw_ros_message);
bool vyra_module_interfaces__srv__get_logs__request__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vyra_module_interfaces__srv__get_logs__request__convert_to_py(void * raw_ros_message);
bool vyra_module_interfaces__srv__get_logs__response__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vyra_module_interfaces__srv__get_logs__response__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vyra_module_interfaces__srv__get_logs__event__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
    if (class_attr == NULL) {
      return false;
    }
    PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
    if (name_attr == NULL) {
      Py_DECREF(class_attr);
      return false;
    }
    PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
    if (module_attr == NULL) {
      Py_DECREF(name_attr);
      Py_DECREF(class_attr);
      return false;
    }

    // PyUnicode_1BYTE_DATA is just a cast
    assert(strncmp("vyra_module_interfaces.srv._get_logs", (char *)PyUnicode_1BYTE_DATA(module_attr), 36) == 0);
    assert(strncmp("GetLogs_Event", (char *)PyUnicode_1BYTE_DATA(name_attr), 13) == 0);

    Py_DECREF(module_attr);
    Py_DECREF(name_attr);
    Py_DECREF(class_attr);
  }
  vyra_module_interfaces__srv__GetLogs_Event * ros_message = _ros_message;
  {  // info
    PyObject * field = PyObject_GetAttrString(_pymsg, "info");
    if (!field) {
      return false;
    }
    if (!service_msgs__msg__service_event_info__convert_from_py(field, &ros_message->info)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // request
    PyObject * field = PyObject_GetAttrString(_pymsg, "request");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'request'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!vyra_module_interfaces__srv__GetLogs_Request__Sequence__init(&(ros_message->request), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create vyra_module_interfaces__srv__GetLogs_Request__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    vyra_module_interfaces__srv__GetLogs_Request * dest = ros_message->request.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!vyra_module_interfaces__srv__get_logs__request__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // response
    PyObject * field = PyObject_GetAttrString(_pymsg, "response");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'response'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!vyra_module_interfaces__srv__GetLogs_Response__Sequence__init(&(ros_message->response), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create vyra_module_interfaces__srv__GetLogs_Response__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    vyra_module_interfaces__srv__GetLogs_Response * dest = ros_message->response.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!vyra_module_interfaces__srv__get_logs__response__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vyra_module_interfaces__srv__get_logs__event__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetLogs_Event */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vyra_module_interfaces.srv._get_logs");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetLogs_Event");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vyra_module_interfaces__srv__GetLogs_Event * ros_message = (vyra_module_interfaces__srv__GetLogs_Event *)raw_ros_message;
  {  // info
    PyObject * field = NULL;
    field = service_msgs__msg__service_event_info__convert_to_py(&ros_message->info);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "info", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // request
    PyObject * field = NULL;
    size_t size = ros_message->request.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    vyra_module_interfaces__srv__GetLogs_Request * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->request.data[i]);
      PyObject * pyitem = vyra_module_interfaces__srv__get_logs__request__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "request", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // response
    PyObject * field = NULL;
    size_t size = ros_message->response.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    vyra_module_interfaces__srv__GetLogs_Response * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->response.data[i]);
      PyObject * pyitem = vyra_module_interfaces__srv__get_logs__response__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "response", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

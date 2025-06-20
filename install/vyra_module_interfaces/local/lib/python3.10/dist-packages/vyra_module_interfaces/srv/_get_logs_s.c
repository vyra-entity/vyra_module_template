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
    char full_classname_dest[53];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("vyra_module_interfaces.srv._get_logs.GetLogs_Request", full_classname_dest, 52) == 0);
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
    char full_classname_dest[54];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("vyra_module_interfaces.srv._get_logs.GetLogs_Response", full_classname_dest, 53) == 0);
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

// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aimdk_msgs:msg/PlayTtsRequest.idl
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
#include "aimdk_msgs/msg/detail/play_tts_request__struct.h"
#include "aimdk_msgs/msg/detail/play_tts_request__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

bool aimdk_msgs__msg__tts_priority_level__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__tts_priority_level__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__msg__play_tts_request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[48];
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
    assert(strncmp("aimdk_msgs.msg._play_tts_request.PlayTtsRequest", full_classname_dest, 47) == 0);
  }
  aimdk_msgs__msg__PlayTtsRequest * ros_message = _ros_message;
  {  // text
    PyObject * field = PyObject_GetAttrString(_pymsg, "text");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->text, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // priority_level
    PyObject * field = PyObject_GetAttrString(_pymsg, "priority_level");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__tts_priority_level__convert_from_py(field, &ros_message->priority_level)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // priority_weight
    PyObject * field = PyObject_GetAttrString(_pymsg, "priority_weight");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->priority_weight = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // domain
    PyObject * field = PyObject_GetAttrString(_pymsg, "domain");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->domain, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // trace_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "trace_id");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->trace_id, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // is_interrupted
    PyObject * field = PyObject_GetAttrString(_pymsg, "is_interrupted");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->is_interrupted = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__msg__play_tts_request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of PlayTtsRequest */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.msg._play_tts_request");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "PlayTtsRequest");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__msg__PlayTtsRequest * ros_message = (aimdk_msgs__msg__PlayTtsRequest *)raw_ros_message;
  {  // text
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->text.data,
      strlen(ros_message->text.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "text", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // priority_level
    PyObject * field = NULL;
    field = aimdk_msgs__msg__tts_priority_level__convert_to_py(&ros_message->priority_level);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "priority_level", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // priority_weight
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->priority_weight);
    {
      int rc = PyObject_SetAttrString(_pymessage, "priority_weight", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // domain
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->domain.data,
      strlen(ros_message->domain.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "domain", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // trace_id
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->trace_id.data,
      strlen(ros_message->trace_id.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "trace_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // is_interrupted
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->is_interrupted ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "is_interrupted", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

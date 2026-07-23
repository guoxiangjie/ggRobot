// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aimdk_msgs:msg/AudioFile.idl
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
#include "aimdk_msgs/msg/detail/audio_file__struct.h"
#include "aimdk_msgs/msg/detail/audio_file__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

bool aimdk_msgs__msg__audio_info__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__audio_info__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__msg__audio_file__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[37];
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
    assert(strncmp("aimdk_msgs.msg._audio_file.AudioFile", full_classname_dest, 36) == 0);
  }
  aimdk_msgs__msg__AudioFile * ros_message = _ros_message;
  {  // pkg_name
    PyObject * field = PyObject_GetAttrString(_pymsg, "pkg_name");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->pkg_name, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // file_name
    PyObject * field = PyObject_GetAttrString(_pymsg, "file_name");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->file_name, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // file_path
    PyObject * field = PyObject_GetAttrString(_pymsg, "file_path");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->file_path, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // info
    PyObject * field = PyObject_GetAttrString(_pymsg, "info");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__audio_info__convert_from_py(field, &ros_message->info)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // priority
    PyObject * field = PyObject_GetAttrString(_pymsg, "priority");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->priority = PyLong_AsUnsignedLong(field);
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

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__msg__audio_file__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of AudioFile */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.msg._audio_file");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "AudioFile");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__msg__AudioFile * ros_message = (aimdk_msgs__msg__AudioFile *)raw_ros_message;
  {  // pkg_name
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->pkg_name.data,
      strlen(ros_message->pkg_name.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "pkg_name", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // file_name
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->file_name.data,
      strlen(ros_message->file_name.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "file_name", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // file_path
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->file_path.data,
      strlen(ros_message->file_path.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "file_path", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // info
    PyObject * field = NULL;
    field = aimdk_msgs__msg__audio_info__convert_to_py(&ros_message->info);
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
  {  // priority
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->priority);
    {
      int rc = PyObject_SetAttrString(_pymessage, "priority", field);
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

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

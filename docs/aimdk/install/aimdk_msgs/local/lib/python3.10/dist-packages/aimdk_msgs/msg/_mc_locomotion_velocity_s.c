// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aimdk_msgs:msg/McLocomotionVelocity.idl
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
#include "aimdk_msgs/msg/detail/mc_locomotion_velocity__struct.h"
#include "aimdk_msgs/msg/detail/mc_locomotion_velocity__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

bool aimdk_msgs__msg__message_header__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__message_header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__msg__mc_locomotion_velocity__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[60];
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
    assert(strncmp("aimdk_msgs.msg._mc_locomotion_velocity.McLocomotionVelocity", full_classname_dest, 59) == 0);
  }
  aimdk_msgs__msg__McLocomotionVelocity * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__message_header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // source
    PyObject * field = PyObject_GetAttrString(_pymsg, "source");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->source, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // forward_velocity
    PyObject * field = PyObject_GetAttrString(_pymsg, "forward_velocity");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->forward_velocity = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // lateral_velocity
    PyObject * field = PyObject_GetAttrString(_pymsg, "lateral_velocity");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->lateral_velocity = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // angular_velocity
    PyObject * field = PyObject_GetAttrString(_pymsg, "angular_velocity");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->angular_velocity = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__msg__mc_locomotion_velocity__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of McLocomotionVelocity */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.msg._mc_locomotion_velocity");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "McLocomotionVelocity");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__msg__McLocomotionVelocity * ros_message = (aimdk_msgs__msg__McLocomotionVelocity *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = aimdk_msgs__msg__message_header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // source
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->source.data,
      strlen(ros_message->source.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "source", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // forward_velocity
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->forward_velocity);
    {
      int rc = PyObject_SetAttrString(_pymessage, "forward_velocity", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // lateral_velocity
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->lateral_velocity);
    {
      int rc = PyObject_SetAttrString(_pymessage, "lateral_velocity", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // angular_velocity
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->angular_velocity);
    {
      int rc = PyObject_SetAttrString(_pymessage, "angular_velocity", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

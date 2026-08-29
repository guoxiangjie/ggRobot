// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aimdk_msgs:srv/SetMcPresetMotion.idl
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
#include "aimdk_msgs/srv/detail/set_mc_preset_motion__struct.h"
#include "aimdk_msgs/srv/detail/set_mc_preset_motion__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

bool aimdk_msgs__msg__request_header__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__request_header__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__mc_control_area__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__mc_control_area__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__mc_preset_motion__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__mc_preset_motion__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__srv__set_mc_preset_motion__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[63];
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
    assert(strncmp("aimdk_msgs.srv._set_mc_preset_motion.SetMcPresetMotion_Request", full_classname_dest, 62) == 0);
  }
  aimdk_msgs__srv__SetMcPresetMotion_Request * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__request_header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // area
    PyObject * field = PyObject_GetAttrString(_pymsg, "area");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__mc_control_area__convert_from_py(field, &ros_message->area)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // motion
    PyObject * field = PyObject_GetAttrString(_pymsg, "motion");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__mc_preset_motion__convert_from_py(field, &ros_message->motion)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // interrupt
    PyObject * field = PyObject_GetAttrString(_pymsg, "interrupt");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->interrupt = (Py_True == field);
    Py_DECREF(field);
  }
  {  // ani_path
    PyObject * field = PyObject_GetAttrString(_pymsg, "ani_path");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->ani_path, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // play_timestamp
    PyObject * field = PyObject_GetAttrString(_pymsg, "play_timestamp");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->play_timestamp = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__srv__set_mc_preset_motion__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SetMcPresetMotion_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.srv._set_mc_preset_motion");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SetMcPresetMotion_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__srv__SetMcPresetMotion_Request * ros_message = (aimdk_msgs__srv__SetMcPresetMotion_Request *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = aimdk_msgs__msg__request_header__convert_to_py(&ros_message->header);
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
  {  // area
    PyObject * field = NULL;
    field = aimdk_msgs__msg__mc_control_area__convert_to_py(&ros_message->area);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "area", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // motion
    PyObject * field = NULL;
    field = aimdk_msgs__msg__mc_preset_motion__convert_to_py(&ros_message->motion);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "motion", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // interrupt
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->interrupt ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "interrupt", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ani_path
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->ani_path.data,
      strlen(ros_message->ani_path.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "ani_path", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // play_timestamp
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->play_timestamp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "play_timestamp", field);
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
// #include "aimdk_msgs/srv/detail/set_mc_preset_motion__struct.h"
// already included above
// #include "aimdk_msgs/srv/detail/set_mc_preset_motion__functions.h"

bool aimdk_msgs__msg__common_task_response__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__common_task_response__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__srv__set_mc_preset_motion__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[64];
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
    assert(strncmp("aimdk_msgs.srv._set_mc_preset_motion.SetMcPresetMotion_Response", full_classname_dest, 63) == 0);
  }
  aimdk_msgs__srv__SetMcPresetMotion_Response * ros_message = _ros_message;
  {  // response
    PyObject * field = PyObject_GetAttrString(_pymsg, "response");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__common_task_response__convert_from_py(field, &ros_message->response)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__srv__set_mc_preset_motion__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SetMcPresetMotion_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.srv._set_mc_preset_motion");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SetMcPresetMotion_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__srv__SetMcPresetMotion_Response * ros_message = (aimdk_msgs__srv__SetMcPresetMotion_Response *)raw_ros_message;
  {  // response
    PyObject * field = NULL;
    field = aimdk_msgs__msg__common_task_response__convert_to_py(&ros_message->response);
    if (!field) {
      return NULL;
    }
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

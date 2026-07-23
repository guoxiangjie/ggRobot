// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aimdk_msgs:srv/SetPmuLed.idl
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
#include "aimdk_msgs/srv/detail/set_pmu_led__struct.h"
#include "aimdk_msgs/srv/detail/set_pmu_led__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

bool aimdk_msgs__msg__common_request__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__common_request__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__srv__set_pmu_led__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[46];
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
    assert(strncmp("aimdk_msgs.srv._set_pmu_led.SetPmuLed_Request", full_classname_dest, 45) == 0);
  }
  aimdk_msgs__srv__SetPmuLed_Request * ros_message = _ros_message;
  {  // request
    PyObject * field = PyObject_GetAttrString(_pymsg, "request");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__common_request__convert_from_py(field, &ros_message->request)) {
      Py_DECREF(field);
      return false;
    }
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
  {  // led_strip_mode
    PyObject * field = PyObject_GetAttrString(_pymsg, "led_strip_mode");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->led_strip_mode = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // r
    PyObject * field = PyObject_GetAttrString(_pymsg, "r");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->r = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // g
    PyObject * field = PyObject_GetAttrString(_pymsg, "g");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->g = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // b
    PyObject * field = PyObject_GetAttrString(_pymsg, "b");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->b = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // priority
    PyObject * field = PyObject_GetAttrString(_pymsg, "priority");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->priority = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // reset_priority
    PyObject * field = PyObject_GetAttrString(_pymsg, "reset_priority");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->reset_priority = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__srv__set_pmu_led__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SetPmuLed_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.srv._set_pmu_led");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SetPmuLed_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__srv__SetPmuLed_Request * ros_message = (aimdk_msgs__srv__SetPmuLed_Request *)raw_ros_message;
  {  // request
    PyObject * field = NULL;
    field = aimdk_msgs__msg__common_request__convert_to_py(&ros_message->request);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "request", field);
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
  {  // led_strip_mode
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->led_strip_mode);
    {
      int rc = PyObject_SetAttrString(_pymessage, "led_strip_mode", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // r
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->r);
    {
      int rc = PyObject_SetAttrString(_pymessage, "r", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // g
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->g);
    {
      int rc = PyObject_SetAttrString(_pymessage, "g", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // b
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->b);
    {
      int rc = PyObject_SetAttrString(_pymessage, "b", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // priority
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->priority);
    {
      int rc = PyObject_SetAttrString(_pymessage, "priority", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // reset_priority
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->reset_priority ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "reset_priority", field);
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
// #include "aimdk_msgs/srv/detail/set_pmu_led__struct.h"
// already included above
// #include "aimdk_msgs/srv/detail/set_pmu_led__functions.h"

bool aimdk_msgs__msg__response_header__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__response_header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__srv__set_pmu_led__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[47];
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
    assert(strncmp("aimdk_msgs.srv._set_pmu_led.SetPmuLed_Response", full_classname_dest, 46) == 0);
  }
  aimdk_msgs__srv__SetPmuLed_Response * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__response_header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // status_code
    PyObject * field = PyObject_GetAttrString(_pymsg, "status_code");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->status_code = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__srv__set_pmu_led__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of SetPmuLed_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.srv._set_pmu_led");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "SetPmuLed_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__srv__SetPmuLed_Response * ros_message = (aimdk_msgs__srv__SetPmuLed_Response *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = aimdk_msgs__msg__response_header__convert_to_py(&ros_message->header);
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
  {  // status_code
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->status_code);
    {
      int rc = PyObject_SetAttrString(_pymessage, "status_code", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

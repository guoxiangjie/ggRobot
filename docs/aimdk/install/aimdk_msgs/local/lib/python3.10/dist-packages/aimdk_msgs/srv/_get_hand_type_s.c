// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aimdk_msgs:srv/GetHandType.idl
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
#include "aimdk_msgs/srv/detail/get_hand_type__struct.h"
#include "aimdk_msgs/srv/detail/get_hand_type__functions.h"

bool aimdk_msgs__msg__common_request__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__common_request__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__srv__get_hand_type__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[50];
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
    assert(strncmp("aimdk_msgs.srv._get_hand_type.GetHandType_Request", full_classname_dest, 49) == 0);
  }
  aimdk_msgs__srv__GetHandType_Request * ros_message = _ros_message;
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

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__srv__get_hand_type__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetHandType_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.srv._get_hand_type");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetHandType_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__srv__GetHandType_Request * ros_message = (aimdk_msgs__srv__GetHandType_Request *)raw_ros_message;
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
// #include "aimdk_msgs/srv/detail/get_hand_type__struct.h"
// already included above
// #include "aimdk_msgs/srv/detail/get_hand_type__functions.h"

bool aimdk_msgs__msg__common_response__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__common_response__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__hand_type__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__hand_type__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__hand_type__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__hand_type__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__srv__get_hand_type__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[51];
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
    assert(strncmp("aimdk_msgs.srv._get_hand_type.GetHandType_Response", full_classname_dest, 50) == 0);
  }
  aimdk_msgs__srv__GetHandType_Response * ros_message = _ros_message;
  {  // reponse
    PyObject * field = PyObject_GetAttrString(_pymsg, "reponse");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__common_response__convert_from_py(field, &ros_message->reponse)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // left_hands_type
    PyObject * field = PyObject_GetAttrString(_pymsg, "left_hands_type");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__hand_type__convert_from_py(field, &ros_message->left_hands_type)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // right_hands_type
    PyObject * field = PyObject_GetAttrString(_pymsg, "right_hands_type");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__hand_type__convert_from_py(field, &ros_message->right_hands_type)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__srv__get_hand_type__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetHandType_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.srv._get_hand_type");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetHandType_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__srv__GetHandType_Response * ros_message = (aimdk_msgs__srv__GetHandType_Response *)raw_ros_message;
  {  // reponse
    PyObject * field = NULL;
    field = aimdk_msgs__msg__common_response__convert_to_py(&ros_message->reponse);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "reponse", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // left_hands_type
    PyObject * field = NULL;
    field = aimdk_msgs__msg__hand_type__convert_to_py(&ros_message->left_hands_type);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "left_hands_type", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // right_hands_type
    PyObject * field = NULL;
    field = aimdk_msgs__msg__hand_type__convert_to_py(&ros_message->right_hands_type);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "right_hands_type", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

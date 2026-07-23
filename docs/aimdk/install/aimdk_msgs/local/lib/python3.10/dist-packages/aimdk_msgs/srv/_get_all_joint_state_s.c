// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aimdk_msgs:srv/GetAllJointState.idl
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
#include "aimdk_msgs/srv/detail/get_all_joint_state__struct.h"
#include "aimdk_msgs/srv/detail/get_all_joint_state__functions.h"

bool aimdk_msgs__msg__common_request__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__common_request__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__srv__get_all_joint_state__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[61];
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
    assert(strncmp("aimdk_msgs.srv._get_all_joint_state.GetAllJointState_Request", full_classname_dest, 60) == 0);
  }
  aimdk_msgs__srv__GetAllJointState_Request * ros_message = _ros_message;
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
PyObject * aimdk_msgs__srv__get_all_joint_state__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetAllJointState_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.srv._get_all_joint_state");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetAllJointState_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__srv__GetAllJointState_Request * ros_message = (aimdk_msgs__srv__GetAllJointState_Request *)raw_ros_message;
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
// #include "aimdk_msgs/srv/detail/get_all_joint_state__struct.h"
// already included above
// #include "aimdk_msgs/srv/detail/get_all_joint_state__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes
#include "aimdk_msgs/msg/detail/joint_state__functions.h"
// end nested array functions include
bool aimdk_msgs__msg__common_response__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__common_response__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__joint_state__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__joint_state__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__joint_state__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__joint_state__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__joint_state__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__joint_state__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__joint_state__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__joint_state__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__srv__get_all_joint_state__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[62];
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
    assert(strncmp("aimdk_msgs.srv._get_all_joint_state.GetAllJointState_Response", full_classname_dest, 61) == 0);
  }
  aimdk_msgs__srv__GetAllJointState_Response * ros_message = _ros_message;
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
  {  // head_joints
    PyObject * field = PyObject_GetAttrString(_pymsg, "head_joints");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'head_joints'");
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
    if (!aimdk_msgs__msg__JointState__Sequence__init(&(ros_message->head_joints), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aimdk_msgs__msg__JointState__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aimdk_msgs__msg__JointState * dest = ros_message->head_joints.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aimdk_msgs__msg__joint_state__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // arm_joints
    PyObject * field = PyObject_GetAttrString(_pymsg, "arm_joints");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'arm_joints'");
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
    if (!aimdk_msgs__msg__JointState__Sequence__init(&(ros_message->arm_joints), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aimdk_msgs__msg__JointState__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aimdk_msgs__msg__JointState * dest = ros_message->arm_joints.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aimdk_msgs__msg__joint_state__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // waist_joints
    PyObject * field = PyObject_GetAttrString(_pymsg, "waist_joints");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'waist_joints'");
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
    if (!aimdk_msgs__msg__JointState__Sequence__init(&(ros_message->waist_joints), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aimdk_msgs__msg__JointState__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aimdk_msgs__msg__JointState * dest = ros_message->waist_joints.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aimdk_msgs__msg__joint_state__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // leg_joints
    PyObject * field = PyObject_GetAttrString(_pymsg, "leg_joints");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'leg_joints'");
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
    if (!aimdk_msgs__msg__JointState__Sequence__init(&(ros_message->leg_joints), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aimdk_msgs__msg__JointState__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aimdk_msgs__msg__JointState * dest = ros_message->leg_joints.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aimdk_msgs__msg__joint_state__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
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
PyObject * aimdk_msgs__srv__get_all_joint_state__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetAllJointState_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.srv._get_all_joint_state");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetAllJointState_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__srv__GetAllJointState_Response * ros_message = (aimdk_msgs__srv__GetAllJointState_Response *)raw_ros_message;
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
  {  // head_joints
    PyObject * field = NULL;
    size_t size = ros_message->head_joints.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aimdk_msgs__msg__JointState * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->head_joints.data[i]);
      PyObject * pyitem = aimdk_msgs__msg__joint_state__convert_to_py(item);
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
      int rc = PyObject_SetAttrString(_pymessage, "head_joints", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // arm_joints
    PyObject * field = NULL;
    size_t size = ros_message->arm_joints.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aimdk_msgs__msg__JointState * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->arm_joints.data[i]);
      PyObject * pyitem = aimdk_msgs__msg__joint_state__convert_to_py(item);
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
      int rc = PyObject_SetAttrString(_pymessage, "arm_joints", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // waist_joints
    PyObject * field = NULL;
    size_t size = ros_message->waist_joints.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aimdk_msgs__msg__JointState * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->waist_joints.data[i]);
      PyObject * pyitem = aimdk_msgs__msg__joint_state__convert_to_py(item);
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
      int rc = PyObject_SetAttrString(_pymessage, "waist_joints", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // leg_joints
    PyObject * field = NULL;
    size_t size = ros_message->leg_joints.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aimdk_msgs__msg__JointState * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->leg_joints.data[i]);
      PyObject * pyitem = aimdk_msgs__msg__joint_state__convert_to_py(item);
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
      int rc = PyObject_SetAttrString(_pymessage, "leg_joints", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

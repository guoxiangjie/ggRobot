// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aimdk_msgs:msg/HandCommandArray.idl
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
#include "aimdk_msgs/msg/detail/hand_command_array__struct.h"
#include "aimdk_msgs/msg/detail/hand_command_array__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes
#include "aimdk_msgs/msg/detail/hand_command__functions.h"
// end nested array functions include
bool aimdk_msgs__msg__message_header__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__message_header__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__hand_type__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__hand_type__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__hand_command__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__hand_command__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__hand_type__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__hand_type__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__hand_command__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__hand_command__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__msg__hand_command_array__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[52];
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
    assert(strncmp("aimdk_msgs.msg._hand_command_array.HandCommandArray", full_classname_dest, 51) == 0);
  }
  aimdk_msgs__msg__HandCommandArray * ros_message = _ros_message;
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
  {  // left_hand_type
    PyObject * field = PyObject_GetAttrString(_pymsg, "left_hand_type");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__hand_type__convert_from_py(field, &ros_message->left_hand_type)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // left_hands
    PyObject * field = PyObject_GetAttrString(_pymsg, "left_hands");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'left_hands'");
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
    if (!aimdk_msgs__msg__HandCommand__Sequence__init(&(ros_message->left_hands), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aimdk_msgs__msg__HandCommand__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aimdk_msgs__msg__HandCommand * dest = ros_message->left_hands.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aimdk_msgs__msg__hand_command__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // right_hand_type
    PyObject * field = PyObject_GetAttrString(_pymsg, "right_hand_type");
    if (!field) {
      return false;
    }
    if (!aimdk_msgs__msg__hand_type__convert_from_py(field, &ros_message->right_hand_type)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // right_hands
    PyObject * field = PyObject_GetAttrString(_pymsg, "right_hands");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'right_hands'");
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
    if (!aimdk_msgs__msg__HandCommand__Sequence__init(&(ros_message->right_hands), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aimdk_msgs__msg__HandCommand__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aimdk_msgs__msg__HandCommand * dest = ros_message->right_hands.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aimdk_msgs__msg__hand_command__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
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
PyObject * aimdk_msgs__msg__hand_command_array__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of HandCommandArray */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.msg._hand_command_array");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "HandCommandArray");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__msg__HandCommandArray * ros_message = (aimdk_msgs__msg__HandCommandArray *)raw_ros_message;
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
  {  // left_hand_type
    PyObject * field = NULL;
    field = aimdk_msgs__msg__hand_type__convert_to_py(&ros_message->left_hand_type);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "left_hand_type", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // left_hands
    PyObject * field = NULL;
    size_t size = ros_message->left_hands.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aimdk_msgs__msg__HandCommand * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->left_hands.data[i]);
      PyObject * pyitem = aimdk_msgs__msg__hand_command__convert_to_py(item);
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
      int rc = PyObject_SetAttrString(_pymessage, "left_hands", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // right_hand_type
    PyObject * field = NULL;
    field = aimdk_msgs__msg__hand_type__convert_to_py(&ros_message->right_hand_type);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "right_hand_type", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // right_hands
    PyObject * field = NULL;
    size_t size = ros_message->right_hands.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aimdk_msgs__msg__HandCommand * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->right_hands.data[i]);
      PyObject * pyitem = aimdk_msgs__msg__hand_command__convert_to_py(item);
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
      int rc = PyObject_SetAttrString(_pymessage, "right_hands", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

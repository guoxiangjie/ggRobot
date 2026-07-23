// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aimdk_msgs:srv/GetStoredMapByName.idl
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
#include "aimdk_msgs/srv/detail/get_stored_map_by_name__struct.h"
#include "aimdk_msgs/srv/detail/get_stored_map_by_name__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__srv__get_stored_map_by_name__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[66];
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
    assert(strncmp("aimdk_msgs.srv._get_stored_map_by_name.GetStoredMapByName_Request", full_classname_dest, 65) == 0);
  }
  aimdk_msgs__srv__GetStoredMapByName_Request * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // map_name
    PyObject * field = PyObject_GetAttrString(_pymsg, "map_name");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->map_name, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__srv__get_stored_map_by_name__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetStoredMapByName_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.srv._get_stored_map_by_name");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetStoredMapByName_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__srv__GetStoredMapByName_Request * ros_message = (aimdk_msgs__srv__GetStoredMapByName_Request *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
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
  {  // map_name
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->map_name.data,
      strlen(ros_message->map_name.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "map_name", field);
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
// #include "aimdk_msgs/srv/detail/get_stored_map_by_name__struct.h"
// already included above
// #include "aimdk_msgs/srv/detail/get_stored_map_by_name__functions.h"

// already included above
// #include "rosidl_runtime_c/string.h"
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes
#include "aimdk_msgs/msg/detail/hr_point__functions.h"
#include "aimdk_msgs/msg/detail/navi_point__functions.h"
#include "aimdk_msgs/msg/detail/path__functions.h"
#include "aimdk_msgs/msg/detail/qr_point__functions.h"
#include "aimdk_msgs/msg/detail/region__functions.h"
// end nested array functions include
ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool nav_msgs__msg__map_meta_data__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * nav_msgs__msg__map_meta_data__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__navi_point__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__navi_point__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__qr_point__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__qr_point__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__hr_point__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__hr_point__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__path__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__path__convert_to_py(void * raw_ros_message);
bool aimdk_msgs__msg__region__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * aimdk_msgs__msg__region__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__srv__get_stored_map_by_name__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[67];
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
    assert(strncmp("aimdk_msgs.srv._get_stored_map_by_name.GetStoredMapByName_Response", full_classname_dest, 66) == 0);
  }
  aimdk_msgs__srv__GetStoredMapByName_Response * ros_message = _ros_message;
  {  // code
    PyObject * field = PyObject_GetAttrString(_pymsg, "code");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->code = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // map_info
    PyObject * field = PyObject_GetAttrString(_pymsg, "map_info");
    if (!field) {
      return false;
    }
    if (!nav_msgs__msg__map_meta_data__convert_from_py(field, &ros_message->map_info)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // map_version
    PyObject * field = PyObject_GetAttrString(_pymsg, "map_version");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->map_version = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // map_path
    PyObject * field = PyObject_GetAttrString(_pymsg, "map_path");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->map_path, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // data
    PyObject * field = PyObject_GetAttrString(_pymsg, "data");
    if (!field) {
      return false;
    }
    if (PyObject_CheckBuffer(field)) {
      // Optimization for converting arrays of primitives
      Py_buffer view;
      int rc = PyObject_GetBuffer(field, &view, PyBUF_SIMPLE);
      if (rc < 0) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = view.len / sizeof(int8_t);
      if (!rosidl_runtime_c__int8__Sequence__init(&(ros_message->data), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create int8__Sequence ros_message");
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      int8_t * dest = ros_message->data.data;
      rc = PyBuffer_ToContiguous(dest, &view, view.len, 'C');
      if (rc < 0) {
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      PyBuffer_Release(&view);
    } else {
      PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'data'");
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
      if (!rosidl_runtime_c__int8__Sequence__init(&(ros_message->data), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create int8__Sequence ros_message");
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      int8_t * dest = ros_message->data.data;
      for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject * item = PySequence_Fast_GET_ITEM(seq_field, i);
        if (!item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        assert(PyLong_Check(item));
        int8_t tmp = (int8_t)PyLong_AsLong(item);
        memcpy(&dest[i], &tmp, sizeof(int8_t));
      }
      Py_DECREF(seq_field);
    }
    Py_DECREF(field);
  }
  {  // navi_points
    PyObject * field = PyObject_GetAttrString(_pymsg, "navi_points");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'navi_points'");
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
    if (!aimdk_msgs__msg__NaviPoint__Sequence__init(&(ros_message->navi_points), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aimdk_msgs__msg__NaviPoint__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aimdk_msgs__msg__NaviPoint * dest = ros_message->navi_points.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aimdk_msgs__msg__navi_point__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // qr_points
    PyObject * field = PyObject_GetAttrString(_pymsg, "qr_points");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'qr_points'");
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
    if (!aimdk_msgs__msg__QRPoint__Sequence__init(&(ros_message->qr_points), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aimdk_msgs__msg__QRPoint__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aimdk_msgs__msg__QRPoint * dest = ros_message->qr_points.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aimdk_msgs__msg__qr_point__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // hr_points
    PyObject * field = PyObject_GetAttrString(_pymsg, "hr_points");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'hr_points'");
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
    if (!aimdk_msgs__msg__HRPoint__Sequence__init(&(ros_message->hr_points), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aimdk_msgs__msg__HRPoint__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aimdk_msgs__msg__HRPoint * dest = ros_message->hr_points.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aimdk_msgs__msg__hr_point__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // paths
    PyObject * field = PyObject_GetAttrString(_pymsg, "paths");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'paths'");
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
    if (!aimdk_msgs__msg__Path__Sequence__init(&(ros_message->paths), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aimdk_msgs__msg__Path__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aimdk_msgs__msg__Path * dest = ros_message->paths.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aimdk_msgs__msg__path__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // regions
    PyObject * field = PyObject_GetAttrString(_pymsg, "regions");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'regions'");
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
    if (!aimdk_msgs__msg__Region__Sequence__init(&(ros_message->regions), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create aimdk_msgs__msg__Region__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    aimdk_msgs__msg__Region * dest = ros_message->regions.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!aimdk_msgs__msg__region__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // map_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "map_id");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->map_id = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__srv__get_stored_map_by_name__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetStoredMapByName_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.srv._get_stored_map_by_name");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetStoredMapByName_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__srv__GetStoredMapByName_Response * ros_message = (aimdk_msgs__srv__GetStoredMapByName_Response *)raw_ros_message;
  {  // code
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->code);
    {
      int rc = PyObject_SetAttrString(_pymessage, "code", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
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
  {  // map_info
    PyObject * field = NULL;
    field = nav_msgs__msg__map_meta_data__convert_to_py(&ros_message->map_info);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "map_info", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // map_version
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->map_version);
    {
      int rc = PyObject_SetAttrString(_pymessage, "map_version", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // map_path
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->map_path.data,
      strlen(ros_message->map_path.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "map_path", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // data
    PyObject * field = NULL;
    field = PyObject_GetAttrString(_pymessage, "data");
    if (!field) {
      return NULL;
    }
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "array.array") == 0);
    // ensure that itemsize matches the sizeof of the ROS message field
    PyObject * itemsize_attr = PyObject_GetAttrString(field, "itemsize");
    assert(itemsize_attr != NULL);
    size_t itemsize = PyLong_AsSize_t(itemsize_attr);
    Py_DECREF(itemsize_attr);
    if (itemsize != sizeof(int8_t)) {
      PyErr_SetString(PyExc_RuntimeError, "itemsize doesn't match expectation");
      Py_DECREF(field);
      return NULL;
    }
    // clear the array, poor approach to remove potential default values
    Py_ssize_t length = PyObject_Length(field);
    if (-1 == length) {
      Py_DECREF(field);
      return NULL;
    }
    if (length > 0) {
      PyObject * pop = PyObject_GetAttrString(field, "pop");
      assert(pop != NULL);
      for (Py_ssize_t i = 0; i < length; ++i) {
        PyObject * ret = PyObject_CallFunctionObjArgs(pop, NULL);
        if (!ret) {
          Py_DECREF(pop);
          Py_DECREF(field);
          return NULL;
        }
        Py_DECREF(ret);
      }
      Py_DECREF(pop);
    }
    if (ros_message->data.size > 0) {
      // populating the array.array using the frombytes method
      PyObject * frombytes = PyObject_GetAttrString(field, "frombytes");
      assert(frombytes != NULL);
      int8_t * src = &(ros_message->data.data[0]);
      PyObject * data = PyBytes_FromStringAndSize((const char *)src, ros_message->data.size * sizeof(int8_t));
      assert(data != NULL);
      PyObject * ret = PyObject_CallFunctionObjArgs(frombytes, data, NULL);
      Py_DECREF(data);
      Py_DECREF(frombytes);
      if (!ret) {
        Py_DECREF(field);
        return NULL;
      }
      Py_DECREF(ret);
    }
    Py_DECREF(field);
  }
  {  // navi_points
    PyObject * field = NULL;
    size_t size = ros_message->navi_points.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aimdk_msgs__msg__NaviPoint * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->navi_points.data[i]);
      PyObject * pyitem = aimdk_msgs__msg__navi_point__convert_to_py(item);
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
      int rc = PyObject_SetAttrString(_pymessage, "navi_points", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // qr_points
    PyObject * field = NULL;
    size_t size = ros_message->qr_points.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aimdk_msgs__msg__QRPoint * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->qr_points.data[i]);
      PyObject * pyitem = aimdk_msgs__msg__qr_point__convert_to_py(item);
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
      int rc = PyObject_SetAttrString(_pymessage, "qr_points", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // hr_points
    PyObject * field = NULL;
    size_t size = ros_message->hr_points.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aimdk_msgs__msg__HRPoint * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->hr_points.data[i]);
      PyObject * pyitem = aimdk_msgs__msg__hr_point__convert_to_py(item);
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
      int rc = PyObject_SetAttrString(_pymessage, "hr_points", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // paths
    PyObject * field = NULL;
    size_t size = ros_message->paths.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aimdk_msgs__msg__Path * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->paths.data[i]);
      PyObject * pyitem = aimdk_msgs__msg__path__convert_to_py(item);
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
      int rc = PyObject_SetAttrString(_pymessage, "paths", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // regions
    PyObject * field = NULL;
    size_t size = ros_message->regions.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    aimdk_msgs__msg__Region * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->regions.data[i]);
      PyObject * pyitem = aimdk_msgs__msg__region__convert_to_py(item);
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
      int rc = PyObject_SetAttrString(_pymessage, "regions", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // map_id
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->map_id);
    {
      int rc = PyObject_SetAttrString(_pymessage, "map_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

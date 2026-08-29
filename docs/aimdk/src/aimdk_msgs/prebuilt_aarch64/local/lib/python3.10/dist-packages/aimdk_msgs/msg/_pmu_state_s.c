// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from aimdk_msgs:msg/PmuState.idl
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
#include "aimdk_msgs/msg/detail/pmu_state__struct.h"
#include "aimdk_msgs/msg/detail/pmu_state__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool aimdk_msgs__msg__pmu_state__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[35];
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
    assert(strncmp("aimdk_msgs.msg._pmu_state.PmuState", full_classname_dest, 34) == 0);
  }
  aimdk_msgs__msg__PmuState * ros_message = _ros_message;
  {  // pmu_software_version
    PyObject * field = PyObject_GetAttrString(_pymsg, "pmu_software_version");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->pmu_software_version, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // pmu_hardware_version
    PyObject * field = PyObject_GetAttrString(_pymsg, "pmu_hardware_version");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->pmu_hardware_version, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // pmu_protocol_version
    PyObject * field = PyObject_GetAttrString(_pymsg, "pmu_protocol_version");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->pmu_protocol_version, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // pmu_bool_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "pmu_bool_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->pmu_bool_status = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // head_power_current
    PyObject * field = PyObject_GetAttrString(_pymsg, "head_power_current");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->head_power_current = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // output_48v_current
    PyObject * field = PyObject_GetAttrString(_pymsg, "output_48v_current");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->output_48v_current = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // rk3588_current
    PyObject * field = PyObject_GetAttrString(_pymsg, "rk3588_current");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->rk3588_current = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // output_12v_current
    PyObject * field = PyObject_GetAttrString(_pymsg, "output_12v_current");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->output_12v_current = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // bus_48v_current
    PyObject * field = PyObject_GetAttrString(_pymsg, "bus_48v_current");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->bus_48v_current = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // orin_current
    PyObject * field = PyObject_GetAttrString(_pymsg, "orin_current");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->orin_current = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // bus_48v_pmos_voltage
    PyObject * field = PyObject_GetAttrString(_pymsg, "bus_48v_pmos_voltage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->bus_48v_pmos_voltage = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // battery_voltage
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_voltage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->battery_voltage = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // fan_voltage
    PyObject * field = PyObject_GetAttrString(_pymsg, "fan_voltage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->fan_voltage = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // output_12v_voltage
    PyObject * field = PyObject_GetAttrString(_pymsg, "output_12v_voltage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->output_12v_voltage = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // output_48v_voltage
    PyObject * field = PyObject_GetAttrString(_pymsg, "output_48v_voltage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->output_48v_voltage = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // bus_48v_voltage
    PyObject * field = PyObject_GetAttrString(_pymsg, "bus_48v_voltage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->bus_48v_voltage = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // head_power_voltage
    PyObject * field = PyObject_GetAttrString(_pymsg, "head_power_voltage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->head_power_voltage = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // orin_voltage
    PyObject * field = PyObject_GetAttrString(_pymsg, "orin_voltage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->orin_voltage = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // rk3588_voltage
    PyObject * field = PyObject_GetAttrString(_pymsg, "rk3588_voltage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->rk3588_voltage = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // fan_speed
    PyObject * field = PyObject_GetAttrString(_pymsg, "fan_speed");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->fan_speed = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // fan_pecentage
    PyObject * field = PyObject_GetAttrString(_pymsg, "fan_pecentage");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->fan_pecentage = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // pmu_temperature
    PyObject * field = PyObject_GetAttrString(_pymsg, "pmu_temperature");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->pmu_temperature = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // bms_manufacturer
    PyObject * field = PyObject_GetAttrString(_pymsg, "bms_manufacturer");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->bms_manufacturer, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // bms_serial_number
    PyObject * field = PyObject_GetAttrString(_pymsg, "bms_serial_number");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->bms_serial_number, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // bms_hardware_version
    PyObject * field = PyObject_GetAttrString(_pymsg, "bms_hardware_version");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->bms_hardware_version, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // bms_software_version
    PyObject * field = PyObject_GetAttrString(_pymsg, "bms_software_version");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->bms_software_version, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // bms_status_bits
    PyObject * field = PyObject_GetAttrString(_pymsg, "bms_status_bits");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->bms_status_bits = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // battery_balance_line_resistance
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_balance_line_resistance");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->battery_balance_line_resistance = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // battery_pack_voltage
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_pack_voltage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->battery_pack_voltage = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // battery_current
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_current");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->battery_current = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // battery_output_power
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_output_power");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->battery_output_power = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // battery_temperature
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_temperature");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->battery_temperature = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // battery_remaining_capacity
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_remaining_capacity");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->battery_remaining_capacity = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // battery_remaining_capacity_percentage
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_remaining_capacity_percentage");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->battery_remaining_capacity_percentage = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // battery_cycle_count
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_cycle_count");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->battery_cycle_count = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // battery_cycle_total_capacity
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_cycle_total_capacity");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->battery_cycle_total_capacity = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * aimdk_msgs__msg__pmu_state__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of PmuState */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("aimdk_msgs.msg._pmu_state");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "PmuState");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  aimdk_msgs__msg__PmuState * ros_message = (aimdk_msgs__msg__PmuState *)raw_ros_message;
  {  // pmu_software_version
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->pmu_software_version.data,
      strlen(ros_message->pmu_software_version.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "pmu_software_version", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pmu_hardware_version
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->pmu_hardware_version.data,
      strlen(ros_message->pmu_hardware_version.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "pmu_hardware_version", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pmu_protocol_version
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->pmu_protocol_version.data,
      strlen(ros_message->pmu_protocol_version.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "pmu_protocol_version", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pmu_bool_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->pmu_bool_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pmu_bool_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // head_power_current
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->head_power_current);
    {
      int rc = PyObject_SetAttrString(_pymessage, "head_power_current", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // output_48v_current
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->output_48v_current);
    {
      int rc = PyObject_SetAttrString(_pymessage, "output_48v_current", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rk3588_current
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->rk3588_current);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rk3588_current", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // output_12v_current
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->output_12v_current);
    {
      int rc = PyObject_SetAttrString(_pymessage, "output_12v_current", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bus_48v_current
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->bus_48v_current);
    {
      int rc = PyObject_SetAttrString(_pymessage, "bus_48v_current", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // orin_current
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->orin_current);
    {
      int rc = PyObject_SetAttrString(_pymessage, "orin_current", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bus_48v_pmos_voltage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->bus_48v_pmos_voltage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "bus_48v_pmos_voltage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_voltage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->battery_voltage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_voltage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fan_voltage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->fan_voltage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fan_voltage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // output_12v_voltage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->output_12v_voltage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "output_12v_voltage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // output_48v_voltage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->output_48v_voltage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "output_48v_voltage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bus_48v_voltage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->bus_48v_voltage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "bus_48v_voltage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // head_power_voltage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->head_power_voltage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "head_power_voltage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // orin_voltage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->orin_voltage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "orin_voltage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rk3588_voltage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->rk3588_voltage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rk3588_voltage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fan_speed
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->fan_speed);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fan_speed", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fan_pecentage
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->fan_pecentage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fan_pecentage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pmu_temperature
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->pmu_temperature);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pmu_temperature", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bms_manufacturer
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->bms_manufacturer.data,
      strlen(ros_message->bms_manufacturer.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "bms_manufacturer", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bms_serial_number
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->bms_serial_number.data,
      strlen(ros_message->bms_serial_number.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "bms_serial_number", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bms_hardware_version
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->bms_hardware_version.data,
      strlen(ros_message->bms_hardware_version.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "bms_hardware_version", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bms_software_version
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->bms_software_version.data,
      strlen(ros_message->bms_software_version.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "bms_software_version", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // bms_status_bits
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->bms_status_bits);
    {
      int rc = PyObject_SetAttrString(_pymessage, "bms_status_bits", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_balance_line_resistance
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->battery_balance_line_resistance);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_balance_line_resistance", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_pack_voltage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->battery_pack_voltage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_pack_voltage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_current
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->battery_current);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_current", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_output_power
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->battery_output_power);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_output_power", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_temperature
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->battery_temperature);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_temperature", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_remaining_capacity
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->battery_remaining_capacity);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_remaining_capacity", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_remaining_capacity_percentage
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->battery_remaining_capacity_percentage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_remaining_capacity_percentage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_cycle_count
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->battery_cycle_count);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_cycle_count", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_cycle_total_capacity
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->battery_cycle_total_capacity);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_cycle_total_capacity", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

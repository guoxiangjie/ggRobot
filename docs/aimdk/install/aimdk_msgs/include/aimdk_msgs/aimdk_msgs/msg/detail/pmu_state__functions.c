// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/PmuState.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/pmu_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `pmu_software_version`
// Member `pmu_hardware_version`
// Member `pmu_protocol_version`
// Member `bms_manufacturer`
// Member `bms_serial_number`
// Member `bms_hardware_version`
// Member `bms_software_version`
#include "rosidl_runtime_c/string_functions.h"

bool
aimdk_msgs__msg__PmuState__init(aimdk_msgs__msg__PmuState * msg)
{
  if (!msg) {
    return false;
  }
  // pmu_software_version
  if (!rosidl_runtime_c__String__init(&msg->pmu_software_version)) {
    aimdk_msgs__msg__PmuState__fini(msg);
    return false;
  }
  // pmu_hardware_version
  if (!rosidl_runtime_c__String__init(&msg->pmu_hardware_version)) {
    aimdk_msgs__msg__PmuState__fini(msg);
    return false;
  }
  // pmu_protocol_version
  if (!rosidl_runtime_c__String__init(&msg->pmu_protocol_version)) {
    aimdk_msgs__msg__PmuState__fini(msg);
    return false;
  }
  // pmu_bool_status
  // head_power_current
  // output_48v_current
  // rk3588_current
  // output_12v_current
  // bus_48v_current
  // orin_current
  // bus_48v_pmos_voltage
  // battery_voltage
  // fan_voltage
  // output_12v_voltage
  // output_48v_voltage
  // bus_48v_voltage
  // head_power_voltage
  // orin_voltage
  // rk3588_voltage
  // fan_speed
  // fan_pecentage
  // pmu_temperature
  // bms_manufacturer
  if (!rosidl_runtime_c__String__init(&msg->bms_manufacturer)) {
    aimdk_msgs__msg__PmuState__fini(msg);
    return false;
  }
  // bms_serial_number
  if (!rosidl_runtime_c__String__init(&msg->bms_serial_number)) {
    aimdk_msgs__msg__PmuState__fini(msg);
    return false;
  }
  // bms_hardware_version
  if (!rosidl_runtime_c__String__init(&msg->bms_hardware_version)) {
    aimdk_msgs__msg__PmuState__fini(msg);
    return false;
  }
  // bms_software_version
  if (!rosidl_runtime_c__String__init(&msg->bms_software_version)) {
    aimdk_msgs__msg__PmuState__fini(msg);
    return false;
  }
  // bms_status_bits
  // battery_balance_line_resistance
  // battery_pack_voltage
  // battery_current
  // battery_output_power
  // battery_temperature
  // battery_remaining_capacity
  // battery_remaining_capacity_percentage
  // battery_cycle_count
  // battery_cycle_total_capacity
  return true;
}

void
aimdk_msgs__msg__PmuState__fini(aimdk_msgs__msg__PmuState * msg)
{
  if (!msg) {
    return;
  }
  // pmu_software_version
  rosidl_runtime_c__String__fini(&msg->pmu_software_version);
  // pmu_hardware_version
  rosidl_runtime_c__String__fini(&msg->pmu_hardware_version);
  // pmu_protocol_version
  rosidl_runtime_c__String__fini(&msg->pmu_protocol_version);
  // pmu_bool_status
  // head_power_current
  // output_48v_current
  // rk3588_current
  // output_12v_current
  // bus_48v_current
  // orin_current
  // bus_48v_pmos_voltage
  // battery_voltage
  // fan_voltage
  // output_12v_voltage
  // output_48v_voltage
  // bus_48v_voltage
  // head_power_voltage
  // orin_voltage
  // rk3588_voltage
  // fan_speed
  // fan_pecentage
  // pmu_temperature
  // bms_manufacturer
  rosidl_runtime_c__String__fini(&msg->bms_manufacturer);
  // bms_serial_number
  rosidl_runtime_c__String__fini(&msg->bms_serial_number);
  // bms_hardware_version
  rosidl_runtime_c__String__fini(&msg->bms_hardware_version);
  // bms_software_version
  rosidl_runtime_c__String__fini(&msg->bms_software_version);
  // bms_status_bits
  // battery_balance_line_resistance
  // battery_pack_voltage
  // battery_current
  // battery_output_power
  // battery_temperature
  // battery_remaining_capacity
  // battery_remaining_capacity_percentage
  // battery_cycle_count
  // battery_cycle_total_capacity
}

bool
aimdk_msgs__msg__PmuState__are_equal(const aimdk_msgs__msg__PmuState * lhs, const aimdk_msgs__msg__PmuState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pmu_software_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->pmu_software_version), &(rhs->pmu_software_version)))
  {
    return false;
  }
  // pmu_hardware_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->pmu_hardware_version), &(rhs->pmu_hardware_version)))
  {
    return false;
  }
  // pmu_protocol_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->pmu_protocol_version), &(rhs->pmu_protocol_version)))
  {
    return false;
  }
  // pmu_bool_status
  if (lhs->pmu_bool_status != rhs->pmu_bool_status) {
    return false;
  }
  // head_power_current
  if (lhs->head_power_current != rhs->head_power_current) {
    return false;
  }
  // output_48v_current
  if (lhs->output_48v_current != rhs->output_48v_current) {
    return false;
  }
  // rk3588_current
  if (lhs->rk3588_current != rhs->rk3588_current) {
    return false;
  }
  // output_12v_current
  if (lhs->output_12v_current != rhs->output_12v_current) {
    return false;
  }
  // bus_48v_current
  if (lhs->bus_48v_current != rhs->bus_48v_current) {
    return false;
  }
  // orin_current
  if (lhs->orin_current != rhs->orin_current) {
    return false;
  }
  // bus_48v_pmos_voltage
  if (lhs->bus_48v_pmos_voltage != rhs->bus_48v_pmos_voltage) {
    return false;
  }
  // battery_voltage
  if (lhs->battery_voltage != rhs->battery_voltage) {
    return false;
  }
  // fan_voltage
  if (lhs->fan_voltage != rhs->fan_voltage) {
    return false;
  }
  // output_12v_voltage
  if (lhs->output_12v_voltage != rhs->output_12v_voltage) {
    return false;
  }
  // output_48v_voltage
  if (lhs->output_48v_voltage != rhs->output_48v_voltage) {
    return false;
  }
  // bus_48v_voltage
  if (lhs->bus_48v_voltage != rhs->bus_48v_voltage) {
    return false;
  }
  // head_power_voltage
  if (lhs->head_power_voltage != rhs->head_power_voltage) {
    return false;
  }
  // orin_voltage
  if (lhs->orin_voltage != rhs->orin_voltage) {
    return false;
  }
  // rk3588_voltage
  if (lhs->rk3588_voltage != rhs->rk3588_voltage) {
    return false;
  }
  // fan_speed
  if (lhs->fan_speed != rhs->fan_speed) {
    return false;
  }
  // fan_pecentage
  if (lhs->fan_pecentage != rhs->fan_pecentage) {
    return false;
  }
  // pmu_temperature
  if (lhs->pmu_temperature != rhs->pmu_temperature) {
    return false;
  }
  // bms_manufacturer
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->bms_manufacturer), &(rhs->bms_manufacturer)))
  {
    return false;
  }
  // bms_serial_number
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->bms_serial_number), &(rhs->bms_serial_number)))
  {
    return false;
  }
  // bms_hardware_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->bms_hardware_version), &(rhs->bms_hardware_version)))
  {
    return false;
  }
  // bms_software_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->bms_software_version), &(rhs->bms_software_version)))
  {
    return false;
  }
  // bms_status_bits
  if (lhs->bms_status_bits != rhs->bms_status_bits) {
    return false;
  }
  // battery_balance_line_resistance
  if (lhs->battery_balance_line_resistance != rhs->battery_balance_line_resistance) {
    return false;
  }
  // battery_pack_voltage
  if (lhs->battery_pack_voltage != rhs->battery_pack_voltage) {
    return false;
  }
  // battery_current
  if (lhs->battery_current != rhs->battery_current) {
    return false;
  }
  // battery_output_power
  if (lhs->battery_output_power != rhs->battery_output_power) {
    return false;
  }
  // battery_temperature
  if (lhs->battery_temperature != rhs->battery_temperature) {
    return false;
  }
  // battery_remaining_capacity
  if (lhs->battery_remaining_capacity != rhs->battery_remaining_capacity) {
    return false;
  }
  // battery_remaining_capacity_percentage
  if (lhs->battery_remaining_capacity_percentage != rhs->battery_remaining_capacity_percentage) {
    return false;
  }
  // battery_cycle_count
  if (lhs->battery_cycle_count != rhs->battery_cycle_count) {
    return false;
  }
  // battery_cycle_total_capacity
  if (lhs->battery_cycle_total_capacity != rhs->battery_cycle_total_capacity) {
    return false;
  }
  return true;
}

bool
aimdk_msgs__msg__PmuState__copy(
  const aimdk_msgs__msg__PmuState * input,
  aimdk_msgs__msg__PmuState * output)
{
  if (!input || !output) {
    return false;
  }
  // pmu_software_version
  if (!rosidl_runtime_c__String__copy(
      &(input->pmu_software_version), &(output->pmu_software_version)))
  {
    return false;
  }
  // pmu_hardware_version
  if (!rosidl_runtime_c__String__copy(
      &(input->pmu_hardware_version), &(output->pmu_hardware_version)))
  {
    return false;
  }
  // pmu_protocol_version
  if (!rosidl_runtime_c__String__copy(
      &(input->pmu_protocol_version), &(output->pmu_protocol_version)))
  {
    return false;
  }
  // pmu_bool_status
  output->pmu_bool_status = input->pmu_bool_status;
  // head_power_current
  output->head_power_current = input->head_power_current;
  // output_48v_current
  output->output_48v_current = input->output_48v_current;
  // rk3588_current
  output->rk3588_current = input->rk3588_current;
  // output_12v_current
  output->output_12v_current = input->output_12v_current;
  // bus_48v_current
  output->bus_48v_current = input->bus_48v_current;
  // orin_current
  output->orin_current = input->orin_current;
  // bus_48v_pmos_voltage
  output->bus_48v_pmos_voltage = input->bus_48v_pmos_voltage;
  // battery_voltage
  output->battery_voltage = input->battery_voltage;
  // fan_voltage
  output->fan_voltage = input->fan_voltage;
  // output_12v_voltage
  output->output_12v_voltage = input->output_12v_voltage;
  // output_48v_voltage
  output->output_48v_voltage = input->output_48v_voltage;
  // bus_48v_voltage
  output->bus_48v_voltage = input->bus_48v_voltage;
  // head_power_voltage
  output->head_power_voltage = input->head_power_voltage;
  // orin_voltage
  output->orin_voltage = input->orin_voltage;
  // rk3588_voltage
  output->rk3588_voltage = input->rk3588_voltage;
  // fan_speed
  output->fan_speed = input->fan_speed;
  // fan_pecentage
  output->fan_pecentage = input->fan_pecentage;
  // pmu_temperature
  output->pmu_temperature = input->pmu_temperature;
  // bms_manufacturer
  if (!rosidl_runtime_c__String__copy(
      &(input->bms_manufacturer), &(output->bms_manufacturer)))
  {
    return false;
  }
  // bms_serial_number
  if (!rosidl_runtime_c__String__copy(
      &(input->bms_serial_number), &(output->bms_serial_number)))
  {
    return false;
  }
  // bms_hardware_version
  if (!rosidl_runtime_c__String__copy(
      &(input->bms_hardware_version), &(output->bms_hardware_version)))
  {
    return false;
  }
  // bms_software_version
  if (!rosidl_runtime_c__String__copy(
      &(input->bms_software_version), &(output->bms_software_version)))
  {
    return false;
  }
  // bms_status_bits
  output->bms_status_bits = input->bms_status_bits;
  // battery_balance_line_resistance
  output->battery_balance_line_resistance = input->battery_balance_line_resistance;
  // battery_pack_voltage
  output->battery_pack_voltage = input->battery_pack_voltage;
  // battery_current
  output->battery_current = input->battery_current;
  // battery_output_power
  output->battery_output_power = input->battery_output_power;
  // battery_temperature
  output->battery_temperature = input->battery_temperature;
  // battery_remaining_capacity
  output->battery_remaining_capacity = input->battery_remaining_capacity;
  // battery_remaining_capacity_percentage
  output->battery_remaining_capacity_percentage = input->battery_remaining_capacity_percentage;
  // battery_cycle_count
  output->battery_cycle_count = input->battery_cycle_count;
  // battery_cycle_total_capacity
  output->battery_cycle_total_capacity = input->battery_cycle_total_capacity;
  return true;
}

aimdk_msgs__msg__PmuState *
aimdk_msgs__msg__PmuState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__PmuState * msg = (aimdk_msgs__msg__PmuState *)allocator.allocate(sizeof(aimdk_msgs__msg__PmuState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__PmuState));
  bool success = aimdk_msgs__msg__PmuState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__PmuState__destroy(aimdk_msgs__msg__PmuState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__PmuState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__PmuState__Sequence__init(aimdk_msgs__msg__PmuState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__PmuState * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__PmuState *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__PmuState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__PmuState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__PmuState__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
aimdk_msgs__msg__PmuState__Sequence__fini(aimdk_msgs__msg__PmuState__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      aimdk_msgs__msg__PmuState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

aimdk_msgs__msg__PmuState__Sequence *
aimdk_msgs__msg__PmuState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__PmuState__Sequence * array = (aimdk_msgs__msg__PmuState__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__PmuState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__PmuState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__PmuState__Sequence__destroy(aimdk_msgs__msg__PmuState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__PmuState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__PmuState__Sequence__are_equal(const aimdk_msgs__msg__PmuState__Sequence * lhs, const aimdk_msgs__msg__PmuState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__PmuState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__PmuState__Sequence__copy(
  const aimdk_msgs__msg__PmuState__Sequence * input,
  aimdk_msgs__msg__PmuState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__PmuState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__PmuState * data =
      (aimdk_msgs__msg__PmuState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__PmuState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__PmuState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__PmuState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

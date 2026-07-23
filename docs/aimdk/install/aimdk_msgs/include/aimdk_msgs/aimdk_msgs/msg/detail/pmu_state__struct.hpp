// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/PmuState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PMU_STATE__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PMU_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__PmuState __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__PmuState __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PmuState_
{
  using Type = PmuState_<ContainerAllocator>;

  explicit PmuState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pmu_software_version = "";
      this->pmu_hardware_version = "";
      this->pmu_protocol_version = "";
      this->pmu_bool_status = 0ul;
      this->head_power_current = 0.0;
      this->output_48v_current = 0.0;
      this->rk3588_current = 0.0;
      this->output_12v_current = 0.0;
      this->bus_48v_current = 0.0;
      this->orin_current = 0.0;
      this->bus_48v_pmos_voltage = 0.0;
      this->battery_voltage = 0.0;
      this->fan_voltage = 0.0;
      this->output_12v_voltage = 0.0;
      this->output_48v_voltage = 0.0;
      this->bus_48v_voltage = 0.0;
      this->head_power_voltage = 0.0;
      this->orin_voltage = 0.0;
      this->rk3588_voltage = 0.0;
      this->fan_speed = 0.0;
      this->fan_pecentage = 0;
      this->pmu_temperature = 0.0;
      this->bms_manufacturer = "";
      this->bms_serial_number = "";
      this->bms_hardware_version = "";
      this->bms_software_version = "";
      this->bms_status_bits = 0ul;
      this->battery_balance_line_resistance = 0;
      this->battery_pack_voltage = 0.0;
      this->battery_current = 0.0;
      this->battery_output_power = 0.0;
      this->battery_temperature = 0.0;
      this->battery_remaining_capacity = 0ul;
      this->battery_remaining_capacity_percentage = 0;
      this->battery_cycle_count = 0;
      this->battery_cycle_total_capacity = 0ul;
    }
  }

  explicit PmuState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pmu_software_version(_alloc),
    pmu_hardware_version(_alloc),
    pmu_protocol_version(_alloc),
    bms_manufacturer(_alloc),
    bms_serial_number(_alloc),
    bms_hardware_version(_alloc),
    bms_software_version(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pmu_software_version = "";
      this->pmu_hardware_version = "";
      this->pmu_protocol_version = "";
      this->pmu_bool_status = 0ul;
      this->head_power_current = 0.0;
      this->output_48v_current = 0.0;
      this->rk3588_current = 0.0;
      this->output_12v_current = 0.0;
      this->bus_48v_current = 0.0;
      this->orin_current = 0.0;
      this->bus_48v_pmos_voltage = 0.0;
      this->battery_voltage = 0.0;
      this->fan_voltage = 0.0;
      this->output_12v_voltage = 0.0;
      this->output_48v_voltage = 0.0;
      this->bus_48v_voltage = 0.0;
      this->head_power_voltage = 0.0;
      this->orin_voltage = 0.0;
      this->rk3588_voltage = 0.0;
      this->fan_speed = 0.0;
      this->fan_pecentage = 0;
      this->pmu_temperature = 0.0;
      this->bms_manufacturer = "";
      this->bms_serial_number = "";
      this->bms_hardware_version = "";
      this->bms_software_version = "";
      this->bms_status_bits = 0ul;
      this->battery_balance_line_resistance = 0;
      this->battery_pack_voltage = 0.0;
      this->battery_current = 0.0;
      this->battery_output_power = 0.0;
      this->battery_temperature = 0.0;
      this->battery_remaining_capacity = 0ul;
      this->battery_remaining_capacity_percentage = 0;
      this->battery_cycle_count = 0;
      this->battery_cycle_total_capacity = 0ul;
    }
  }

  // field types and members
  using _pmu_software_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _pmu_software_version_type pmu_software_version;
  using _pmu_hardware_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _pmu_hardware_version_type pmu_hardware_version;
  using _pmu_protocol_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _pmu_protocol_version_type pmu_protocol_version;
  using _pmu_bool_status_type =
    uint32_t;
  _pmu_bool_status_type pmu_bool_status;
  using _head_power_current_type =
    double;
  _head_power_current_type head_power_current;
  using _output_48v_current_type =
    double;
  _output_48v_current_type output_48v_current;
  using _rk3588_current_type =
    double;
  _rk3588_current_type rk3588_current;
  using _output_12v_current_type =
    double;
  _output_12v_current_type output_12v_current;
  using _bus_48v_current_type =
    double;
  _bus_48v_current_type bus_48v_current;
  using _orin_current_type =
    double;
  _orin_current_type orin_current;
  using _bus_48v_pmos_voltage_type =
    double;
  _bus_48v_pmos_voltage_type bus_48v_pmos_voltage;
  using _battery_voltage_type =
    double;
  _battery_voltage_type battery_voltage;
  using _fan_voltage_type =
    double;
  _fan_voltage_type fan_voltage;
  using _output_12v_voltage_type =
    double;
  _output_12v_voltage_type output_12v_voltage;
  using _output_48v_voltage_type =
    double;
  _output_48v_voltage_type output_48v_voltage;
  using _bus_48v_voltage_type =
    double;
  _bus_48v_voltage_type bus_48v_voltage;
  using _head_power_voltage_type =
    double;
  _head_power_voltage_type head_power_voltage;
  using _orin_voltage_type =
    double;
  _orin_voltage_type orin_voltage;
  using _rk3588_voltage_type =
    double;
  _rk3588_voltage_type rk3588_voltage;
  using _fan_speed_type =
    double;
  _fan_speed_type fan_speed;
  using _fan_pecentage_type =
    uint8_t;
  _fan_pecentage_type fan_pecentage;
  using _pmu_temperature_type =
    double;
  _pmu_temperature_type pmu_temperature;
  using _bms_manufacturer_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _bms_manufacturer_type bms_manufacturer;
  using _bms_serial_number_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _bms_serial_number_type bms_serial_number;
  using _bms_hardware_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _bms_hardware_version_type bms_hardware_version;
  using _bms_software_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _bms_software_version_type bms_software_version;
  using _bms_status_bits_type =
    uint32_t;
  _bms_status_bits_type bms_status_bits;
  using _battery_balance_line_resistance_type =
    uint16_t;
  _battery_balance_line_resistance_type battery_balance_line_resistance;
  using _battery_pack_voltage_type =
    double;
  _battery_pack_voltage_type battery_pack_voltage;
  using _battery_current_type =
    double;
  _battery_current_type battery_current;
  using _battery_output_power_type =
    double;
  _battery_output_power_type battery_output_power;
  using _battery_temperature_type =
    double;
  _battery_temperature_type battery_temperature;
  using _battery_remaining_capacity_type =
    uint32_t;
  _battery_remaining_capacity_type battery_remaining_capacity;
  using _battery_remaining_capacity_percentage_type =
    uint8_t;
  _battery_remaining_capacity_percentage_type battery_remaining_capacity_percentage;
  using _battery_cycle_count_type =
    uint16_t;
  _battery_cycle_count_type battery_cycle_count;
  using _battery_cycle_total_capacity_type =
    uint32_t;
  _battery_cycle_total_capacity_type battery_cycle_total_capacity;

  // setters for named parameter idiom
  Type & set__pmu_software_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->pmu_software_version = _arg;
    return *this;
  }
  Type & set__pmu_hardware_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->pmu_hardware_version = _arg;
    return *this;
  }
  Type & set__pmu_protocol_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->pmu_protocol_version = _arg;
    return *this;
  }
  Type & set__pmu_bool_status(
    const uint32_t & _arg)
  {
    this->pmu_bool_status = _arg;
    return *this;
  }
  Type & set__head_power_current(
    const double & _arg)
  {
    this->head_power_current = _arg;
    return *this;
  }
  Type & set__output_48v_current(
    const double & _arg)
  {
    this->output_48v_current = _arg;
    return *this;
  }
  Type & set__rk3588_current(
    const double & _arg)
  {
    this->rk3588_current = _arg;
    return *this;
  }
  Type & set__output_12v_current(
    const double & _arg)
  {
    this->output_12v_current = _arg;
    return *this;
  }
  Type & set__bus_48v_current(
    const double & _arg)
  {
    this->bus_48v_current = _arg;
    return *this;
  }
  Type & set__orin_current(
    const double & _arg)
  {
    this->orin_current = _arg;
    return *this;
  }
  Type & set__bus_48v_pmos_voltage(
    const double & _arg)
  {
    this->bus_48v_pmos_voltage = _arg;
    return *this;
  }
  Type & set__battery_voltage(
    const double & _arg)
  {
    this->battery_voltage = _arg;
    return *this;
  }
  Type & set__fan_voltage(
    const double & _arg)
  {
    this->fan_voltage = _arg;
    return *this;
  }
  Type & set__output_12v_voltage(
    const double & _arg)
  {
    this->output_12v_voltage = _arg;
    return *this;
  }
  Type & set__output_48v_voltage(
    const double & _arg)
  {
    this->output_48v_voltage = _arg;
    return *this;
  }
  Type & set__bus_48v_voltage(
    const double & _arg)
  {
    this->bus_48v_voltage = _arg;
    return *this;
  }
  Type & set__head_power_voltage(
    const double & _arg)
  {
    this->head_power_voltage = _arg;
    return *this;
  }
  Type & set__orin_voltage(
    const double & _arg)
  {
    this->orin_voltage = _arg;
    return *this;
  }
  Type & set__rk3588_voltage(
    const double & _arg)
  {
    this->rk3588_voltage = _arg;
    return *this;
  }
  Type & set__fan_speed(
    const double & _arg)
  {
    this->fan_speed = _arg;
    return *this;
  }
  Type & set__fan_pecentage(
    const uint8_t & _arg)
  {
    this->fan_pecentage = _arg;
    return *this;
  }
  Type & set__pmu_temperature(
    const double & _arg)
  {
    this->pmu_temperature = _arg;
    return *this;
  }
  Type & set__bms_manufacturer(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->bms_manufacturer = _arg;
    return *this;
  }
  Type & set__bms_serial_number(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->bms_serial_number = _arg;
    return *this;
  }
  Type & set__bms_hardware_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->bms_hardware_version = _arg;
    return *this;
  }
  Type & set__bms_software_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->bms_software_version = _arg;
    return *this;
  }
  Type & set__bms_status_bits(
    const uint32_t & _arg)
  {
    this->bms_status_bits = _arg;
    return *this;
  }
  Type & set__battery_balance_line_resistance(
    const uint16_t & _arg)
  {
    this->battery_balance_line_resistance = _arg;
    return *this;
  }
  Type & set__battery_pack_voltage(
    const double & _arg)
  {
    this->battery_pack_voltage = _arg;
    return *this;
  }
  Type & set__battery_current(
    const double & _arg)
  {
    this->battery_current = _arg;
    return *this;
  }
  Type & set__battery_output_power(
    const double & _arg)
  {
    this->battery_output_power = _arg;
    return *this;
  }
  Type & set__battery_temperature(
    const double & _arg)
  {
    this->battery_temperature = _arg;
    return *this;
  }
  Type & set__battery_remaining_capacity(
    const uint32_t & _arg)
  {
    this->battery_remaining_capacity = _arg;
    return *this;
  }
  Type & set__battery_remaining_capacity_percentage(
    const uint8_t & _arg)
  {
    this->battery_remaining_capacity_percentage = _arg;
    return *this;
  }
  Type & set__battery_cycle_count(
    const uint16_t & _arg)
  {
    this->battery_cycle_count = _arg;
    return *this;
  }
  Type & set__battery_cycle_total_capacity(
    const uint32_t & _arg)
  {
    this->battery_cycle_total_capacity = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::PmuState_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::PmuState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::PmuState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::PmuState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::PmuState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::PmuState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::PmuState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::PmuState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::PmuState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::PmuState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__PmuState
    std::shared_ptr<aimdk_msgs::msg::PmuState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__PmuState
    std::shared_ptr<aimdk_msgs::msg::PmuState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PmuState_ & other) const
  {
    if (this->pmu_software_version != other.pmu_software_version) {
      return false;
    }
    if (this->pmu_hardware_version != other.pmu_hardware_version) {
      return false;
    }
    if (this->pmu_protocol_version != other.pmu_protocol_version) {
      return false;
    }
    if (this->pmu_bool_status != other.pmu_bool_status) {
      return false;
    }
    if (this->head_power_current != other.head_power_current) {
      return false;
    }
    if (this->output_48v_current != other.output_48v_current) {
      return false;
    }
    if (this->rk3588_current != other.rk3588_current) {
      return false;
    }
    if (this->output_12v_current != other.output_12v_current) {
      return false;
    }
    if (this->bus_48v_current != other.bus_48v_current) {
      return false;
    }
    if (this->orin_current != other.orin_current) {
      return false;
    }
    if (this->bus_48v_pmos_voltage != other.bus_48v_pmos_voltage) {
      return false;
    }
    if (this->battery_voltage != other.battery_voltage) {
      return false;
    }
    if (this->fan_voltage != other.fan_voltage) {
      return false;
    }
    if (this->output_12v_voltage != other.output_12v_voltage) {
      return false;
    }
    if (this->output_48v_voltage != other.output_48v_voltage) {
      return false;
    }
    if (this->bus_48v_voltage != other.bus_48v_voltage) {
      return false;
    }
    if (this->head_power_voltage != other.head_power_voltage) {
      return false;
    }
    if (this->orin_voltage != other.orin_voltage) {
      return false;
    }
    if (this->rk3588_voltage != other.rk3588_voltage) {
      return false;
    }
    if (this->fan_speed != other.fan_speed) {
      return false;
    }
    if (this->fan_pecentage != other.fan_pecentage) {
      return false;
    }
    if (this->pmu_temperature != other.pmu_temperature) {
      return false;
    }
    if (this->bms_manufacturer != other.bms_manufacturer) {
      return false;
    }
    if (this->bms_serial_number != other.bms_serial_number) {
      return false;
    }
    if (this->bms_hardware_version != other.bms_hardware_version) {
      return false;
    }
    if (this->bms_software_version != other.bms_software_version) {
      return false;
    }
    if (this->bms_status_bits != other.bms_status_bits) {
      return false;
    }
    if (this->battery_balance_line_resistance != other.battery_balance_line_resistance) {
      return false;
    }
    if (this->battery_pack_voltage != other.battery_pack_voltage) {
      return false;
    }
    if (this->battery_current != other.battery_current) {
      return false;
    }
    if (this->battery_output_power != other.battery_output_power) {
      return false;
    }
    if (this->battery_temperature != other.battery_temperature) {
      return false;
    }
    if (this->battery_remaining_capacity != other.battery_remaining_capacity) {
      return false;
    }
    if (this->battery_remaining_capacity_percentage != other.battery_remaining_capacity_percentage) {
      return false;
    }
    if (this->battery_cycle_count != other.battery_cycle_count) {
      return false;
    }
    if (this->battery_cycle_total_capacity != other.battery_cycle_total_capacity) {
      return false;
    }
    return true;
  }
  bool operator!=(const PmuState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PmuState_

// alias to use template instance with default allocator
using PmuState =
  aimdk_msgs::msg::PmuState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PMU_STATE__STRUCT_HPP_

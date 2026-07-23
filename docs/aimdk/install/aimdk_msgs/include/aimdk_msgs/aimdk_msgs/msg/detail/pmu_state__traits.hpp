// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/PmuState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PMU_STATE__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PMU_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/pmu_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PmuState & msg,
  std::ostream & out)
{
  out << "{";
  // member: pmu_software_version
  {
    out << "pmu_software_version: ";
    rosidl_generator_traits::value_to_yaml(msg.pmu_software_version, out);
    out << ", ";
  }

  // member: pmu_hardware_version
  {
    out << "pmu_hardware_version: ";
    rosidl_generator_traits::value_to_yaml(msg.pmu_hardware_version, out);
    out << ", ";
  }

  // member: pmu_protocol_version
  {
    out << "pmu_protocol_version: ";
    rosidl_generator_traits::value_to_yaml(msg.pmu_protocol_version, out);
    out << ", ";
  }

  // member: pmu_bool_status
  {
    out << "pmu_bool_status: ";
    rosidl_generator_traits::value_to_yaml(msg.pmu_bool_status, out);
    out << ", ";
  }

  // member: head_power_current
  {
    out << "head_power_current: ";
    rosidl_generator_traits::value_to_yaml(msg.head_power_current, out);
    out << ", ";
  }

  // member: output_48v_current
  {
    out << "output_48v_current: ";
    rosidl_generator_traits::value_to_yaml(msg.output_48v_current, out);
    out << ", ";
  }

  // member: rk3588_current
  {
    out << "rk3588_current: ";
    rosidl_generator_traits::value_to_yaml(msg.rk3588_current, out);
    out << ", ";
  }

  // member: output_12v_current
  {
    out << "output_12v_current: ";
    rosidl_generator_traits::value_to_yaml(msg.output_12v_current, out);
    out << ", ";
  }

  // member: bus_48v_current
  {
    out << "bus_48v_current: ";
    rosidl_generator_traits::value_to_yaml(msg.bus_48v_current, out);
    out << ", ";
  }

  // member: orin_current
  {
    out << "orin_current: ";
    rosidl_generator_traits::value_to_yaml(msg.orin_current, out);
    out << ", ";
  }

  // member: bus_48v_pmos_voltage
  {
    out << "bus_48v_pmos_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.bus_48v_pmos_voltage, out);
    out << ", ";
  }

  // member: battery_voltage
  {
    out << "battery_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_voltage, out);
    out << ", ";
  }

  // member: fan_voltage
  {
    out << "fan_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.fan_voltage, out);
    out << ", ";
  }

  // member: output_12v_voltage
  {
    out << "output_12v_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.output_12v_voltage, out);
    out << ", ";
  }

  // member: output_48v_voltage
  {
    out << "output_48v_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.output_48v_voltage, out);
    out << ", ";
  }

  // member: bus_48v_voltage
  {
    out << "bus_48v_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.bus_48v_voltage, out);
    out << ", ";
  }

  // member: head_power_voltage
  {
    out << "head_power_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.head_power_voltage, out);
    out << ", ";
  }

  // member: orin_voltage
  {
    out << "orin_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.orin_voltage, out);
    out << ", ";
  }

  // member: rk3588_voltage
  {
    out << "rk3588_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.rk3588_voltage, out);
    out << ", ";
  }

  // member: fan_speed
  {
    out << "fan_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.fan_speed, out);
    out << ", ";
  }

  // member: fan_pecentage
  {
    out << "fan_pecentage: ";
    rosidl_generator_traits::value_to_yaml(msg.fan_pecentage, out);
    out << ", ";
  }

  // member: pmu_temperature
  {
    out << "pmu_temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.pmu_temperature, out);
    out << ", ";
  }

  // member: bms_manufacturer
  {
    out << "bms_manufacturer: ";
    rosidl_generator_traits::value_to_yaml(msg.bms_manufacturer, out);
    out << ", ";
  }

  // member: bms_serial_number
  {
    out << "bms_serial_number: ";
    rosidl_generator_traits::value_to_yaml(msg.bms_serial_number, out);
    out << ", ";
  }

  // member: bms_hardware_version
  {
    out << "bms_hardware_version: ";
    rosidl_generator_traits::value_to_yaml(msg.bms_hardware_version, out);
    out << ", ";
  }

  // member: bms_software_version
  {
    out << "bms_software_version: ";
    rosidl_generator_traits::value_to_yaml(msg.bms_software_version, out);
    out << ", ";
  }

  // member: bms_status_bits
  {
    out << "bms_status_bits: ";
    rosidl_generator_traits::value_to_yaml(msg.bms_status_bits, out);
    out << ", ";
  }

  // member: battery_balance_line_resistance
  {
    out << "battery_balance_line_resistance: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_balance_line_resistance, out);
    out << ", ";
  }

  // member: battery_pack_voltage
  {
    out << "battery_pack_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_pack_voltage, out);
    out << ", ";
  }

  // member: battery_current
  {
    out << "battery_current: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_current, out);
    out << ", ";
  }

  // member: battery_output_power
  {
    out << "battery_output_power: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_output_power, out);
    out << ", ";
  }

  // member: battery_temperature
  {
    out << "battery_temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_temperature, out);
    out << ", ";
  }

  // member: battery_remaining_capacity
  {
    out << "battery_remaining_capacity: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_remaining_capacity, out);
    out << ", ";
  }

  // member: battery_remaining_capacity_percentage
  {
    out << "battery_remaining_capacity_percentage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_remaining_capacity_percentage, out);
    out << ", ";
  }

  // member: battery_cycle_count
  {
    out << "battery_cycle_count: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_cycle_count, out);
    out << ", ";
  }

  // member: battery_cycle_total_capacity
  {
    out << "battery_cycle_total_capacity: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_cycle_total_capacity, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PmuState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pmu_software_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pmu_software_version: ";
    rosidl_generator_traits::value_to_yaml(msg.pmu_software_version, out);
    out << "\n";
  }

  // member: pmu_hardware_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pmu_hardware_version: ";
    rosidl_generator_traits::value_to_yaml(msg.pmu_hardware_version, out);
    out << "\n";
  }

  // member: pmu_protocol_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pmu_protocol_version: ";
    rosidl_generator_traits::value_to_yaml(msg.pmu_protocol_version, out);
    out << "\n";
  }

  // member: pmu_bool_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pmu_bool_status: ";
    rosidl_generator_traits::value_to_yaml(msg.pmu_bool_status, out);
    out << "\n";
  }

  // member: head_power_current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "head_power_current: ";
    rosidl_generator_traits::value_to_yaml(msg.head_power_current, out);
    out << "\n";
  }

  // member: output_48v_current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "output_48v_current: ";
    rosidl_generator_traits::value_to_yaml(msg.output_48v_current, out);
    out << "\n";
  }

  // member: rk3588_current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rk3588_current: ";
    rosidl_generator_traits::value_to_yaml(msg.rk3588_current, out);
    out << "\n";
  }

  // member: output_12v_current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "output_12v_current: ";
    rosidl_generator_traits::value_to_yaml(msg.output_12v_current, out);
    out << "\n";
  }

  // member: bus_48v_current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bus_48v_current: ";
    rosidl_generator_traits::value_to_yaml(msg.bus_48v_current, out);
    out << "\n";
  }

  // member: orin_current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "orin_current: ";
    rosidl_generator_traits::value_to_yaml(msg.orin_current, out);
    out << "\n";
  }

  // member: bus_48v_pmos_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bus_48v_pmos_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.bus_48v_pmos_voltage, out);
    out << "\n";
  }

  // member: battery_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_voltage, out);
    out << "\n";
  }

  // member: fan_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fan_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.fan_voltage, out);
    out << "\n";
  }

  // member: output_12v_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "output_12v_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.output_12v_voltage, out);
    out << "\n";
  }

  // member: output_48v_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "output_48v_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.output_48v_voltage, out);
    out << "\n";
  }

  // member: bus_48v_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bus_48v_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.bus_48v_voltage, out);
    out << "\n";
  }

  // member: head_power_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "head_power_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.head_power_voltage, out);
    out << "\n";
  }

  // member: orin_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "orin_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.orin_voltage, out);
    out << "\n";
  }

  // member: rk3588_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rk3588_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.rk3588_voltage, out);
    out << "\n";
  }

  // member: fan_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fan_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.fan_speed, out);
    out << "\n";
  }

  // member: fan_pecentage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fan_pecentage: ";
    rosidl_generator_traits::value_to_yaml(msg.fan_pecentage, out);
    out << "\n";
  }

  // member: pmu_temperature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pmu_temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.pmu_temperature, out);
    out << "\n";
  }

  // member: bms_manufacturer
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bms_manufacturer: ";
    rosidl_generator_traits::value_to_yaml(msg.bms_manufacturer, out);
    out << "\n";
  }

  // member: bms_serial_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bms_serial_number: ";
    rosidl_generator_traits::value_to_yaml(msg.bms_serial_number, out);
    out << "\n";
  }

  // member: bms_hardware_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bms_hardware_version: ";
    rosidl_generator_traits::value_to_yaml(msg.bms_hardware_version, out);
    out << "\n";
  }

  // member: bms_software_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bms_software_version: ";
    rosidl_generator_traits::value_to_yaml(msg.bms_software_version, out);
    out << "\n";
  }

  // member: bms_status_bits
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bms_status_bits: ";
    rosidl_generator_traits::value_to_yaml(msg.bms_status_bits, out);
    out << "\n";
  }

  // member: battery_balance_line_resistance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_balance_line_resistance: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_balance_line_resistance, out);
    out << "\n";
  }

  // member: battery_pack_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_pack_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_pack_voltage, out);
    out << "\n";
  }

  // member: battery_current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_current: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_current, out);
    out << "\n";
  }

  // member: battery_output_power
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_output_power: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_output_power, out);
    out << "\n";
  }

  // member: battery_temperature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_temperature, out);
    out << "\n";
  }

  // member: battery_remaining_capacity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_remaining_capacity: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_remaining_capacity, out);
    out << "\n";
  }

  // member: battery_remaining_capacity_percentage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_remaining_capacity_percentage: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_remaining_capacity_percentage, out);
    out << "\n";
  }

  // member: battery_cycle_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_cycle_count: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_cycle_count, out);
    out << "\n";
  }

  // member: battery_cycle_total_capacity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_cycle_total_capacity: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_cycle_total_capacity, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PmuState & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace aimdk_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aimdk_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aimdk_msgs::msg::PmuState & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::PmuState & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::PmuState>()
{
  return "aimdk_msgs::msg::PmuState";
}

template<>
inline const char * name<aimdk_msgs::msg::PmuState>()
{
  return "aimdk_msgs/msg/PmuState";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::PmuState>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::PmuState>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::PmuState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__PMU_STATE__TRAITS_HPP_

// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/PmuState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PMU_STATE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PMU_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/pmu_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_PmuState_battery_cycle_total_capacity
{
public:
  explicit Init_PmuState_battery_cycle_total_capacity(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::PmuState battery_cycle_total_capacity(::aimdk_msgs::msg::PmuState::_battery_cycle_total_capacity_type arg)
  {
    msg_.battery_cycle_total_capacity = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_battery_cycle_count
{
public:
  explicit Init_PmuState_battery_cycle_count(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_battery_cycle_total_capacity battery_cycle_count(::aimdk_msgs::msg::PmuState::_battery_cycle_count_type arg)
  {
    msg_.battery_cycle_count = std::move(arg);
    return Init_PmuState_battery_cycle_total_capacity(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_battery_remaining_capacity_percentage
{
public:
  explicit Init_PmuState_battery_remaining_capacity_percentage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_battery_cycle_count battery_remaining_capacity_percentage(::aimdk_msgs::msg::PmuState::_battery_remaining_capacity_percentage_type arg)
  {
    msg_.battery_remaining_capacity_percentage = std::move(arg);
    return Init_PmuState_battery_cycle_count(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_battery_remaining_capacity
{
public:
  explicit Init_PmuState_battery_remaining_capacity(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_battery_remaining_capacity_percentage battery_remaining_capacity(::aimdk_msgs::msg::PmuState::_battery_remaining_capacity_type arg)
  {
    msg_.battery_remaining_capacity = std::move(arg);
    return Init_PmuState_battery_remaining_capacity_percentage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_battery_temperature
{
public:
  explicit Init_PmuState_battery_temperature(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_battery_remaining_capacity battery_temperature(::aimdk_msgs::msg::PmuState::_battery_temperature_type arg)
  {
    msg_.battery_temperature = std::move(arg);
    return Init_PmuState_battery_remaining_capacity(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_battery_output_power
{
public:
  explicit Init_PmuState_battery_output_power(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_battery_temperature battery_output_power(::aimdk_msgs::msg::PmuState::_battery_output_power_type arg)
  {
    msg_.battery_output_power = std::move(arg);
    return Init_PmuState_battery_temperature(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_battery_current
{
public:
  explicit Init_PmuState_battery_current(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_battery_output_power battery_current(::aimdk_msgs::msg::PmuState::_battery_current_type arg)
  {
    msg_.battery_current = std::move(arg);
    return Init_PmuState_battery_output_power(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_battery_pack_voltage
{
public:
  explicit Init_PmuState_battery_pack_voltage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_battery_current battery_pack_voltage(::aimdk_msgs::msg::PmuState::_battery_pack_voltage_type arg)
  {
    msg_.battery_pack_voltage = std::move(arg);
    return Init_PmuState_battery_current(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_battery_balance_line_resistance
{
public:
  explicit Init_PmuState_battery_balance_line_resistance(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_battery_pack_voltage battery_balance_line_resistance(::aimdk_msgs::msg::PmuState::_battery_balance_line_resistance_type arg)
  {
    msg_.battery_balance_line_resistance = std::move(arg);
    return Init_PmuState_battery_pack_voltage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_bms_status_bits
{
public:
  explicit Init_PmuState_bms_status_bits(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_battery_balance_line_resistance bms_status_bits(::aimdk_msgs::msg::PmuState::_bms_status_bits_type arg)
  {
    msg_.bms_status_bits = std::move(arg);
    return Init_PmuState_battery_balance_line_resistance(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_bms_software_version
{
public:
  explicit Init_PmuState_bms_software_version(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_bms_status_bits bms_software_version(::aimdk_msgs::msg::PmuState::_bms_software_version_type arg)
  {
    msg_.bms_software_version = std::move(arg);
    return Init_PmuState_bms_status_bits(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_bms_hardware_version
{
public:
  explicit Init_PmuState_bms_hardware_version(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_bms_software_version bms_hardware_version(::aimdk_msgs::msg::PmuState::_bms_hardware_version_type arg)
  {
    msg_.bms_hardware_version = std::move(arg);
    return Init_PmuState_bms_software_version(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_bms_serial_number
{
public:
  explicit Init_PmuState_bms_serial_number(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_bms_hardware_version bms_serial_number(::aimdk_msgs::msg::PmuState::_bms_serial_number_type arg)
  {
    msg_.bms_serial_number = std::move(arg);
    return Init_PmuState_bms_hardware_version(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_bms_manufacturer
{
public:
  explicit Init_PmuState_bms_manufacturer(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_bms_serial_number bms_manufacturer(::aimdk_msgs::msg::PmuState::_bms_manufacturer_type arg)
  {
    msg_.bms_manufacturer = std::move(arg);
    return Init_PmuState_bms_serial_number(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_pmu_temperature
{
public:
  explicit Init_PmuState_pmu_temperature(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_bms_manufacturer pmu_temperature(::aimdk_msgs::msg::PmuState::_pmu_temperature_type arg)
  {
    msg_.pmu_temperature = std::move(arg);
    return Init_PmuState_bms_manufacturer(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_fan_pecentage
{
public:
  explicit Init_PmuState_fan_pecentage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_pmu_temperature fan_pecentage(::aimdk_msgs::msg::PmuState::_fan_pecentage_type arg)
  {
    msg_.fan_pecentage = std::move(arg);
    return Init_PmuState_pmu_temperature(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_fan_speed
{
public:
  explicit Init_PmuState_fan_speed(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_fan_pecentage fan_speed(::aimdk_msgs::msg::PmuState::_fan_speed_type arg)
  {
    msg_.fan_speed = std::move(arg);
    return Init_PmuState_fan_pecentage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_rk3588_voltage
{
public:
  explicit Init_PmuState_rk3588_voltage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_fan_speed rk3588_voltage(::aimdk_msgs::msg::PmuState::_rk3588_voltage_type arg)
  {
    msg_.rk3588_voltage = std::move(arg);
    return Init_PmuState_fan_speed(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_orin_voltage
{
public:
  explicit Init_PmuState_orin_voltage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_rk3588_voltage orin_voltage(::aimdk_msgs::msg::PmuState::_orin_voltage_type arg)
  {
    msg_.orin_voltage = std::move(arg);
    return Init_PmuState_rk3588_voltage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_head_power_voltage
{
public:
  explicit Init_PmuState_head_power_voltage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_orin_voltage head_power_voltage(::aimdk_msgs::msg::PmuState::_head_power_voltage_type arg)
  {
    msg_.head_power_voltage = std::move(arg);
    return Init_PmuState_orin_voltage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_bus_48v_voltage
{
public:
  explicit Init_PmuState_bus_48v_voltage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_head_power_voltage bus_48v_voltage(::aimdk_msgs::msg::PmuState::_bus_48v_voltage_type arg)
  {
    msg_.bus_48v_voltage = std::move(arg);
    return Init_PmuState_head_power_voltage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_output_48v_voltage
{
public:
  explicit Init_PmuState_output_48v_voltage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_bus_48v_voltage output_48v_voltage(::aimdk_msgs::msg::PmuState::_output_48v_voltage_type arg)
  {
    msg_.output_48v_voltage = std::move(arg);
    return Init_PmuState_bus_48v_voltage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_output_12v_voltage
{
public:
  explicit Init_PmuState_output_12v_voltage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_output_48v_voltage output_12v_voltage(::aimdk_msgs::msg::PmuState::_output_12v_voltage_type arg)
  {
    msg_.output_12v_voltage = std::move(arg);
    return Init_PmuState_output_48v_voltage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_fan_voltage
{
public:
  explicit Init_PmuState_fan_voltage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_output_12v_voltage fan_voltage(::aimdk_msgs::msg::PmuState::_fan_voltage_type arg)
  {
    msg_.fan_voltage = std::move(arg);
    return Init_PmuState_output_12v_voltage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_battery_voltage
{
public:
  explicit Init_PmuState_battery_voltage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_fan_voltage battery_voltage(::aimdk_msgs::msg::PmuState::_battery_voltage_type arg)
  {
    msg_.battery_voltage = std::move(arg);
    return Init_PmuState_fan_voltage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_bus_48v_pmos_voltage
{
public:
  explicit Init_PmuState_bus_48v_pmos_voltage(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_battery_voltage bus_48v_pmos_voltage(::aimdk_msgs::msg::PmuState::_bus_48v_pmos_voltage_type arg)
  {
    msg_.bus_48v_pmos_voltage = std::move(arg);
    return Init_PmuState_battery_voltage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_orin_current
{
public:
  explicit Init_PmuState_orin_current(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_bus_48v_pmos_voltage orin_current(::aimdk_msgs::msg::PmuState::_orin_current_type arg)
  {
    msg_.orin_current = std::move(arg);
    return Init_PmuState_bus_48v_pmos_voltage(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_bus_48v_current
{
public:
  explicit Init_PmuState_bus_48v_current(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_orin_current bus_48v_current(::aimdk_msgs::msg::PmuState::_bus_48v_current_type arg)
  {
    msg_.bus_48v_current = std::move(arg);
    return Init_PmuState_orin_current(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_output_12v_current
{
public:
  explicit Init_PmuState_output_12v_current(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_bus_48v_current output_12v_current(::aimdk_msgs::msg::PmuState::_output_12v_current_type arg)
  {
    msg_.output_12v_current = std::move(arg);
    return Init_PmuState_bus_48v_current(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_rk3588_current
{
public:
  explicit Init_PmuState_rk3588_current(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_output_12v_current rk3588_current(::aimdk_msgs::msg::PmuState::_rk3588_current_type arg)
  {
    msg_.rk3588_current = std::move(arg);
    return Init_PmuState_output_12v_current(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_output_48v_current
{
public:
  explicit Init_PmuState_output_48v_current(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_rk3588_current output_48v_current(::aimdk_msgs::msg::PmuState::_output_48v_current_type arg)
  {
    msg_.output_48v_current = std::move(arg);
    return Init_PmuState_rk3588_current(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_head_power_current
{
public:
  explicit Init_PmuState_head_power_current(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_output_48v_current head_power_current(::aimdk_msgs::msg::PmuState::_head_power_current_type arg)
  {
    msg_.head_power_current = std::move(arg);
    return Init_PmuState_output_48v_current(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_pmu_bool_status
{
public:
  explicit Init_PmuState_pmu_bool_status(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_head_power_current pmu_bool_status(::aimdk_msgs::msg::PmuState::_pmu_bool_status_type arg)
  {
    msg_.pmu_bool_status = std::move(arg);
    return Init_PmuState_head_power_current(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_pmu_protocol_version
{
public:
  explicit Init_PmuState_pmu_protocol_version(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_pmu_bool_status pmu_protocol_version(::aimdk_msgs::msg::PmuState::_pmu_protocol_version_type arg)
  {
    msg_.pmu_protocol_version = std::move(arg);
    return Init_PmuState_pmu_bool_status(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_pmu_hardware_version
{
public:
  explicit Init_PmuState_pmu_hardware_version(::aimdk_msgs::msg::PmuState & msg)
  : msg_(msg)
  {}
  Init_PmuState_pmu_protocol_version pmu_hardware_version(::aimdk_msgs::msg::PmuState::_pmu_hardware_version_type arg)
  {
    msg_.pmu_hardware_version = std::move(arg);
    return Init_PmuState_pmu_protocol_version(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

class Init_PmuState_pmu_software_version
{
public:
  Init_PmuState_pmu_software_version()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PmuState_pmu_hardware_version pmu_software_version(::aimdk_msgs::msg::PmuState::_pmu_software_version_type arg)
  {
    msg_.pmu_software_version = std::move(arg);
    return Init_PmuState_pmu_hardware_version(msg_);
  }

private:
  ::aimdk_msgs::msg::PmuState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::PmuState>()
{
  return aimdk_msgs::msg::builder::Init_PmuState_pmu_software_version();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PMU_STATE__BUILDER_HPP_

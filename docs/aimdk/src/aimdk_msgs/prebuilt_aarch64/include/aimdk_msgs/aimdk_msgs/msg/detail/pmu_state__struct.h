// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/PmuState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PMU_STATE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__PMU_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pmu_software_version'
// Member 'pmu_hardware_version'
// Member 'pmu_protocol_version'
// Member 'bms_manufacturer'
// Member 'bms_serial_number'
// Member 'bms_hardware_version'
// Member 'bms_software_version'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/PmuState in the package aimdk_msgs.
/**
  * -------------- pmu -------------- #
  * 版本信息
 */
typedef struct aimdk_msgs__msg__PmuState
{
  /// 软件版本
  rosidl_runtime_c__String pmu_software_version;
  /// 硬件版本
  rosidl_runtime_c__String pmu_hardware_version;
  /// 协议版本
  rosidl_runtime_c__String pmu_protocol_version;
  /// 布尔状态
  uint32_t pmu_bool_status;
  /// 布尔状态位定义说明：
  /// bit 0: rk3588PowerGood          RK3588 电源状态
  /// bit 1: rk3588Monitor1           RK3588 监控状态1
  /// bit 2: rk3588Monitor2           RK3588 监控状态2
  /// bit 3: orinPowerGood            ORIN 电源状态
  /// bit 4: orinMonitor1             ORIN 监控状态1
  /// bit 5: orinMonitor2             ORIN 监控状态2
  /// bit 6: bus48vOverCurrent        48V 总线过流
  /// bit 7: bus48vOverTemperature    48V 总线过温
  /// bit 8: rk3588PlugDetect         RK3588 插入检测
  /// bit 9: orinNXPlugDetect         ORIN NX 插入检测
  /// bits 10~31: reserved            保留位
  /// 电流信息
  /// 头部电流（单位：A）
  double head_power_current;
  /// 48V输出电流（单位：A）
  double output_48v_current;
  /// rk3588电流（单位：A）
  double rk3588_current;
  /// 12V输出电流（单位：A）
  double output_12v_current;
  /// 48V总线电流（单位：A）
  double bus_48v_current;
  /// ORIN电流（单位：A）
  double orin_current;
  /// 电压信息
  /// 48V PMOS电压（单位：V）
  double bus_48v_pmos_voltage;
  /// 电池电压（单位：V）
  double battery_voltage;
  /// 风扇电压（单位：V）
  double fan_voltage;
  /// 12V输出电压（单位：V）
  double output_12v_voltage;
  /// 48V输出电压（单位：V）
  double output_48v_voltage;
  /// 48V总线电压（单位：V）
  double bus_48v_voltage;
  /// 头部电压（单位：V）
  double head_power_voltage;
  /// ORIN电压（单位：V）
  double orin_voltage;
  /// rk3588电压（单位：V）
  double rk3588_voltage;
  /// 其他狀态
  /// 风扇转速（单位：RPM）
  double fan_speed;
  /// 风扇转速百分比（单位：%）
  uint8_t fan_pecentage;
  /// 温度（单位: °C）
  double pmu_temperature;
  /// -------------- bms -------------- #
  /// 版本信息
  /// 厂家信息
  rosidl_runtime_c__String bms_manufacturer;
  /// 序列号
  rosidl_runtime_c__String bms_serial_number;
  /// 硬件版本
  rosidl_runtime_c__String bms_hardware_version;
  /// 软件版本
  rosidl_runtime_c__String bms_software_version;
  /// 状态信息
  /// 状态位和状态码
  uint32_t bms_status_bits;
  /// 状态位和状态码说明
  /// bit 0: chargeFlag                           充电标志
  /// bit 1: chargeOverCurrentFlag                充电过流标志
  /// bit 2: dischargeFlag                        放电标志
  /// bit 3: dischargeOverCurrentFlag             放电过流标志
  /// bit 4: shortCircuitFlag                     电池短路标志
  /// bit 5: cellOverVoltageFlag                  电芯电压过压标志
  /// bit 6: cellUnderVoltageFlag                 电芯电压欠压标志
  /// bit 7: batteryOverVoltageFlag               电池总电压过压标志
  /// bit 8 batteryUnderVoltageFlag               电池总电压欠压标志
  /// bit 9: cellOpenCircuitFlag                  电芯检测到开路标志
  /// bit 10: ntcOpenCircuitFlag                  温度传感器检测到开路标志
  /// bit 11: cellDischargeOverTemperatureFlag    电芯温度超过放电温度上限标志
  /// bit 12: cellChargeOverTemperatureFlag       电芯温度超过充电温度上限标志
  /// bit 13: cellDischargeUnderTemperatureFlag   电芯温度低于放电温度下限标志
  /// bit 14: cellChargeUnderTemperatureFlag      电芯温度低于充电温度下限标志
  /// bit 15: reserved_1                          保留位
  /// bit 16: cellMaxVoltageDiffOverHighFlag      电芯最大电压差超过上限标志
  /// bit 17: mosfetChargeDisableFlag             MOSFET禁止充电标志
  /// bit 18: mosfetDischargeDisableFlag          MOSFET禁止放电标志
  /// bit 19: mosfetOverTemperatureFlag           MOSFET温度超过工作温度上限标志
  /// bit 20: balanceLineResistanceOverHighFlag   电池包均衡线电阻超过上限标志
  /// bit 21~31: reserved_11                      保留位
  /// 电池包均衡线电阻（单位：mΩ）
  uint16_t battery_balance_line_resistance;
  /// 电池包电压（单位：V）
  double battery_pack_voltage;
  /// 电池包电流（单位：A，充电为正，放电为负）
  double battery_current;
  /// 电池包输出功率（单位：W）
  double battery_output_power;
  /// 电池包当前温度（单位：℃）
  double battery_temperature;
  /// 当前电池剩余容量（单位：mAh）
  uint32_t battery_remaining_capacity;
  /// 当前电池剩余容量百分比（单位：％）
  uint8_t battery_remaining_capacity_percentage;
  /// 当前电池包完整循环次数（单位：次）
  uint16_t battery_cycle_count;
  /// 总充放电容量累计（单位：Ah）
  uint32_t battery_cycle_total_capacity;
} aimdk_msgs__msg__PmuState;

// Struct for a sequence of aimdk_msgs__msg__PmuState.
typedef struct aimdk_msgs__msg__PmuState__Sequence
{
  aimdk_msgs__msg__PmuState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__PmuState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__PMU_STATE__STRUCT_H_

# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/PmuState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PmuState(type):
    """Metaclass of message 'PmuState'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('aimdk_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'aimdk_msgs.msg.PmuState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__pmu_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__pmu_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__pmu_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__pmu_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__pmu_state

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PmuState(metaclass=Metaclass_PmuState):
    """Message class 'PmuState'."""

    __slots__ = [
        '_pmu_software_version',
        '_pmu_hardware_version',
        '_pmu_protocol_version',
        '_pmu_bool_status',
        '_head_power_current',
        '_output_48v_current',
        '_rk3588_current',
        '_output_12v_current',
        '_bus_48v_current',
        '_orin_current',
        '_bus_48v_pmos_voltage',
        '_battery_voltage',
        '_fan_voltage',
        '_output_12v_voltage',
        '_output_48v_voltage',
        '_bus_48v_voltage',
        '_head_power_voltage',
        '_orin_voltage',
        '_rk3588_voltage',
        '_fan_speed',
        '_fan_pecentage',
        '_pmu_temperature',
        '_bms_manufacturer',
        '_bms_serial_number',
        '_bms_hardware_version',
        '_bms_software_version',
        '_bms_status_bits',
        '_battery_balance_line_resistance',
        '_battery_pack_voltage',
        '_battery_current',
        '_battery_output_power',
        '_battery_temperature',
        '_battery_remaining_capacity',
        '_battery_remaining_capacity_percentage',
        '_battery_cycle_count',
        '_battery_cycle_total_capacity',
    ]

    _fields_and_field_types = {
        'pmu_software_version': 'string',
        'pmu_hardware_version': 'string',
        'pmu_protocol_version': 'string',
        'pmu_bool_status': 'uint32',
        'head_power_current': 'double',
        'output_48v_current': 'double',
        'rk3588_current': 'double',
        'output_12v_current': 'double',
        'bus_48v_current': 'double',
        'orin_current': 'double',
        'bus_48v_pmos_voltage': 'double',
        'battery_voltage': 'double',
        'fan_voltage': 'double',
        'output_12v_voltage': 'double',
        'output_48v_voltage': 'double',
        'bus_48v_voltage': 'double',
        'head_power_voltage': 'double',
        'orin_voltage': 'double',
        'rk3588_voltage': 'double',
        'fan_speed': 'double',
        'fan_pecentage': 'uint8',
        'pmu_temperature': 'double',
        'bms_manufacturer': 'string',
        'bms_serial_number': 'string',
        'bms_hardware_version': 'string',
        'bms_software_version': 'string',
        'bms_status_bits': 'uint32',
        'battery_balance_line_resistance': 'uint16',
        'battery_pack_voltage': 'double',
        'battery_current': 'double',
        'battery_output_power': 'double',
        'battery_temperature': 'double',
        'battery_remaining_capacity': 'uint32',
        'battery_remaining_capacity_percentage': 'uint8',
        'battery_cycle_count': 'uint16',
        'battery_cycle_total_capacity': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.pmu_software_version = kwargs.get('pmu_software_version', str())
        self.pmu_hardware_version = kwargs.get('pmu_hardware_version', str())
        self.pmu_protocol_version = kwargs.get('pmu_protocol_version', str())
        self.pmu_bool_status = kwargs.get('pmu_bool_status', int())
        self.head_power_current = kwargs.get('head_power_current', float())
        self.output_48v_current = kwargs.get('output_48v_current', float())
        self.rk3588_current = kwargs.get('rk3588_current', float())
        self.output_12v_current = kwargs.get('output_12v_current', float())
        self.bus_48v_current = kwargs.get('bus_48v_current', float())
        self.orin_current = kwargs.get('orin_current', float())
        self.bus_48v_pmos_voltage = kwargs.get('bus_48v_pmos_voltage', float())
        self.battery_voltage = kwargs.get('battery_voltage', float())
        self.fan_voltage = kwargs.get('fan_voltage', float())
        self.output_12v_voltage = kwargs.get('output_12v_voltage', float())
        self.output_48v_voltage = kwargs.get('output_48v_voltage', float())
        self.bus_48v_voltage = kwargs.get('bus_48v_voltage', float())
        self.head_power_voltage = kwargs.get('head_power_voltage', float())
        self.orin_voltage = kwargs.get('orin_voltage', float())
        self.rk3588_voltage = kwargs.get('rk3588_voltage', float())
        self.fan_speed = kwargs.get('fan_speed', float())
        self.fan_pecentage = kwargs.get('fan_pecentage', int())
        self.pmu_temperature = kwargs.get('pmu_temperature', float())
        self.bms_manufacturer = kwargs.get('bms_manufacturer', str())
        self.bms_serial_number = kwargs.get('bms_serial_number', str())
        self.bms_hardware_version = kwargs.get('bms_hardware_version', str())
        self.bms_software_version = kwargs.get('bms_software_version', str())
        self.bms_status_bits = kwargs.get('bms_status_bits', int())
        self.battery_balance_line_resistance = kwargs.get('battery_balance_line_resistance', int())
        self.battery_pack_voltage = kwargs.get('battery_pack_voltage', float())
        self.battery_current = kwargs.get('battery_current', float())
        self.battery_output_power = kwargs.get('battery_output_power', float())
        self.battery_temperature = kwargs.get('battery_temperature', float())
        self.battery_remaining_capacity = kwargs.get('battery_remaining_capacity', int())
        self.battery_remaining_capacity_percentage = kwargs.get('battery_remaining_capacity_percentage', int())
        self.battery_cycle_count = kwargs.get('battery_cycle_count', int())
        self.battery_cycle_total_capacity = kwargs.get('battery_cycle_total_capacity', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.pmu_software_version != other.pmu_software_version:
            return False
        if self.pmu_hardware_version != other.pmu_hardware_version:
            return False
        if self.pmu_protocol_version != other.pmu_protocol_version:
            return False
        if self.pmu_bool_status != other.pmu_bool_status:
            return False
        if self.head_power_current != other.head_power_current:
            return False
        if self.output_48v_current != other.output_48v_current:
            return False
        if self.rk3588_current != other.rk3588_current:
            return False
        if self.output_12v_current != other.output_12v_current:
            return False
        if self.bus_48v_current != other.bus_48v_current:
            return False
        if self.orin_current != other.orin_current:
            return False
        if self.bus_48v_pmos_voltage != other.bus_48v_pmos_voltage:
            return False
        if self.battery_voltage != other.battery_voltage:
            return False
        if self.fan_voltage != other.fan_voltage:
            return False
        if self.output_12v_voltage != other.output_12v_voltage:
            return False
        if self.output_48v_voltage != other.output_48v_voltage:
            return False
        if self.bus_48v_voltage != other.bus_48v_voltage:
            return False
        if self.head_power_voltage != other.head_power_voltage:
            return False
        if self.orin_voltage != other.orin_voltage:
            return False
        if self.rk3588_voltage != other.rk3588_voltage:
            return False
        if self.fan_speed != other.fan_speed:
            return False
        if self.fan_pecentage != other.fan_pecentage:
            return False
        if self.pmu_temperature != other.pmu_temperature:
            return False
        if self.bms_manufacturer != other.bms_manufacturer:
            return False
        if self.bms_serial_number != other.bms_serial_number:
            return False
        if self.bms_hardware_version != other.bms_hardware_version:
            return False
        if self.bms_software_version != other.bms_software_version:
            return False
        if self.bms_status_bits != other.bms_status_bits:
            return False
        if self.battery_balance_line_resistance != other.battery_balance_line_resistance:
            return False
        if self.battery_pack_voltage != other.battery_pack_voltage:
            return False
        if self.battery_current != other.battery_current:
            return False
        if self.battery_output_power != other.battery_output_power:
            return False
        if self.battery_temperature != other.battery_temperature:
            return False
        if self.battery_remaining_capacity != other.battery_remaining_capacity:
            return False
        if self.battery_remaining_capacity_percentage != other.battery_remaining_capacity_percentage:
            return False
        if self.battery_cycle_count != other.battery_cycle_count:
            return False
        if self.battery_cycle_total_capacity != other.battery_cycle_total_capacity:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def pmu_software_version(self):
        """Message field 'pmu_software_version'."""
        return self._pmu_software_version

    @pmu_software_version.setter
    def pmu_software_version(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'pmu_software_version' field must be of type 'str'"
        self._pmu_software_version = value

    @builtins.property
    def pmu_hardware_version(self):
        """Message field 'pmu_hardware_version'."""
        return self._pmu_hardware_version

    @pmu_hardware_version.setter
    def pmu_hardware_version(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'pmu_hardware_version' field must be of type 'str'"
        self._pmu_hardware_version = value

    @builtins.property
    def pmu_protocol_version(self):
        """Message field 'pmu_protocol_version'."""
        return self._pmu_protocol_version

    @pmu_protocol_version.setter
    def pmu_protocol_version(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'pmu_protocol_version' field must be of type 'str'"
        self._pmu_protocol_version = value

    @builtins.property
    def pmu_bool_status(self):
        """Message field 'pmu_bool_status'."""
        return self._pmu_bool_status

    @pmu_bool_status.setter
    def pmu_bool_status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'pmu_bool_status' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'pmu_bool_status' field must be an unsigned integer in [0, 4294967295]"
        self._pmu_bool_status = value

    @builtins.property
    def head_power_current(self):
        """Message field 'head_power_current'."""
        return self._head_power_current

    @head_power_current.setter
    def head_power_current(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'head_power_current' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'head_power_current' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._head_power_current = value

    @builtins.property
    def output_48v_current(self):
        """Message field 'output_48v_current'."""
        return self._output_48v_current

    @output_48v_current.setter
    def output_48v_current(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'output_48v_current' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'output_48v_current' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._output_48v_current = value

    @builtins.property
    def rk3588_current(self):
        """Message field 'rk3588_current'."""
        return self._rk3588_current

    @rk3588_current.setter
    def rk3588_current(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'rk3588_current' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'rk3588_current' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._rk3588_current = value

    @builtins.property
    def output_12v_current(self):
        """Message field 'output_12v_current'."""
        return self._output_12v_current

    @output_12v_current.setter
    def output_12v_current(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'output_12v_current' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'output_12v_current' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._output_12v_current = value

    @builtins.property
    def bus_48v_current(self):
        """Message field 'bus_48v_current'."""
        return self._bus_48v_current

    @bus_48v_current.setter
    def bus_48v_current(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bus_48v_current' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'bus_48v_current' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._bus_48v_current = value

    @builtins.property
    def orin_current(self):
        """Message field 'orin_current'."""
        return self._orin_current

    @orin_current.setter
    def orin_current(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'orin_current' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'orin_current' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._orin_current = value

    @builtins.property
    def bus_48v_pmos_voltage(self):
        """Message field 'bus_48v_pmos_voltage'."""
        return self._bus_48v_pmos_voltage

    @bus_48v_pmos_voltage.setter
    def bus_48v_pmos_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bus_48v_pmos_voltage' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'bus_48v_pmos_voltage' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._bus_48v_pmos_voltage = value

    @builtins.property
    def battery_voltage(self):
        """Message field 'battery_voltage'."""
        return self._battery_voltage

    @battery_voltage.setter
    def battery_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'battery_voltage' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'battery_voltage' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._battery_voltage = value

    @builtins.property
    def fan_voltage(self):
        """Message field 'fan_voltage'."""
        return self._fan_voltage

    @fan_voltage.setter
    def fan_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'fan_voltage' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'fan_voltage' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._fan_voltage = value

    @builtins.property
    def output_12v_voltage(self):
        """Message field 'output_12v_voltage'."""
        return self._output_12v_voltage

    @output_12v_voltage.setter
    def output_12v_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'output_12v_voltage' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'output_12v_voltage' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._output_12v_voltage = value

    @builtins.property
    def output_48v_voltage(self):
        """Message field 'output_48v_voltage'."""
        return self._output_48v_voltage

    @output_48v_voltage.setter
    def output_48v_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'output_48v_voltage' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'output_48v_voltage' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._output_48v_voltage = value

    @builtins.property
    def bus_48v_voltage(self):
        """Message field 'bus_48v_voltage'."""
        return self._bus_48v_voltage

    @bus_48v_voltage.setter
    def bus_48v_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bus_48v_voltage' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'bus_48v_voltage' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._bus_48v_voltage = value

    @builtins.property
    def head_power_voltage(self):
        """Message field 'head_power_voltage'."""
        return self._head_power_voltage

    @head_power_voltage.setter
    def head_power_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'head_power_voltage' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'head_power_voltage' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._head_power_voltage = value

    @builtins.property
    def orin_voltage(self):
        """Message field 'orin_voltage'."""
        return self._orin_voltage

    @orin_voltage.setter
    def orin_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'orin_voltage' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'orin_voltage' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._orin_voltage = value

    @builtins.property
    def rk3588_voltage(self):
        """Message field 'rk3588_voltage'."""
        return self._rk3588_voltage

    @rk3588_voltage.setter
    def rk3588_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'rk3588_voltage' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'rk3588_voltage' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._rk3588_voltage = value

    @builtins.property
    def fan_speed(self):
        """Message field 'fan_speed'."""
        return self._fan_speed

    @fan_speed.setter
    def fan_speed(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'fan_speed' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'fan_speed' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._fan_speed = value

    @builtins.property
    def fan_pecentage(self):
        """Message field 'fan_pecentage'."""
        return self._fan_pecentage

    @fan_pecentage.setter
    def fan_pecentage(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'fan_pecentage' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'fan_pecentage' field must be an unsigned integer in [0, 255]"
        self._fan_pecentage = value

    @builtins.property
    def pmu_temperature(self):
        """Message field 'pmu_temperature'."""
        return self._pmu_temperature

    @pmu_temperature.setter
    def pmu_temperature(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pmu_temperature' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'pmu_temperature' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._pmu_temperature = value

    @builtins.property
    def bms_manufacturer(self):
        """Message field 'bms_manufacturer'."""
        return self._bms_manufacturer

    @bms_manufacturer.setter
    def bms_manufacturer(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'bms_manufacturer' field must be of type 'str'"
        self._bms_manufacturer = value

    @builtins.property
    def bms_serial_number(self):
        """Message field 'bms_serial_number'."""
        return self._bms_serial_number

    @bms_serial_number.setter
    def bms_serial_number(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'bms_serial_number' field must be of type 'str'"
        self._bms_serial_number = value

    @builtins.property
    def bms_hardware_version(self):
        """Message field 'bms_hardware_version'."""
        return self._bms_hardware_version

    @bms_hardware_version.setter
    def bms_hardware_version(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'bms_hardware_version' field must be of type 'str'"
        self._bms_hardware_version = value

    @builtins.property
    def bms_software_version(self):
        """Message field 'bms_software_version'."""
        return self._bms_software_version

    @bms_software_version.setter
    def bms_software_version(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'bms_software_version' field must be of type 'str'"
        self._bms_software_version = value

    @builtins.property
    def bms_status_bits(self):
        """Message field 'bms_status_bits'."""
        return self._bms_status_bits

    @bms_status_bits.setter
    def bms_status_bits(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'bms_status_bits' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'bms_status_bits' field must be an unsigned integer in [0, 4294967295]"
        self._bms_status_bits = value

    @builtins.property
    def battery_balance_line_resistance(self):
        """Message field 'battery_balance_line_resistance'."""
        return self._battery_balance_line_resistance

    @battery_balance_line_resistance.setter
    def battery_balance_line_resistance(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'battery_balance_line_resistance' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'battery_balance_line_resistance' field must be an unsigned integer in [0, 65535]"
        self._battery_balance_line_resistance = value

    @builtins.property
    def battery_pack_voltage(self):
        """Message field 'battery_pack_voltage'."""
        return self._battery_pack_voltage

    @battery_pack_voltage.setter
    def battery_pack_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'battery_pack_voltage' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'battery_pack_voltage' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._battery_pack_voltage = value

    @builtins.property
    def battery_current(self):
        """Message field 'battery_current'."""
        return self._battery_current

    @battery_current.setter
    def battery_current(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'battery_current' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'battery_current' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._battery_current = value

    @builtins.property
    def battery_output_power(self):
        """Message field 'battery_output_power'."""
        return self._battery_output_power

    @battery_output_power.setter
    def battery_output_power(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'battery_output_power' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'battery_output_power' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._battery_output_power = value

    @builtins.property
    def battery_temperature(self):
        """Message field 'battery_temperature'."""
        return self._battery_temperature

    @battery_temperature.setter
    def battery_temperature(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'battery_temperature' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'battery_temperature' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._battery_temperature = value

    @builtins.property
    def battery_remaining_capacity(self):
        """Message field 'battery_remaining_capacity'."""
        return self._battery_remaining_capacity

    @battery_remaining_capacity.setter
    def battery_remaining_capacity(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'battery_remaining_capacity' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'battery_remaining_capacity' field must be an unsigned integer in [0, 4294967295]"
        self._battery_remaining_capacity = value

    @builtins.property
    def battery_remaining_capacity_percentage(self):
        """Message field 'battery_remaining_capacity_percentage'."""
        return self._battery_remaining_capacity_percentage

    @battery_remaining_capacity_percentage.setter
    def battery_remaining_capacity_percentage(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'battery_remaining_capacity_percentage' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'battery_remaining_capacity_percentage' field must be an unsigned integer in [0, 255]"
        self._battery_remaining_capacity_percentage = value

    @builtins.property
    def battery_cycle_count(self):
        """Message field 'battery_cycle_count'."""
        return self._battery_cycle_count

    @battery_cycle_count.setter
    def battery_cycle_count(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'battery_cycle_count' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'battery_cycle_count' field must be an unsigned integer in [0, 65535]"
        self._battery_cycle_count = value

    @builtins.property
    def battery_cycle_total_capacity(self):
        """Message field 'battery_cycle_total_capacity'."""
        return self._battery_cycle_total_capacity

    @battery_cycle_total_capacity.setter
    def battery_cycle_total_capacity(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'battery_cycle_total_capacity' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'battery_cycle_total_capacity' field must be an unsigned integer in [0, 4294967295]"
        self._battery_cycle_total_capacity = value

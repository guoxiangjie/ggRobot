# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/TtsPriorityLevel.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TtsPriorityLevel(type):
    """Metaclass of message 'TtsPriorityLevel'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'UNKNOWN': 0,
        'BACKGROUND_L1': 1,
        'SERVICE_L2': 2,
        'MISSION_L4': 4,
        'INTERACTION_L6': 6,
        'SYSTEM_L7': 7,
        'WARNING_L8': 8,
        'SAFETY_L10': 10,
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
                'aimdk_msgs.msg.TtsPriorityLevel')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__tts_priority_level
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__tts_priority_level
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__tts_priority_level
            cls._TYPE_SUPPORT = module.type_support_msg__msg__tts_priority_level
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__tts_priority_level

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'UNKNOWN': cls.__constants['UNKNOWN'],
            'BACKGROUND_L1': cls.__constants['BACKGROUND_L1'],
            'SERVICE_L2': cls.__constants['SERVICE_L2'],
            'MISSION_L4': cls.__constants['MISSION_L4'],
            'INTERACTION_L6': cls.__constants['INTERACTION_L6'],
            'SYSTEM_L7': cls.__constants['SYSTEM_L7'],
            'WARNING_L8': cls.__constants['WARNING_L8'],
            'SAFETY_L10': cls.__constants['SAFETY_L10'],
        }

    @property
    def UNKNOWN(self):
        """Message constant 'UNKNOWN'."""
        return Metaclass_TtsPriorityLevel.__constants['UNKNOWN']

    @property
    def BACKGROUND_L1(self):
        """Message constant 'BACKGROUND_L1'."""
        return Metaclass_TtsPriorityLevel.__constants['BACKGROUND_L1']

    @property
    def SERVICE_L2(self):
        """Message constant 'SERVICE_L2'."""
        return Metaclass_TtsPriorityLevel.__constants['SERVICE_L2']

    @property
    def MISSION_L4(self):
        """Message constant 'MISSION_L4'."""
        return Metaclass_TtsPriorityLevel.__constants['MISSION_L4']

    @property
    def INTERACTION_L6(self):
        """Message constant 'INTERACTION_L6'."""
        return Metaclass_TtsPriorityLevel.__constants['INTERACTION_L6']

    @property
    def SYSTEM_L7(self):
        """Message constant 'SYSTEM_L7'."""
        return Metaclass_TtsPriorityLevel.__constants['SYSTEM_L7']

    @property
    def WARNING_L8(self):
        """Message constant 'WARNING_L8'."""
        return Metaclass_TtsPriorityLevel.__constants['WARNING_L8']

    @property
    def SAFETY_L10(self):
        """Message constant 'SAFETY_L10'."""
        return Metaclass_TtsPriorityLevel.__constants['SAFETY_L10']


class TtsPriorityLevel(metaclass=Metaclass_TtsPriorityLevel):
    """
    Message class 'TtsPriorityLevel'.

    Constants:
      UNKNOWN
      BACKGROUND_L1
      SERVICE_L2
      MISSION_L4
      INTERACTION_L6
      SYSTEM_L7
      WARNING_L8
      SAFETY_L10
    """

    __slots__ = [
        '_value',
    ]

    _fields_and_field_types = {
        'value': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.value = kwargs.get('value', int())

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
        if self.value != other.value:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def value(self):
        """Message field 'value'."""
        return self._value

    @value.setter
    def value(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'value' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'value' field must be an unsigned integer in [0, 255]"
        self._value = value

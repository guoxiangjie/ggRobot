# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/SystemStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SystemStatus(type):
    """Metaclass of message 'SystemStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'IN_INITIAL': 0,
        'IN_READY': 1,
        'IN_MOVE': 2,
        'IN_ROLLBACK': 3,
        'IN_FALLBACK': 4,
        'IN_FALLBACK_MOVE': 5,
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
                'aimdk_msgs.msg.SystemStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__system_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__system_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__system_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__system_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__system_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'IN_INITIAL': cls.__constants['IN_INITIAL'],
            'IN_READY': cls.__constants['IN_READY'],
            'IN_MOVE': cls.__constants['IN_MOVE'],
            'IN_ROLLBACK': cls.__constants['IN_ROLLBACK'],
            'IN_FALLBACK': cls.__constants['IN_FALLBACK'],
            'IN_FALLBACK_MOVE': cls.__constants['IN_FALLBACK_MOVE'],
        }

    @property
    def IN_INITIAL(self):
        """Message constant 'IN_INITIAL'."""
        return Metaclass_SystemStatus.__constants['IN_INITIAL']

    @property
    def IN_READY(self):
        """Message constant 'IN_READY'."""
        return Metaclass_SystemStatus.__constants['IN_READY']

    @property
    def IN_MOVE(self):
        """Message constant 'IN_MOVE'."""
        return Metaclass_SystemStatus.__constants['IN_MOVE']

    @property
    def IN_ROLLBACK(self):
        """Message constant 'IN_ROLLBACK'."""
        return Metaclass_SystemStatus.__constants['IN_ROLLBACK']

    @property
    def IN_FALLBACK(self):
        """Message constant 'IN_FALLBACK'."""
        return Metaclass_SystemStatus.__constants['IN_FALLBACK']

    @property
    def IN_FALLBACK_MOVE(self):
        """Message constant 'IN_FALLBACK_MOVE'."""
        return Metaclass_SystemStatus.__constants['IN_FALLBACK_MOVE']


class SystemStatus(metaclass=Metaclass_SystemStatus):
    """
    Message class 'SystemStatus'.

    Constants:
      IN_INITIAL
      IN_READY
      IN_MOVE
      IN_ROLLBACK
      IN_FALLBACK
      IN_FALLBACK_MOVE
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

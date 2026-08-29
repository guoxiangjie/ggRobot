# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/CommonState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_CommonState(type):
    """Metaclass of message 'CommonState'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'UNKNOWN': 0,
        'SUCCESS': 1,
        'FAILURE': 2,
        'ABORTED': 3,
        'TIMEOUT': 4,
        'INVALID': 5,
        'IN_MANUAL': 6,
        'NOT_READY': 100,
        'PENDING': 200,
        'CREATED': 300,
        'RUNNING': 400,
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
                'aimdk_msgs.msg.CommonState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__common_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__common_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__common_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__common_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__common_state

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'UNKNOWN': cls.__constants['UNKNOWN'],
            'SUCCESS': cls.__constants['SUCCESS'],
            'FAILURE': cls.__constants['FAILURE'],
            'ABORTED': cls.__constants['ABORTED'],
            'TIMEOUT': cls.__constants['TIMEOUT'],
            'INVALID': cls.__constants['INVALID'],
            'IN_MANUAL': cls.__constants['IN_MANUAL'],
            'NOT_READY': cls.__constants['NOT_READY'],
            'PENDING': cls.__constants['PENDING'],
            'CREATED': cls.__constants['CREATED'],
            'RUNNING': cls.__constants['RUNNING'],
        }

    @property
    def UNKNOWN(self):
        """Message constant 'UNKNOWN'."""
        return Metaclass_CommonState.__constants['UNKNOWN']

    @property
    def SUCCESS(self):
        """Message constant 'SUCCESS'."""
        return Metaclass_CommonState.__constants['SUCCESS']

    @property
    def FAILURE(self):
        """Message constant 'FAILURE'."""
        return Metaclass_CommonState.__constants['FAILURE']

    @property
    def ABORTED(self):
        """Message constant 'ABORTED'."""
        return Metaclass_CommonState.__constants['ABORTED']

    @property
    def TIMEOUT(self):
        """Message constant 'TIMEOUT'."""
        return Metaclass_CommonState.__constants['TIMEOUT']

    @property
    def INVALID(self):
        """Message constant 'INVALID'."""
        return Metaclass_CommonState.__constants['INVALID']

    @property
    def IN_MANUAL(self):
        """Message constant 'IN_MANUAL'."""
        return Metaclass_CommonState.__constants['IN_MANUAL']

    @property
    def NOT_READY(self):
        """Message constant 'NOT_READY'."""
        return Metaclass_CommonState.__constants['NOT_READY']

    @property
    def PENDING(self):
        """Message constant 'PENDING'."""
        return Metaclass_CommonState.__constants['PENDING']

    @property
    def CREATED(self):
        """Message constant 'CREATED'."""
        return Metaclass_CommonState.__constants['CREATED']

    @property
    def RUNNING(self):
        """Message constant 'RUNNING'."""
        return Metaclass_CommonState.__constants['RUNNING']


class CommonState(metaclass=Metaclass_CommonState):
    """
    Message class 'CommonState'.

    Constants:
      UNKNOWN
      SUCCESS
      FAILURE
      ABORTED
      TIMEOUT
      INVALID
      IN_MANUAL
      NOT_READY
      PENDING
      CREATED
      RUNNING
    """

    __slots__ = [
        '_value',
    ]

    _fields_and_field_types = {
        'value': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
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
            assert value >= -2147483648 and value < 2147483648, \
                "The 'value' field must be an integer in [-2147483648, 2147483647]"
        self._value = value

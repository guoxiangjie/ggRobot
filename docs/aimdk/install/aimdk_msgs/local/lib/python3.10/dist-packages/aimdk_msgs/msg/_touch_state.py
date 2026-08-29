# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/TouchState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

# Member 'data'
# Member 'threshold'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TouchState(type):
    """Metaclass of message 'TouchState'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'UNKNOWN': 0,
        'IDLE': 1,
        'TOUCH': 2,
        'SLIDE': 3,
        'PAT_ONCE': 4,
        'PAT_TWICE': 5,
        'PAT_TRIPLE': 6,
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
                'aimdk_msgs.msg.TouchState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__touch_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__touch_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__touch_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__touch_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__touch_state

            from aimdk_msgs.msg import MessageHeader
            if MessageHeader.__class__._TYPE_SUPPORT is None:
                MessageHeader.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'UNKNOWN': cls.__constants['UNKNOWN'],
            'IDLE': cls.__constants['IDLE'],
            'TOUCH': cls.__constants['TOUCH'],
            'SLIDE': cls.__constants['SLIDE'],
            'PAT_ONCE': cls.__constants['PAT_ONCE'],
            'PAT_TWICE': cls.__constants['PAT_TWICE'],
            'PAT_TRIPLE': cls.__constants['PAT_TRIPLE'],
        }

    @property
    def UNKNOWN(self):
        """Message constant 'UNKNOWN'."""
        return Metaclass_TouchState.__constants['UNKNOWN']

    @property
    def IDLE(self):
        """Message constant 'IDLE'."""
        return Metaclass_TouchState.__constants['IDLE']

    @property
    def TOUCH(self):
        """Message constant 'TOUCH'."""
        return Metaclass_TouchState.__constants['TOUCH']

    @property
    def SLIDE(self):
        """Message constant 'SLIDE'."""
        return Metaclass_TouchState.__constants['SLIDE']

    @property
    def PAT_ONCE(self):
        """Message constant 'PAT_ONCE'."""
        return Metaclass_TouchState.__constants['PAT_ONCE']

    @property
    def PAT_TWICE(self):
        """Message constant 'PAT_TWICE'."""
        return Metaclass_TouchState.__constants['PAT_TWICE']

    @property
    def PAT_TRIPLE(self):
        """Message constant 'PAT_TRIPLE'."""
        return Metaclass_TouchState.__constants['PAT_TRIPLE']


class TouchState(metaclass=Metaclass_TouchState):
    """
    Message class 'TouchState'.

    Constants:
      UNKNOWN
      IDLE
      TOUCH
      SLIDE
      PAT_ONCE
      PAT_TWICE
      PAT_TRIPLE
    """

    __slots__ = [
        '_header',
        '_event_type',
        '_data',
        '_threshold',
        '_is_touched',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/MessageHeader',
        'event_type': 'uint8',
        'data': 'uint32[8]',
        'threshold': 'uint32[8]',
        'is_touched': 'boolean[8]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'MessageHeader'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint32'), 8),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint32'), 8),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('boolean'), 8),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import MessageHeader
        self.header = kwargs.get('header', MessageHeader())
        self.event_type = kwargs.get('event_type', int())
        if 'data' not in kwargs:
            self.data = numpy.zeros(8, dtype=numpy.uint32)
        else:
            self.data = numpy.array(kwargs.get('data'), dtype=numpy.uint32)
            assert self.data.shape == (8, )
        if 'threshold' not in kwargs:
            self.threshold = numpy.zeros(8, dtype=numpy.uint32)
        else:
            self.threshold = numpy.array(kwargs.get('threshold'), dtype=numpy.uint32)
            assert self.threshold.shape == (8, )
        self.is_touched = kwargs.get(
            'is_touched',
            [bool() for x in range(8)]
        )

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
        if self.header != other.header:
            return False
        if self.event_type != other.event_type:
            return False
        if all(self.data != other.data):
            return False
        if all(self.threshold != other.threshold):
            return False
        if self.is_touched != other.is_touched:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from aimdk_msgs.msg import MessageHeader
            assert \
                isinstance(value, MessageHeader), \
                "The 'header' field must be a sub message of type 'MessageHeader'"
        self._header = value

    @builtins.property
    def event_type(self):
        """Message field 'event_type'."""
        return self._event_type

    @event_type.setter
    def event_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'event_type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'event_type' field must be an unsigned integer in [0, 255]"
        self._event_type = value

    @builtins.property
    def data(self):
        """Message field 'data'."""
        return self._data

    @data.setter
    def data(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.uint32, \
                "The 'data' numpy.ndarray() must have the dtype of 'numpy.uint32'"
            assert value.size == 8, \
                "The 'data' numpy.ndarray() must have a size of 8"
            self._data = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 8 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 4294967296 for val in value)), \
                "The 'data' field must be a set or sequence with length 8 and each value of type 'int' and each unsigned integer in [0, 4294967295]"
        self._data = numpy.array(value, dtype=numpy.uint32)

    @builtins.property
    def threshold(self):
        """Message field 'threshold'."""
        return self._threshold

    @threshold.setter
    def threshold(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.uint32, \
                "The 'threshold' numpy.ndarray() must have the dtype of 'numpy.uint32'"
            assert value.size == 8, \
                "The 'threshold' numpy.ndarray() must have a size of 8"
            self._threshold = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 8 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 4294967296 for val in value)), \
                "The 'threshold' field must be a set or sequence with length 8 and each value of type 'int' and each unsigned integer in [0, 4294967295]"
        self._threshold = numpy.array(value, dtype=numpy.uint32)

    @builtins.property
    def is_touched(self):
        """Message field 'is_touched'."""
        return self._is_touched

    @is_touched.setter
    def is_touched(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 8 and
                 all(isinstance(v, bool) for v in value) and
                 True), \
                "The 'is_touched' field must be a set or sequence with length 8 and each value of type 'bool'"
        self._is_touched = value

# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/FaceEmojiStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_FaceEmojiStatus(type):
    """Metaclass of message 'FaceEmojiStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'STATUS_IDLE': 0,
        'STATUS_START': 1,
        'STATUS_RUNNING': 2,
        'STATUS_FINISHED': 3,
        'STATUS_STOPPED': 4,
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
                'aimdk_msgs.msg.FaceEmojiStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__face_emoji_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__face_emoji_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__face_emoji_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__face_emoji_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__face_emoji_status

            from aimdk_msgs.msg import MessageHeader
            if MessageHeader.__class__._TYPE_SUPPORT is None:
                MessageHeader.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'STATUS_IDLE': cls.__constants['STATUS_IDLE'],
            'STATUS_START': cls.__constants['STATUS_START'],
            'STATUS_RUNNING': cls.__constants['STATUS_RUNNING'],
            'STATUS_FINISHED': cls.__constants['STATUS_FINISHED'],
            'STATUS_STOPPED': cls.__constants['STATUS_STOPPED'],
        }

    @property
    def STATUS_IDLE(self):
        """Message constant 'STATUS_IDLE'."""
        return Metaclass_FaceEmojiStatus.__constants['STATUS_IDLE']

    @property
    def STATUS_START(self):
        """Message constant 'STATUS_START'."""
        return Metaclass_FaceEmojiStatus.__constants['STATUS_START']

    @property
    def STATUS_RUNNING(self):
        """Message constant 'STATUS_RUNNING'."""
        return Metaclass_FaceEmojiStatus.__constants['STATUS_RUNNING']

    @property
    def STATUS_FINISHED(self):
        """Message constant 'STATUS_FINISHED'."""
        return Metaclass_FaceEmojiStatus.__constants['STATUS_FINISHED']

    @property
    def STATUS_STOPPED(self):
        """Message constant 'STATUS_STOPPED'."""
        return Metaclass_FaceEmojiStatus.__constants['STATUS_STOPPED']


class FaceEmojiStatus(metaclass=Metaclass_FaceEmojiStatus):
    """
    Message class 'FaceEmojiStatus'.

    Constants:
      STATUS_IDLE
      STATUS_START
      STATUS_RUNNING
      STATUS_FINISHED
      STATUS_STOPPED
    """

    __slots__ = [
        '_header',
        '_e_path',
        '_e_path_list',
        '_e_id',
        '_mode',
        '_priority',
        '_status',
        '_time_to_end_ms',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/MessageHeader',
        'e_path': 'string',
        'e_path_list': 'sequence<string>',
        'e_id': 'uint8',
        'mode': 'uint8',
        'priority': 'int32',
        'status': 'uint8',
        'time_to_end_ms': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'MessageHeader'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import MessageHeader
        self.header = kwargs.get('header', MessageHeader())
        self.e_path = kwargs.get('e_path', str())
        self.e_path_list = kwargs.get('e_path_list', [])
        self.e_id = kwargs.get('e_id', int())
        self.mode = kwargs.get('mode', int())
        self.priority = kwargs.get('priority', int())
        self.status = kwargs.get('status', int())
        self.time_to_end_ms = kwargs.get('time_to_end_ms', float())

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
        if self.e_path != other.e_path:
            return False
        if self.e_path_list != other.e_path_list:
            return False
        if self.e_id != other.e_id:
            return False
        if self.mode != other.mode:
            return False
        if self.priority != other.priority:
            return False
        if self.status != other.status:
            return False
        if self.time_to_end_ms != other.time_to_end_ms:
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
    def e_path(self):
        """Message field 'e_path'."""
        return self._e_path

    @e_path.setter
    def e_path(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'e_path' field must be of type 'str'"
        self._e_path = value

    @builtins.property
    def e_path_list(self):
        """Message field 'e_path_list'."""
        return self._e_path_list

    @e_path_list.setter
    def e_path_list(self, value):
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
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'e_path_list' field must be a set or sequence and each value of type 'str'"
        self._e_path_list = value

    @builtins.property
    def e_id(self):
        """Message field 'e_id'."""
        return self._e_id

    @e_id.setter
    def e_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'e_id' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'e_id' field must be an unsigned integer in [0, 255]"
        self._e_id = value

    @builtins.property
    def mode(self):
        """Message field 'mode'."""
        return self._mode

    @mode.setter
    def mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mode' field must be an unsigned integer in [0, 255]"
        self._mode = value

    @builtins.property
    def priority(self):
        """Message field 'priority'."""
        return self._priority

    @priority.setter
    def priority(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'priority' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'priority' field must be an integer in [-2147483648, 2147483647]"
        self._priority = value

    @builtins.property
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'status' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'status' field must be an unsigned integer in [0, 255]"
        self._status = value

    @builtins.property
    def time_to_end_ms(self):
        """Message field 'time_to_end_ms'."""
        return self._time_to_end_ms

    @time_to_end_ms.setter
    def time_to_end_ms(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'time_to_end_ms' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'time_to_end_ms' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._time_to_end_ms = value

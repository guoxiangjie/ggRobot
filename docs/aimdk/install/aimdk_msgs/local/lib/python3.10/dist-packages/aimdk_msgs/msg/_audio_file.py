# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/AudioFile.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AudioFile(type):
    """Metaclass of message 'AudioFile'."""

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
                'aimdk_msgs.msg.AudioFile')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__audio_file
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__audio_file
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__audio_file
            cls._TYPE_SUPPORT = module.type_support_msg__msg__audio_file
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__audio_file

            from aimdk_msgs.msg import AudioInfo
            if AudioInfo.__class__._TYPE_SUPPORT is None:
                AudioInfo.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class AudioFile(metaclass=Metaclass_AudioFile):
    """Message class 'AudioFile'."""

    __slots__ = [
        '_pkg_name',
        '_file_name',
        '_file_path',
        '_info',
        '_priority',
        '_priority_weight',
    ]

    _fields_and_field_types = {
        'pkg_name': 'string',
        'file_name': 'string',
        'file_path': 'string',
        'info': 'aimdk_msgs/AudioInfo',
        'priority': 'uint32',
        'priority_weight': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'AudioInfo'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.pkg_name = kwargs.get('pkg_name', str())
        self.file_name = kwargs.get('file_name', str())
        self.file_path = kwargs.get('file_path', str())
        from aimdk_msgs.msg import AudioInfo
        self.info = kwargs.get('info', AudioInfo())
        self.priority = kwargs.get('priority', int())
        self.priority_weight = kwargs.get('priority_weight', int())

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
        if self.pkg_name != other.pkg_name:
            return False
        if self.file_name != other.file_name:
            return False
        if self.file_path != other.file_path:
            return False
        if self.info != other.info:
            return False
        if self.priority != other.priority:
            return False
        if self.priority_weight != other.priority_weight:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def pkg_name(self):
        """Message field 'pkg_name'."""
        return self._pkg_name

    @pkg_name.setter
    def pkg_name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'pkg_name' field must be of type 'str'"
        self._pkg_name = value

    @builtins.property
    def file_name(self):
        """Message field 'file_name'."""
        return self._file_name

    @file_name.setter
    def file_name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'file_name' field must be of type 'str'"
        self._file_name = value

    @builtins.property
    def file_path(self):
        """Message field 'file_path'."""
        return self._file_path

    @file_path.setter
    def file_path(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'file_path' field must be of type 'str'"
        self._file_path = value

    @builtins.property
    def info(self):
        """Message field 'info'."""
        return self._info

    @info.setter
    def info(self, value):
        if __debug__:
            from aimdk_msgs.msg import AudioInfo
            assert \
                isinstance(value, AudioInfo), \
                "The 'info' field must be a sub message of type 'AudioInfo'"
        self._info = value

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
            assert value >= 0 and value < 4294967296, \
                "The 'priority' field must be an unsigned integer in [0, 4294967295]"
        self._priority = value

    @builtins.property
    def priority_weight(self):
        """Message field 'priority_weight'."""
        return self._priority_weight

    @priority_weight.setter
    def priority_weight(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'priority_weight' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'priority_weight' field must be an unsigned integer in [0, 4294967295]"
        self._priority_weight = value

# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/PlayMediaFileRequest.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PlayMediaFileRequest(type):
    """Metaclass of message 'PlayMediaFileRequest'."""

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
                'aimdk_msgs.msg.PlayMediaFileRequest')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__play_media_file_request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__play_media_file_request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__play_media_file_request
            cls._TYPE_SUPPORT = module.type_support_msg__msg__play_media_file_request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__play_media_file_request

            from aimdk_msgs.msg import TtsPriorityLevel
            if TtsPriorityLevel.__class__._TYPE_SUPPORT is None:
                TtsPriorityLevel.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PlayMediaFileRequest(metaclass=Metaclass_PlayMediaFileRequest):
    """Message class 'PlayMediaFileRequest'."""

    __slots__ = [
        '_file_name',
        '_sample_rate',
        '_priority_level',
        '_priority_weight',
        '_domain',
        '_trace_id',
        '_is_interrupted',
    ]

    _fields_and_field_types = {
        'file_name': 'string',
        'sample_rate': 'uint32',
        'priority_level': 'aimdk_msgs/TtsPriorityLevel',
        'priority_weight': 'uint32',
        'domain': 'string',
        'trace_id': 'string',
        'is_interrupted': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'TtsPriorityLevel'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.file_name = kwargs.get('file_name', str())
        self.sample_rate = kwargs.get('sample_rate', int())
        from aimdk_msgs.msg import TtsPriorityLevel
        self.priority_level = kwargs.get('priority_level', TtsPriorityLevel())
        self.priority_weight = kwargs.get('priority_weight', int())
        self.domain = kwargs.get('domain', str())
        self.trace_id = kwargs.get('trace_id', str())
        self.is_interrupted = kwargs.get('is_interrupted', bool())

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
        if self.file_name != other.file_name:
            return False
        if self.sample_rate != other.sample_rate:
            return False
        if self.priority_level != other.priority_level:
            return False
        if self.priority_weight != other.priority_weight:
            return False
        if self.domain != other.domain:
            return False
        if self.trace_id != other.trace_id:
            return False
        if self.is_interrupted != other.is_interrupted:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

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
    def sample_rate(self):
        """Message field 'sample_rate'."""
        return self._sample_rate

    @sample_rate.setter
    def sample_rate(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sample_rate' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'sample_rate' field must be an unsigned integer in [0, 4294967295]"
        self._sample_rate = value

    @builtins.property
    def priority_level(self):
        """Message field 'priority_level'."""
        return self._priority_level

    @priority_level.setter
    def priority_level(self, value):
        if __debug__:
            from aimdk_msgs.msg import TtsPriorityLevel
            assert \
                isinstance(value, TtsPriorityLevel), \
                "The 'priority_level' field must be a sub message of type 'TtsPriorityLevel'"
        self._priority_level = value

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

    @builtins.property
    def domain(self):
        """Message field 'domain'."""
        return self._domain

    @domain.setter
    def domain(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'domain' field must be of type 'str'"
        self._domain = value

    @builtins.property
    def trace_id(self):
        """Message field 'trace_id'."""
        return self._trace_id

    @trace_id.setter
    def trace_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'trace_id' field must be of type 'str'"
        self._trace_id = value

    @builtins.property
    def is_interrupted(self):
        """Message field 'is_interrupted'."""
        return self._is_interrupted

    @is_interrupted.setter
    def is_interrupted(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_interrupted' field must be of type 'bool'"
        self._is_interrupted = value

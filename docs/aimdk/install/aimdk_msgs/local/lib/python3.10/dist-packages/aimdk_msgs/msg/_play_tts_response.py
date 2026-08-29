# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/PlayTtsResponse.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PlayTtsResponse(type):
    """Metaclass of message 'PlayTtsResponse'."""

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
                'aimdk_msgs.msg.PlayTtsResponse')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__play_tts_response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__play_tts_response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__play_tts_response
            cls._TYPE_SUPPORT = module.type_support_msg__msg__play_tts_response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__play_tts_response

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


class PlayTtsResponse(metaclass=Metaclass_PlayTtsResponse):
    """Message class 'PlayTtsResponse'."""

    __slots__ = [
        '_text',
        '_priority_level',
        '_priority_weight',
        '_domain',
        '_trace_id',
        '_is_success',
        '_error_message',
        '_estimated_duration',
    ]

    _fields_and_field_types = {
        'text': 'string',
        'priority_level': 'aimdk_msgs/TtsPriorityLevel',
        'priority_weight': 'uint32',
        'domain': 'string',
        'trace_id': 'string',
        'is_success': 'boolean',
        'error_message': 'string',
        'estimated_duration': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'TtsPriorityLevel'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.text = kwargs.get('text', str())
        from aimdk_msgs.msg import TtsPriorityLevel
        self.priority_level = kwargs.get('priority_level', TtsPriorityLevel())
        self.priority_weight = kwargs.get('priority_weight', int())
        self.domain = kwargs.get('domain', str())
        self.trace_id = kwargs.get('trace_id', str())
        self.is_success = kwargs.get('is_success', bool())
        self.error_message = kwargs.get('error_message', str())
        self.estimated_duration = kwargs.get('estimated_duration', int())

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
        if self.text != other.text:
            return False
        if self.priority_level != other.priority_level:
            return False
        if self.priority_weight != other.priority_weight:
            return False
        if self.domain != other.domain:
            return False
        if self.trace_id != other.trace_id:
            return False
        if self.is_success != other.is_success:
            return False
        if self.error_message != other.error_message:
            return False
        if self.estimated_duration != other.estimated_duration:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def text(self):
        """Message field 'text'."""
        return self._text

    @text.setter
    def text(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'text' field must be of type 'str'"
        self._text = value

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
    def is_success(self):
        """Message field 'is_success'."""
        return self._is_success

    @is_success.setter
    def is_success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_success' field must be of type 'bool'"
        self._is_success = value

    @builtins.property
    def error_message(self):
        """Message field 'error_message'."""
        return self._error_message

    @error_message.setter
    def error_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'error_message' field must be of type 'str'"
        self._error_message = value

    @builtins.property
    def estimated_duration(self):
        """Message field 'estimated_duration'."""
        return self._estimated_duration

    @estimated_duration.setter
    def estimated_duration(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'estimated_duration' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'estimated_duration' field must be an unsigned integer in [0, 4294967295]"
        self._estimated_duration = value

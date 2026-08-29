# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/PlayVideoGroup.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PlayVideoGroup_Request(type):
    """Metaclass of message 'PlayVideoGroup_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'EMOTION_MODE_ONCE': 1,
        'EMOTION_MODE_LOOP': 2,
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
                'aimdk_msgs.srv.PlayVideoGroup_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__play_video_group__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__play_video_group__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__play_video_group__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__play_video_group__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__play_video_group__request

            from aimdk_msgs.msg import CommonRequest
            if CommonRequest.__class__._TYPE_SUPPORT is None:
                CommonRequest.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'EMOTION_MODE_ONCE': cls.__constants['EMOTION_MODE_ONCE'],
            'EMOTION_MODE_LOOP': cls.__constants['EMOTION_MODE_LOOP'],
        }

    @property
    def EMOTION_MODE_ONCE(self):
        """Message constant 'EMOTION_MODE_ONCE'."""
        return Metaclass_PlayVideoGroup_Request.__constants['EMOTION_MODE_ONCE']

    @property
    def EMOTION_MODE_LOOP(self):
        """Message constant 'EMOTION_MODE_LOOP'."""
        return Metaclass_PlayVideoGroup_Request.__constants['EMOTION_MODE_LOOP']


class PlayVideoGroup_Request(metaclass=Metaclass_PlayVideoGroup_Request):
    """
    Message class 'PlayVideoGroup_Request'.

    Constants:
      EMOTION_MODE_ONCE
      EMOTION_MODE_LOOP
    """

    __slots__ = [
        '_header',
        '_video_path_list',
        '_mode',
        '_priority',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/CommonRequest',
        'video_path_list': 'sequence<string>',
        'mode': 'uint8',
        'priority': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonRequest'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonRequest
        self.header = kwargs.get('header', CommonRequest())
        self.video_path_list = kwargs.get('video_path_list', [])
        self.mode = kwargs.get('mode', int())
        self.priority = kwargs.get('priority', int())

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
        if self.video_path_list != other.video_path_list:
            return False
        if self.mode != other.mode:
            return False
        if self.priority != other.priority:
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
            from aimdk_msgs.msg import CommonRequest
            assert \
                isinstance(value, CommonRequest), \
                "The 'header' field must be a sub message of type 'CommonRequest'"
        self._header = value

    @builtins.property
    def video_path_list(self):
        """Message field 'video_path_list'."""
        return self._video_path_list

    @video_path_list.setter
    def video_path_list(self, value):
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
                "The 'video_path_list' field must be a set or sequence and each value of type 'str'"
        self._video_path_list = value

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


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_PlayVideoGroup_Response(type):
    """Metaclass of message 'PlayVideoGroup_Response'."""

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
                'aimdk_msgs.srv.PlayVideoGroup_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__play_video_group__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__play_video_group__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__play_video_group__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__play_video_group__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__play_video_group__response

            from aimdk_msgs.msg import CommonResponse
            if CommonResponse.__class__._TYPE_SUPPORT is None:
                CommonResponse.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PlayVideoGroup_Response(metaclass=Metaclass_PlayVideoGroup_Response):
    """Message class 'PlayVideoGroup_Response'."""

    __slots__ = [
        '_header',
        '_success',
        '_message',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/CommonResponse',
        'success': 'boolean',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonResponse'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonResponse
        self.header = kwargs.get('header', CommonResponse())
        self.success = kwargs.get('success', bool())
        self.message = kwargs.get('message', str())

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
        if self.success != other.success:
            return False
        if self.message != other.message:
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
            from aimdk_msgs.msg import CommonResponse
            assert \
                isinstance(value, CommonResponse), \
                "The 'header' field must be a sub message of type 'CommonResponse'"
        self._header = value

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value


class Metaclass_PlayVideoGroup(type):
    """Metaclass of service 'PlayVideoGroup'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('aimdk_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'aimdk_msgs.srv.PlayVideoGroup')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__play_video_group

            from aimdk_msgs.srv import _play_video_group
            if _play_video_group.Metaclass_PlayVideoGroup_Request._TYPE_SUPPORT is None:
                _play_video_group.Metaclass_PlayVideoGroup_Request.__import_type_support__()
            if _play_video_group.Metaclass_PlayVideoGroup_Response._TYPE_SUPPORT is None:
                _play_video_group.Metaclass_PlayVideoGroup_Response.__import_type_support__()


class PlayVideoGroup(metaclass=Metaclass_PlayVideoGroup):
    from aimdk_msgs.srv._play_video_group import PlayVideoGroup_Request as Request
    from aimdk_msgs.srv._play_video_group import PlayVideoGroup_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

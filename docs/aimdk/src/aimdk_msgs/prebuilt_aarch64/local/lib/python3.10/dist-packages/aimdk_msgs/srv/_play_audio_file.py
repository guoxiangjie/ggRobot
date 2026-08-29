# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/PlayAudioFile.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PlayAudioFile_Request(type):
    """Metaclass of message 'PlayAudioFile_Request'."""

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
                'aimdk_msgs.srv.PlayAudioFile_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__play_audio_file__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__play_audio_file__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__play_audio_file__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__play_audio_file__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__play_audio_file__request

            from aimdk_msgs.msg import AudioFile
            if AudioFile.__class__._TYPE_SUPPORT is None:
                AudioFile.__class__.__import_type_support__()

            from aimdk_msgs.msg import CommonRequest
            if CommonRequest.__class__._TYPE_SUPPORT is None:
                CommonRequest.__class__.__import_type_support__()

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PlayAudioFile_Request(metaclass=Metaclass_PlayAudioFile_Request):
    """Message class 'PlayAudioFile_Request'."""

    __slots__ = [
        '_request',
        '_file',
        '_play_stamps',
    ]

    _fields_and_field_types = {
        'request': 'aimdk_msgs/CommonRequest',
        'file': 'aimdk_msgs/AudioFile',
        'play_stamps': 'builtin_interfaces/Time',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonRequest'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'AudioFile'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonRequest
        self.request = kwargs.get('request', CommonRequest())
        from aimdk_msgs.msg import AudioFile
        self.file = kwargs.get('file', AudioFile())
        from builtin_interfaces.msg import Time
        self.play_stamps = kwargs.get('play_stamps', Time())

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
        if self.request != other.request:
            return False
        if self.file != other.file:
            return False
        if self.play_stamps != other.play_stamps:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def request(self):
        """Message field 'request'."""
        return self._request

    @request.setter
    def request(self, value):
        if __debug__:
            from aimdk_msgs.msg import CommonRequest
            assert \
                isinstance(value, CommonRequest), \
                "The 'request' field must be a sub message of type 'CommonRequest'"
        self._request = value

    @builtins.property
    def file(self):
        """Message field 'file'."""
        return self._file

    @file.setter
    def file(self, value):
        if __debug__:
            from aimdk_msgs.msg import AudioFile
            assert \
                isinstance(value, AudioFile), \
                "The 'file' field must be a sub message of type 'AudioFile'"
        self._file = value

    @builtins.property
    def play_stamps(self):
        """Message field 'play_stamps'."""
        return self._play_stamps

    @play_stamps.setter
    def play_stamps(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'play_stamps' field must be a sub message of type 'Time'"
        self._play_stamps = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_PlayAudioFile_Response(type):
    """Metaclass of message 'PlayAudioFile_Response'."""

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
                'aimdk_msgs.srv.PlayAudioFile_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__play_audio_file__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__play_audio_file__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__play_audio_file__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__play_audio_file__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__play_audio_file__response

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


class PlayAudioFile_Response(metaclass=Metaclass_PlayAudioFile_Response):
    """Message class 'PlayAudioFile_Response'."""

    __slots__ = [
        '_reponse',
    ]

    _fields_and_field_types = {
        'reponse': 'aimdk_msgs/CommonResponse',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonResponse'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonResponse
        self.reponse = kwargs.get('reponse', CommonResponse())

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
        if self.reponse != other.reponse:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def reponse(self):
        """Message field 'reponse'."""
        return self._reponse

    @reponse.setter
    def reponse(self, value):
        if __debug__:
            from aimdk_msgs.msg import CommonResponse
            assert \
                isinstance(value, CommonResponse), \
                "The 'reponse' field must be a sub message of type 'CommonResponse'"
        self._reponse = value


class Metaclass_PlayAudioFile(type):
    """Metaclass of service 'PlayAudioFile'."""

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
                'aimdk_msgs.srv.PlayAudioFile')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__play_audio_file

            from aimdk_msgs.srv import _play_audio_file
            if _play_audio_file.Metaclass_PlayAudioFile_Request._TYPE_SUPPORT is None:
                _play_audio_file.Metaclass_PlayAudioFile_Request.__import_type_support__()
            if _play_audio_file.Metaclass_PlayAudioFile_Response._TYPE_SUPPORT is None:
                _play_audio_file.Metaclass_PlayAudioFile_Response.__import_type_support__()


class PlayAudioFile(metaclass=Metaclass_PlayAudioFile):
    from aimdk_msgs.srv._play_audio_file import PlayAudioFile_Request as Request
    from aimdk_msgs.srv._play_audio_file import PlayAudioFile_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

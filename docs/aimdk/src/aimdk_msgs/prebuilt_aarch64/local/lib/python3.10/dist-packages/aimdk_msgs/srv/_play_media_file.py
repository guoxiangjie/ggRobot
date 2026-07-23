# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/PlayMediaFile.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PlayMediaFile_Request(type):
    """Metaclass of message 'PlayMediaFile_Request'."""

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
                'aimdk_msgs.srv.PlayMediaFile_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__play_media_file__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__play_media_file__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__play_media_file__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__play_media_file__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__play_media_file__request

            from aimdk_msgs.msg import CommonRequest
            if CommonRequest.__class__._TYPE_SUPPORT is None:
                CommonRequest.__class__.__import_type_support__()

            from aimdk_msgs.msg import PlayMediaFileRequest
            if PlayMediaFileRequest.__class__._TYPE_SUPPORT is None:
                PlayMediaFileRequest.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PlayMediaFile_Request(metaclass=Metaclass_PlayMediaFile_Request):
    """Message class 'PlayMediaFile_Request'."""

    __slots__ = [
        '_header',
        '_media_file_req',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/CommonRequest',
        'media_file_req': 'aimdk_msgs/PlayMediaFileRequest',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonRequest'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'PlayMediaFileRequest'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonRequest
        self.header = kwargs.get('header', CommonRequest())
        from aimdk_msgs.msg import PlayMediaFileRequest
        self.media_file_req = kwargs.get('media_file_req', PlayMediaFileRequest())

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
        if self.media_file_req != other.media_file_req:
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
    def media_file_req(self):
        """Message field 'media_file_req'."""
        return self._media_file_req

    @media_file_req.setter
    def media_file_req(self, value):
        if __debug__:
            from aimdk_msgs.msg import PlayMediaFileRequest
            assert \
                isinstance(value, PlayMediaFileRequest), \
                "The 'media_file_req' field must be a sub message of type 'PlayMediaFileRequest'"
        self._media_file_req = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_PlayMediaFile_Response(type):
    """Metaclass of message 'PlayMediaFile_Response'."""

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
                'aimdk_msgs.srv.PlayMediaFile_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__play_media_file__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__play_media_file__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__play_media_file__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__play_media_file__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__play_media_file__response

            from aimdk_msgs.msg import CommonResponse
            if CommonResponse.__class__._TYPE_SUPPORT is None:
                CommonResponse.__class__.__import_type_support__()

            from aimdk_msgs.msg import PlayTtsResponse
            if PlayTtsResponse.__class__._TYPE_SUPPORT is None:
                PlayTtsResponse.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PlayMediaFile_Response(metaclass=Metaclass_PlayMediaFile_Response):
    """Message class 'PlayMediaFile_Response'."""

    __slots__ = [
        '_header',
        '_tts_resp',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/CommonResponse',
        'tts_resp': 'aimdk_msgs/PlayTtsResponse',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonResponse'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'PlayTtsResponse'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonResponse
        self.header = kwargs.get('header', CommonResponse())
        from aimdk_msgs.msg import PlayTtsResponse
        self.tts_resp = kwargs.get('tts_resp', PlayTtsResponse())

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
        if self.tts_resp != other.tts_resp:
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
    def tts_resp(self):
        """Message field 'tts_resp'."""
        return self._tts_resp

    @tts_resp.setter
    def tts_resp(self, value):
        if __debug__:
            from aimdk_msgs.msg import PlayTtsResponse
            assert \
                isinstance(value, PlayTtsResponse), \
                "The 'tts_resp' field must be a sub message of type 'PlayTtsResponse'"
        self._tts_resp = value


class Metaclass_PlayMediaFile(type):
    """Metaclass of service 'PlayMediaFile'."""

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
                'aimdk_msgs.srv.PlayMediaFile')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__play_media_file

            from aimdk_msgs.srv import _play_media_file
            if _play_media_file.Metaclass_PlayMediaFile_Request._TYPE_SUPPORT is None:
                _play_media_file.Metaclass_PlayMediaFile_Request.__import_type_support__()
            if _play_media_file.Metaclass_PlayMediaFile_Response._TYPE_SUPPORT is None:
                _play_media_file.Metaclass_PlayMediaFile_Response.__import_type_support__()


class PlayMediaFile(metaclass=Metaclass_PlayMediaFile):
    from aimdk_msgs.srv._play_media_file import PlayMediaFile_Request as Request
    from aimdk_msgs.srv._play_media_file import PlayMediaFile_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

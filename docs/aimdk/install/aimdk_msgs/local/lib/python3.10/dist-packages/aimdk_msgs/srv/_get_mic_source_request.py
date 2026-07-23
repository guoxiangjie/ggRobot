# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/GetMicSourceRequest.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetMicSourceRequest_Request(type):
    """Metaclass of message 'GetMicSourceRequest_Request'."""

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
                'aimdk_msgs.srv.GetMicSourceRequest_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_mic_source_request__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_mic_source_request__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_mic_source_request__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_mic_source_request__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_mic_source_request__request

            from aimdk_msgs.msg import CommonRequest
            if CommonRequest.__class__._TYPE_SUPPORT is None:
                CommonRequest.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetMicSourceRequest_Request(metaclass=Metaclass_GetMicSourceRequest_Request):
    """Message class 'GetMicSourceRequest_Request'."""

    __slots__ = [
        '_header',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/CommonRequest',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonRequest'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonRequest
        self.header = kwargs.get('header', CommonRequest())

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


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_GetMicSourceRequest_Response(type):
    """Metaclass of message 'GetMicSourceRequest_Response'."""

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
                'aimdk_msgs.srv.GetMicSourceRequest_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_mic_source_request__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_mic_source_request__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_mic_source_request__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_mic_source_request__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_mic_source_request__response

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


class GetMicSourceRequest_Response(metaclass=Metaclass_GetMicSourceRequest_Response):
    """Message class 'GetMicSourceRequest_Response'."""

    __slots__ = [
        '_header',
        '_mic_source',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/CommonResponse',
        'mic_source': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonResponse'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonResponse
        self.header = kwargs.get('header', CommonResponse())
        self.mic_source = kwargs.get('mic_source', int())

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
        if self.mic_source != other.mic_source:
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
    def mic_source(self):
        """Message field 'mic_source'."""
        return self._mic_source

    @mic_source.setter
    def mic_source(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mic_source' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'mic_source' field must be an unsigned integer in [0, 4294967295]"
        self._mic_source = value


class Metaclass_GetMicSourceRequest(type):
    """Metaclass of service 'GetMicSourceRequest'."""

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
                'aimdk_msgs.srv.GetMicSourceRequest')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_mic_source_request

            from aimdk_msgs.srv import _get_mic_source_request
            if _get_mic_source_request.Metaclass_GetMicSourceRequest_Request._TYPE_SUPPORT is None:
                _get_mic_source_request.Metaclass_GetMicSourceRequest_Request.__import_type_support__()
            if _get_mic_source_request.Metaclass_GetMicSourceRequest_Response._TYPE_SUPPORT is None:
                _get_mic_source_request.Metaclass_GetMicSourceRequest_Response.__import_type_support__()


class GetMicSourceRequest(metaclass=Metaclass_GetMicSourceRequest):
    from aimdk_msgs.srv._get_mic_source_request import GetMicSourceRequest_Request as Request
    from aimdk_msgs.srv._get_mic_source_request import GetMicSourceRequest_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

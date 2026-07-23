# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/GetMcAction.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetMcAction_Request(type):
    """Metaclass of message 'GetMcAction_Request'."""

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
                'aimdk_msgs.srv.GetMcAction_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_mc_action__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_mc_action__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_mc_action__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_mc_action__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_mc_action__request

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


class GetMcAction_Request(metaclass=Metaclass_GetMcAction_Request):
    """Message class 'GetMcAction_Request'."""

    __slots__ = [
        '_request',
    ]

    _fields_and_field_types = {
        'request': 'aimdk_msgs/CommonRequest',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonRequest'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonRequest
        self.request = kwargs.get('request', CommonRequest())

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


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_GetMcAction_Response(type):
    """Metaclass of message 'GetMcAction_Response'."""

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
                'aimdk_msgs.srv.GetMcAction_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_mc_action__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_mc_action__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_mc_action__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_mc_action__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_mc_action__response

            from aimdk_msgs.msg import McActionInfo
            if McActionInfo.__class__._TYPE_SUPPORT is None:
                McActionInfo.__class__.__import_type_support__()

            from aimdk_msgs.msg import ResponseHeader
            if ResponseHeader.__class__._TYPE_SUPPORT is None:
                ResponseHeader.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetMcAction_Response(metaclass=Metaclass_GetMcAction_Response):
    """Message class 'GetMcAction_Response'."""

    __slots__ = [
        '_header',
        '_info',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/ResponseHeader',
        'info': 'aimdk_msgs/McActionInfo',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'ResponseHeader'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'McActionInfo'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import ResponseHeader
        self.header = kwargs.get('header', ResponseHeader())
        from aimdk_msgs.msg import McActionInfo
        self.info = kwargs.get('info', McActionInfo())

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
        if self.info != other.info:
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
            from aimdk_msgs.msg import ResponseHeader
            assert \
                isinstance(value, ResponseHeader), \
                "The 'header' field must be a sub message of type 'ResponseHeader'"
        self._header = value

    @builtins.property
    def info(self):
        """Message field 'info'."""
        return self._info

    @info.setter
    def info(self, value):
        if __debug__:
            from aimdk_msgs.msg import McActionInfo
            assert \
                isinstance(value, McActionInfo), \
                "The 'info' field must be a sub message of type 'McActionInfo'"
        self._info = value


class Metaclass_GetMcAction(type):
    """Metaclass of service 'GetMcAction'."""

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
                'aimdk_msgs.srv.GetMcAction')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_mc_action

            from aimdk_msgs.srv import _get_mc_action
            if _get_mc_action.Metaclass_GetMcAction_Request._TYPE_SUPPORT is None:
                _get_mc_action.Metaclass_GetMcAction_Request.__import_type_support__()
            if _get_mc_action.Metaclass_GetMcAction_Response._TYPE_SUPPORT is None:
                _get_mc_action.Metaclass_GetMcAction_Response.__import_type_support__()


class GetMcAction(metaclass=Metaclass_GetMcAction):
    from aimdk_msgs.srv._get_mc_action import GetMcAction_Request as Request
    from aimdk_msgs.srv._get_mc_action import GetMcAction_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

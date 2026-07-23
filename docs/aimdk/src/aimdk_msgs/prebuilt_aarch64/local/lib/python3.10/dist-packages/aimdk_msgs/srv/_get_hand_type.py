# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/GetHandType.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetHandType_Request(type):
    """Metaclass of message 'GetHandType_Request'."""

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
                'aimdk_msgs.srv.GetHandType_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_hand_type__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_hand_type__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_hand_type__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_hand_type__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_hand_type__request

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


class GetHandType_Request(metaclass=Metaclass_GetHandType_Request):
    """Message class 'GetHandType_Request'."""

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


class Metaclass_GetHandType_Response(type):
    """Metaclass of message 'GetHandType_Response'."""

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
                'aimdk_msgs.srv.GetHandType_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_hand_type__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_hand_type__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_hand_type__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_hand_type__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_hand_type__response

            from aimdk_msgs.msg import CommonResponse
            if CommonResponse.__class__._TYPE_SUPPORT is None:
                CommonResponse.__class__.__import_type_support__()

            from aimdk_msgs.msg import HandType
            if HandType.__class__._TYPE_SUPPORT is None:
                HandType.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetHandType_Response(metaclass=Metaclass_GetHandType_Response):
    """Message class 'GetHandType_Response'."""

    __slots__ = [
        '_reponse',
        '_left_hands_type',
        '_right_hands_type',
    ]

    _fields_and_field_types = {
        'reponse': 'aimdk_msgs/CommonResponse',
        'left_hands_type': 'aimdk_msgs/HandType',
        'right_hands_type': 'aimdk_msgs/HandType',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonResponse'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'HandType'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'HandType'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonResponse
        self.reponse = kwargs.get('reponse', CommonResponse())
        from aimdk_msgs.msg import HandType
        self.left_hands_type = kwargs.get('left_hands_type', HandType())
        from aimdk_msgs.msg import HandType
        self.right_hands_type = kwargs.get('right_hands_type', HandType())

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
        if self.left_hands_type != other.left_hands_type:
            return False
        if self.right_hands_type != other.right_hands_type:
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

    @builtins.property
    def left_hands_type(self):
        """Message field 'left_hands_type'."""
        return self._left_hands_type

    @left_hands_type.setter
    def left_hands_type(self, value):
        if __debug__:
            from aimdk_msgs.msg import HandType
            assert \
                isinstance(value, HandType), \
                "The 'left_hands_type' field must be a sub message of type 'HandType'"
        self._left_hands_type = value

    @builtins.property
    def right_hands_type(self):
        """Message field 'right_hands_type'."""
        return self._right_hands_type

    @right_hands_type.setter
    def right_hands_type(self, value):
        if __debug__:
            from aimdk_msgs.msg import HandType
            assert \
                isinstance(value, HandType), \
                "The 'right_hands_type' field must be a sub message of type 'HandType'"
        self._right_hands_type = value


class Metaclass_GetHandType(type):
    """Metaclass of service 'GetHandType'."""

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
                'aimdk_msgs.srv.GetHandType')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_hand_type

            from aimdk_msgs.srv import _get_hand_type
            if _get_hand_type.Metaclass_GetHandType_Request._TYPE_SUPPORT is None:
                _get_hand_type.Metaclass_GetHandType_Request.__import_type_support__()
            if _get_hand_type.Metaclass_GetHandType_Response._TYPE_SUPPORT is None:
                _get_hand_type.Metaclass_GetHandType_Response.__import_type_support__()


class GetHandType(metaclass=Metaclass_GetHandType):
    from aimdk_msgs.srv._get_hand_type import GetHandType_Request as Request
    from aimdk_msgs.srv._get_hand_type import GetHandType_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

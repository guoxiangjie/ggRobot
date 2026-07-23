# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/SetMcInputSource.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SetMcInputSource_Request(type):
    """Metaclass of message 'SetMcInputSource_Request'."""

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
                'aimdk_msgs.srv.SetMcInputSource_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_mc_input_source__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_mc_input_source__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_mc_input_source__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_mc_input_source__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_mc_input_source__request

            from aimdk_msgs.msg import CommonRequest
            if CommonRequest.__class__._TYPE_SUPPORT is None:
                CommonRequest.__class__.__import_type_support__()

            from aimdk_msgs.msg import McInputAction
            if McInputAction.__class__._TYPE_SUPPORT is None:
                McInputAction.__class__.__import_type_support__()

            from aimdk_msgs.msg import McInputSource
            if McInputSource.__class__._TYPE_SUPPORT is None:
                McInputSource.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetMcInputSource_Request(metaclass=Metaclass_SetMcInputSource_Request):
    """Message class 'SetMcInputSource_Request'."""

    __slots__ = [
        '_request',
        '_action',
        '_input_source',
    ]

    _fields_and_field_types = {
        'request': 'aimdk_msgs/CommonRequest',
        'action': 'aimdk_msgs/McInputAction',
        'input_source': 'aimdk_msgs/McInputSource',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonRequest'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'McInputAction'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'McInputSource'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonRequest
        self.request = kwargs.get('request', CommonRequest())
        from aimdk_msgs.msg import McInputAction
        self.action = kwargs.get('action', McInputAction())
        from aimdk_msgs.msg import McInputSource
        self.input_source = kwargs.get('input_source', McInputSource())

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
        if self.action != other.action:
            return False
        if self.input_source != other.input_source:
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
    def action(self):
        """Message field 'action'."""
        return self._action

    @action.setter
    def action(self, value):
        if __debug__:
            from aimdk_msgs.msg import McInputAction
            assert \
                isinstance(value, McInputAction), \
                "The 'action' field must be a sub message of type 'McInputAction'"
        self._action = value

    @builtins.property
    def input_source(self):
        """Message field 'input_source'."""
        return self._input_source

    @input_source.setter
    def input_source(self, value):
        if __debug__:
            from aimdk_msgs.msg import McInputSource
            assert \
                isinstance(value, McInputSource), \
                "The 'input_source' field must be a sub message of type 'McInputSource'"
        self._input_source = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SetMcInputSource_Response(type):
    """Metaclass of message 'SetMcInputSource_Response'."""

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
                'aimdk_msgs.srv.SetMcInputSource_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_mc_input_source__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_mc_input_source__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_mc_input_source__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_mc_input_source__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_mc_input_source__response

            from aimdk_msgs.msg import CommonTaskResponse
            if CommonTaskResponse.__class__._TYPE_SUPPORT is None:
                CommonTaskResponse.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetMcInputSource_Response(metaclass=Metaclass_SetMcInputSource_Response):
    """Message class 'SetMcInputSource_Response'."""

    __slots__ = [
        '_response',
    ]

    _fields_and_field_types = {
        'response': 'aimdk_msgs/CommonTaskResponse',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonTaskResponse'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonTaskResponse
        self.response = kwargs.get('response', CommonTaskResponse())

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
        if self.response != other.response:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def response(self):
        """Message field 'response'."""
        return self._response

    @response.setter
    def response(self, value):
        if __debug__:
            from aimdk_msgs.msg import CommonTaskResponse
            assert \
                isinstance(value, CommonTaskResponse), \
                "The 'response' field must be a sub message of type 'CommonTaskResponse'"
        self._response = value


class Metaclass_SetMcInputSource(type):
    """Metaclass of service 'SetMcInputSource'."""

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
                'aimdk_msgs.srv.SetMcInputSource')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__set_mc_input_source

            from aimdk_msgs.srv import _set_mc_input_source
            if _set_mc_input_source.Metaclass_SetMcInputSource_Request._TYPE_SUPPORT is None:
                _set_mc_input_source.Metaclass_SetMcInputSource_Request.__import_type_support__()
            if _set_mc_input_source.Metaclass_SetMcInputSource_Response._TYPE_SUPPORT is None:
                _set_mc_input_source.Metaclass_SetMcInputSource_Response.__import_type_support__()


class SetMcInputSource(metaclass=Metaclass_SetMcInputSource):
    from aimdk_msgs.srv._set_mc_input_source import SetMcInputSource_Request as Request
    from aimdk_msgs.srv._set_mc_input_source import SetMcInputSource_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

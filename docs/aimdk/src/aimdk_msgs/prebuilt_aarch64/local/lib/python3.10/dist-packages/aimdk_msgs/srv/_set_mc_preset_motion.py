# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/SetMcPresetMotion.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SetMcPresetMotion_Request(type):
    """Metaclass of message 'SetMcPresetMotion_Request'."""

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
                'aimdk_msgs.srv.SetMcPresetMotion_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_mc_preset_motion__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_mc_preset_motion__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_mc_preset_motion__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_mc_preset_motion__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_mc_preset_motion__request

            from aimdk_msgs.msg import McControlArea
            if McControlArea.__class__._TYPE_SUPPORT is None:
                McControlArea.__class__.__import_type_support__()

            from aimdk_msgs.msg import McPresetMotion
            if McPresetMotion.__class__._TYPE_SUPPORT is None:
                McPresetMotion.__class__.__import_type_support__()

            from aimdk_msgs.msg import RequestHeader
            if RequestHeader.__class__._TYPE_SUPPORT is None:
                RequestHeader.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetMcPresetMotion_Request(metaclass=Metaclass_SetMcPresetMotion_Request):
    """Message class 'SetMcPresetMotion_Request'."""

    __slots__ = [
        '_header',
        '_area',
        '_motion',
        '_interrupt',
        '_ani_path',
        '_play_timestamp',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/RequestHeader',
        'area': 'aimdk_msgs/McControlArea',
        'motion': 'aimdk_msgs/McPresetMotion',
        'interrupt': 'boolean',
        'ani_path': 'string',
        'play_timestamp': 'uint64',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'RequestHeader'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'McControlArea'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'McPresetMotion'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import RequestHeader
        self.header = kwargs.get('header', RequestHeader())
        from aimdk_msgs.msg import McControlArea
        self.area = kwargs.get('area', McControlArea())
        from aimdk_msgs.msg import McPresetMotion
        self.motion = kwargs.get('motion', McPresetMotion())
        self.interrupt = kwargs.get('interrupt', bool())
        self.ani_path = kwargs.get('ani_path', str())
        self.play_timestamp = kwargs.get('play_timestamp', int())

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
        if self.area != other.area:
            return False
        if self.motion != other.motion:
            return False
        if self.interrupt != other.interrupt:
            return False
        if self.ani_path != other.ani_path:
            return False
        if self.play_timestamp != other.play_timestamp:
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
            from aimdk_msgs.msg import RequestHeader
            assert \
                isinstance(value, RequestHeader), \
                "The 'header' field must be a sub message of type 'RequestHeader'"
        self._header = value

    @builtins.property
    def area(self):
        """Message field 'area'."""
        return self._area

    @area.setter
    def area(self, value):
        if __debug__:
            from aimdk_msgs.msg import McControlArea
            assert \
                isinstance(value, McControlArea), \
                "The 'area' field must be a sub message of type 'McControlArea'"
        self._area = value

    @builtins.property
    def motion(self):
        """Message field 'motion'."""
        return self._motion

    @motion.setter
    def motion(self, value):
        if __debug__:
            from aimdk_msgs.msg import McPresetMotion
            assert \
                isinstance(value, McPresetMotion), \
                "The 'motion' field must be a sub message of type 'McPresetMotion'"
        self._motion = value

    @builtins.property
    def interrupt(self):
        """Message field 'interrupt'."""
        return self._interrupt

    @interrupt.setter
    def interrupt(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'interrupt' field must be of type 'bool'"
        self._interrupt = value

    @builtins.property
    def ani_path(self):
        """Message field 'ani_path'."""
        return self._ani_path

    @ani_path.setter
    def ani_path(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'ani_path' field must be of type 'str'"
        self._ani_path = value

    @builtins.property
    def play_timestamp(self):
        """Message field 'play_timestamp'."""
        return self._play_timestamp

    @play_timestamp.setter
    def play_timestamp(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'play_timestamp' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'play_timestamp' field must be an unsigned integer in [0, 18446744073709551615]"
        self._play_timestamp = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SetMcPresetMotion_Response(type):
    """Metaclass of message 'SetMcPresetMotion_Response'."""

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
                'aimdk_msgs.srv.SetMcPresetMotion_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_mc_preset_motion__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_mc_preset_motion__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_mc_preset_motion__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_mc_preset_motion__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_mc_preset_motion__response

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


class SetMcPresetMotion_Response(metaclass=Metaclass_SetMcPresetMotion_Response):
    """Message class 'SetMcPresetMotion_Response'."""

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


class Metaclass_SetMcPresetMotion(type):
    """Metaclass of service 'SetMcPresetMotion'."""

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
                'aimdk_msgs.srv.SetMcPresetMotion')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__set_mc_preset_motion

            from aimdk_msgs.srv import _set_mc_preset_motion
            if _set_mc_preset_motion.Metaclass_SetMcPresetMotion_Request._TYPE_SUPPORT is None:
                _set_mc_preset_motion.Metaclass_SetMcPresetMotion_Request.__import_type_support__()
            if _set_mc_preset_motion.Metaclass_SetMcPresetMotion_Response._TYPE_SUPPORT is None:
                _set_mc_preset_motion.Metaclass_SetMcPresetMotion_Response.__import_type_support__()


class SetMcPresetMotion(metaclass=Metaclass_SetMcPresetMotion):
    from aimdk_msgs.srv._set_mc_preset_motion import SetMcPresetMotion_Request as Request
    from aimdk_msgs.srv._set_mc_preset_motion import SetMcPresetMotion_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

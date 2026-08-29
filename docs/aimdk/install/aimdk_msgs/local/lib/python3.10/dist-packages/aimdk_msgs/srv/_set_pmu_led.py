# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/SetPmuLed.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SetPmuLed_Request(type):
    """Metaclass of message 'SetPmuLed_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'LED_STRIP_MODE_CONSTANT': 0,
        'LED_STRIP_MODE_BREATH': 1,
        'LED_STRIP_MODE_FLASH': 2,
        'LED_STRIP_MODE_FLOW': 3,
        'LED_STRIP_MODE_MAX': 4,
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
                'aimdk_msgs.srv.SetPmuLed_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_pmu_led__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_pmu_led__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_pmu_led__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_pmu_led__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_pmu_led__request

            from aimdk_msgs.msg import CommonRequest
            if CommonRequest.__class__._TYPE_SUPPORT is None:
                CommonRequest.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'LED_STRIP_MODE_CONSTANT': cls.__constants['LED_STRIP_MODE_CONSTANT'],
            'LED_STRIP_MODE_BREATH': cls.__constants['LED_STRIP_MODE_BREATH'],
            'LED_STRIP_MODE_FLASH': cls.__constants['LED_STRIP_MODE_FLASH'],
            'LED_STRIP_MODE_FLOW': cls.__constants['LED_STRIP_MODE_FLOW'],
            'LED_STRIP_MODE_MAX': cls.__constants['LED_STRIP_MODE_MAX'],
        }

    @property
    def LED_STRIP_MODE_CONSTANT(self):
        """Message constant 'LED_STRIP_MODE_CONSTANT'."""
        return Metaclass_SetPmuLed_Request.__constants['LED_STRIP_MODE_CONSTANT']

    @property
    def LED_STRIP_MODE_BREATH(self):
        """Message constant 'LED_STRIP_MODE_BREATH'."""
        return Metaclass_SetPmuLed_Request.__constants['LED_STRIP_MODE_BREATH']

    @property
    def LED_STRIP_MODE_FLASH(self):
        """Message constant 'LED_STRIP_MODE_FLASH'."""
        return Metaclass_SetPmuLed_Request.__constants['LED_STRIP_MODE_FLASH']

    @property
    def LED_STRIP_MODE_FLOW(self):
        """Message constant 'LED_STRIP_MODE_FLOW'."""
        return Metaclass_SetPmuLed_Request.__constants['LED_STRIP_MODE_FLOW']

    @property
    def LED_STRIP_MODE_MAX(self):
        """Message constant 'LED_STRIP_MODE_MAX'."""
        return Metaclass_SetPmuLed_Request.__constants['LED_STRIP_MODE_MAX']


class SetPmuLed_Request(metaclass=Metaclass_SetPmuLed_Request):
    """
    Message class 'SetPmuLed_Request'.

    Constants:
      LED_STRIP_MODE_CONSTANT
      LED_STRIP_MODE_BREATH
      LED_STRIP_MODE_FLASH
      LED_STRIP_MODE_FLOW
      LED_STRIP_MODE_MAX
    """

    __slots__ = [
        '_request',
        '_trace_id',
        '_led_strip_mode',
        '_r',
        '_g',
        '_b',
        '_priority',
        '_reset_priority',
    ]

    _fields_and_field_types = {
        'request': 'aimdk_msgs/CommonRequest',
        'trace_id': 'string',
        'led_strip_mode': 'uint8',
        'r': 'uint8',
        'g': 'uint8',
        'b': 'uint8',
        'priority': 'int32',
        'reset_priority': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonRequest'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonRequest
        self.request = kwargs.get('request', CommonRequest())
        self.trace_id = kwargs.get('trace_id', str())
        self.led_strip_mode = kwargs.get('led_strip_mode', int())
        self.r = kwargs.get('r', int())
        self.g = kwargs.get('g', int())
        self.b = kwargs.get('b', int())
        self.priority = kwargs.get('priority', int())
        self.reset_priority = kwargs.get('reset_priority', bool())

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
        if self.trace_id != other.trace_id:
            return False
        if self.led_strip_mode != other.led_strip_mode:
            return False
        if self.r != other.r:
            return False
        if self.g != other.g:
            return False
        if self.b != other.b:
            return False
        if self.priority != other.priority:
            return False
        if self.reset_priority != other.reset_priority:
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
    def led_strip_mode(self):
        """Message field 'led_strip_mode'."""
        return self._led_strip_mode

    @led_strip_mode.setter
    def led_strip_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'led_strip_mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'led_strip_mode' field must be an unsigned integer in [0, 255]"
        self._led_strip_mode = value

    @builtins.property
    def r(self):
        """Message field 'r'."""
        return self._r

    @r.setter
    def r(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'r' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'r' field must be an unsigned integer in [0, 255]"
        self._r = value

    @builtins.property
    def g(self):
        """Message field 'g'."""
        return self._g

    @g.setter
    def g(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'g' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'g' field must be an unsigned integer in [0, 255]"
        self._g = value

    @builtins.property
    def b(self):
        """Message field 'b'."""
        return self._b

    @b.setter
    def b(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'b' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'b' field must be an unsigned integer in [0, 255]"
        self._b = value

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

    @builtins.property
    def reset_priority(self):
        """Message field 'reset_priority'."""
        return self._reset_priority

    @reset_priority.setter
    def reset_priority(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'reset_priority' field must be of type 'bool'"
        self._reset_priority = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SetPmuLed_Response(type):
    """Metaclass of message 'SetPmuLed_Response'."""

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
                'aimdk_msgs.srv.SetPmuLed_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_pmu_led__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_pmu_led__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_pmu_led__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_pmu_led__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_pmu_led__response

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


class SetPmuLed_Response(metaclass=Metaclass_SetPmuLed_Response):
    """Message class 'SetPmuLed_Response'."""

    __slots__ = [
        '_header',
        '_status_code',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/ResponseHeader',
        'status_code': 'uint16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'ResponseHeader'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import ResponseHeader
        self.header = kwargs.get('header', ResponseHeader())
        self.status_code = kwargs.get('status_code', int())

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
        if self.status_code != other.status_code:
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
    def status_code(self):
        """Message field 'status_code'."""
        return self._status_code

    @status_code.setter
    def status_code(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'status_code' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'status_code' field must be an unsigned integer in [0, 65535]"
        self._status_code = value


class Metaclass_SetPmuLed(type):
    """Metaclass of service 'SetPmuLed'."""

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
                'aimdk_msgs.srv.SetPmuLed')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__set_pmu_led

            from aimdk_msgs.srv import _set_pmu_led
            if _set_pmu_led.Metaclass_SetPmuLed_Request._TYPE_SUPPORT is None:
                _set_pmu_led.Metaclass_SetPmuLed_Request.__import_type_support__()
            if _set_pmu_led.Metaclass_SetPmuLed_Response._TYPE_SUPPORT is None:
                _set_pmu_led.Metaclass_SetPmuLed_Response.__import_type_support__()


class SetPmuLed(metaclass=Metaclass_SetPmuLed):
    from aimdk_msgs.srv._set_pmu_led import SetPmuLed_Request as Request
    from aimdk_msgs.srv._set_pmu_led import SetPmuLed_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

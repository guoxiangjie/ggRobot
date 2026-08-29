# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/PlayEmoji.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_PlayEmoji_Request(type):
    """Metaclass of message 'PlayEmoji_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'EMOTION_UNKNOWN': 0,
        'EMOTION_IDLE_BLINK': 1,
        'EMOTION_IDLE_CALM_1': 10,
        'EMOTION_IDLE_CALM_2': 11,
        'EMOTION_IDLE_GAME': 20,
        'EMOTION_IDLE_CUTE_1': 30,
        'EMOTION_IDLE_CUTE_2': 31,
        'EMOTION_IDLE_CUTE_3': 32,
        'EMOTION_IDLE_CUTE_4': 33,
        'EMOTION_EYE_CLOSE': 40,
        'EMOTION_EYE_OPEN': 50,
        'EMOTION_EYE_BORING_1': 60,
        'EMOTION_EYE_ABNORMAL': 70,
        'EMOTION_EYE_SLEEPY': 80,
        'EMOTION_EYE_HAPPY': 90,
        'EMOTION_EYE_EXTREMEHAPPY_1': 100,
        'EMOTION_EYE_EXTREMEHAPPY_2': 101,
        'EMOTION_EYE_SAD': 110,
        'EMOTION_EYE_SYMPATHY': 120,
        'EMOTION_EYE_CONFUSE': 130,
        'EMOTION_EYE_SHOCK': 140,
        'EMOTION_EYE_ACTCUTE': 150,
        'EMOTION_EYE_SERIOUS': 160,
        'EMOTION_EYE_THINKING': 170,
        'EMOTION_EYE_ANGRY': 180,
        'EMOTION_EYE_EXTREMEANGRY': 190,
        'EMOTION_EYE_ADORE': 200,
        'EMOTION_EYE_EXTREMEADORE': 210,
        'EMOTION_EYE_CHARGE': 220,
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
                'aimdk_msgs.srv.PlayEmoji_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__play_emoji__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__play_emoji__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__play_emoji__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__play_emoji__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__play_emoji__request

            from aimdk_msgs.msg import CommonRequest
            if CommonRequest.__class__._TYPE_SUPPORT is None:
                CommonRequest.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'EMOTION_UNKNOWN': cls.__constants['EMOTION_UNKNOWN'],
            'EMOTION_IDLE_BLINK': cls.__constants['EMOTION_IDLE_BLINK'],
            'EMOTION_IDLE_CALM_1': cls.__constants['EMOTION_IDLE_CALM_1'],
            'EMOTION_IDLE_CALM_2': cls.__constants['EMOTION_IDLE_CALM_2'],
            'EMOTION_IDLE_GAME': cls.__constants['EMOTION_IDLE_GAME'],
            'EMOTION_IDLE_CUTE_1': cls.__constants['EMOTION_IDLE_CUTE_1'],
            'EMOTION_IDLE_CUTE_2': cls.__constants['EMOTION_IDLE_CUTE_2'],
            'EMOTION_IDLE_CUTE_3': cls.__constants['EMOTION_IDLE_CUTE_3'],
            'EMOTION_IDLE_CUTE_4': cls.__constants['EMOTION_IDLE_CUTE_4'],
            'EMOTION_EYE_CLOSE': cls.__constants['EMOTION_EYE_CLOSE'],
            'EMOTION_EYE_OPEN': cls.__constants['EMOTION_EYE_OPEN'],
            'EMOTION_EYE_BORING_1': cls.__constants['EMOTION_EYE_BORING_1'],
            'EMOTION_EYE_ABNORMAL': cls.__constants['EMOTION_EYE_ABNORMAL'],
            'EMOTION_EYE_SLEEPY': cls.__constants['EMOTION_EYE_SLEEPY'],
            'EMOTION_EYE_HAPPY': cls.__constants['EMOTION_EYE_HAPPY'],
            'EMOTION_EYE_EXTREMEHAPPY_1': cls.__constants['EMOTION_EYE_EXTREMEHAPPY_1'],
            'EMOTION_EYE_EXTREMEHAPPY_2': cls.__constants['EMOTION_EYE_EXTREMEHAPPY_2'],
            'EMOTION_EYE_SAD': cls.__constants['EMOTION_EYE_SAD'],
            'EMOTION_EYE_SYMPATHY': cls.__constants['EMOTION_EYE_SYMPATHY'],
            'EMOTION_EYE_CONFUSE': cls.__constants['EMOTION_EYE_CONFUSE'],
            'EMOTION_EYE_SHOCK': cls.__constants['EMOTION_EYE_SHOCK'],
            'EMOTION_EYE_ACTCUTE': cls.__constants['EMOTION_EYE_ACTCUTE'],
            'EMOTION_EYE_SERIOUS': cls.__constants['EMOTION_EYE_SERIOUS'],
            'EMOTION_EYE_THINKING': cls.__constants['EMOTION_EYE_THINKING'],
            'EMOTION_EYE_ANGRY': cls.__constants['EMOTION_EYE_ANGRY'],
            'EMOTION_EYE_EXTREMEANGRY': cls.__constants['EMOTION_EYE_EXTREMEANGRY'],
            'EMOTION_EYE_ADORE': cls.__constants['EMOTION_EYE_ADORE'],
            'EMOTION_EYE_EXTREMEADORE': cls.__constants['EMOTION_EYE_EXTREMEADORE'],
            'EMOTION_EYE_CHARGE': cls.__constants['EMOTION_EYE_CHARGE'],
            'EMOTION_MODE_ONCE': cls.__constants['EMOTION_MODE_ONCE'],
            'EMOTION_MODE_LOOP': cls.__constants['EMOTION_MODE_LOOP'],
        }

    @property
    def EMOTION_UNKNOWN(self):
        """Message constant 'EMOTION_UNKNOWN'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_UNKNOWN']

    @property
    def EMOTION_IDLE_BLINK(self):
        """Message constant 'EMOTION_IDLE_BLINK'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_IDLE_BLINK']

    @property
    def EMOTION_IDLE_CALM_1(self):
        """Message constant 'EMOTION_IDLE_CALM_1'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_IDLE_CALM_1']

    @property
    def EMOTION_IDLE_CALM_2(self):
        """Message constant 'EMOTION_IDLE_CALM_2'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_IDLE_CALM_2']

    @property
    def EMOTION_IDLE_GAME(self):
        """Message constant 'EMOTION_IDLE_GAME'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_IDLE_GAME']

    @property
    def EMOTION_IDLE_CUTE_1(self):
        """Message constant 'EMOTION_IDLE_CUTE_1'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_IDLE_CUTE_1']

    @property
    def EMOTION_IDLE_CUTE_2(self):
        """Message constant 'EMOTION_IDLE_CUTE_2'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_IDLE_CUTE_2']

    @property
    def EMOTION_IDLE_CUTE_3(self):
        """Message constant 'EMOTION_IDLE_CUTE_3'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_IDLE_CUTE_3']

    @property
    def EMOTION_IDLE_CUTE_4(self):
        """Message constant 'EMOTION_IDLE_CUTE_4'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_IDLE_CUTE_4']

    @property
    def EMOTION_EYE_CLOSE(self):
        """Message constant 'EMOTION_EYE_CLOSE'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_CLOSE']

    @property
    def EMOTION_EYE_OPEN(self):
        """Message constant 'EMOTION_EYE_OPEN'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_OPEN']

    @property
    def EMOTION_EYE_BORING_1(self):
        """Message constant 'EMOTION_EYE_BORING_1'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_BORING_1']

    @property
    def EMOTION_EYE_ABNORMAL(self):
        """Message constant 'EMOTION_EYE_ABNORMAL'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_ABNORMAL']

    @property
    def EMOTION_EYE_SLEEPY(self):
        """Message constant 'EMOTION_EYE_SLEEPY'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_SLEEPY']

    @property
    def EMOTION_EYE_HAPPY(self):
        """Message constant 'EMOTION_EYE_HAPPY'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_HAPPY']

    @property
    def EMOTION_EYE_EXTREMEHAPPY_1(self):
        """Message constant 'EMOTION_EYE_EXTREMEHAPPY_1'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_EXTREMEHAPPY_1']

    @property
    def EMOTION_EYE_EXTREMEHAPPY_2(self):
        """Message constant 'EMOTION_EYE_EXTREMEHAPPY_2'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_EXTREMEHAPPY_2']

    @property
    def EMOTION_EYE_SAD(self):
        """Message constant 'EMOTION_EYE_SAD'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_SAD']

    @property
    def EMOTION_EYE_SYMPATHY(self):
        """Message constant 'EMOTION_EYE_SYMPATHY'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_SYMPATHY']

    @property
    def EMOTION_EYE_CONFUSE(self):
        """Message constant 'EMOTION_EYE_CONFUSE'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_CONFUSE']

    @property
    def EMOTION_EYE_SHOCK(self):
        """Message constant 'EMOTION_EYE_SHOCK'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_SHOCK']

    @property
    def EMOTION_EYE_ACTCUTE(self):
        """Message constant 'EMOTION_EYE_ACTCUTE'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_ACTCUTE']

    @property
    def EMOTION_EYE_SERIOUS(self):
        """Message constant 'EMOTION_EYE_SERIOUS'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_SERIOUS']

    @property
    def EMOTION_EYE_THINKING(self):
        """Message constant 'EMOTION_EYE_THINKING'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_THINKING']

    @property
    def EMOTION_EYE_ANGRY(self):
        """Message constant 'EMOTION_EYE_ANGRY'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_ANGRY']

    @property
    def EMOTION_EYE_EXTREMEANGRY(self):
        """Message constant 'EMOTION_EYE_EXTREMEANGRY'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_EXTREMEANGRY']

    @property
    def EMOTION_EYE_ADORE(self):
        """Message constant 'EMOTION_EYE_ADORE'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_ADORE']

    @property
    def EMOTION_EYE_EXTREMEADORE(self):
        """Message constant 'EMOTION_EYE_EXTREMEADORE'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_EXTREMEADORE']

    @property
    def EMOTION_EYE_CHARGE(self):
        """Message constant 'EMOTION_EYE_CHARGE'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_EYE_CHARGE']

    @property
    def EMOTION_MODE_ONCE(self):
        """Message constant 'EMOTION_MODE_ONCE'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_MODE_ONCE']

    @property
    def EMOTION_MODE_LOOP(self):
        """Message constant 'EMOTION_MODE_LOOP'."""
        return Metaclass_PlayEmoji_Request.__constants['EMOTION_MODE_LOOP']


class PlayEmoji_Request(metaclass=Metaclass_PlayEmoji_Request):
    """
    Message class 'PlayEmoji_Request'.

    Constants:
      EMOTION_UNKNOWN
      EMOTION_IDLE_BLINK
      EMOTION_IDLE_CALM_1
      EMOTION_IDLE_CALM_2
      EMOTION_IDLE_GAME
      EMOTION_IDLE_CUTE_1
      EMOTION_IDLE_CUTE_2
      EMOTION_IDLE_CUTE_3
      EMOTION_IDLE_CUTE_4
      EMOTION_EYE_CLOSE
      EMOTION_EYE_OPEN
      EMOTION_EYE_BORING_1
      EMOTION_EYE_ABNORMAL
      EMOTION_EYE_SLEEPY
      EMOTION_EYE_HAPPY
      EMOTION_EYE_EXTREMEHAPPY_1
      EMOTION_EYE_EXTREMEHAPPY_2
      EMOTION_EYE_SAD
      EMOTION_EYE_SYMPATHY
      EMOTION_EYE_CONFUSE
      EMOTION_EYE_SHOCK
      EMOTION_EYE_ACTCUTE
      EMOTION_EYE_SERIOUS
      EMOTION_EYE_THINKING
      EMOTION_EYE_ANGRY
      EMOTION_EYE_EXTREMEANGRY
      EMOTION_EYE_ADORE
      EMOTION_EYE_EXTREMEADORE
      EMOTION_EYE_CHARGE
      EMOTION_MODE_ONCE
      EMOTION_MODE_LOOP
    """

    __slots__ = [
        '_header',
        '_emotion_id',
        '_mode',
        '_priority',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/CommonRequest',
        'emotion_id': 'uint8',
        'mode': 'uint8',
        'priority': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonRequest'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonRequest
        self.header = kwargs.get('header', CommonRequest())
        self.emotion_id = kwargs.get('emotion_id', int())
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
        if self.emotion_id != other.emotion_id:
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
    def emotion_id(self):
        """Message field 'emotion_id'."""
        return self._emotion_id

    @emotion_id.setter
    def emotion_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'emotion_id' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'emotion_id' field must be an unsigned integer in [0, 255]"
        self._emotion_id = value

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


class Metaclass_PlayEmoji_Response(type):
    """Metaclass of message 'PlayEmoji_Response'."""

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
                'aimdk_msgs.srv.PlayEmoji_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__play_emoji__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__play_emoji__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__play_emoji__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__play_emoji__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__play_emoji__response

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


class PlayEmoji_Response(metaclass=Metaclass_PlayEmoji_Response):
    """Message class 'PlayEmoji_Response'."""

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


class Metaclass_PlayEmoji(type):
    """Metaclass of service 'PlayEmoji'."""

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
                'aimdk_msgs.srv.PlayEmoji')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__play_emoji

            from aimdk_msgs.srv import _play_emoji
            if _play_emoji.Metaclass_PlayEmoji_Request._TYPE_SUPPORT is None:
                _play_emoji.Metaclass_PlayEmoji_Request.__import_type_support__()
            if _play_emoji.Metaclass_PlayEmoji_Response._TYPE_SUPPORT is None:
                _play_emoji.Metaclass_PlayEmoji_Response.__import_type_support__()


class PlayEmoji(metaclass=Metaclass_PlayEmoji):
    from aimdk_msgs.srv._play_emoji import PlayEmoji_Request as Request
    from aimdk_msgs.srv._play_emoji import PlayEmoji_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

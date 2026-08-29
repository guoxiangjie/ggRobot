# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/McPresetMotion.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_McPresetMotion(type):
    """Metaclass of message 'McPresetMotion'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'RAISE_HAND': 1001,
        'WAVE_HAND': 1002,
        'SHAKE_HAND': 1003,
        'FLYING_KISS_HAND': 1004,
        'CLAP_HAND': 1008,
        'TURN_WAVE_HAND': 2001,
        'INTERACTION_BOW': 3001,
        'INTERACTION_LIKE': 3002,
        'INTERACTION_YE': 3003,
        'INTERACTION_SWEATHEART': 3004,
        'SALUTE': 1013,
        'INTERACTION_SAD': 3006,
        'INTERACTION_LIGHTWAVE': 3007,
        'INTERACTION_HUG': 3008,
        'INTERACTION_HANDX': 3009,
        'INTERACTION_CHESTWAVE': 3010,
        'INTERACTION_CHEER': 3011,
        'INTERACTION_BLOWKISS': 3012,
        'INTERACTION_BASSDANCE1': 3013,
        'INTERACTION_BASSDANCE2': 3014,
        'HITCLAP': 3015,
        'INTERACTION_SPEAK': 3016,
        'CLIPFIST': 1009,
        'INTERACTION_PHOTOPOSTURE': 3018,
        'INTERACTION_PHOTOTRIPPLEPOSTURE': 3019,
        'POINT_HEAD': 4001,
        'SHAKE_HEAD': 4002,
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
                'aimdk_msgs.msg.McPresetMotion')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__mc_preset_motion
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__mc_preset_motion
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__mc_preset_motion
            cls._TYPE_SUPPORT = module.type_support_msg__msg__mc_preset_motion
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__mc_preset_motion

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'RAISE_HAND': cls.__constants['RAISE_HAND'],
            'WAVE_HAND': cls.__constants['WAVE_HAND'],
            'SHAKE_HAND': cls.__constants['SHAKE_HAND'],
            'FLYING_KISS_HAND': cls.__constants['FLYING_KISS_HAND'],
            'CLAP_HAND': cls.__constants['CLAP_HAND'],
            'TURN_WAVE_HAND': cls.__constants['TURN_WAVE_HAND'],
            'INTERACTION_BOW': cls.__constants['INTERACTION_BOW'],
            'INTERACTION_LIKE': cls.__constants['INTERACTION_LIKE'],
            'INTERACTION_YE': cls.__constants['INTERACTION_YE'],
            'INTERACTION_SWEATHEART': cls.__constants['INTERACTION_SWEATHEART'],
            'SALUTE': cls.__constants['SALUTE'],
            'INTERACTION_SAD': cls.__constants['INTERACTION_SAD'],
            'INTERACTION_LIGHTWAVE': cls.__constants['INTERACTION_LIGHTWAVE'],
            'INTERACTION_HUG': cls.__constants['INTERACTION_HUG'],
            'INTERACTION_HANDX': cls.__constants['INTERACTION_HANDX'],
            'INTERACTION_CHESTWAVE': cls.__constants['INTERACTION_CHESTWAVE'],
            'INTERACTION_CHEER': cls.__constants['INTERACTION_CHEER'],
            'INTERACTION_BLOWKISS': cls.__constants['INTERACTION_BLOWKISS'],
            'INTERACTION_BASSDANCE1': cls.__constants['INTERACTION_BASSDANCE1'],
            'INTERACTION_BASSDANCE2': cls.__constants['INTERACTION_BASSDANCE2'],
            'HITCLAP': cls.__constants['HITCLAP'],
            'INTERACTION_SPEAK': cls.__constants['INTERACTION_SPEAK'],
            'CLIPFIST': cls.__constants['CLIPFIST'],
            'INTERACTION_PHOTOPOSTURE': cls.__constants['INTERACTION_PHOTOPOSTURE'],
            'INTERACTION_PHOTOTRIPPLEPOSTURE': cls.__constants['INTERACTION_PHOTOTRIPPLEPOSTURE'],
            'POINT_HEAD': cls.__constants['POINT_HEAD'],
            'SHAKE_HEAD': cls.__constants['SHAKE_HEAD'],
        }

    @property
    def RAISE_HAND(self):
        """Message constant 'RAISE_HAND'."""
        return Metaclass_McPresetMotion.__constants['RAISE_HAND']

    @property
    def WAVE_HAND(self):
        """Message constant 'WAVE_HAND'."""
        return Metaclass_McPresetMotion.__constants['WAVE_HAND']

    @property
    def SHAKE_HAND(self):
        """Message constant 'SHAKE_HAND'."""
        return Metaclass_McPresetMotion.__constants['SHAKE_HAND']

    @property
    def FLYING_KISS_HAND(self):
        """Message constant 'FLYING_KISS_HAND'."""
        return Metaclass_McPresetMotion.__constants['FLYING_KISS_HAND']

    @property
    def CLAP_HAND(self):
        """Message constant 'CLAP_HAND'."""
        return Metaclass_McPresetMotion.__constants['CLAP_HAND']

    @property
    def TURN_WAVE_HAND(self):
        """Message constant 'TURN_WAVE_HAND'."""
        return Metaclass_McPresetMotion.__constants['TURN_WAVE_HAND']

    @property
    def INTERACTION_BOW(self):
        """Message constant 'INTERACTION_BOW'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_BOW']

    @property
    def INTERACTION_LIKE(self):
        """Message constant 'INTERACTION_LIKE'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_LIKE']

    @property
    def INTERACTION_YE(self):
        """Message constant 'INTERACTION_YE'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_YE']

    @property
    def INTERACTION_SWEATHEART(self):
        """Message constant 'INTERACTION_SWEATHEART'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_SWEATHEART']

    @property
    def SALUTE(self):
        """Message constant 'SALUTE'."""
        return Metaclass_McPresetMotion.__constants['SALUTE']

    @property
    def INTERACTION_SAD(self):
        """Message constant 'INTERACTION_SAD'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_SAD']

    @property
    def INTERACTION_LIGHTWAVE(self):
        """Message constant 'INTERACTION_LIGHTWAVE'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_LIGHTWAVE']

    @property
    def INTERACTION_HUG(self):
        """Message constant 'INTERACTION_HUG'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_HUG']

    @property
    def INTERACTION_HANDX(self):
        """Message constant 'INTERACTION_HANDX'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_HANDX']

    @property
    def INTERACTION_CHESTWAVE(self):
        """Message constant 'INTERACTION_CHESTWAVE'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_CHESTWAVE']

    @property
    def INTERACTION_CHEER(self):
        """Message constant 'INTERACTION_CHEER'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_CHEER']

    @property
    def INTERACTION_BLOWKISS(self):
        """Message constant 'INTERACTION_BLOWKISS'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_BLOWKISS']

    @property
    def INTERACTION_BASSDANCE1(self):
        """Message constant 'INTERACTION_BASSDANCE1'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_BASSDANCE1']

    @property
    def INTERACTION_BASSDANCE2(self):
        """Message constant 'INTERACTION_BASSDANCE2'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_BASSDANCE2']

    @property
    def HITCLAP(self):
        """Message constant 'HITCLAP'."""
        return Metaclass_McPresetMotion.__constants['HITCLAP']

    @property
    def INTERACTION_SPEAK(self):
        """Message constant 'INTERACTION_SPEAK'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_SPEAK']

    @property
    def CLIPFIST(self):
        """Message constant 'CLIPFIST'."""
        return Metaclass_McPresetMotion.__constants['CLIPFIST']

    @property
    def INTERACTION_PHOTOPOSTURE(self):
        """Message constant 'INTERACTION_PHOTOPOSTURE'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_PHOTOPOSTURE']

    @property
    def INTERACTION_PHOTOTRIPPLEPOSTURE(self):
        """Message constant 'INTERACTION_PHOTOTRIPPLEPOSTURE'."""
        return Metaclass_McPresetMotion.__constants['INTERACTION_PHOTOTRIPPLEPOSTURE']

    @property
    def POINT_HEAD(self):
        """Message constant 'POINT_HEAD'."""
        return Metaclass_McPresetMotion.__constants['POINT_HEAD']

    @property
    def SHAKE_HEAD(self):
        """Message constant 'SHAKE_HEAD'."""
        return Metaclass_McPresetMotion.__constants['SHAKE_HEAD']


class McPresetMotion(metaclass=Metaclass_McPresetMotion):
    """
    Message class 'McPresetMotion'.

    Constants:
      RAISE_HAND
      WAVE_HAND
      SHAKE_HAND
      FLYING_KISS_HAND
      CLAP_HAND
      TURN_WAVE_HAND
      INTERACTION_BOW
      INTERACTION_LIKE
      INTERACTION_YE
      INTERACTION_SWEATHEART
      SALUTE
      INTERACTION_SAD
      INTERACTION_LIGHTWAVE
      INTERACTION_HUG
      INTERACTION_HANDX
      INTERACTION_CHESTWAVE
      INTERACTION_CHEER
      INTERACTION_BLOWKISS
      INTERACTION_BASSDANCE1
      INTERACTION_BASSDANCE2
      HITCLAP
      INTERACTION_SPEAK
      CLIPFIST
      INTERACTION_PHOTOPOSTURE
      INTERACTION_PHOTOTRIPPLEPOSTURE
      POINT_HEAD
      SHAKE_HEAD
    """

    __slots__ = [
        '_value',
    ]

    _fields_and_field_types = {
        'value': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.value = kwargs.get('value', int())

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
        if self.value != other.value:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def value(self):
        """Message field 'value'."""
        return self._value

    @value.setter
    def value(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'value' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'value' field must be an integer in [-2147483648, 2147483647]"
        self._value = value

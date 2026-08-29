# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/McAction.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_McAction(type):
    """Metaclass of message 'McAction'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'PASSIVE_DEFAULT': 1,
        'SOFT_EMERGENCY_STOP': 2,
        'DAMPING_DEFAULT': 3,
        'ZERO_TORQUE_DEFAULT': 4,
        'JOINT_DEFAULT': 100,
        'JOINT_FREEZE': 101,
        'STAND_DEFAULT': 200,
        'STAND_BODY_CONTROL': 201,
        'LOCOMOTION_DEFAULT': 300,
        'RUN_DEFAULT': 301,
        'LOCOMOTION_STEP': 302,
        'VR_REMOTE_CONTROLLER': 400,
        'SIT_DOWN_DEFAULT': 2000,
        'CROUCH_DOWN_DEFAULT': 2002,
        'LIE_DOWN_DEFAULT': 2004,
        'STAND_UP_DEFAULT': 2005,
        'ASCEND_STAIRS': 2006,
        'DESCEND_STAIRS': 2008,
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
                'aimdk_msgs.msg.McAction')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__mc_action
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__mc_action
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__mc_action
            cls._TYPE_SUPPORT = module.type_support_msg__msg__mc_action
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__mc_action

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'PASSIVE_DEFAULT': cls.__constants['PASSIVE_DEFAULT'],
            'SOFT_EMERGENCY_STOP': cls.__constants['SOFT_EMERGENCY_STOP'],
            'DAMPING_DEFAULT': cls.__constants['DAMPING_DEFAULT'],
            'ZERO_TORQUE_DEFAULT': cls.__constants['ZERO_TORQUE_DEFAULT'],
            'JOINT_DEFAULT': cls.__constants['JOINT_DEFAULT'],
            'JOINT_FREEZE': cls.__constants['JOINT_FREEZE'],
            'STAND_DEFAULT': cls.__constants['STAND_DEFAULT'],
            'STAND_BODY_CONTROL': cls.__constants['STAND_BODY_CONTROL'],
            'LOCOMOTION_DEFAULT': cls.__constants['LOCOMOTION_DEFAULT'],
            'RUN_DEFAULT': cls.__constants['RUN_DEFAULT'],
            'LOCOMOTION_STEP': cls.__constants['LOCOMOTION_STEP'],
            'VR_REMOTE_CONTROLLER': cls.__constants['VR_REMOTE_CONTROLLER'],
            'SIT_DOWN_DEFAULT': cls.__constants['SIT_DOWN_DEFAULT'],
            'CROUCH_DOWN_DEFAULT': cls.__constants['CROUCH_DOWN_DEFAULT'],
            'LIE_DOWN_DEFAULT': cls.__constants['LIE_DOWN_DEFAULT'],
            'STAND_UP_DEFAULT': cls.__constants['STAND_UP_DEFAULT'],
            'ASCEND_STAIRS': cls.__constants['ASCEND_STAIRS'],
            'DESCEND_STAIRS': cls.__constants['DESCEND_STAIRS'],
        }

    @property
    def PASSIVE_DEFAULT(self):
        """Message constant 'PASSIVE_DEFAULT'."""
        return Metaclass_McAction.__constants['PASSIVE_DEFAULT']

    @property
    def SOFT_EMERGENCY_STOP(self):
        """Message constant 'SOFT_EMERGENCY_STOP'."""
        return Metaclass_McAction.__constants['SOFT_EMERGENCY_STOP']

    @property
    def DAMPING_DEFAULT(self):
        """Message constant 'DAMPING_DEFAULT'."""
        return Metaclass_McAction.__constants['DAMPING_DEFAULT']

    @property
    def ZERO_TORQUE_DEFAULT(self):
        """Message constant 'ZERO_TORQUE_DEFAULT'."""
        return Metaclass_McAction.__constants['ZERO_TORQUE_DEFAULT']

    @property
    def JOINT_DEFAULT(self):
        """Message constant 'JOINT_DEFAULT'."""
        return Metaclass_McAction.__constants['JOINT_DEFAULT']

    @property
    def JOINT_FREEZE(self):
        """Message constant 'JOINT_FREEZE'."""
        return Metaclass_McAction.__constants['JOINT_FREEZE']

    @property
    def STAND_DEFAULT(self):
        """Message constant 'STAND_DEFAULT'."""
        return Metaclass_McAction.__constants['STAND_DEFAULT']

    @property
    def STAND_BODY_CONTROL(self):
        """Message constant 'STAND_BODY_CONTROL'."""
        return Metaclass_McAction.__constants['STAND_BODY_CONTROL']

    @property
    def LOCOMOTION_DEFAULT(self):
        """Message constant 'LOCOMOTION_DEFAULT'."""
        return Metaclass_McAction.__constants['LOCOMOTION_DEFAULT']

    @property
    def RUN_DEFAULT(self):
        """Message constant 'RUN_DEFAULT'."""
        return Metaclass_McAction.__constants['RUN_DEFAULT']

    @property
    def LOCOMOTION_STEP(self):
        """Message constant 'LOCOMOTION_STEP'."""
        return Metaclass_McAction.__constants['LOCOMOTION_STEP']

    @property
    def VR_REMOTE_CONTROLLER(self):
        """Message constant 'VR_REMOTE_CONTROLLER'."""
        return Metaclass_McAction.__constants['VR_REMOTE_CONTROLLER']

    @property
    def SIT_DOWN_DEFAULT(self):
        """Message constant 'SIT_DOWN_DEFAULT'."""
        return Metaclass_McAction.__constants['SIT_DOWN_DEFAULT']

    @property
    def CROUCH_DOWN_DEFAULT(self):
        """Message constant 'CROUCH_DOWN_DEFAULT'."""
        return Metaclass_McAction.__constants['CROUCH_DOWN_DEFAULT']

    @property
    def LIE_DOWN_DEFAULT(self):
        """Message constant 'LIE_DOWN_DEFAULT'."""
        return Metaclass_McAction.__constants['LIE_DOWN_DEFAULT']

    @property
    def STAND_UP_DEFAULT(self):
        """Message constant 'STAND_UP_DEFAULT'."""
        return Metaclass_McAction.__constants['STAND_UP_DEFAULT']

    @property
    def ASCEND_STAIRS(self):
        """Message constant 'ASCEND_STAIRS'."""
        return Metaclass_McAction.__constants['ASCEND_STAIRS']

    @property
    def DESCEND_STAIRS(self):
        """Message constant 'DESCEND_STAIRS'."""
        return Metaclass_McAction.__constants['DESCEND_STAIRS']


class McAction(metaclass=Metaclass_McAction):
    """
    Message class 'McAction'.

    Constants:
      PASSIVE_DEFAULT
      SOFT_EMERGENCY_STOP
      DAMPING_DEFAULT
      ZERO_TORQUE_DEFAULT
      JOINT_DEFAULT
      JOINT_FREEZE
      STAND_DEFAULT
      STAND_BODY_CONTROL
      LOCOMOTION_DEFAULT
      RUN_DEFAULT
      LOCOMOTION_STEP
      VR_REMOTE_CONTROLLER
      SIT_DOWN_DEFAULT
      CROUCH_DOWN_DEFAULT
      LIE_DOWN_DEFAULT
      STAND_UP_DEFAULT
      ASCEND_STAIRS
      DESCEND_STAIRS
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

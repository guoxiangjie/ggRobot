# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/McLocomotionVelocity.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_McLocomotionVelocity(type):
    """Metaclass of message 'McLocomotionVelocity'."""

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
                'aimdk_msgs.msg.McLocomotionVelocity')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__mc_locomotion_velocity
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__mc_locomotion_velocity
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__mc_locomotion_velocity
            cls._TYPE_SUPPORT = module.type_support_msg__msg__mc_locomotion_velocity
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__mc_locomotion_velocity

            from aimdk_msgs.msg import MessageHeader
            if MessageHeader.__class__._TYPE_SUPPORT is None:
                MessageHeader.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class McLocomotionVelocity(metaclass=Metaclass_McLocomotionVelocity):
    """Message class 'McLocomotionVelocity'."""

    __slots__ = [
        '_header',
        '_source',
        '_forward_velocity',
        '_lateral_velocity',
        '_angular_velocity',
    ]

    _fields_and_field_types = {
        'header': 'aimdk_msgs/MessageHeader',
        'source': 'string',
        'forward_velocity': 'double',
        'lateral_velocity': 'double',
        'angular_velocity': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'MessageHeader'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import MessageHeader
        self.header = kwargs.get('header', MessageHeader())
        self.source = kwargs.get('source', str())
        self.forward_velocity = kwargs.get('forward_velocity', float())
        self.lateral_velocity = kwargs.get('lateral_velocity', float())
        self.angular_velocity = kwargs.get('angular_velocity', float())

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
        if self.source != other.source:
            return False
        if self.forward_velocity != other.forward_velocity:
            return False
        if self.lateral_velocity != other.lateral_velocity:
            return False
        if self.angular_velocity != other.angular_velocity:
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
            from aimdk_msgs.msg import MessageHeader
            assert \
                isinstance(value, MessageHeader), \
                "The 'header' field must be a sub message of type 'MessageHeader'"
        self._header = value

    @builtins.property
    def source(self):
        """Message field 'source'."""
        return self._source

    @source.setter
    def source(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'source' field must be of type 'str'"
        self._source = value

    @builtins.property
    def forward_velocity(self):
        """Message field 'forward_velocity'."""
        return self._forward_velocity

    @forward_velocity.setter
    def forward_velocity(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'forward_velocity' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'forward_velocity' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._forward_velocity = value

    @builtins.property
    def lateral_velocity(self):
        """Message field 'lateral_velocity'."""
        return self._lateral_velocity

    @lateral_velocity.setter
    def lateral_velocity(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'lateral_velocity' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'lateral_velocity' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._lateral_velocity = value

    @builtins.property
    def angular_velocity(self):
        """Message field 'angular_velocity'."""
        return self._angular_velocity

    @angular_velocity.setter
    def angular_velocity(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'angular_velocity' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'angular_velocity' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._angular_velocity = value

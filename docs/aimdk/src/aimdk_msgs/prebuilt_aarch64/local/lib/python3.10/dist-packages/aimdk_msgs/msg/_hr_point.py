# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/HRPoint.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_HRPoint(type):
    """Metaclass of message 'HRPoint'."""

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
                'aimdk_msgs.msg.HRPoint')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__hr_point
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__hr_point
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__hr_point
            cls._TYPE_SUPPORT = module.type_support_msg__msg__hr_point
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__hr_point

            from aimdk_msgs.msg import QRCode
            if QRCode.__class__._TYPE_SUPPORT is None:
                QRCode.__class__.__import_type_support__()

            from geometry_msgs.msg import Pose
            if Pose.__class__._TYPE_SUPPORT is None:
                Pose.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class HRPoint(metaclass=Metaclass_HRPoint):
    """Message class 'HRPoint'."""

    __slots__ = [
        '_point_id',
        '_pose',
        '_qr_list',
        '_use_head',
    ]

    _fields_and_field_types = {
        'point_id': 'int32',
        'pose': 'geometry_msgs/Pose',
        'qr_list': 'sequence<aimdk_msgs/QRCode>',
        'use_head': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Pose'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'QRCode')),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.point_id = kwargs.get('point_id', int())
        from geometry_msgs.msg import Pose
        self.pose = kwargs.get('pose', Pose())
        self.qr_list = kwargs.get('qr_list', [])
        self.use_head = kwargs.get('use_head', bool())

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
        if self.point_id != other.point_id:
            return False
        if self.pose != other.pose:
            return False
        if self.qr_list != other.qr_list:
            return False
        if self.use_head != other.use_head:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def point_id(self):
        """Message field 'point_id'."""
        return self._point_id

    @point_id.setter
    def point_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'point_id' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'point_id' field must be an integer in [-2147483648, 2147483647]"
        self._point_id = value

    @builtins.property
    def pose(self):
        """Message field 'pose'."""
        return self._pose

    @pose.setter
    def pose(self, value):
        if __debug__:
            from geometry_msgs.msg import Pose
            assert \
                isinstance(value, Pose), \
                "The 'pose' field must be a sub message of type 'Pose'"
        self._pose = value

    @builtins.property
    def qr_list(self):
        """Message field 'qr_list'."""
        return self._qr_list

    @qr_list.setter
    def qr_list(self, value):
        if __debug__:
            from aimdk_msgs.msg import QRCode
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, QRCode) for v in value) and
                 True), \
                "The 'qr_list' field must be a set or sequence and each value of type 'QRCode'"
        self._qr_list = value

    @builtins.property
    def use_head(self):
        """Message field 'use_head'."""
        return self._use_head

    @use_head.setter
    def use_head(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'use_head' field must be of type 'bool'"
        self._use_head = value

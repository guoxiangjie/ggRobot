# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/RobotResourceMapping.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RobotResourceMapping(type):
    """Metaclass of message 'RobotResourceMapping'."""

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
                'aimdk_msgs.msg.RobotResourceMapping')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__robot_resource_mapping
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__robot_resource_mapping
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__robot_resource_mapping
            cls._TYPE_SUPPORT = module.type_support_msg__msg__robot_resource_mapping
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__robot_resource_mapping

            from aimdk_msgs.msg import RobotResource
            if RobotResource.__class__._TYPE_SUPPORT is None:
                RobotResource.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RobotResourceMapping(metaclass=Metaclass_RobotResourceMapping):
    """Message class 'RobotResourceMapping'."""

    __slots__ = [
        '_is_master',
        '_robot_ip',
        '_robot_resource_list',
    ]

    _fields_and_field_types = {
        'is_master': 'boolean',
        'robot_ip': 'string',
        'robot_resource_list': 'sequence<aimdk_msgs/RobotResource>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'RobotResource')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.is_master = kwargs.get('is_master', bool())
        self.robot_ip = kwargs.get('robot_ip', str())
        self.robot_resource_list = kwargs.get('robot_resource_list', [])

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
        if self.is_master != other.is_master:
            return False
        if self.robot_ip != other.robot_ip:
            return False
        if self.robot_resource_list != other.robot_resource_list:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def is_master(self):
        """Message field 'is_master'."""
        return self._is_master

    @is_master.setter
    def is_master(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_master' field must be of type 'bool'"
        self._is_master = value

    @builtins.property
    def robot_ip(self):
        """Message field 'robot_ip'."""
        return self._robot_ip

    @robot_ip.setter
    def robot_ip(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'robot_ip' field must be of type 'str'"
        self._robot_ip = value

    @builtins.property
    def robot_resource_list(self):
        """Message field 'robot_resource_list'."""
        return self._robot_resource_list

    @robot_resource_list.setter
    def robot_resource_list(self, value):
        if __debug__:
            from aimdk_msgs.msg import RobotResource
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
                 all(isinstance(v, RobotResource) for v in value) and
                 True), \
                "The 'robot_resource_list' field must be a set or sequence and each value of type 'RobotResource'"
        self._robot_resource_list = value

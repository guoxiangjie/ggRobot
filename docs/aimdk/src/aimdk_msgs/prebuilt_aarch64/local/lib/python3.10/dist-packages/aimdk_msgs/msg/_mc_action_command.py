# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/McActionCommand.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_McActionCommand(type):
    """Metaclass of message 'McActionCommand'."""

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
                'aimdk_msgs.msg.McActionCommand')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__mc_action_command
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__mc_action_command
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__mc_action_command
            cls._TYPE_SUPPORT = module.type_support_msg__msg__mc_action_command
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__mc_action_command

            from aimdk_msgs.msg import McAction
            if McAction.__class__._TYPE_SUPPORT is None:
                McAction.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class McActionCommand(metaclass=Metaclass_McActionCommand):
    """Message class 'McActionCommand'."""

    __slots__ = [
        '_action',
        '_action_desc',
    ]

    _fields_and_field_types = {
        'action': 'aimdk_msgs/McAction',
        'action_desc': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'McAction'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import McAction
        self.action = kwargs.get('action', McAction())
        self.action_desc = kwargs.get('action_desc', str())

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
        if self.action != other.action:
            return False
        if self.action_desc != other.action_desc:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def action(self):
        """Message field 'action'."""
        return self._action

    @action.setter
    def action(self, value):
        if __debug__:
            from aimdk_msgs.msg import McAction
            assert \
                isinstance(value, McAction), \
                "The 'action' field must be a sub message of type 'McAction'"
        self._action = value

    @builtins.property
    def action_desc(self):
        """Message field 'action_desc'."""
        return self._action_desc

    @action_desc.setter
    def action_desc(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'action_desc' field must be of type 'str'"
        self._action_desc = value

# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/McActionInfo.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_McActionInfo(type):
    """Metaclass of message 'McActionInfo'."""

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
                'aimdk_msgs.msg.McActionInfo')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__mc_action_info
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__mc_action_info
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__mc_action_info
            cls._TYPE_SUPPORT = module.type_support_msg__msg__mc_action_info
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__mc_action_info

            from aimdk_msgs.msg import McAction
            if McAction.__class__._TYPE_SUPPORT is None:
                McAction.__class__.__import_type_support__()

            from aimdk_msgs.msg import McActionStatus
            if McActionStatus.__class__._TYPE_SUPPORT is None:
                McActionStatus.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class McActionInfo(metaclass=Metaclass_McActionInfo):
    """Message class 'McActionInfo'."""

    __slots__ = [
        '_current_action',
        '_action_desc',
        '_status',
    ]

    _fields_and_field_types = {
        'current_action': 'aimdk_msgs/McAction',
        'action_desc': 'string',
        'status': 'aimdk_msgs/McActionStatus',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'McAction'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'McActionStatus'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import McAction
        self.current_action = kwargs.get('current_action', McAction())
        self.action_desc = kwargs.get('action_desc', str())
        from aimdk_msgs.msg import McActionStatus
        self.status = kwargs.get('status', McActionStatus())

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
        if self.current_action != other.current_action:
            return False
        if self.action_desc != other.action_desc:
            return False
        if self.status != other.status:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def current_action(self):
        """Message field 'current_action'."""
        return self._current_action

    @current_action.setter
    def current_action(self, value):
        if __debug__:
            from aimdk_msgs.msg import McAction
            assert \
                isinstance(value, McAction), \
                "The 'current_action' field must be a sub message of type 'McAction'"
        self._current_action = value

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

    @builtins.property
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            from aimdk_msgs.msg import McActionStatus
            assert \
                isinstance(value, McActionStatus), \
                "The 'status' field must be a sub message of type 'McActionStatus'"
        self._status = value

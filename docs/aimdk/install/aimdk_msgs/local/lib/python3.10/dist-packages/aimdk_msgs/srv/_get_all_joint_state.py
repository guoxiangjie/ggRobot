# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/GetAllJointState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetAllJointState_Request(type):
    """Metaclass of message 'GetAllJointState_Request'."""

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
                'aimdk_msgs.srv.GetAllJointState_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_all_joint_state__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_all_joint_state__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_all_joint_state__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_all_joint_state__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_all_joint_state__request

            from aimdk_msgs.msg import CommonRequest
            if CommonRequest.__class__._TYPE_SUPPORT is None:
                CommonRequest.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetAllJointState_Request(metaclass=Metaclass_GetAllJointState_Request):
    """Message class 'GetAllJointState_Request'."""

    __slots__ = [
        '_request',
    ]

    _fields_and_field_types = {
        'request': 'aimdk_msgs/CommonRequest',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonRequest'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonRequest
        self.request = kwargs.get('request', CommonRequest())

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


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_GetAllJointState_Response(type):
    """Metaclass of message 'GetAllJointState_Response'."""

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
                'aimdk_msgs.srv.GetAllJointState_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_all_joint_state__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_all_joint_state__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_all_joint_state__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_all_joint_state__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_all_joint_state__response

            from aimdk_msgs.msg import CommonResponse
            if CommonResponse.__class__._TYPE_SUPPORT is None:
                CommonResponse.__class__.__import_type_support__()

            from aimdk_msgs.msg import JointState
            if JointState.__class__._TYPE_SUPPORT is None:
                JointState.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetAllJointState_Response(metaclass=Metaclass_GetAllJointState_Response):
    """Message class 'GetAllJointState_Response'."""

    __slots__ = [
        '_reponse',
        '_head_joints',
        '_arm_joints',
        '_waist_joints',
        '_leg_joints',
    ]

    _fields_and_field_types = {
        'reponse': 'aimdk_msgs/CommonResponse',
        'head_joints': 'sequence<aimdk_msgs/JointState>',
        'arm_joints': 'sequence<aimdk_msgs/JointState>',
        'waist_joints': 'sequence<aimdk_msgs/JointState>',
        'leg_joints': 'sequence<aimdk_msgs/JointState>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'CommonResponse'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'JointState')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'JointState')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'JointState')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'JointState')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from aimdk_msgs.msg import CommonResponse
        self.reponse = kwargs.get('reponse', CommonResponse())
        self.head_joints = kwargs.get('head_joints', [])
        self.arm_joints = kwargs.get('arm_joints', [])
        self.waist_joints = kwargs.get('waist_joints', [])
        self.leg_joints = kwargs.get('leg_joints', [])

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
        if self.reponse != other.reponse:
            return False
        if self.head_joints != other.head_joints:
            return False
        if self.arm_joints != other.arm_joints:
            return False
        if self.waist_joints != other.waist_joints:
            return False
        if self.leg_joints != other.leg_joints:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def reponse(self):
        """Message field 'reponse'."""
        return self._reponse

    @reponse.setter
    def reponse(self, value):
        if __debug__:
            from aimdk_msgs.msg import CommonResponse
            assert \
                isinstance(value, CommonResponse), \
                "The 'reponse' field must be a sub message of type 'CommonResponse'"
        self._reponse = value

    @builtins.property
    def head_joints(self):
        """Message field 'head_joints'."""
        return self._head_joints

    @head_joints.setter
    def head_joints(self, value):
        if __debug__:
            from aimdk_msgs.msg import JointState
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
                 all(isinstance(v, JointState) for v in value) and
                 True), \
                "The 'head_joints' field must be a set or sequence and each value of type 'JointState'"
        self._head_joints = value

    @builtins.property
    def arm_joints(self):
        """Message field 'arm_joints'."""
        return self._arm_joints

    @arm_joints.setter
    def arm_joints(self, value):
        if __debug__:
            from aimdk_msgs.msg import JointState
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
                 all(isinstance(v, JointState) for v in value) and
                 True), \
                "The 'arm_joints' field must be a set or sequence and each value of type 'JointState'"
        self._arm_joints = value

    @builtins.property
    def waist_joints(self):
        """Message field 'waist_joints'."""
        return self._waist_joints

    @waist_joints.setter
    def waist_joints(self, value):
        if __debug__:
            from aimdk_msgs.msg import JointState
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
                 all(isinstance(v, JointState) for v in value) and
                 True), \
                "The 'waist_joints' field must be a set or sequence and each value of type 'JointState'"
        self._waist_joints = value

    @builtins.property
    def leg_joints(self):
        """Message field 'leg_joints'."""
        return self._leg_joints

    @leg_joints.setter
    def leg_joints(self, value):
        if __debug__:
            from aimdk_msgs.msg import JointState
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
                 all(isinstance(v, JointState) for v in value) and
                 True), \
                "The 'leg_joints' field must be a set or sequence and each value of type 'JointState'"
        self._leg_joints = value


class Metaclass_GetAllJointState(type):
    """Metaclass of service 'GetAllJointState'."""

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
                'aimdk_msgs.srv.GetAllJointState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_all_joint_state

            from aimdk_msgs.srv import _get_all_joint_state
            if _get_all_joint_state.Metaclass_GetAllJointState_Request._TYPE_SUPPORT is None:
                _get_all_joint_state.Metaclass_GetAllJointState_Request.__import_type_support__()
            if _get_all_joint_state.Metaclass_GetAllJointState_Response._TYPE_SUPPORT is None:
                _get_all_joint_state.Metaclass_GetAllJointState_Response.__import_type_support__()


class GetAllJointState(metaclass=Metaclass_GetAllJointState):
    from aimdk_msgs.srv._get_all_joint_state import GetAllJointState_Request as Request
    from aimdk_msgs.srv._get_all_joint_state import GetAllJointState_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

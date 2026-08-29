# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/AgentPropertyIdType.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AgentPropertyIdType(type):
    """Metaclass of message 'AgentPropertyIdType'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'AGENT_PROPERTY_UNDEFINED': 0,
        'AGENT_PROPERTY_LANGUAGE': 1,
        'AGENT_PROPERTY_RUN_MODE': 2,
        'AGENT_PROPERTY_GREET': 3,
        'AGENT_PROPERTY_HEAD_FOLLOW': 4,
        'AGENT_PROPERTY_DUPLEX_TIMEOUT': 5,
        'AGENT_PROPERTY_ENVIRONMENT_SWITCH': 6,
        'AGENT_PROPERTY_WELCOME_STATUS': 7,
        'AGENT_PROPERTY_SITE_SWITCH': 8,
        'AGENT_PROPERTY_LANGUAGE_LIST': 9,
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
                'aimdk_msgs.msg.AgentPropertyIdType')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__agent_property_id_type
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__agent_property_id_type
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__agent_property_id_type
            cls._TYPE_SUPPORT = module.type_support_msg__msg__agent_property_id_type
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__agent_property_id_type

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'AGENT_PROPERTY_UNDEFINED': cls.__constants['AGENT_PROPERTY_UNDEFINED'],
            'AGENT_PROPERTY_LANGUAGE': cls.__constants['AGENT_PROPERTY_LANGUAGE'],
            'AGENT_PROPERTY_RUN_MODE': cls.__constants['AGENT_PROPERTY_RUN_MODE'],
            'AGENT_PROPERTY_GREET': cls.__constants['AGENT_PROPERTY_GREET'],
            'AGENT_PROPERTY_HEAD_FOLLOW': cls.__constants['AGENT_PROPERTY_HEAD_FOLLOW'],
            'AGENT_PROPERTY_DUPLEX_TIMEOUT': cls.__constants['AGENT_PROPERTY_DUPLEX_TIMEOUT'],
            'AGENT_PROPERTY_ENVIRONMENT_SWITCH': cls.__constants['AGENT_PROPERTY_ENVIRONMENT_SWITCH'],
            'AGENT_PROPERTY_WELCOME_STATUS': cls.__constants['AGENT_PROPERTY_WELCOME_STATUS'],
            'AGENT_PROPERTY_SITE_SWITCH': cls.__constants['AGENT_PROPERTY_SITE_SWITCH'],
            'AGENT_PROPERTY_LANGUAGE_LIST': cls.__constants['AGENT_PROPERTY_LANGUAGE_LIST'],
        }

    @property
    def AGENT_PROPERTY_UNDEFINED(self):
        """Message constant 'AGENT_PROPERTY_UNDEFINED'."""
        return Metaclass_AgentPropertyIdType.__constants['AGENT_PROPERTY_UNDEFINED']

    @property
    def AGENT_PROPERTY_LANGUAGE(self):
        """Message constant 'AGENT_PROPERTY_LANGUAGE'."""
        return Metaclass_AgentPropertyIdType.__constants['AGENT_PROPERTY_LANGUAGE']

    @property
    def AGENT_PROPERTY_RUN_MODE(self):
        """Message constant 'AGENT_PROPERTY_RUN_MODE'."""
        return Metaclass_AgentPropertyIdType.__constants['AGENT_PROPERTY_RUN_MODE']

    @property
    def AGENT_PROPERTY_GREET(self):
        """Message constant 'AGENT_PROPERTY_GREET'."""
        return Metaclass_AgentPropertyIdType.__constants['AGENT_PROPERTY_GREET']

    @property
    def AGENT_PROPERTY_HEAD_FOLLOW(self):
        """Message constant 'AGENT_PROPERTY_HEAD_FOLLOW'."""
        return Metaclass_AgentPropertyIdType.__constants['AGENT_PROPERTY_HEAD_FOLLOW']

    @property
    def AGENT_PROPERTY_DUPLEX_TIMEOUT(self):
        """Message constant 'AGENT_PROPERTY_DUPLEX_TIMEOUT'."""
        return Metaclass_AgentPropertyIdType.__constants['AGENT_PROPERTY_DUPLEX_TIMEOUT']

    @property
    def AGENT_PROPERTY_ENVIRONMENT_SWITCH(self):
        """Message constant 'AGENT_PROPERTY_ENVIRONMENT_SWITCH'."""
        return Metaclass_AgentPropertyIdType.__constants['AGENT_PROPERTY_ENVIRONMENT_SWITCH']

    @property
    def AGENT_PROPERTY_WELCOME_STATUS(self):
        """Message constant 'AGENT_PROPERTY_WELCOME_STATUS'."""
        return Metaclass_AgentPropertyIdType.__constants['AGENT_PROPERTY_WELCOME_STATUS']

    @property
    def AGENT_PROPERTY_SITE_SWITCH(self):
        """Message constant 'AGENT_PROPERTY_SITE_SWITCH'."""
        return Metaclass_AgentPropertyIdType.__constants['AGENT_PROPERTY_SITE_SWITCH']

    @property
    def AGENT_PROPERTY_LANGUAGE_LIST(self):
        """Message constant 'AGENT_PROPERTY_LANGUAGE_LIST'."""
        return Metaclass_AgentPropertyIdType.__constants['AGENT_PROPERTY_LANGUAGE_LIST']


class AgentPropertyIdType(metaclass=Metaclass_AgentPropertyIdType):
    """
    Message class 'AgentPropertyIdType'.

    Constants:
      AGENT_PROPERTY_UNDEFINED
      AGENT_PROPERTY_LANGUAGE
      AGENT_PROPERTY_RUN_MODE
      AGENT_PROPERTY_GREET
      AGENT_PROPERTY_HEAD_FOLLOW
      AGENT_PROPERTY_DUPLEX_TIMEOUT
      AGENT_PROPERTY_ENVIRONMENT_SWITCH
      AGENT_PROPERTY_WELCOME_STATUS
      AGENT_PROPERTY_SITE_SWITCH
      AGENT_PROPERTY_LANGUAGE_LIST
    """

    __slots__ = [
        '_value',
    ]

    _fields_and_field_types = {
        'value': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
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
            assert value >= 0 and value < 256, \
                "The 'value' field must be an unsigned integer in [0, 255]"
        self._value = value

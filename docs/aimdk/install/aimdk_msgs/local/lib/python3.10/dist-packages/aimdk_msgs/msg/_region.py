# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/Region.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Region(type):
    """Metaclass of message 'Region'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'REGION_UNDEFINED': 0,
        'REGION_WORKING_SPACE': 1,
        'REGION_VIRTUAL_WALL': 2,
        'REGION_DRAWING_UNDEFINED': 0,
        'REGION_DRAWING_CLOSURE': 1,
        'REGION_DRAWING_LINES': 2,
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
                'aimdk_msgs.msg.Region')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__region
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__region
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__region
            cls._TYPE_SUPPORT = module.type_support_msg__msg__region
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__region

            from geometry_msgs.msg import Polygon
            if Polygon.__class__._TYPE_SUPPORT is None:
                Polygon.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'REGION_UNDEFINED': cls.__constants['REGION_UNDEFINED'],
            'REGION_WORKING_SPACE': cls.__constants['REGION_WORKING_SPACE'],
            'REGION_VIRTUAL_WALL': cls.__constants['REGION_VIRTUAL_WALL'],
            'REGION_DRAWING_UNDEFINED': cls.__constants['REGION_DRAWING_UNDEFINED'],
            'REGION_DRAWING_CLOSURE': cls.__constants['REGION_DRAWING_CLOSURE'],
            'REGION_DRAWING_LINES': cls.__constants['REGION_DRAWING_LINES'],
        }

    @property
    def REGION_UNDEFINED(self):
        """Message constant 'REGION_UNDEFINED'."""
        return Metaclass_Region.__constants['REGION_UNDEFINED']

    @property
    def REGION_WORKING_SPACE(self):
        """Message constant 'REGION_WORKING_SPACE'."""
        return Metaclass_Region.__constants['REGION_WORKING_SPACE']

    @property
    def REGION_VIRTUAL_WALL(self):
        """Message constant 'REGION_VIRTUAL_WALL'."""
        return Metaclass_Region.__constants['REGION_VIRTUAL_WALL']

    @property
    def REGION_DRAWING_UNDEFINED(self):
        """Message constant 'REGION_DRAWING_UNDEFINED'."""
        return Metaclass_Region.__constants['REGION_DRAWING_UNDEFINED']

    @property
    def REGION_DRAWING_CLOSURE(self):
        """Message constant 'REGION_DRAWING_CLOSURE'."""
        return Metaclass_Region.__constants['REGION_DRAWING_CLOSURE']

    @property
    def REGION_DRAWING_LINES(self):
        """Message constant 'REGION_DRAWING_LINES'."""
        return Metaclass_Region.__constants['REGION_DRAWING_LINES']


class Region(metaclass=Metaclass_Region):
    """
    Message class 'Region'.

    Constants:
      REGION_UNDEFINED
      REGION_WORKING_SPACE
      REGION_VIRTUAL_WALL
      REGION_DRAWING_UNDEFINED
      REGION_DRAWING_CLOSURE
      REGION_DRAWING_LINES
    """

    __slots__ = [
        '_type',
        '_drawing_type',
        '_name',
        '_polygon',
    ]

    _fields_and_field_types = {
        'type': 'uint8',
        'drawing_type': 'uint8',
        'name': 'string',
        'polygon': 'geometry_msgs/Polygon',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Polygon'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.type = kwargs.get('type', int())
        self.drawing_type = kwargs.get('drawing_type', int())
        self.name = kwargs.get('name', str())
        from geometry_msgs.msg import Polygon
        self.polygon = kwargs.get('polygon', Polygon())

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
        if self.type != other.type:
            return False
        if self.drawing_type != other.drawing_type:
            return False
        if self.name != other.name:
            return False
        if self.polygon != other.polygon:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property  # noqa: A003
    def type(self):  # noqa: A003
        """Message field 'type'."""
        return self._type

    @type.setter  # noqa: A003
    def type(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'type' field must be an unsigned integer in [0, 255]"
        self._type = value

    @builtins.property
    def drawing_type(self):
        """Message field 'drawing_type'."""
        return self._drawing_type

    @drawing_type.setter
    def drawing_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'drawing_type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'drawing_type' field must be an unsigned integer in [0, 255]"
        self._drawing_type = value

    @builtins.property
    def name(self):
        """Message field 'name'."""
        return self._name

    @name.setter
    def name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'name' field must be of type 'str'"
        self._name = value

    @builtins.property
    def polygon(self):
        """Message field 'polygon'."""
        return self._polygon

    @polygon.setter
    def polygon(self, value):
        if __debug__:
            from geometry_msgs.msg import Polygon
            assert \
                isinstance(value, Polygon), \
                "The 'polygon' field must be a sub message of type 'Polygon'"
        self._polygon = value

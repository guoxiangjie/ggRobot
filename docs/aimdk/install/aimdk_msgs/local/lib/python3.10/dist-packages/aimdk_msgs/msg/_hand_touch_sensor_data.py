# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:msg/HandTouchSensorData.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

# Member 'palm_touch_data'
# Member 'back_of_hand_touch_data'
# Member 'thumb_touch_data'
# Member 'index_finger_touch_data'
# Member 'middle_finger_touch_data'
# Member 'ring_finger_touch_data'
# Member 'little_finger_touch_data'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_HandTouchSensorData(type):
    """Metaclass of message 'HandTouchSensorData'."""

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
                'aimdk_msgs.msg.HandTouchSensorData')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__hand_touch_sensor_data
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__hand_touch_sensor_data
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__hand_touch_sensor_data
            cls._TYPE_SUPPORT = module.type_support_msg__msg__hand_touch_sensor_data
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__hand_touch_sensor_data

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class HandTouchSensorData(metaclass=Metaclass_HandTouchSensorData):
    """Message class 'HandTouchSensorData'."""

    __slots__ = [
        '_palm_touch_data',
        '_back_of_hand_touch_data',
        '_thumb_touch_data',
        '_index_finger_touch_data',
        '_middle_finger_touch_data',
        '_ring_finger_touch_data',
        '_little_finger_touch_data',
    ]

    _fields_and_field_types = {
        'palm_touch_data': 'uint8[36]',
        'back_of_hand_touch_data': 'uint8[36]',
        'thumb_touch_data': 'uint8[16]',
        'index_finger_touch_data': 'uint8[16]',
        'middle_finger_touch_data': 'uint8[16]',
        'ring_finger_touch_data': 'uint8[16]',
        'little_finger_touch_data': 'uint8[16]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint8'), 36),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint8'), 36),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint8'), 16),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint8'), 16),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint8'), 16),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint8'), 16),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint8'), 16),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        if 'palm_touch_data' not in kwargs:
            self.palm_touch_data = numpy.zeros(36, dtype=numpy.uint8)
        else:
            self.palm_touch_data = numpy.array(kwargs.get('palm_touch_data'), dtype=numpy.uint8)
            assert self.palm_touch_data.shape == (36, )
        if 'back_of_hand_touch_data' not in kwargs:
            self.back_of_hand_touch_data = numpy.zeros(36, dtype=numpy.uint8)
        else:
            self.back_of_hand_touch_data = numpy.array(kwargs.get('back_of_hand_touch_data'), dtype=numpy.uint8)
            assert self.back_of_hand_touch_data.shape == (36, )
        if 'thumb_touch_data' not in kwargs:
            self.thumb_touch_data = numpy.zeros(16, dtype=numpy.uint8)
        else:
            self.thumb_touch_data = numpy.array(kwargs.get('thumb_touch_data'), dtype=numpy.uint8)
            assert self.thumb_touch_data.shape == (16, )
        if 'index_finger_touch_data' not in kwargs:
            self.index_finger_touch_data = numpy.zeros(16, dtype=numpy.uint8)
        else:
            self.index_finger_touch_data = numpy.array(kwargs.get('index_finger_touch_data'), dtype=numpy.uint8)
            assert self.index_finger_touch_data.shape == (16, )
        if 'middle_finger_touch_data' not in kwargs:
            self.middle_finger_touch_data = numpy.zeros(16, dtype=numpy.uint8)
        else:
            self.middle_finger_touch_data = numpy.array(kwargs.get('middle_finger_touch_data'), dtype=numpy.uint8)
            assert self.middle_finger_touch_data.shape == (16, )
        if 'ring_finger_touch_data' not in kwargs:
            self.ring_finger_touch_data = numpy.zeros(16, dtype=numpy.uint8)
        else:
            self.ring_finger_touch_data = numpy.array(kwargs.get('ring_finger_touch_data'), dtype=numpy.uint8)
            assert self.ring_finger_touch_data.shape == (16, )
        if 'little_finger_touch_data' not in kwargs:
            self.little_finger_touch_data = numpy.zeros(16, dtype=numpy.uint8)
        else:
            self.little_finger_touch_data = numpy.array(kwargs.get('little_finger_touch_data'), dtype=numpy.uint8)
            assert self.little_finger_touch_data.shape == (16, )

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
        if all(self.palm_touch_data != other.palm_touch_data):
            return False
        if all(self.back_of_hand_touch_data != other.back_of_hand_touch_data):
            return False
        if all(self.thumb_touch_data != other.thumb_touch_data):
            return False
        if all(self.index_finger_touch_data != other.index_finger_touch_data):
            return False
        if all(self.middle_finger_touch_data != other.middle_finger_touch_data):
            return False
        if all(self.ring_finger_touch_data != other.ring_finger_touch_data):
            return False
        if all(self.little_finger_touch_data != other.little_finger_touch_data):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def palm_touch_data(self):
        """Message field 'palm_touch_data'."""
        return self._palm_touch_data

    @palm_touch_data.setter
    def palm_touch_data(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.uint8, \
                "The 'palm_touch_data' numpy.ndarray() must have the dtype of 'numpy.uint8'"
            assert value.size == 36, \
                "The 'palm_touch_data' numpy.ndarray() must have a size of 36"
            self._palm_touch_data = value
            return
        if __debug__:
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
                 len(value) == 36 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'palm_touch_data' field must be a set or sequence with length 36 and each value of type 'int' and each unsigned integer in [0, 255]"
        self._palm_touch_data = numpy.array(value, dtype=numpy.uint8)

    @builtins.property
    def back_of_hand_touch_data(self):
        """Message field 'back_of_hand_touch_data'."""
        return self._back_of_hand_touch_data

    @back_of_hand_touch_data.setter
    def back_of_hand_touch_data(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.uint8, \
                "The 'back_of_hand_touch_data' numpy.ndarray() must have the dtype of 'numpy.uint8'"
            assert value.size == 36, \
                "The 'back_of_hand_touch_data' numpy.ndarray() must have a size of 36"
            self._back_of_hand_touch_data = value
            return
        if __debug__:
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
                 len(value) == 36 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'back_of_hand_touch_data' field must be a set or sequence with length 36 and each value of type 'int' and each unsigned integer in [0, 255]"
        self._back_of_hand_touch_data = numpy.array(value, dtype=numpy.uint8)

    @builtins.property
    def thumb_touch_data(self):
        """Message field 'thumb_touch_data'."""
        return self._thumb_touch_data

    @thumb_touch_data.setter
    def thumb_touch_data(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.uint8, \
                "The 'thumb_touch_data' numpy.ndarray() must have the dtype of 'numpy.uint8'"
            assert value.size == 16, \
                "The 'thumb_touch_data' numpy.ndarray() must have a size of 16"
            self._thumb_touch_data = value
            return
        if __debug__:
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
                 len(value) == 16 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'thumb_touch_data' field must be a set or sequence with length 16 and each value of type 'int' and each unsigned integer in [0, 255]"
        self._thumb_touch_data = numpy.array(value, dtype=numpy.uint8)

    @builtins.property
    def index_finger_touch_data(self):
        """Message field 'index_finger_touch_data'."""
        return self._index_finger_touch_data

    @index_finger_touch_data.setter
    def index_finger_touch_data(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.uint8, \
                "The 'index_finger_touch_data' numpy.ndarray() must have the dtype of 'numpy.uint8'"
            assert value.size == 16, \
                "The 'index_finger_touch_data' numpy.ndarray() must have a size of 16"
            self._index_finger_touch_data = value
            return
        if __debug__:
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
                 len(value) == 16 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'index_finger_touch_data' field must be a set or sequence with length 16 and each value of type 'int' and each unsigned integer in [0, 255]"
        self._index_finger_touch_data = numpy.array(value, dtype=numpy.uint8)

    @builtins.property
    def middle_finger_touch_data(self):
        """Message field 'middle_finger_touch_data'."""
        return self._middle_finger_touch_data

    @middle_finger_touch_data.setter
    def middle_finger_touch_data(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.uint8, \
                "The 'middle_finger_touch_data' numpy.ndarray() must have the dtype of 'numpy.uint8'"
            assert value.size == 16, \
                "The 'middle_finger_touch_data' numpy.ndarray() must have a size of 16"
            self._middle_finger_touch_data = value
            return
        if __debug__:
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
                 len(value) == 16 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'middle_finger_touch_data' field must be a set or sequence with length 16 and each value of type 'int' and each unsigned integer in [0, 255]"
        self._middle_finger_touch_data = numpy.array(value, dtype=numpy.uint8)

    @builtins.property
    def ring_finger_touch_data(self):
        """Message field 'ring_finger_touch_data'."""
        return self._ring_finger_touch_data

    @ring_finger_touch_data.setter
    def ring_finger_touch_data(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.uint8, \
                "The 'ring_finger_touch_data' numpy.ndarray() must have the dtype of 'numpy.uint8'"
            assert value.size == 16, \
                "The 'ring_finger_touch_data' numpy.ndarray() must have a size of 16"
            self._ring_finger_touch_data = value
            return
        if __debug__:
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
                 len(value) == 16 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'ring_finger_touch_data' field must be a set or sequence with length 16 and each value of type 'int' and each unsigned integer in [0, 255]"
        self._ring_finger_touch_data = numpy.array(value, dtype=numpy.uint8)

    @builtins.property
    def little_finger_touch_data(self):
        """Message field 'little_finger_touch_data'."""
        return self._little_finger_touch_data

    @little_finger_touch_data.setter
    def little_finger_touch_data(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.uint8, \
                "The 'little_finger_touch_data' numpy.ndarray() must have the dtype of 'numpy.uint8'"
            assert value.size == 16, \
                "The 'little_finger_touch_data' numpy.ndarray() must have a size of 16"
            self._little_finger_touch_data = value
            return
        if __debug__:
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
                 len(value) == 16 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'little_finger_touch_data' field must be a set or sequence with length 16 and each value of type 'int' and each unsigned integer in [0, 255]"
        self._little_finger_touch_data = numpy.array(value, dtype=numpy.uint8)

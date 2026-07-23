# generated from rosidl_generator_py/resource/_idl.py.em
# with input from aimdk_msgs:srv/GetStoredMapByName.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetStoredMapByName_Request(type):
    """Metaclass of message 'GetStoredMapByName_Request'."""

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
                'aimdk_msgs.srv.GetStoredMapByName_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_stored_map_by_name__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_stored_map_by_name__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_stored_map_by_name__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_stored_map_by_name__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_stored_map_by_name__request

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetStoredMapByName_Request(metaclass=Metaclass_GetStoredMapByName_Request):
    """Message class 'GetStoredMapByName_Request'."""

    __slots__ = [
        '_header',
        '_map_name',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'map_name': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.map_name = kwargs.get('map_name', str())

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
        if self.map_name != other.map_name:
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
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def map_name(self):
        """Message field 'map_name'."""
        return self._map_name

    @map_name.setter
    def map_name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'map_name' field must be of type 'str'"
        self._map_name = value


# Import statements for member types

# Member 'data'
import array  # noqa: E402, I100

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_GetStoredMapByName_Response(type):
    """Metaclass of message 'GetStoredMapByName_Response'."""

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
                'aimdk_msgs.srv.GetStoredMapByName_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_stored_map_by_name__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_stored_map_by_name__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_stored_map_by_name__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_stored_map_by_name__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_stored_map_by_name__response

            from aimdk_msgs.msg import HRPoint
            if HRPoint.__class__._TYPE_SUPPORT is None:
                HRPoint.__class__.__import_type_support__()

            from aimdk_msgs.msg import NaviPoint
            if NaviPoint.__class__._TYPE_SUPPORT is None:
                NaviPoint.__class__.__import_type_support__()

            from aimdk_msgs.msg import Path
            if Path.__class__._TYPE_SUPPORT is None:
                Path.__class__.__import_type_support__()

            from aimdk_msgs.msg import QRPoint
            if QRPoint.__class__._TYPE_SUPPORT is None:
                QRPoint.__class__.__import_type_support__()

            from aimdk_msgs.msg import Region
            if Region.__class__._TYPE_SUPPORT is None:
                Region.__class__.__import_type_support__()

            from nav_msgs.msg import MapMetaData
            if MapMetaData.__class__._TYPE_SUPPORT is None:
                MapMetaData.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetStoredMapByName_Response(metaclass=Metaclass_GetStoredMapByName_Response):
    """Message class 'GetStoredMapByName_Response'."""

    __slots__ = [
        '_code',
        '_header',
        '_map_info',
        '_map_version',
        '_map_path',
        '_data',
        '_navi_points',
        '_qr_points',
        '_hr_points',
        '_paths',
        '_regions',
        '_map_id',
    ]

    _fields_and_field_types = {
        'code': 'uint64',
        'header': 'std_msgs/Header',
        'map_info': 'nav_msgs/MapMetaData',
        'map_version': 'uint64',
        'map_path': 'string',
        'data': 'sequence<int8>',
        'navi_points': 'sequence<aimdk_msgs/NaviPoint>',
        'qr_points': 'sequence<aimdk_msgs/QRPoint>',
        'hr_points': 'sequence<aimdk_msgs/HRPoint>',
        'paths': 'sequence<aimdk_msgs/Path>',
        'regions': 'sequence<aimdk_msgs/Region>',
        'map_id': 'uint64',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['nav_msgs', 'msg'], 'MapMetaData'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int8')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'NaviPoint')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'QRPoint')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'HRPoint')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'Path')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['aimdk_msgs', 'msg'], 'Region')),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.code = kwargs.get('code', int())
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        from nav_msgs.msg import MapMetaData
        self.map_info = kwargs.get('map_info', MapMetaData())
        self.map_version = kwargs.get('map_version', int())
        self.map_path = kwargs.get('map_path', str())
        self.data = array.array('b', kwargs.get('data', []))
        self.navi_points = kwargs.get('navi_points', [])
        self.qr_points = kwargs.get('qr_points', [])
        self.hr_points = kwargs.get('hr_points', [])
        self.paths = kwargs.get('paths', [])
        self.regions = kwargs.get('regions', [])
        self.map_id = kwargs.get('map_id', int())

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
        if self.code != other.code:
            return False
        if self.header != other.header:
            return False
        if self.map_info != other.map_info:
            return False
        if self.map_version != other.map_version:
            return False
        if self.map_path != other.map_path:
            return False
        if self.data != other.data:
            return False
        if self.navi_points != other.navi_points:
            return False
        if self.qr_points != other.qr_points:
            return False
        if self.hr_points != other.hr_points:
            return False
        if self.paths != other.paths:
            return False
        if self.regions != other.regions:
            return False
        if self.map_id != other.map_id:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def code(self):
        """Message field 'code'."""
        return self._code

    @code.setter
    def code(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'code' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'code' field must be an unsigned integer in [0, 18446744073709551615]"
        self._code = value

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def map_info(self):
        """Message field 'map_info'."""
        return self._map_info

    @map_info.setter
    def map_info(self, value):
        if __debug__:
            from nav_msgs.msg import MapMetaData
            assert \
                isinstance(value, MapMetaData), \
                "The 'map_info' field must be a sub message of type 'MapMetaData'"
        self._map_info = value

    @builtins.property
    def map_version(self):
        """Message field 'map_version'."""
        return self._map_version

    @map_version.setter
    def map_version(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'map_version' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'map_version' field must be an unsigned integer in [0, 18446744073709551615]"
        self._map_version = value

    @builtins.property
    def map_path(self):
        """Message field 'map_path'."""
        return self._map_path

    @map_path.setter
    def map_path(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'map_path' field must be of type 'str'"
        self._map_path = value

    @builtins.property
    def data(self):
        """Message field 'data'."""
        return self._data

    @data.setter
    def data(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'b', \
                "The 'data' array.array() must have the type code of 'b'"
            self._data = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -128 and val < 128 for val in value)), \
                "The 'data' field must be a set or sequence and each value of type 'int' and each integer in [-128, 127]"
        self._data = array.array('b', value)

    @builtins.property
    def navi_points(self):
        """Message field 'navi_points'."""
        return self._navi_points

    @navi_points.setter
    def navi_points(self, value):
        if __debug__:
            from aimdk_msgs.msg import NaviPoint
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
                 all(isinstance(v, NaviPoint) for v in value) and
                 True), \
                "The 'navi_points' field must be a set or sequence and each value of type 'NaviPoint'"
        self._navi_points = value

    @builtins.property
    def qr_points(self):
        """Message field 'qr_points'."""
        return self._qr_points

    @qr_points.setter
    def qr_points(self, value):
        if __debug__:
            from aimdk_msgs.msg import QRPoint
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
                 all(isinstance(v, QRPoint) for v in value) and
                 True), \
                "The 'qr_points' field must be a set or sequence and each value of type 'QRPoint'"
        self._qr_points = value

    @builtins.property
    def hr_points(self):
        """Message field 'hr_points'."""
        return self._hr_points

    @hr_points.setter
    def hr_points(self, value):
        if __debug__:
            from aimdk_msgs.msg import HRPoint
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
                 all(isinstance(v, HRPoint) for v in value) and
                 True), \
                "The 'hr_points' field must be a set or sequence and each value of type 'HRPoint'"
        self._hr_points = value

    @builtins.property
    def paths(self):
        """Message field 'paths'."""
        return self._paths

    @paths.setter
    def paths(self, value):
        if __debug__:
            from aimdk_msgs.msg import Path
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
                 all(isinstance(v, Path) for v in value) and
                 True), \
                "The 'paths' field must be a set or sequence and each value of type 'Path'"
        self._paths = value

    @builtins.property
    def regions(self):
        """Message field 'regions'."""
        return self._regions

    @regions.setter
    def regions(self, value):
        if __debug__:
            from aimdk_msgs.msg import Region
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
                 all(isinstance(v, Region) for v in value) and
                 True), \
                "The 'regions' field must be a set or sequence and each value of type 'Region'"
        self._regions = value

    @builtins.property
    def map_id(self):
        """Message field 'map_id'."""
        return self._map_id

    @map_id.setter
    def map_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'map_id' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'map_id' field must be an unsigned integer in [0, 18446744073709551615]"
        self._map_id = value


class Metaclass_GetStoredMapByName(type):
    """Metaclass of service 'GetStoredMapByName'."""

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
                'aimdk_msgs.srv.GetStoredMapByName')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_stored_map_by_name

            from aimdk_msgs.srv import _get_stored_map_by_name
            if _get_stored_map_by_name.Metaclass_GetStoredMapByName_Request._TYPE_SUPPORT is None:
                _get_stored_map_by_name.Metaclass_GetStoredMapByName_Request.__import_type_support__()
            if _get_stored_map_by_name.Metaclass_GetStoredMapByName_Response._TYPE_SUPPORT is None:
                _get_stored_map_by_name.Metaclass_GetStoredMapByName_Response.__import_type_support__()


class GetStoredMapByName(metaclass=Metaclass_GetStoredMapByName):
    from aimdk_msgs.srv._get_stored_map_by_name import GetStoredMapByName_Request as Request
    from aimdk_msgs.srv._get_stored_map_by_name import GetStoredMapByName_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

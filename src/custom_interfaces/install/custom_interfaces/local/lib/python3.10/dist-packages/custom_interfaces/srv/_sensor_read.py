# generated from rosidl_generator_py/resource/_idl.py.em
# with input from custom_interfaces:srv/SensorRead.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SensorRead_Request(type):
    """Metaclass of message 'SensorRead_Request'."""

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
            module = import_type_support('custom_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'custom_interfaces.srv.SensorRead_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__sensor_read__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__sensor_read__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__sensor_read__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__sensor_read__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__sensor_read__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SensorRead_Request(metaclass=Metaclass_SensorRead_Request):
    """Message class 'SensorRead_Request'."""

    __slots__ = [
        '_num_samples',
    ]

    _fields_and_field_types = {
        'num_samples': 'int8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.num_samples = kwargs.get('num_samples', int())

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
        if self.num_samples != other.num_samples:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def num_samples(self):
        """Message field 'num_samples'."""
        return self._num_samples

    @num_samples.setter
    def num_samples(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num_samples' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'num_samples' field must be an integer in [-128, 127]"
        self._num_samples = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SensorRead_Response(type):
    """Metaclass of message 'SensorRead_Response'."""

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
            module = import_type_support('custom_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'custom_interfaces.srv.SensorRead_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__sensor_read__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__sensor_read__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__sensor_read__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__sensor_read__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__sensor_read__response

            from custom_interfaces.msg import SensorSample
            if SensorSample.__class__._TYPE_SUPPORT is None:
                SensorSample.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SensorRead_Response(metaclass=Metaclass_SensorRead_Response):
    """Message class 'SensorRead_Response'."""

    __slots__ = [
        '_readings',
    ]

    _fields_and_field_types = {
        'readings': 'sequence<custom_interfaces/SensorSample, 8>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['custom_interfaces', 'msg'], 'SensorSample'), 8),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.readings = kwargs.get('readings', [])

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
        if self.readings != other.readings:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def readings(self):
        """Message field 'readings'."""
        return self._readings

    @readings.setter
    def readings(self, value):
        if __debug__:
            from custom_interfaces.msg import SensorSample
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
                 len(value) <= 8 and
                 all(isinstance(v, SensorSample) for v in value) and
                 True), \
                "The 'readings' field must be a set or sequence with length <= 8 and each value of type 'SensorSample'"
        self._readings = value


class Metaclass_SensorRead(type):
    """Metaclass of service 'SensorRead'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('custom_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'custom_interfaces.srv.SensorRead')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__sensor_read

            from custom_interfaces.srv import _sensor_read
            if _sensor_read.Metaclass_SensorRead_Request._TYPE_SUPPORT is None:
                _sensor_read.Metaclass_SensorRead_Request.__import_type_support__()
            if _sensor_read.Metaclass_SensorRead_Response._TYPE_SUPPORT is None:
                _sensor_read.Metaclass_SensorRead_Response.__import_type_support__()


class SensorRead(metaclass=Metaclass_SensorRead):
    from custom_interfaces.srv._sensor_read import SensorRead_Request as Request
    from custom_interfaces.srv._sensor_read import SensorRead_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

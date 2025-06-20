# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vyra_module_interfaces:msg/LoggerStream.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_LoggerStream(type):
    """Metaclass of message 'LoggerStream'."""

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
            module = import_type_support('vyra_module_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vyra_module_interfaces.msg.LoggerStream')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__logger_stream
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__logger_stream
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__logger_stream
            cls._TYPE_SUPPORT = module.type_support_msg__msg__logger_stream
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__logger_stream

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class LoggerStream(metaclass=Metaclass_LoggerStream):
    """Message class 'LoggerStream'."""

    __slots__ = [
        '_log_level',
        '_log_message',
        '_timestamp',
    ]

    _fields_and_field_types = {
        'log_level': 'string',
        'log_message': 'string',
        'timestamp': 'builtin_interfaces/Time',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.log_level = kwargs.get('log_level', str())
        self.log_message = kwargs.get('log_message', str())
        from builtin_interfaces.msg import Time
        self.timestamp = kwargs.get('timestamp', Time())

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
        if self.log_level != other.log_level:
            return False
        if self.log_message != other.log_message:
            return False
        if self.timestamp != other.timestamp:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def log_level(self):
        """Message field 'log_level'."""
        return self._log_level

    @log_level.setter
    def log_level(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'log_level' field must be of type 'str'"
        self._log_level = value

    @builtins.property
    def log_message(self):
        """Message field 'log_message'."""
        return self._log_message

    @log_message.setter
    def log_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'log_message' field must be of type 'str'"
        self._log_message = value

    @builtins.property
    def timestamp(self):
        """Message field 'timestamp'."""
        return self._timestamp

    @timestamp.setter
    def timestamp(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'timestamp' field must be a sub message of type 'Time'"
        self._timestamp = value

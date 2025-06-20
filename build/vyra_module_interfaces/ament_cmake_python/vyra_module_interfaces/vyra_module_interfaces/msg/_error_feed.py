# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vyra_module_interfaces:msg/ErrorFeed.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ErrorFeed(type):
    """Metaclass of message 'ErrorFeed'."""

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
                'vyra_module_interfaces.msg.ErrorFeed')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__error_feed
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__error_feed
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__error_feed
            cls._TYPE_SUPPORT = module.type_support_msg__msg__error_feed
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__error_feed

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


class ErrorFeed(metaclass=Metaclass_ErrorFeed):
    """Message class 'ErrorFeed'."""

    __slots__ = [
        '_error_code',
        '_module_id',
        '_description',
        '_solution',
        '_miscellaneous',
        '_timestamp',
    ]

    _fields_and_field_types = {
        'error_code': 'uint32',
        'module_id': 'string',
        'description': 'string',
        'solution': 'string',
        'miscellaneous': 'string',
        'timestamp': 'builtin_interfaces/Time',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.error_code = kwargs.get('error_code', int())
        self.module_id = kwargs.get('module_id', str())
        self.description = kwargs.get('description', str())
        self.solution = kwargs.get('solution', str())
        self.miscellaneous = kwargs.get('miscellaneous', str())
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
        if self.error_code != other.error_code:
            return False
        if self.module_id != other.module_id:
            return False
        if self.description != other.description:
            return False
        if self.solution != other.solution:
            return False
        if self.miscellaneous != other.miscellaneous:
            return False
        if self.timestamp != other.timestamp:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def error_code(self):
        """Message field 'error_code'."""
        return self._error_code

    @error_code.setter
    def error_code(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'error_code' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'error_code' field must be an unsigned integer in [0, 4294967295]"
        self._error_code = value

    @builtins.property
    def module_id(self):
        """Message field 'module_id'."""
        return self._module_id

    @module_id.setter
    def module_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'module_id' field must be of type 'str'"
        self._module_id = value

    @builtins.property
    def description(self):
        """Message field 'description'."""
        return self._description

    @description.setter
    def description(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'description' field must be of type 'str'"
        self._description = value

    @builtins.property
    def solution(self):
        """Message field 'solution'."""
        return self._solution

    @solution.setter
    def solution(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'solution' field must be of type 'str'"
        self._solution = value

    @builtins.property
    def miscellaneous(self):
        """Message field 'miscellaneous'."""
        return self._miscellaneous

    @miscellaneous.setter
    def miscellaneous(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'miscellaneous' field must be of type 'str'"
        self._miscellaneous = value

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

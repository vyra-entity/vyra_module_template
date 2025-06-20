# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vyra_module_interfaces:srv/GetLogs.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetLogs_Request(type):
    """Metaclass of message 'GetLogs_Request'."""

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
                'vyra_module_interfaces.srv.GetLogs_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_logs__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_logs__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_logs__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_logs__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_logs__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetLogs_Request(metaclass=Metaclass_GetLogs_Request):
    """Message class 'GetLogs_Request'."""

    __slots__ = [
        '_log_lines',
        '_log_level',
    ]

    _fields_and_field_types = {
        'log_lines': 'int32',
        'log_level': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.log_lines = kwargs.get('log_lines', int())
        self.log_level = kwargs.get('log_level', int())

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
        if self.log_lines != other.log_lines:
            return False
        if self.log_level != other.log_level:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def log_lines(self):
        """Message field 'log_lines'."""
        return self._log_lines

    @log_lines.setter
    def log_lines(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'log_lines' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'log_lines' field must be an integer in [-2147483648, 2147483647]"
        self._log_lines = value

    @builtins.property
    def log_level(self):
        """Message field 'log_level'."""
        return self._log_level

    @log_level.setter
    def log_level(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'log_level' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'log_level' field must be an unsigned integer in [0, 255]"
        self._log_level = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_GetLogs_Response(type):
    """Metaclass of message 'GetLogs_Response'."""

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
                'vyra_module_interfaces.srv.GetLogs_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_logs__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_logs__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_logs__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_logs__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_logs__response

            from vyra_module_interfaces.msg import LoggerStream
            if LoggerStream.__class__._TYPE_SUPPORT is None:
                LoggerStream.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetLogs_Response(metaclass=Metaclass_GetLogs_Response):
    """Message class 'GetLogs_Response'."""

    __slots__ = [
        '_log_messages',
    ]

    _fields_and_field_types = {
        'log_messages': 'sequence<vyra_module_interfaces/LoggerStream>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['vyra_module_interfaces', 'msg'], 'LoggerStream')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.log_messages = kwargs.get('log_messages', [])

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
        if self.log_messages != other.log_messages:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def log_messages(self):
        """Message field 'log_messages'."""
        return self._log_messages

    @log_messages.setter
    def log_messages(self, value):
        if __debug__:
            from vyra_module_interfaces.msg import LoggerStream
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
                 all(isinstance(v, LoggerStream) for v in value) and
                 True), \
                "The 'log_messages' field must be a set or sequence and each value of type 'LoggerStream'"
        self._log_messages = value


class Metaclass_GetLogs(type):
    """Metaclass of service 'GetLogs'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('vyra_module_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vyra_module_interfaces.srv.GetLogs')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_logs

            from vyra_module_interfaces.srv import _get_logs
            if _get_logs.Metaclass_GetLogs_Request._TYPE_SUPPORT is None:
                _get_logs.Metaclass_GetLogs_Request.__import_type_support__()
            if _get_logs.Metaclass_GetLogs_Response._TYPE_SUPPORT is None:
                _get_logs.Metaclass_GetLogs_Response.__import_type_support__()


class GetLogs(metaclass=Metaclass_GetLogs):
    from vyra_module_interfaces.srv._get_logs import GetLogs_Request as Request
    from vyra_module_interfaces.srv._get_logs import GetLogs_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

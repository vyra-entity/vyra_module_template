# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vyra_module_interfaces:srv/GetCapabilities.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetCapabilities_Request(type):
    """Metaclass of message 'GetCapabilities_Request'."""

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
                'vyra_module_interfaces.srv.GetCapabilities_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_capabilities__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_capabilities__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_capabilities__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_capabilities__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_capabilities__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetCapabilities_Request(metaclass=Metaclass_GetCapabilities_Request):
    """Message class 'GetCapabilities_Request'."""

    __slots__ = [
    ]

    _fields_and_field_types = {
    }

    SLOT_TYPES = (
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))

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
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)


# Import statements for member types

import builtins  # noqa: E402, I100

# already imported above
# import rosidl_parser.definition


class Metaclass_GetCapabilities_Response(type):
    """Metaclass of message 'GetCapabilities_Response'."""

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
                'vyra_module_interfaces.srv.GetCapabilities_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_capabilities__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_capabilities__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_capabilities__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_capabilities__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_capabilities__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetCapabilities_Response(metaclass=Metaclass_GetCapabilities_Response):
    """Message class 'GetCapabilities_Response'."""

    __slots__ = [
        '_capabilities',
    ]

    _fields_and_field_types = {
        'capabilities': 'sequence<string>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.capabilities = kwargs.get('capabilities', [])

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
        if self.capabilities != other.capabilities:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def capabilities(self):
        """Message field 'capabilities'."""
        return self._capabilities

    @capabilities.setter
    def capabilities(self, value):
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
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'capabilities' field must be a set or sequence and each value of type 'str'"
        self._capabilities = value


class Metaclass_GetCapabilities(type):
    """Metaclass of service 'GetCapabilities'."""

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
                'vyra_module_interfaces.srv.GetCapabilities')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_capabilities

            from vyra_module_interfaces.srv import _get_capabilities
            if _get_capabilities.Metaclass_GetCapabilities_Request._TYPE_SUPPORT is None:
                _get_capabilities.Metaclass_GetCapabilities_Request.__import_type_support__()
            if _get_capabilities.Metaclass_GetCapabilities_Response._TYPE_SUPPORT is None:
                _get_capabilities.Metaclass_GetCapabilities_Response.__import_type_support__()


class GetCapabilities(metaclass=Metaclass_GetCapabilities):
    from vyra_module_interfaces.srv._get_capabilities import GetCapabilities_Request as Request
    from vyra_module_interfaces.srv._get_capabilities import GetCapabilities_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

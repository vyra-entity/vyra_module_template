# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vos_module_interfaces:srv/HealthCheck.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_HealthCheck_Request(type):
    """Metaclass of message 'HealthCheck_Request'."""

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
            module = import_type_support('vos_module_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vos_module_interfaces.srv.HealthCheck_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__health_check__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__health_check__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__health_check__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__health_check__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__health_check__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class HealthCheck_Request(metaclass=Metaclass_HealthCheck_Request):
    """Message class 'HealthCheck_Request'."""

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


class Metaclass_HealthCheck_Response(type):
    """Metaclass of message 'HealthCheck_Response'."""

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
            module = import_type_support('vos_module_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vos_module_interfaces.srv.HealthCheck_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__health_check__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__health_check__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__health_check__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__health_check__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__health_check__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class HealthCheck_Response(metaclass=Metaclass_HealthCheck_Response):
    """Message class 'HealthCheck_Response'."""

    __slots__ = [
        '_alive',
        '_state',
        '_health_status',
        '_issues',
    ]

    _fields_and_field_types = {
        'alive': 'boolean',
        'state': 'string',
        'health_status': 'string',
        'issues': 'sequence<string>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.alive = kwargs.get('alive', bool())
        self.state = kwargs.get('state', str())
        self.health_status = kwargs.get('health_status', str())
        self.issues = kwargs.get('issues', [])

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
        if self.alive != other.alive:
            return False
        if self.state != other.state:
            return False
        if self.health_status != other.health_status:
            return False
        if self.issues != other.issues:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def alive(self):
        """Message field 'alive'."""
        return self._alive

    @alive.setter
    def alive(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'alive' field must be of type 'bool'"
        self._alive = value

    @builtins.property
    def state(self):
        """Message field 'state'."""
        return self._state

    @state.setter
    def state(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'state' field must be of type 'str'"
        self._state = value

    @builtins.property
    def health_status(self):
        """Message field 'health_status'."""
        return self._health_status

    @health_status.setter
    def health_status(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'health_status' field must be of type 'str'"
        self._health_status = value

    @builtins.property
    def issues(self):
        """Message field 'issues'."""
        return self._issues

    @issues.setter
    def issues(self, value):
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
                "The 'issues' field must be a set or sequence and each value of type 'str'"
        self._issues = value


class Metaclass_HealthCheck(type):
    """Metaclass of service 'HealthCheck'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('vos_module_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vos_module_interfaces.srv.HealthCheck')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__health_check

            from vos_module_interfaces.srv import _health_check
            if _health_check.Metaclass_HealthCheck_Request._TYPE_SUPPORT is None:
                _health_check.Metaclass_HealthCheck_Request.__import_type_support__()
            if _health_check.Metaclass_HealthCheck_Response._TYPE_SUPPORT is None:
                _health_check.Metaclass_HealthCheck_Response.__import_type_support__()


class HealthCheck(metaclass=Metaclass_HealthCheck):
    from vos_module_interfaces.srv._health_check import HealthCheck_Request as Request
    from vos_module_interfaces.srv._health_check import HealthCheck_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

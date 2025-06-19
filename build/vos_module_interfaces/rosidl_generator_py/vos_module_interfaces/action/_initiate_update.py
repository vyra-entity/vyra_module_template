# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vos_module_interfaces:action/InitiateUpdate.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_InitiateUpdate_Goal(type):
    """Metaclass of message 'InitiateUpdate_Goal'."""

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
                'vos_module_interfaces.action.InitiateUpdate_Goal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__initiate_update__goal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__initiate_update__goal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__initiate_update__goal
            cls._TYPE_SUPPORT = module.type_support_msg__action__initiate_update__goal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__initiate_update__goal

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class InitiateUpdate_Goal(metaclass=Metaclass_InitiateUpdate_Goal):
    """Message class 'InitiateUpdate_Goal'."""

    __slots__ = [
        '_module_name',
        '_update_url',
        '_target_version',
        '_force',
        '_expected_hash',
    ]

    _fields_and_field_types = {
        'module_name': 'string',
        'update_url': 'string',
        'target_version': 'string',
        'force': 'boolean',
        'expected_hash': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.module_name = kwargs.get('module_name', str())
        self.update_url = kwargs.get('update_url', str())
        self.target_version = kwargs.get('target_version', str())
        self.force = kwargs.get('force', bool())
        self.expected_hash = kwargs.get('expected_hash', str())

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
        if self.module_name != other.module_name:
            return False
        if self.update_url != other.update_url:
            return False
        if self.target_version != other.target_version:
            return False
        if self.force != other.force:
            return False
        if self.expected_hash != other.expected_hash:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def module_name(self):
        """Message field 'module_name'."""
        return self._module_name

    @module_name.setter
    def module_name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'module_name' field must be of type 'str'"
        self._module_name = value

    @builtins.property
    def update_url(self):
        """Message field 'update_url'."""
        return self._update_url

    @update_url.setter
    def update_url(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'update_url' field must be of type 'str'"
        self._update_url = value

    @builtins.property
    def target_version(self):
        """Message field 'target_version'."""
        return self._target_version

    @target_version.setter
    def target_version(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'target_version' field must be of type 'str'"
        self._target_version = value

    @builtins.property
    def force(self):
        """Message field 'force'."""
        return self._force

    @force.setter
    def force(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'force' field must be of type 'bool'"
        self._force = value

    @builtins.property
    def expected_hash(self):
        """Message field 'expected_hash'."""
        return self._expected_hash

    @expected_hash.setter
    def expected_hash(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'expected_hash' field must be of type 'str'"
        self._expected_hash = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_InitiateUpdate_Result(type):
    """Metaclass of message 'InitiateUpdate_Result'."""

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
                'vos_module_interfaces.action.InitiateUpdate_Result')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__initiate_update__result
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__initiate_update__result
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__initiate_update__result
            cls._TYPE_SUPPORT = module.type_support_msg__action__initiate_update__result
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__initiate_update__result

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class InitiateUpdate_Result(metaclass=Metaclass_InitiateUpdate_Result):
    """Message class 'InitiateUpdate_Result'."""

    __slots__ = [
        '_success',
        '_report',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'report': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.report = kwargs.get('report', str())

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
        if self.success != other.success:
            return False
        if self.report != other.report:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

    @builtins.property
    def report(self):
        """Message field 'report'."""
        return self._report

    @report.setter
    def report(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'report' field must be of type 'str'"
        self._report = value


# Import statements for member types

# already imported above
# import builtins

import math  # noqa: E402, I100

# already imported above
# import rosidl_parser.definition


class Metaclass_InitiateUpdate_Feedback(type):
    """Metaclass of message 'InitiateUpdate_Feedback'."""

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
                'vos_module_interfaces.action.InitiateUpdate_Feedback')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__initiate_update__feedback
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__initiate_update__feedback
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__initiate_update__feedback
            cls._TYPE_SUPPORT = module.type_support_msg__action__initiate_update__feedback
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__initiate_update__feedback

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class InitiateUpdate_Feedback(metaclass=Metaclass_InitiateUpdate_Feedback):
    """Message class 'InitiateUpdate_Feedback'."""

    __slots__ = [
        '_status_message',
        '_progress_percentage',
    ]

    _fields_and_field_types = {
        'status_message': 'string',
        'progress_percentage': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status_message = kwargs.get('status_message', str())
        self.progress_percentage = kwargs.get('progress_percentage', float())

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
        if self.status_message != other.status_message:
            return False
        if self.progress_percentage != other.progress_percentage:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def status_message(self):
        """Message field 'status_message'."""
        return self._status_message

    @status_message.setter
    def status_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'status_message' field must be of type 'str'"
        self._status_message = value

    @builtins.property
    def progress_percentage(self):
        """Message field 'progress_percentage'."""
        return self._progress_percentage

    @progress_percentage.setter
    def progress_percentage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'progress_percentage' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'progress_percentage' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._progress_percentage = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_InitiateUpdate_SendGoal_Request(type):
    """Metaclass of message 'InitiateUpdate_SendGoal_Request'."""

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
                'vos_module_interfaces.action.InitiateUpdate_SendGoal_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__initiate_update__send_goal__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__initiate_update__send_goal__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__initiate_update__send_goal__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__initiate_update__send_goal__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__initiate_update__send_goal__request

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

            from vos_module_interfaces.action import InitiateUpdate
            if InitiateUpdate.Goal.__class__._TYPE_SUPPORT is None:
                InitiateUpdate.Goal.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class InitiateUpdate_SendGoal_Request(metaclass=Metaclass_InitiateUpdate_SendGoal_Request):
    """Message class 'InitiateUpdate_SendGoal_Request'."""

    __slots__ = [
        '_goal_id',
        '_goal',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'goal': 'vos_module_interfaces/InitiateUpdate_Goal',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vos_module_interfaces', 'action'], 'InitiateUpdate_Goal'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from vos_module_interfaces.action._initiate_update import InitiateUpdate_Goal
        self.goal = kwargs.get('goal', InitiateUpdate_Goal())

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
        if self.goal_id != other.goal_id:
            return False
        if self.goal != other.goal:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value

    @builtins.property
    def goal(self):
        """Message field 'goal'."""
        return self._goal

    @goal.setter
    def goal(self, value):
        if __debug__:
            from vos_module_interfaces.action._initiate_update import InitiateUpdate_Goal
            assert \
                isinstance(value, InitiateUpdate_Goal), \
                "The 'goal' field must be a sub message of type 'InitiateUpdate_Goal'"
        self._goal = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_InitiateUpdate_SendGoal_Response(type):
    """Metaclass of message 'InitiateUpdate_SendGoal_Response'."""

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
                'vos_module_interfaces.action.InitiateUpdate_SendGoal_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__initiate_update__send_goal__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__initiate_update__send_goal__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__initiate_update__send_goal__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__initiate_update__send_goal__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__initiate_update__send_goal__response

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


class InitiateUpdate_SendGoal_Response(metaclass=Metaclass_InitiateUpdate_SendGoal_Response):
    """Message class 'InitiateUpdate_SendGoal_Response'."""

    __slots__ = [
        '_accepted',
        '_stamp',
    ]

    _fields_and_field_types = {
        'accepted': 'boolean',
        'stamp': 'builtin_interfaces/Time',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.accepted = kwargs.get('accepted', bool())
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())

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
        if self.accepted != other.accepted:
            return False
        if self.stamp != other.stamp:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def accepted(self):
        """Message field 'accepted'."""
        return self._accepted

    @accepted.setter
    def accepted(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'accepted' field must be of type 'bool'"
        self._accepted = value

    @builtins.property
    def stamp(self):
        """Message field 'stamp'."""
        return self._stamp

    @stamp.setter
    def stamp(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'stamp' field must be a sub message of type 'Time'"
        self._stamp = value


class Metaclass_InitiateUpdate_SendGoal(type):
    """Metaclass of service 'InitiateUpdate_SendGoal'."""

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
                'vos_module_interfaces.action.InitiateUpdate_SendGoal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__initiate_update__send_goal

            from vos_module_interfaces.action import _initiate_update
            if _initiate_update.Metaclass_InitiateUpdate_SendGoal_Request._TYPE_SUPPORT is None:
                _initiate_update.Metaclass_InitiateUpdate_SendGoal_Request.__import_type_support__()
            if _initiate_update.Metaclass_InitiateUpdate_SendGoal_Response._TYPE_SUPPORT is None:
                _initiate_update.Metaclass_InitiateUpdate_SendGoal_Response.__import_type_support__()


class InitiateUpdate_SendGoal(metaclass=Metaclass_InitiateUpdate_SendGoal):
    from vos_module_interfaces.action._initiate_update import InitiateUpdate_SendGoal_Request as Request
    from vos_module_interfaces.action._initiate_update import InitiateUpdate_SendGoal_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_InitiateUpdate_GetResult_Request(type):
    """Metaclass of message 'InitiateUpdate_GetResult_Request'."""

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
                'vos_module_interfaces.action.InitiateUpdate_GetResult_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__initiate_update__get_result__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__initiate_update__get_result__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__initiate_update__get_result__request
            cls._TYPE_SUPPORT = module.type_support_msg__action__initiate_update__get_result__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__initiate_update__get_result__request

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class InitiateUpdate_GetResult_Request(metaclass=Metaclass_InitiateUpdate_GetResult_Request):
    """Message class 'InitiateUpdate_GetResult_Request'."""

    __slots__ = [
        '_goal_id',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())

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
        if self.goal_id != other.goal_id:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_InitiateUpdate_GetResult_Response(type):
    """Metaclass of message 'InitiateUpdate_GetResult_Response'."""

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
                'vos_module_interfaces.action.InitiateUpdate_GetResult_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__initiate_update__get_result__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__initiate_update__get_result__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__initiate_update__get_result__response
            cls._TYPE_SUPPORT = module.type_support_msg__action__initiate_update__get_result__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__initiate_update__get_result__response

            from vos_module_interfaces.action import InitiateUpdate
            if InitiateUpdate.Result.__class__._TYPE_SUPPORT is None:
                InitiateUpdate.Result.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class InitiateUpdate_GetResult_Response(metaclass=Metaclass_InitiateUpdate_GetResult_Response):
    """Message class 'InitiateUpdate_GetResult_Response'."""

    __slots__ = [
        '_status',
        '_result',
    ]

    _fields_and_field_types = {
        'status': 'int8',
        'result': 'vos_module_interfaces/InitiateUpdate_Result',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vos_module_interfaces', 'action'], 'InitiateUpdate_Result'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', int())
        from vos_module_interfaces.action._initiate_update import InitiateUpdate_Result
        self.result = kwargs.get('result', InitiateUpdate_Result())

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
        if self.status != other.status:
            return False
        if self.result != other.result:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'status' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'status' field must be an integer in [-128, 127]"
        self._status = value

    @builtins.property
    def result(self):
        """Message field 'result'."""
        return self._result

    @result.setter
    def result(self, value):
        if __debug__:
            from vos_module_interfaces.action._initiate_update import InitiateUpdate_Result
            assert \
                isinstance(value, InitiateUpdate_Result), \
                "The 'result' field must be a sub message of type 'InitiateUpdate_Result'"
        self._result = value


class Metaclass_InitiateUpdate_GetResult(type):
    """Metaclass of service 'InitiateUpdate_GetResult'."""

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
                'vos_module_interfaces.action.InitiateUpdate_GetResult')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__action__initiate_update__get_result

            from vos_module_interfaces.action import _initiate_update
            if _initiate_update.Metaclass_InitiateUpdate_GetResult_Request._TYPE_SUPPORT is None:
                _initiate_update.Metaclass_InitiateUpdate_GetResult_Request.__import_type_support__()
            if _initiate_update.Metaclass_InitiateUpdate_GetResult_Response._TYPE_SUPPORT is None:
                _initiate_update.Metaclass_InitiateUpdate_GetResult_Response.__import_type_support__()


class InitiateUpdate_GetResult(metaclass=Metaclass_InitiateUpdate_GetResult):
    from vos_module_interfaces.action._initiate_update import InitiateUpdate_GetResult_Request as Request
    from vos_module_interfaces.action._initiate_update import InitiateUpdate_GetResult_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_InitiateUpdate_FeedbackMessage(type):
    """Metaclass of message 'InitiateUpdate_FeedbackMessage'."""

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
                'vos_module_interfaces.action.InitiateUpdate_FeedbackMessage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__action__initiate_update__feedback_message
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__action__initiate_update__feedback_message
            cls._CONVERT_TO_PY = module.convert_to_py_msg__action__initiate_update__feedback_message
            cls._TYPE_SUPPORT = module.type_support_msg__action__initiate_update__feedback_message
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__action__initiate_update__feedback_message

            from unique_identifier_msgs.msg import UUID
            if UUID.__class__._TYPE_SUPPORT is None:
                UUID.__class__.__import_type_support__()

            from vos_module_interfaces.action import InitiateUpdate
            if InitiateUpdate.Feedback.__class__._TYPE_SUPPORT is None:
                InitiateUpdate.Feedback.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class InitiateUpdate_FeedbackMessage(metaclass=Metaclass_InitiateUpdate_FeedbackMessage):
    """Message class 'InitiateUpdate_FeedbackMessage'."""

    __slots__ = [
        '_goal_id',
        '_feedback',
    ]

    _fields_and_field_types = {
        'goal_id': 'unique_identifier_msgs/UUID',
        'feedback': 'vos_module_interfaces/InitiateUpdate_Feedback',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['unique_identifier_msgs', 'msg'], 'UUID'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vos_module_interfaces', 'action'], 'InitiateUpdate_Feedback'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from unique_identifier_msgs.msg import UUID
        self.goal_id = kwargs.get('goal_id', UUID())
        from vos_module_interfaces.action._initiate_update import InitiateUpdate_Feedback
        self.feedback = kwargs.get('feedback', InitiateUpdate_Feedback())

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
        if self.goal_id != other.goal_id:
            return False
        if self.feedback != other.feedback:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def goal_id(self):
        """Message field 'goal_id'."""
        return self._goal_id

    @goal_id.setter
    def goal_id(self, value):
        if __debug__:
            from unique_identifier_msgs.msg import UUID
            assert \
                isinstance(value, UUID), \
                "The 'goal_id' field must be a sub message of type 'UUID'"
        self._goal_id = value

    @builtins.property
    def feedback(self):
        """Message field 'feedback'."""
        return self._feedback

    @feedback.setter
    def feedback(self, value):
        if __debug__:
            from vos_module_interfaces.action._initiate_update import InitiateUpdate_Feedback
            assert \
                isinstance(value, InitiateUpdate_Feedback), \
                "The 'feedback' field must be a sub message of type 'InitiateUpdate_Feedback'"
        self._feedback = value


class Metaclass_InitiateUpdate(type):
    """Metaclass of action 'InitiateUpdate'."""

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
                'vos_module_interfaces.action.InitiateUpdate')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_action__action__initiate_update

            from action_msgs.msg import _goal_status_array
            if _goal_status_array.Metaclass_GoalStatusArray._TYPE_SUPPORT is None:
                _goal_status_array.Metaclass_GoalStatusArray.__import_type_support__()
            from action_msgs.srv import _cancel_goal
            if _cancel_goal.Metaclass_CancelGoal._TYPE_SUPPORT is None:
                _cancel_goal.Metaclass_CancelGoal.__import_type_support__()

            from vos_module_interfaces.action import _initiate_update
            if _initiate_update.Metaclass_InitiateUpdate_SendGoal._TYPE_SUPPORT is None:
                _initiate_update.Metaclass_InitiateUpdate_SendGoal.__import_type_support__()
            if _initiate_update.Metaclass_InitiateUpdate_GetResult._TYPE_SUPPORT is None:
                _initiate_update.Metaclass_InitiateUpdate_GetResult.__import_type_support__()
            if _initiate_update.Metaclass_InitiateUpdate_FeedbackMessage._TYPE_SUPPORT is None:
                _initiate_update.Metaclass_InitiateUpdate_FeedbackMessage.__import_type_support__()


class InitiateUpdate(metaclass=Metaclass_InitiateUpdate):

    # The goal message defined in the action definition.
    from vos_module_interfaces.action._initiate_update import InitiateUpdate_Goal as Goal
    # The result message defined in the action definition.
    from vos_module_interfaces.action._initiate_update import InitiateUpdate_Result as Result
    # The feedback message defined in the action definition.
    from vos_module_interfaces.action._initiate_update import InitiateUpdate_Feedback as Feedback

    class Impl:

        # The send_goal service using a wrapped version of the goal message as a request.
        from vos_module_interfaces.action._initiate_update import InitiateUpdate_SendGoal as SendGoalService
        # The get_result service using a wrapped version of the result message as a response.
        from vos_module_interfaces.action._initiate_update import InitiateUpdate_GetResult as GetResultService
        # The feedback message with generic fields which wraps the feedback message.
        from vos_module_interfaces.action._initiate_update import InitiateUpdate_FeedbackMessage as FeedbackMessage

        # The generic service to cancel a goal.
        from action_msgs.srv._cancel_goal import CancelGoal as CancelGoalService
        # The generic message for get the status of a goal.
        from action_msgs.msg._goal_status_array import GoalStatusArray as GoalStatusMessage

    def __init__(self):
        raise NotImplementedError('Action classes can not be instantiated')

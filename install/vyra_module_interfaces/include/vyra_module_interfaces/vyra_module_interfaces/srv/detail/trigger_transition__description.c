// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vyra_module_interfaces:srv/TriggerTransition.idl
// generated code does not contain a copyright notice

#include "vyra_module_interfaces/srv/detail/trigger_transition__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__TriggerTransition__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x17, 0xd9, 0xd9, 0x56, 0x2e, 0xfb, 0xfe, 0xfe,
      0xaf, 0x26, 0x89, 0xd1, 0x07, 0xb1, 0xbe, 0x1b,
      0xe3, 0xb5, 0x35, 0xc2, 0x9a, 0x3f, 0x7d, 0x75,
      0xd4, 0x95, 0x4f, 0x6c, 0xa5, 0x23, 0x99, 0xb0,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__TriggerTransition_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xa7, 0x23, 0xfb, 0x58, 0xbd, 0x61, 0x93, 0xc0,
      0x74, 0x75, 0x51, 0x32, 0x26, 0x77, 0x00, 0xc0,
      0x65, 0x05, 0x00, 0x4c, 0xee, 0x89, 0x66, 0x8f,
      0xab, 0x3b, 0xc3, 0xc0, 0xa5, 0xbe, 0x6a, 0xd8,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__TriggerTransition_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6d, 0xaa, 0x41, 0xef, 0x2b, 0x40, 0xd8, 0x1d,
      0x00, 0x6a, 0xc9, 0x25, 0xd1, 0xd1, 0x1b, 0x95,
      0xa2, 0x51, 0x33, 0xea, 0xff, 0xbf, 0xfd, 0x02,
      0x80, 0x19, 0x0c, 0x71, 0xea, 0xcc, 0xa9, 0x86,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__TriggerTransition_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x07, 0x5e, 0xad, 0xb8, 0x28, 0x05, 0x7f, 0xc0,
      0x22, 0xad, 0xf3, 0x87, 0xdf, 0x14, 0xac, 0xba,
      0xab, 0x71, 0x78, 0xcf, 0xc1, 0x4a, 0x0f, 0x7c,
      0x2c, 0x8c, 0xbd, 0x81, 0x29, 0x0f, 0xd4, 0x38,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char vyra_module_interfaces__srv__TriggerTransition__TYPE_NAME[] = "vyra_module_interfaces/srv/TriggerTransition";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";
static char vyra_module_interfaces__srv__TriggerTransition_Event__TYPE_NAME[] = "vyra_module_interfaces/srv/TriggerTransition_Event";
static char vyra_module_interfaces__srv__TriggerTransition_Request__TYPE_NAME[] = "vyra_module_interfaces/srv/TriggerTransition_Request";
static char vyra_module_interfaces__srv__TriggerTransition_Response__TYPE_NAME[] = "vyra_module_interfaces/srv/TriggerTransition_Response";

// Define type names, field names, and default values
static char vyra_module_interfaces__srv__TriggerTransition__FIELD_NAME__request_message[] = "request_message";
static char vyra_module_interfaces__srv__TriggerTransition__FIELD_NAME__response_message[] = "response_message";
static char vyra_module_interfaces__srv__TriggerTransition__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__TriggerTransition__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__TriggerTransition__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vyra_module_interfaces__srv__TriggerTransition_Request__TYPE_NAME, 52, 52},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__TriggerTransition__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vyra_module_interfaces__srv__TriggerTransition_Response__TYPE_NAME, 53, 53},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__TriggerTransition__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vyra_module_interfaces__srv__TriggerTransition_Event__TYPE_NAME, 50, 50},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vyra_module_interfaces__srv__TriggerTransition__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__TriggerTransition_Event__TYPE_NAME, 50, 50},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__TriggerTransition_Request__TYPE_NAME, 52, 52},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__TriggerTransition_Response__TYPE_NAME, 53, 53},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__srv__TriggerTransition__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__TriggerTransition__TYPE_NAME, 44, 44},
      {vyra_module_interfaces__srv__TriggerTransition__FIELDS, 3, 3},
    },
    {vyra_module_interfaces__srv__TriggerTransition__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = vyra_module_interfaces__srv__TriggerTransition_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = vyra_module_interfaces__srv__TriggerTransition_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = vyra_module_interfaces__srv__TriggerTransition_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char vyra_module_interfaces__srv__TriggerTransition_Request__FIELD_NAME__transition_name[] = "transition_name";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__TriggerTransition_Request__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__TriggerTransition_Request__FIELD_NAME__transition_name, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__srv__TriggerTransition_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__TriggerTransition_Request__TYPE_NAME, 52, 52},
      {vyra_module_interfaces__srv__TriggerTransition_Request__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char vyra_module_interfaces__srv__TriggerTransition_Response__FIELD_NAME__success[] = "success";
static char vyra_module_interfaces__srv__TriggerTransition_Response__FIELD_NAME__message[] = "message";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__TriggerTransition_Response__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__TriggerTransition_Response__FIELD_NAME__success, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__TriggerTransition_Response__FIELD_NAME__message, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__srv__TriggerTransition_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__TriggerTransition_Response__TYPE_NAME, 53, 53},
      {vyra_module_interfaces__srv__TriggerTransition_Response__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char vyra_module_interfaces__srv__TriggerTransition_Event__FIELD_NAME__info[] = "info";
static char vyra_module_interfaces__srv__TriggerTransition_Event__FIELD_NAME__request[] = "request";
static char vyra_module_interfaces__srv__TriggerTransition_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__TriggerTransition_Event__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__TriggerTransition_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__TriggerTransition_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {vyra_module_interfaces__srv__TriggerTransition_Request__TYPE_NAME, 52, 52},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__TriggerTransition_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {vyra_module_interfaces__srv__TriggerTransition_Response__TYPE_NAME, 53, 53},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vyra_module_interfaces__srv__TriggerTransition_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__TriggerTransition_Request__TYPE_NAME, 52, 52},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__TriggerTransition_Response__TYPE_NAME, 53, 53},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__srv__TriggerTransition_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__TriggerTransition_Event__TYPE_NAME, 50, 50},
      {vyra_module_interfaces__srv__TriggerTransition_Event__FIELDS, 3, 3},
    },
    {vyra_module_interfaces__srv__TriggerTransition_Event__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = vyra_module_interfaces__srv__TriggerTransition_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = vyra_module_interfaces__srv__TriggerTransition_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# SetState.srv\n"
  "\n"
  "# Request\n"
  "string transition_name  # Name of the transition to set to change the current state\n"
  "---\n"
  "# Response\n"
  "bool success  # Indicates whether the operation was successful thus the state was set\n"
  "string message  # Additional information about the operation, e.g., \"Transition started successfully\", \"Transition failed due to error\", etc.\n"
  "\n"
  "# This service is used to set the state of a transition in the V.Y.R.A. system.\n"
  "# The transition_name is the name of the transition to set.\n"
  "# The success field indicates whether the operation was successful.\n"
  "# The message field provides additional information about the operation.\n"
  "# Example usage:\n"
  "# - Request: \"transition_name\": \"activate\"\n"
  "# - Response: \"success\": true, \"message\": \"Transition started successfully\"\n"
  "# This service is used to set the state of a transition in the V.Y.R.A. system.\n"
  "";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__TriggerTransition__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__TriggerTransition__TYPE_NAME, 44, 44},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 852, 852},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__TriggerTransition_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__TriggerTransition_Request__TYPE_NAME, 52, 52},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__TriggerTransition_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__TriggerTransition_Response__TYPE_NAME, 53, 53},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__TriggerTransition_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__TriggerTransition_Event__TYPE_NAME, 50, 50},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__TriggerTransition__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__TriggerTransition__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[3] = *vyra_module_interfaces__srv__TriggerTransition_Event__get_individual_type_description_source(NULL);
    sources[4] = *vyra_module_interfaces__srv__TriggerTransition_Request__get_individual_type_description_source(NULL);
    sources[5] = *vyra_module_interfaces__srv__TriggerTransition_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__TriggerTransition_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__TriggerTransition_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__TriggerTransition_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__TriggerTransition_Response__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__TriggerTransition_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__TriggerTransition_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[3] = *vyra_module_interfaces__srv__TriggerTransition_Request__get_individual_type_description_source(NULL);
    sources[4] = *vyra_module_interfaces__srv__TriggerTransition_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

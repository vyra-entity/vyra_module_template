// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vyra_module_interfaces:srv/HealthCheck.idl
// generated code does not contain a copyright notice

#include "vyra_module_interfaces/srv/detail/health_check__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__HealthCheck__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x8f, 0x68, 0xa6, 0x9f, 0x37, 0x50, 0x4f, 0xdb,
      0x0e, 0x96, 0x63, 0x16, 0x1b, 0x96, 0x6e, 0x28,
      0xb2, 0x8d, 0xed, 0xe2, 0x26, 0x46, 0x81, 0x13,
      0xe4, 0xe1, 0x88, 0x5d, 0x62, 0x31, 0xf0, 0x61,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__HealthCheck_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xb9, 0x46, 0xe2, 0xf6, 0x93, 0xc3, 0x1c, 0xce,
      0x0d, 0x13, 0x82, 0x7f, 0x12, 0xd8, 0xaa, 0x35,
      0x9e, 0x9a, 0x31, 0x1e, 0x16, 0x9f, 0xed, 0xbc,
      0xb7, 0x9f, 0x32, 0x2e, 0x6b, 0xb8, 0xeb, 0x4d,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__HealthCheck_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x93, 0xbb, 0xf5, 0x77, 0x44, 0x22, 0x81, 0x95,
      0xe6, 0x85, 0xaa, 0x49, 0xab, 0x03, 0xe5, 0xe8,
      0xee, 0xd5, 0x92, 0x0b, 0x5f, 0xe5, 0x42, 0x12,
      0xe4, 0x5a, 0x5c, 0x9a, 0x38, 0x2d, 0xe1, 0x13,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__HealthCheck_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6d, 0x68, 0x5d, 0xde, 0xfb, 0x52, 0x86, 0x1a,
      0x3e, 0x8d, 0xe4, 0x04, 0xdb, 0xfd, 0x3c, 0x4b,
      0x89, 0x1c, 0x85, 0x9b, 0x65, 0x9b, 0x68, 0xa3,
      0x42, 0x8b, 0x92, 0x7e, 0x67, 0xb5, 0x24, 0x05,
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

static char vyra_module_interfaces__srv__HealthCheck__TYPE_NAME[] = "vyra_module_interfaces/srv/HealthCheck";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";
static char vyra_module_interfaces__srv__HealthCheck_Event__TYPE_NAME[] = "vyra_module_interfaces/srv/HealthCheck_Event";
static char vyra_module_interfaces__srv__HealthCheck_Request__TYPE_NAME[] = "vyra_module_interfaces/srv/HealthCheck_Request";
static char vyra_module_interfaces__srv__HealthCheck_Response__TYPE_NAME[] = "vyra_module_interfaces/srv/HealthCheck_Response";

// Define type names, field names, and default values
static char vyra_module_interfaces__srv__HealthCheck__FIELD_NAME__request_message[] = "request_message";
static char vyra_module_interfaces__srv__HealthCheck__FIELD_NAME__response_message[] = "response_message";
static char vyra_module_interfaces__srv__HealthCheck__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__HealthCheck__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__HealthCheck__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vyra_module_interfaces__srv__HealthCheck_Request__TYPE_NAME, 46, 46},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vyra_module_interfaces__srv__HealthCheck_Response__TYPE_NAME, 47, 47},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vyra_module_interfaces__srv__HealthCheck_Event__TYPE_NAME, 44, 44},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vyra_module_interfaces__srv__HealthCheck__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck_Event__TYPE_NAME, 44, 44},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck_Request__TYPE_NAME, 46, 46},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck_Response__TYPE_NAME, 47, 47},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__srv__HealthCheck__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__HealthCheck__TYPE_NAME, 38, 38},
      {vyra_module_interfaces__srv__HealthCheck__FIELDS, 3, 3},
    },
    {vyra_module_interfaces__srv__HealthCheck__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = vyra_module_interfaces__srv__HealthCheck_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = vyra_module_interfaces__srv__HealthCheck_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = vyra_module_interfaces__srv__HealthCheck_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char vyra_module_interfaces__srv__HealthCheck_Request__FIELD_NAME__structure_needs_at_least_one_member[] = "structure_needs_at_least_one_member";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__HealthCheck_Request__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__HealthCheck_Request__FIELD_NAME__structure_needs_at_least_one_member, 35, 35},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__srv__HealthCheck_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__HealthCheck_Request__TYPE_NAME, 46, 46},
      {vyra_module_interfaces__srv__HealthCheck_Request__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char vyra_module_interfaces__srv__HealthCheck_Response__FIELD_NAME__alive[] = "alive";
static char vyra_module_interfaces__srv__HealthCheck_Response__FIELD_NAME__state[] = "state";
static char vyra_module_interfaces__srv__HealthCheck_Response__FIELD_NAME__health_status[] = "health_status";
static char vyra_module_interfaces__srv__HealthCheck_Response__FIELD_NAME__issues[] = "issues";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__HealthCheck_Response__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__HealthCheck_Response__FIELD_NAME__alive, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck_Response__FIELD_NAME__state, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck_Response__FIELD_NAME__health_status, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck_Response__FIELD_NAME__issues, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__srv__HealthCheck_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__HealthCheck_Response__TYPE_NAME, 47, 47},
      {vyra_module_interfaces__srv__HealthCheck_Response__FIELDS, 4, 4},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char vyra_module_interfaces__srv__HealthCheck_Event__FIELD_NAME__info[] = "info";
static char vyra_module_interfaces__srv__HealthCheck_Event__FIELD_NAME__request[] = "request";
static char vyra_module_interfaces__srv__HealthCheck_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__HealthCheck_Event__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__HealthCheck_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {vyra_module_interfaces__srv__HealthCheck_Request__TYPE_NAME, 46, 46},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {vyra_module_interfaces__srv__HealthCheck_Response__TYPE_NAME, 47, 47},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vyra_module_interfaces__srv__HealthCheck_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck_Request__TYPE_NAME, 46, 46},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__HealthCheck_Response__TYPE_NAME, 47, 47},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__srv__HealthCheck_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__HealthCheck_Event__TYPE_NAME, 44, 44},
      {vyra_module_interfaces__srv__HealthCheck_Event__FIELDS, 3, 3},
    },
    {vyra_module_interfaces__srv__HealthCheck_Event__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = vyra_module_interfaces__srv__HealthCheck_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = vyra_module_interfaces__srv__HealthCheck_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# HealthCheck.srv\n"
  "---\n"
  "bool alive  # Indicates if the system is alive/online and ready to process requests\n"
  "string state  # Current state of the system, e.g., \"active\", ...\n"
  "string health_status  # Detailed health status of the system, e.g., \"all systems operational\", \"minor issues detected\", \"major issues detected\"\n"
  "string[] issues  # List of issues detected, if any, e.g., [\"disk space low\", \"network latency high\"]";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__HealthCheck__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__HealthCheck__TYPE_NAME, 38, 38},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 416, 416},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__HealthCheck_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__HealthCheck_Request__TYPE_NAME, 46, 46},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__HealthCheck_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__HealthCheck_Response__TYPE_NAME, 47, 47},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__HealthCheck_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__HealthCheck_Event__TYPE_NAME, 44, 44},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__HealthCheck__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__HealthCheck__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[3] = *vyra_module_interfaces__srv__HealthCheck_Event__get_individual_type_description_source(NULL);
    sources[4] = *vyra_module_interfaces__srv__HealthCheck_Request__get_individual_type_description_source(NULL);
    sources[5] = *vyra_module_interfaces__srv__HealthCheck_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__HealthCheck_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__HealthCheck_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__HealthCheck_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__HealthCheck_Response__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__HealthCheck_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__HealthCheck_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[3] = *vyra_module_interfaces__srv__HealthCheck_Request__get_individual_type_description_source(NULL);
    sources[4] = *vyra_module_interfaces__srv__HealthCheck_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

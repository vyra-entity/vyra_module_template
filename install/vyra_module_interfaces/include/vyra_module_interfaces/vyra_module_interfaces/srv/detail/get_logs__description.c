// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vyra_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice

#include "vyra_module_interfaces/srv/detail/get_logs__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__GetLogs__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xdd, 0xac, 0x33, 0x4c, 0xce, 0x7c, 0x64, 0x1f,
      0xa4, 0xaf, 0x2f, 0x61, 0xa5, 0x1c, 0xf3, 0x1a,
      0x05, 0x2f, 0xd1, 0xca, 0x18, 0x86, 0x52, 0x01,
      0x95, 0x14, 0x2f, 0x75, 0x5f, 0xf7, 0x7a, 0xbf,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__GetLogs_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x47, 0x8c, 0x92, 0xf6, 0x63, 0x3d, 0x20, 0xe7,
      0x26, 0xcc, 0xbc, 0xc2, 0x1e, 0x7e, 0x6e, 0x33,
      0xde, 0x70, 0x94, 0xa8, 0x55, 0x61, 0x48, 0x66,
      0xbc, 0xc9, 0x84, 0xd8, 0x58, 0x3c, 0xcd, 0x9c,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__GetLogs_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x72, 0x32, 0x02, 0xbb, 0xc8, 0x0b, 0x5a, 0x1b,
      0xaf, 0x40, 0x17, 0x38, 0x1d, 0x51, 0x0a, 0xdc,
      0x4a, 0x10, 0xd0, 0x67, 0x00, 0xe7, 0x86, 0xf5,
      0xd1, 0xed, 0x1c, 0xd0, 0x07, 0x98, 0x5d, 0x3a,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__srv__GetLogs_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xe2, 0xb1, 0x3a, 0xf0, 0xb9, 0x32, 0xfc, 0xe2,
      0xaa, 0xe3, 0x15, 0x65, 0xae, 0xed, 0x44, 0x19,
      0x5d, 0xef, 0xdc, 0xee, 0x44, 0xde, 0xaf, 0x84,
      0xba, 0x73, 0x05, 0xa6, 0xdb, 0x40, 0x8e, 0x23,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "vyra_module_interfaces/msg/detail/logger_stream__functions.h"

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
static const rosidl_type_hash_t vyra_module_interfaces__msg__LoggerStream__EXPECTED_HASH = {1, {
    0xd3, 0xfc, 0x56, 0x35, 0x3b, 0x06, 0xd9, 0xbb,
    0x81, 0xb8, 0x1a, 0x47, 0x52, 0x07, 0x1e, 0x7a,
    0xa8, 0x7f, 0x79, 0x17, 0x6e, 0xcc, 0x76, 0x27,
    0xe3, 0xf1, 0xed, 0x18, 0xd3, 0x8d, 0x10, 0x91,
  }};
#endif

static char vyra_module_interfaces__srv__GetLogs__TYPE_NAME[] = "vyra_module_interfaces/srv/GetLogs";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";
static char vyra_module_interfaces__msg__LoggerStream__TYPE_NAME[] = "vyra_module_interfaces/msg/LoggerStream";
static char vyra_module_interfaces__srv__GetLogs_Event__TYPE_NAME[] = "vyra_module_interfaces/srv/GetLogs_Event";
static char vyra_module_interfaces__srv__GetLogs_Request__TYPE_NAME[] = "vyra_module_interfaces/srv/GetLogs_Request";
static char vyra_module_interfaces__srv__GetLogs_Response__TYPE_NAME[] = "vyra_module_interfaces/srv/GetLogs_Response";

// Define type names, field names, and default values
static char vyra_module_interfaces__srv__GetLogs__FIELD_NAME__request_message[] = "request_message";
static char vyra_module_interfaces__srv__GetLogs__FIELD_NAME__response_message[] = "response_message";
static char vyra_module_interfaces__srv__GetLogs__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__GetLogs__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__GetLogs__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vyra_module_interfaces__srv__GetLogs_Request__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__GetLogs__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vyra_module_interfaces__srv__GetLogs_Response__TYPE_NAME, 43, 43},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__GetLogs__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {vyra_module_interfaces__srv__GetLogs_Event__TYPE_NAME, 40, 40},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vyra_module_interfaces__srv__GetLogs__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__LoggerStream__TYPE_NAME, 39, 39},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__GetLogs_Event__TYPE_NAME, 40, 40},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__GetLogs_Request__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__GetLogs_Response__TYPE_NAME, 43, 43},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__srv__GetLogs__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__GetLogs__TYPE_NAME, 34, 34},
      {vyra_module_interfaces__srv__GetLogs__FIELDS, 3, 3},
    },
    {vyra_module_interfaces__srv__GetLogs__REFERENCED_TYPE_DESCRIPTIONS, 6, 6},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&vyra_module_interfaces__msg__LoggerStream__EXPECTED_HASH, vyra_module_interfaces__msg__LoggerStream__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = vyra_module_interfaces__msg__LoggerStream__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = vyra_module_interfaces__srv__GetLogs_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = vyra_module_interfaces__srv__GetLogs_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[5].fields = vyra_module_interfaces__srv__GetLogs_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char vyra_module_interfaces__srv__GetLogs_Request__FIELD_NAME__log_lines[] = "log_lines";
static char vyra_module_interfaces__srv__GetLogs_Request__FIELD_NAME__log_level[] = "log_level";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__GetLogs_Request__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__GetLogs_Request__FIELD_NAME__log_lines, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__GetLogs_Request__FIELD_NAME__log_level, 9, 9},
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
vyra_module_interfaces__srv__GetLogs_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__GetLogs_Request__TYPE_NAME, 42, 42},
      {vyra_module_interfaces__srv__GetLogs_Request__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char vyra_module_interfaces__srv__GetLogs_Response__FIELD_NAME__log_messages[] = "log_messages";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__GetLogs_Response__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__GetLogs_Response__FIELD_NAME__log_messages, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {vyra_module_interfaces__msg__LoggerStream__TYPE_NAME, 39, 39},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vyra_module_interfaces__srv__GetLogs_Response__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__LoggerStream__TYPE_NAME, 39, 39},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__srv__GetLogs_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__GetLogs_Response__TYPE_NAME, 43, 43},
      {vyra_module_interfaces__srv__GetLogs_Response__FIELDS, 1, 1},
    },
    {vyra_module_interfaces__srv__GetLogs_Response__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&vyra_module_interfaces__msg__LoggerStream__EXPECTED_HASH, vyra_module_interfaces__msg__LoggerStream__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = vyra_module_interfaces__msg__LoggerStream__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char vyra_module_interfaces__srv__GetLogs_Event__FIELD_NAME__info[] = "info";
static char vyra_module_interfaces__srv__GetLogs_Event__FIELD_NAME__request[] = "request";
static char vyra_module_interfaces__srv__GetLogs_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__srv__GetLogs_Event__FIELDS[] = {
  {
    {vyra_module_interfaces__srv__GetLogs_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__GetLogs_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {vyra_module_interfaces__srv__GetLogs_Request__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__GetLogs_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {vyra_module_interfaces__srv__GetLogs_Response__TYPE_NAME, 43, 43},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vyra_module_interfaces__srv__GetLogs_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__LoggerStream__TYPE_NAME, 39, 39},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__GetLogs_Request__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__srv__GetLogs_Response__TYPE_NAME, 43, 43},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__srv__GetLogs_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__srv__GetLogs_Event__TYPE_NAME, 40, 40},
      {vyra_module_interfaces__srv__GetLogs_Event__FIELDS, 3, 3},
    },
    {vyra_module_interfaces__srv__GetLogs_Event__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&vyra_module_interfaces__msg__LoggerStream__EXPECTED_HASH, vyra_module_interfaces__msg__LoggerStream__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = vyra_module_interfaces__msg__LoggerStream__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = vyra_module_interfaces__srv__GetLogs_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = vyra_module_interfaces__srv__GetLogs_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# GetLogs.srv\n"
  "# Request\n"
  "int32 log_lines\n"
  "uint8 log_level\n"
  "---\n"
  "# Response\n"
  "vyra_module_interfaces/LoggerStream[] log_messages\n"
  "\n"
  "# This service is used to retrieve logs from the V.Y.R.A. system.\n"
  "# The log_lines field specifies the number of log lines to retrieve.\n"
  "# The log_level field specifies the minimum log level to retrieve (e.g., INFO, WARNING, ERROR).";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__GetLogs__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__GetLogs__TYPE_NAME, 34, 34},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 354, 354},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__GetLogs_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__GetLogs_Request__TYPE_NAME, 42, 42},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__GetLogs_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__GetLogs_Response__TYPE_NAME, 43, 43},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__srv__GetLogs_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__srv__GetLogs_Event__TYPE_NAME, 40, 40},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__GetLogs__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[7];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 7, 7};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__GetLogs__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[3] = *vyra_module_interfaces__msg__LoggerStream__get_individual_type_description_source(NULL);
    sources[4] = *vyra_module_interfaces__srv__GetLogs_Event__get_individual_type_description_source(NULL);
    sources[5] = *vyra_module_interfaces__srv__GetLogs_Request__get_individual_type_description_source(NULL);
    sources[6] = *vyra_module_interfaces__srv__GetLogs_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__GetLogs_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__GetLogs_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__GetLogs_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__GetLogs_Response__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *vyra_module_interfaces__msg__LoggerStream__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__srv__GetLogs_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__srv__GetLogs_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[3] = *vyra_module_interfaces__msg__LoggerStream__get_individual_type_description_source(NULL);
    sources[4] = *vyra_module_interfaces__srv__GetLogs_Request__get_individual_type_description_source(NULL);
    sources[5] = *vyra_module_interfaces__srv__GetLogs_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

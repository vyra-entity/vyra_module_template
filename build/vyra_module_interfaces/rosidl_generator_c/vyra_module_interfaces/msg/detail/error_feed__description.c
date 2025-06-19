// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vyra_module_interfaces:msg/ErrorFeed.idl
// generated code does not contain a copyright notice

#include "vyra_module_interfaces/msg/detail/error_feed__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__msg__ErrorFeed__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xa0, 0xba, 0x4e, 0x6c, 0x8d, 0x0a, 0xef, 0x71,
      0xf6, 0xb6, 0xfb, 0x67, 0x96, 0xc8, 0xe9, 0x97,
      0xe6, 0x5d, 0xa1, 0x2c, 0x75, 0x59, 0x23, 0x9e,
      0x8d, 0xab, 0xd5, 0x5c, 0x1f, 0x51, 0x77, 0x09,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
#endif

static char vyra_module_interfaces__msg__ErrorFeed__TYPE_NAME[] = "vyra_module_interfaces/msg/ErrorFeed";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";

// Define type names, field names, and default values
static char vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__error_code[] = "error_code";
static char vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__module_id[] = "module_id";
static char vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__description[] = "description";
static char vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__solution[] = "solution";
static char vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__miscellaneous[] = "miscellaneous";
static char vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__timestamp[] = "timestamp";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__msg__ErrorFeed__FIELDS[] = {
  {
    {vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__error_code, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__module_id, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__description, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__solution, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__miscellaneous, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__ErrorFeed__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vyra_module_interfaces__msg__ErrorFeed__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__msg__ErrorFeed__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__msg__ErrorFeed__TYPE_NAME, 36, 36},
      {vyra_module_interfaces__msg__ErrorFeed__FIELDS, 6, 6},
    },
    {vyra_module_interfaces__msg__ErrorFeed__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# ErrorFeed.msg\n"
  "\n"
  "uint32 error_code\n"
  "string module_id\n"
  "string description\n"
  "string solution\n"
  "string miscellaneous\n"
  "builtin_interfaces/Time timestamp\n"
  "\n"
  "# The error code representing the specific error\n"
  "# A description of the error\n"
  "# A list of asset IDs related to the error\n"
  "# The timestamp when the error occurred\n"
  "# This message is used to communicate error information in the system\n"
  "# between different components or modules.\n"
  "# It can be used for logging, debugging, or alerting purposes.\n"
  "# The error_code is a unique identifier for the error type (hex-foramt).\n"
  "# The error_description provides additional context about the error.\n"
  "# The assets array contains objects (e.g., pictures) to illustrate the error.";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__msg__ErrorFeed__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__msg__ErrorFeed__TYPE_NAME, 36, 36},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 700, 700},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__msg__ErrorFeed__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__msg__ErrorFeed__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

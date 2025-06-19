// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vyra_module_interfaces:msg/StateFeed.idl
// generated code does not contain a copyright notice

#include "vyra_module_interfaces/msg/detail/state_feed__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__msg__StateFeed__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x8c, 0x94, 0x2e, 0xe8, 0x70, 0x0c, 0xad, 0xbf,
      0xe9, 0xc9, 0x9e, 0xd0, 0xa7, 0xb1, 0x91, 0x1d,
      0x76, 0x14, 0x9c, 0x4f, 0xf8, 0x08, 0x19, 0x6c,
      0x81, 0xaa, 0xe1, 0xf9, 0x4a, 0x9a, 0x96, 0xa2,
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

static char vyra_module_interfaces__msg__StateFeed__TYPE_NAME[] = "vyra_module_interfaces/msg/StateFeed";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";

// Define type names, field names, and default values
static char vyra_module_interfaces__msg__StateFeed__FIELD_NAME__prev_state[] = "prev_state";
static char vyra_module_interfaces__msg__StateFeed__FIELD_NAME__current_state[] = "current_state";
static char vyra_module_interfaces__msg__StateFeed__FIELD_NAME__timestamp[] = "timestamp";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__msg__StateFeed__FIELDS[] = {
  {
    {vyra_module_interfaces__msg__StateFeed__FIELD_NAME__prev_state, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__StateFeed__FIELD_NAME__current_state, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__StateFeed__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vyra_module_interfaces__msg__StateFeed__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__msg__StateFeed__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__msg__StateFeed__TYPE_NAME, 36, 36},
      {vyra_module_interfaces__msg__StateFeed__FIELDS, 3, 3},
    },
    {vyra_module_interfaces__msg__StateFeed__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# StateFeeder.msg\n"
  "\n"
  "string prev_state\n"
  "string current_state\n"
  "builtin_interfaces/Time timestamp\n"
  "\n"
  "# The previous state of the system\n"
  "# The current state of the system\n"
  "# The timestamp when the state change occurred\n"
  "# This message is used to communicate state changes in the system\n"
  "# between different components or modules.";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__msg__StateFeed__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__msg__StateFeed__TYPE_NAME, 36, 36},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 317, 317},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__msg__StateFeed__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__msg__StateFeed__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vyra_module_interfaces:msg/LoggerStream.idl
// generated code does not contain a copyright notice

#include "vyra_module_interfaces/msg/detail/logger_stream__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__msg__LoggerStream__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xd3, 0xfc, 0x56, 0x35, 0x3b, 0x06, 0xd9, 0xbb,
      0x81, 0xb8, 0x1a, 0x47, 0x52, 0x07, 0x1e, 0x7a,
      0xa8, 0x7f, 0x79, 0x17, 0x6e, 0xcc, 0x76, 0x27,
      0xe3, 0xf1, 0xed, 0x18, 0xd3, 0x8d, 0x10, 0x91,
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

static char vyra_module_interfaces__msg__LoggerStream__TYPE_NAME[] = "vyra_module_interfaces/msg/LoggerStream";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";

// Define type names, field names, and default values
static char vyra_module_interfaces__msg__LoggerStream__FIELD_NAME__log_level[] = "log_level";
static char vyra_module_interfaces__msg__LoggerStream__FIELD_NAME__log_message[] = "log_message";
static char vyra_module_interfaces__msg__LoggerStream__FIELD_NAME__timestamp[] = "timestamp";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__msg__LoggerStream__FIELDS[] = {
  {
    {vyra_module_interfaces__msg__LoggerStream__FIELD_NAME__log_level, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__LoggerStream__FIELD_NAME__log_message, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__LoggerStream__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vyra_module_interfaces__msg__LoggerStream__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__msg__LoggerStream__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__msg__LoggerStream__TYPE_NAME, 39, 39},
      {vyra_module_interfaces__msg__LoggerStream__FIELDS, 3, 3},
    },
    {vyra_module_interfaces__msg__LoggerStream__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# LoggerStream.msg\n"
  "\n"
  "string log_level\n"
  "string log_message\n"
  "builtin_interfaces/Time timestamp\n"
  "\n"
  "# This message is used to represent a log entry in the V.Y.R.A. system.\n"
  "# The log_level field indicates the severity of the log message (e.g., INFO, WARNING, ERROR).\n"
  "# The log_message field contains the actual log message.\n"
  "# The timestamp field indicates when the log entry was created.\n"
  "# Example usage:\n"
  "# - log_level: \"INFO\"\n"
  "# - log_message: \"System started successfully\"\n"
  "# - timestamp: \"2023-10-01T12:00:00Z\"";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__msg__LoggerStream__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__msg__LoggerStream__TYPE_NAME, 39, 39},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 501, 501},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__msg__LoggerStream__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__msg__LoggerStream__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

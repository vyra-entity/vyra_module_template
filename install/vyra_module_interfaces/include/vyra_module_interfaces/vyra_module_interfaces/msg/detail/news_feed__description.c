// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vyra_module_interfaces:msg/NewsFeed.idl
// generated code does not contain a copyright notice

#include "vyra_module_interfaces/msg/detail/news_feed__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vyra_module_interfaces
const rosidl_type_hash_t *
vyra_module_interfaces__msg__NewsFeed__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xa4, 0x26, 0x1b, 0xb2, 0xb1, 0x93, 0x78, 0xc9,
      0x0c, 0x73, 0xa0, 0x4c, 0x0f, 0xbe, 0x87, 0x51,
      0xe1, 0x9e, 0x7a, 0xbb, 0x92, 0xdb, 0x00, 0x4d,
      0x2d, 0x46, 0x30, 0x5b, 0x19, 0x1c, 0x66, 0x46,
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

static char vyra_module_interfaces__msg__NewsFeed__TYPE_NAME[] = "vyra_module_interfaces/msg/NewsFeed";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";

// Define type names, field names, and default values
static char vyra_module_interfaces__msg__NewsFeed__FIELD_NAME__type[] = "type";
static char vyra_module_interfaces__msg__NewsFeed__FIELD_NAME__message[] = "message";
static char vyra_module_interfaces__msg__NewsFeed__FIELD_NAME__timestamp[] = "timestamp";
static char vyra_module_interfaces__msg__NewsFeed__FIELD_NAME__module_id[] = "module_id";
static char vyra_module_interfaces__msg__NewsFeed__FIELD_NAME__module_name[] = "module_name";

static rosidl_runtime_c__type_description__Field vyra_module_interfaces__msg__NewsFeed__FIELDS[] = {
  {
    {vyra_module_interfaces__msg__NewsFeed__FIELD_NAME__type, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__NewsFeed__FIELD_NAME__message, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__NewsFeed__FIELD_NAME__timestamp, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__NewsFeed__FIELD_NAME__module_id, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vyra_module_interfaces__msg__NewsFeed__FIELD_NAME__module_name, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription vyra_module_interfaces__msg__NewsFeed__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vyra_module_interfaces__msg__NewsFeed__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vyra_module_interfaces__msg__NewsFeed__TYPE_NAME, 35, 35},
      {vyra_module_interfaces__msg__NewsFeed__FIELDS, 5, 5},
    },
    {vyra_module_interfaces__msg__NewsFeed__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# NewsFeed.msg\n"
  "\n"
  "string type \n"
  "string message\n"
  "builtin_interfaces/Time timestamp\n"
  "string module_id\n"
  "string module_name";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vyra_module_interfaces__msg__NewsFeed__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vyra_module_interfaces__msg__NewsFeed__TYPE_NAME, 35, 35},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 113, 113},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vyra_module_interfaces__msg__NewsFeed__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vyra_module_interfaces__msg__NewsFeed__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

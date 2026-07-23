// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aimdk_msgs:srv/GetStoredMapByName.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aimdk_msgs/srv/detail/get_stored_map_by_name__rosidl_typesupport_introspection_c.h"
#include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aimdk_msgs/srv/detail/get_stored_map_by_name__functions.h"
#include "aimdk_msgs/srv/detail/get_stored_map_by_name__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `map_name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aimdk_msgs__srv__GetStoredMapByName_Request__init(message_memory);
}

void aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_fini_function(void * message_memory)
{
  aimdk_msgs__srv__GetStoredMapByName_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Request, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "map_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Request, map_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_message_members = {
  "aimdk_msgs__srv",  // message namespace
  "GetStoredMapByName_Request",  // message name
  2,  // number of fields
  sizeof(aimdk_msgs__srv__GetStoredMapByName_Request),
  aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_message_member_array,  // message members
  aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_message_type_support_handle = {
  0,
  &aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetStoredMapByName_Request)() {
  aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_message_type_support_handle.typesupport_identifier) {
    aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aimdk_msgs__srv__GetStoredMapByName_Request__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "aimdk_msgs/srv/detail/get_stored_map_by_name__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aimdk_msgs/srv/detail/get_stored_map_by_name__functions.h"
// already included above
// #include "aimdk_msgs/srv/detail/get_stored_map_by_name__struct.h"


// Include directives for member types
// Member `header`
// already included above
// #include "std_msgs/msg/header.h"
// Member `header`
// already included above
// #include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `map_info`
#include "nav_msgs/msg/map_meta_data.h"
// Member `map_info`
#include "nav_msgs/msg/detail/map_meta_data__rosidl_typesupport_introspection_c.h"
// Member `map_path`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `navi_points`
#include "aimdk_msgs/msg/navi_point.h"
// Member `navi_points`
#include "aimdk_msgs/msg/detail/navi_point__rosidl_typesupport_introspection_c.h"
// Member `qr_points`
#include "aimdk_msgs/msg/qr_point.h"
// Member `qr_points`
#include "aimdk_msgs/msg/detail/qr_point__rosidl_typesupport_introspection_c.h"
// Member `hr_points`
#include "aimdk_msgs/msg/hr_point.h"
// Member `hr_points`
#include "aimdk_msgs/msg/detail/hr_point__rosidl_typesupport_introspection_c.h"
// Member `paths`
#include "aimdk_msgs/msg/path.h"
// Member `paths`
#include "aimdk_msgs/msg/detail/path__rosidl_typesupport_introspection_c.h"
// Member `regions`
#include "aimdk_msgs/msg/region.h"
// Member `regions`
#include "aimdk_msgs/msg/detail/region__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aimdk_msgs__srv__GetStoredMapByName_Response__init(message_memory);
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_fini_function(void * message_memory)
{
  aimdk_msgs__srv__GetStoredMapByName_Response__fini(message_memory);
}

size_t aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__data(
  const void * untyped_member)
{
  const rosidl_runtime_c__int8__Sequence * member =
    (const rosidl_runtime_c__int8__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__data(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int8__Sequence * member =
    (const rosidl_runtime_c__int8__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__data(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int8__Sequence * member =
    (rosidl_runtime_c__int8__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int8_t * item =
    ((const int8_t *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__data(untyped_member, index));
  int8_t * value =
    (int8_t *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int8_t * item =
    ((int8_t *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__data(untyped_member, index));
  const int8_t * value =
    (const int8_t *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__data(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int8__Sequence * member =
    (rosidl_runtime_c__int8__Sequence *)(untyped_member);
  rosidl_runtime_c__int8__Sequence__fini(member);
  return rosidl_runtime_c__int8__Sequence__init(member, size);
}

size_t aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__navi_points(
  const void * untyped_member)
{
  const aimdk_msgs__msg__NaviPoint__Sequence * member =
    (const aimdk_msgs__msg__NaviPoint__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__navi_points(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__NaviPoint__Sequence * member =
    (const aimdk_msgs__msg__NaviPoint__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__navi_points(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__NaviPoint__Sequence * member =
    (aimdk_msgs__msg__NaviPoint__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__navi_points(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__NaviPoint * item =
    ((const aimdk_msgs__msg__NaviPoint *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__navi_points(untyped_member, index));
  aimdk_msgs__msg__NaviPoint * value =
    (aimdk_msgs__msg__NaviPoint *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__navi_points(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__NaviPoint * item =
    ((aimdk_msgs__msg__NaviPoint *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__navi_points(untyped_member, index));
  const aimdk_msgs__msg__NaviPoint * value =
    (const aimdk_msgs__msg__NaviPoint *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__navi_points(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__NaviPoint__Sequence * member =
    (aimdk_msgs__msg__NaviPoint__Sequence *)(untyped_member);
  aimdk_msgs__msg__NaviPoint__Sequence__fini(member);
  return aimdk_msgs__msg__NaviPoint__Sequence__init(member, size);
}

size_t aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__qr_points(
  const void * untyped_member)
{
  const aimdk_msgs__msg__QRPoint__Sequence * member =
    (const aimdk_msgs__msg__QRPoint__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__qr_points(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__QRPoint__Sequence * member =
    (const aimdk_msgs__msg__QRPoint__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__qr_points(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__QRPoint__Sequence * member =
    (aimdk_msgs__msg__QRPoint__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__qr_points(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__QRPoint * item =
    ((const aimdk_msgs__msg__QRPoint *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__qr_points(untyped_member, index));
  aimdk_msgs__msg__QRPoint * value =
    (aimdk_msgs__msg__QRPoint *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__qr_points(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__QRPoint * item =
    ((aimdk_msgs__msg__QRPoint *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__qr_points(untyped_member, index));
  const aimdk_msgs__msg__QRPoint * value =
    (const aimdk_msgs__msg__QRPoint *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__qr_points(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__QRPoint__Sequence * member =
    (aimdk_msgs__msg__QRPoint__Sequence *)(untyped_member);
  aimdk_msgs__msg__QRPoint__Sequence__fini(member);
  return aimdk_msgs__msg__QRPoint__Sequence__init(member, size);
}

size_t aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__hr_points(
  const void * untyped_member)
{
  const aimdk_msgs__msg__HRPoint__Sequence * member =
    (const aimdk_msgs__msg__HRPoint__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__hr_points(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__HRPoint__Sequence * member =
    (const aimdk_msgs__msg__HRPoint__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__hr_points(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__HRPoint__Sequence * member =
    (aimdk_msgs__msg__HRPoint__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__hr_points(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__HRPoint * item =
    ((const aimdk_msgs__msg__HRPoint *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__hr_points(untyped_member, index));
  aimdk_msgs__msg__HRPoint * value =
    (aimdk_msgs__msg__HRPoint *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__hr_points(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__HRPoint * item =
    ((aimdk_msgs__msg__HRPoint *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__hr_points(untyped_member, index));
  const aimdk_msgs__msg__HRPoint * value =
    (const aimdk_msgs__msg__HRPoint *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__hr_points(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__HRPoint__Sequence * member =
    (aimdk_msgs__msg__HRPoint__Sequence *)(untyped_member);
  aimdk_msgs__msg__HRPoint__Sequence__fini(member);
  return aimdk_msgs__msg__HRPoint__Sequence__init(member, size);
}

size_t aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__paths(
  const void * untyped_member)
{
  const aimdk_msgs__msg__Path__Sequence * member =
    (const aimdk_msgs__msg__Path__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__paths(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__Path__Sequence * member =
    (const aimdk_msgs__msg__Path__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__paths(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__Path__Sequence * member =
    (aimdk_msgs__msg__Path__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__paths(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__Path * item =
    ((const aimdk_msgs__msg__Path *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__paths(untyped_member, index));
  aimdk_msgs__msg__Path * value =
    (aimdk_msgs__msg__Path *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__paths(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__Path * item =
    ((aimdk_msgs__msg__Path *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__paths(untyped_member, index));
  const aimdk_msgs__msg__Path * value =
    (const aimdk_msgs__msg__Path *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__paths(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__Path__Sequence * member =
    (aimdk_msgs__msg__Path__Sequence *)(untyped_member);
  aimdk_msgs__msg__Path__Sequence__fini(member);
  return aimdk_msgs__msg__Path__Sequence__init(member, size);
}

size_t aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__regions(
  const void * untyped_member)
{
  const aimdk_msgs__msg__Region__Sequence * member =
    (const aimdk_msgs__msg__Region__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__regions(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__Region__Sequence * member =
    (const aimdk_msgs__msg__Region__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__regions(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__Region__Sequence * member =
    (aimdk_msgs__msg__Region__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__regions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__Region * item =
    ((const aimdk_msgs__msg__Region *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__regions(untyped_member, index));
  aimdk_msgs__msg__Region * value =
    (aimdk_msgs__msg__Region *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__regions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__Region * item =
    ((aimdk_msgs__msg__Region *)
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__regions(untyped_member, index));
  const aimdk_msgs__msg__Region * value =
    (const aimdk_msgs__msg__Region *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__regions(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__Region__Sequence * member =
    (aimdk_msgs__msg__Region__Sequence *)(untyped_member);
  aimdk_msgs__msg__Region__Sequence__fini(member);
  return aimdk_msgs__msg__Region__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_member_array[12] = {
  {
    "code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "map_info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, map_info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "map_version",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, map_version),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "map_path",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, map_path),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, data),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__data,  // size() function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__data,  // get_const(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__data,  // get(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__data,  // fetch(index, &value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__data,  // assign(index, value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__data  // resize(index) function pointer
  },
  {
    "navi_points",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, navi_points),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__navi_points,  // size() function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__navi_points,  // get_const(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__navi_points,  // get(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__navi_points,  // fetch(index, &value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__navi_points,  // assign(index, value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__navi_points  // resize(index) function pointer
  },
  {
    "qr_points",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, qr_points),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__qr_points,  // size() function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__qr_points,  // get_const(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__qr_points,  // get(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__qr_points,  // fetch(index, &value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__qr_points,  // assign(index, value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__qr_points  // resize(index) function pointer
  },
  {
    "hr_points",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, hr_points),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__hr_points,  // size() function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__hr_points,  // get_const(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__hr_points,  // get(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__hr_points,  // fetch(index, &value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__hr_points,  // assign(index, value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__hr_points  // resize(index) function pointer
  },
  {
    "paths",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, paths),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__paths,  // size() function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__paths,  // get_const(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__paths,  // get(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__paths,  // fetch(index, &value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__paths,  // assign(index, value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__paths  // resize(index) function pointer
  },
  {
    "regions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, regions),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__size_function__GetStoredMapByName_Response__regions,  // size() function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_const_function__GetStoredMapByName_Response__regions,  // get_const(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__get_function__GetStoredMapByName_Response__regions,  // get(index) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__fetch_function__GetStoredMapByName_Response__regions,  // fetch(index, &value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__assign_function__GetStoredMapByName_Response__regions,  // assign(index, value) function pointer
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__resize_function__GetStoredMapByName_Response__regions  // resize(index) function pointer
  },
  {
    "map_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetStoredMapByName_Response, map_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_members = {
  "aimdk_msgs__srv",  // message namespace
  "GetStoredMapByName_Response",  // message name
  12,  // number of fields
  sizeof(aimdk_msgs__srv__GetStoredMapByName_Response),
  aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_member_array,  // message members
  aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_type_support_handle = {
  0,
  &aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetStoredMapByName_Response)() {
  aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, nav_msgs, msg, MapMetaData)();
  aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_member_array[6].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, NaviPoint)();
  aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_member_array[7].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, QRPoint)();
  aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_member_array[8].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, HRPoint)();
  aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_member_array[9].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, Path)();
  aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_member_array[10].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, Region)();
  if (!aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_type_support_handle.typesupport_identifier) {
    aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aimdk_msgs__srv__GetStoredMapByName_Response__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "aimdk_msgs/srv/detail/get_stored_map_by_name__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers aimdk_msgs__srv__detail__get_stored_map_by_name__rosidl_typesupport_introspection_c__GetStoredMapByName_service_members = {
  "aimdk_msgs__srv",  // service namespace
  "GetStoredMapByName",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // aimdk_msgs__srv__detail__get_stored_map_by_name__rosidl_typesupport_introspection_c__GetStoredMapByName_Request_message_type_support_handle,
  NULL  // response message
  // aimdk_msgs__srv__detail__get_stored_map_by_name__rosidl_typesupport_introspection_c__GetStoredMapByName_Response_message_type_support_handle
};

static rosidl_service_type_support_t aimdk_msgs__srv__detail__get_stored_map_by_name__rosidl_typesupport_introspection_c__GetStoredMapByName_service_type_support_handle = {
  0,
  &aimdk_msgs__srv__detail__get_stored_map_by_name__rosidl_typesupport_introspection_c__GetStoredMapByName_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetStoredMapByName_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetStoredMapByName_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetStoredMapByName)() {
  if (!aimdk_msgs__srv__detail__get_stored_map_by_name__rosidl_typesupport_introspection_c__GetStoredMapByName_service_type_support_handle.typesupport_identifier) {
    aimdk_msgs__srv__detail__get_stored_map_by_name__rosidl_typesupport_introspection_c__GetStoredMapByName_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)aimdk_msgs__srv__detail__get_stored_map_by_name__rosidl_typesupport_introspection_c__GetStoredMapByName_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetStoredMapByName_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetStoredMapByName_Response)()->data;
  }

  return &aimdk_msgs__srv__detail__get_stored_map_by_name__rosidl_typesupport_introspection_c__GetStoredMapByName_service_type_support_handle;
}

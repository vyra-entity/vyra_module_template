cmake_minimum_required(VERSION 3.5)
project(vyra_module_interfaces)
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(unique_identifier_msgs REQUIRED)
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/NewsFeed.msg"
  "msg/VolatileList.msg"
  "msg/VolatileHash.msg"
  "msg/ErrorFeed.msg"
  "msg/LoggerStream.msg"
  "msg/VolatileSet.msg"
  "msg/KeyValue.msg"
  "msg/VolatileString.msg"
  "msg/StateFeed.msg"
  "srv/RequestAcess.srv"
  "srv/HealthCheck.srv"
  "srv/GetCapabilities.srv"
  "srv/TriggerTransition.srv"
  "srv/GetLogs.srv"
  "srv/StartUp.srv"
  "action/InitiateUpdate.action"
  DEPENDENCIES std_msgs
  # Add additional dependencies here
)
install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)
ament_export_dependencies(rosidl_default_runtime)
ament_package()

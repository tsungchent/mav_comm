cmake_minimum_required(VERSION 3.5)
project(mav_state_machine_msgs)

find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(std_msgs REQUIRED)

set(
  msg_files
  "msg/StartStopTask.msg"
)

set(
  srv_files
  "srv/RunTaskService.srv"
)

rosidl_generate_interfaces(${PROJECT_NAME} 
  ${msg_files}
  ${srv_files}
  DEPENDENCIES builtin_interfaces std_msgs
  ADD_LINTER_TESTS
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
cmake_minimum_required(VERSION 3.5)
project(mav_system_msgs)

find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)

set(
  msg_files
  "msg/CpuInfo.msg"
  "msg/ProcessInfo.msg"
)
rosidl_generate_interfaces(${PROJECT_NAME} 
  ${msg_files}
  DEPENDENCIES std_msgs
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
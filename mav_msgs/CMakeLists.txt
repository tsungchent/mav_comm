cmake_minimum_required(VERSION 3.5)
project(mav_msgs)

find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(eigen_vendor REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)
# find_package(rosidl_default_generatorss REQUIRED)
find_package(Eigen3 QUIET)

if(NOT EIGEN3_FOUND)
  find_package(Eigen REQUIRED)
  set(EIGEN3_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS})
else()
  set(EIGEN3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
endif()

add_definitions(-std=c++11)

set(
  msg_files
  "msg/Actuators.msg"
  "msg/AttitudeThrust.msg"
  "msg/RateThrust.msg"
  "msg/RollPitchYawrateThrust.msg"
  "msg/TorqueThrust.msg"
  "msg/Status.msg"
  "msg/FilteredSensorData.msg"
  "msg/GpsWaypoint.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME} 
  ${msg_files}
  DEPENDENCIES std_msgs geometry_msgs
  ADD_LINTER_TESTS
)

# install(TARGETS
#  ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
#  ARCHIVE DESTINATION lib
#  LIBRARY DESTINATION lib
#  RUNTIME DESTINATION bin)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  FILES_MATCHING PATTERN "*.h"
)

# ament_export_dependencies(${PROJECT_NAME})
# ament_export_dependencies(rosidl_default_runtime)
# ament_export_dependencies(std_msgs)
# ament_export_dependencies(geometry_msgs)

ament_package()

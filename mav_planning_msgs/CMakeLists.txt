cmake_minimum_required(VERSION 3.5)
project(mav_planning_msgs)

find_package(ament_cmake REQUIRED)

find_package(builtin_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(mav_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)


find_package(Eigen3 QUIET)
if(NOT EIGEN3_FOUND)
  find_package(Eigen REQUIRED)
  set(EIGEN3_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS})
else()
  # ROS > Indigo.
  set(EIGEN3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
endif()

set(
  msg_files
  "msg/Point2D.msg"
  "msg/PointCloudWithPose.msg"
  "msg/Polygon2D.msg"
  "msg/PolygonWithHoles.msg"
  "msg/PolygonWithHolesStamped.msg"
  "msg/PolynomialSegment.msg"
  "msg/PolynomialTrajectory.msg"
  "msg/PolynomialSegment4D.msg"
  "msg/PolynomialTrajectory4D.msg"
)

set(
  srv_files
  "srv/PlannerService.srv"
  "srv/PolygonService.srv"
  "srv/ChangeNameService.srv"
)

rosidl_generate_interfaces(${PROJECT_NAME} 
  ${msg_files}
  ${srv_files}
  DEPENDENCIES builtin_interfaces geometry_msgs sensor_msgs std_msgs mav_msgs trajectory_msgs
  ADD_LINTER_TESTS
)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  FILES_MATCHING PATTERN "*.h"
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
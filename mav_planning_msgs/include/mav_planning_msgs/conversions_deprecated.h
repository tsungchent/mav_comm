/*
 * Copyright 2015 Fadri Furrer, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Michael Burri, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Markus Achtelik, ASL, ETH Zurich, Switzerland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MAV_PLANNING_MSGS_CONVERSIONS_DEPRECATED_H
#define MAV_PLANNING_MSGS_CONVERSIONS_DEPRECATED_H

#include <geometry_msgs/msg/Point.h>
#include <geometry_msgs/msg/Quaternion.h>
#include <geometry_msgs/msg/Vector3.h>

#include "mav_planning_msgs/msg/polynomial_segment4_d.h"
#include "mav_planning_msgs/msg/polynomial_trajectory4_d.h"
#include "mav_planning_msgs/eigen_planning_msgs.h"

#include "mav_msgs/common.h"

namespace mav_planning_msgs {
using PolynomialSegment4D = mav_planning_msgs::msg::PolynomialSegment4D;
using PolynomialTrajectory4D = mav_planning_msgs::msg::PolynomialTrajectory4D;

/// Converts a PolynomialSegment double array to an Eigen::VectorXd.
inline void vectorFromMsgArray(const PolynomialSegment4D::_x_type& array,
                               Eigen::VectorXd* x);

/// Converts an Eigen::VectorXd to a PolynomialSegment double array.
inline void msgArrayFromVector(const Eigen::VectorXd& x,
                               PolynomialSegment4D::_x_type* array);

/// Converts a PolynomialSegment message to an EigenPolynomialSegment structure.
inline void eigenPolynomialSegmentFromMsg(const PolynomialSegment4D& msg,
                                          EigenPolynomialSegment* segment) {
  assert(segment != NULL);

  vectorFromMsgArray(msg.x, &(segment->x));
  vectorFromMsgArray(msg.y, &(segment->y));
  vectorFromMsgArray(msg.z, &(segment->z));
  vectorFromMsgArray(msg.yaw, &(segment->yaw));

  segment->segment_time_ns = mav_msgs::toNSec(msg.segment_time);
  // msg.segment_time.sec * 1000000000ull + msg.segment_time.nanosec;
  segment->num_coeffs = msg.num_coeffs;
}

/// Converts a PolynomialTrajectory message to a EigenPolynomialTrajectory
inline void eigenPolynomialTrajectoryFromMsg(
    const PolynomialTrajectory4D& msg,
    EigenPolynomialTrajectory* eigen_trajectory) {
  assert(eigen_trajectory != NULL);
  eigen_trajectory->clear();
  eigen_trajectory->reserve(msg.segments.size());
  for (PolynomialTrajectory4D::_segments_type::const_iterator it =
           msg.segments.begin();
       it != msg.segments.end(); ++it) {
    EigenPolynomialSegment segment;
    eigenPolynomialSegmentFromMsg(*it, &segment);
    eigen_trajectory->push_back(segment);
  }
}


/// Converts an EigenPolynomialSegment to a PolynomialSegment message. Does NOT
/// set the header!
inline void polynomialSegmentMsgFromEigen(const EigenPolynomialSegment& segment,
                                          PolynomialSegment4D* msg) {
  assert(msg != NULL);
  msgArrayFromVector(segment.x, &(msg->x));
  msgArrayFromVector(segment.y, &(msg->y));
  msgArrayFromVector(segment.z, &(msg->z));
  msgArrayFromVector(segment.yaw, &(msg->yaw));

  mav_msgs::fromNSec(segment.segment_time_ns, msg->segment_time);
  msg->num_coeffs = segment.num_coeffs;
}

/// Converts an EigenPolynomialTrajectory to a PolynomialTrajectory message.
/// Does NOT set the header!
inline void polynomialTrajectoryMsgFromEigen(
    const EigenPolynomialTrajectory& eigen_trajectory,
    PolynomialTrajectory4D* msg) {
  assert(msg != NULL);
  msg->segments.reserve(eigen_trajectory.size());
  for (EigenPolynomialTrajectory::const_iterator it = eigen_trajectory.begin();
       it != eigen_trajectory.end(); ++it) {
    PolynomialSegment4D segment;
    polynomialSegmentMsgFromEigen(*it, &segment);
    msg->segments.push_back(segment);
  }
}

}  // namespace mav_planning_msgs

#endif // MAV_PLANNING_MSGS_CONVERSIONS_DEPRECATED_H

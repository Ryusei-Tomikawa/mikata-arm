﻿#ifndef OPEN_MANIPULATOR_TELEOP_H
#define OPEN_MANIPULATOR_TELEOP_H

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Joy.h>

#include <termios.h>
#include "open_manipulator_msgs/SetJointPosition.h"
#include "open_manipulator_msgs/SetKinematicsPose.h"

#define NUM_OF_JOINT 6
#define DELTA 0.01
#define JOINT_DELTA 0.05
#define PATH_TIME 0.5

class OpenManipulatorTeleop
{
 private:
  // ROS NodeHandle
  ros::NodeHandle node_handle_;
  ros::NodeHandle priv_node_handle_;

  ros::ServiceClient goal_task_space_path_from_present_position_only_client_;
  ros::ServiceClient goal_joint_space_path_client_;
  ros::ServiceClient goal_tool_control_client_;

  ros::Subscriber joint_states_sub_;
  ros::Subscriber kinematics_pose_sub_;
  ros::Subscriber joy_command_sub_;

  std::vector<double> present_joint_angle_;
  std::vector<double> present_kinematic_position_;

 public:

  OpenManipulatorTeleop();
  ~OpenManipulatorTeleop();

  void initClient();
  void initSubscriber();

  void jointStatesCallback(const sensor_msgs::JointState::ConstPtr &msg);
  void kinematicsPoseCallback(const open_manipulator_msgs::KinematicsPose::ConstPtr &msg);
  void joyCallback(const sensor_msgs::Joy::ConstPtr &msg);

  std::vector<double> getPresentJointAngle();
  std::vector<double> getPresentKinematicsPose();

  bool setJointSpacePath(std::vector<std::string> joint_name, std::vector<double> joint_angle, double path_time);

  bool setTaskSpacePathFromPresentPositionOnly(std::vector<double> kinematics_pose, double path_time);

  bool setToolControl(std::vector<double> joint_angle);

  void setGoal(const char *str);
};

#endif //OPEN_MANIPULATOR_TELEOP_H

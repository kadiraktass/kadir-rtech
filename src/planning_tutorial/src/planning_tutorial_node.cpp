#include "ros/ros.h"
#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayTrajectory.h>




int main(int argc, char **argv)
{	

ros::init(argc, argv, "planning_tutorial_node");
 
ros::NodeHandle n;
//ros::Publisher display_publisher = node_handle.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path",1,true);
  ros::AsyncSpinner spinner(1);
  spinner.start();
  moveit::planning_interface::MoveGroup group("sia5");
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  moveit_msgs::DisplayTrajectory display_trajectory;
  moveit::planning_interface::MoveGroup::Plan my_plan;

  std::vector<geometry_msgs::Pose> waypoints;
  geometry_msgs::PoseStamped currentPose;
  currentPose = group.getCurrentPose();
  geometry_msgs::Pose target_pose1;


  target_pose1.orientation.x = currentPose.pose.orientation.x;
  target_pose1.orientation.y = currentPose.pose.orientation.y;
  target_pose1.orientation.z = currentPose.pose.orientation.z;
  target_pose1.orientation.w = currentPose.pose.orientation.w;
  target_pose1.position.x = currentPose.pose.position.x;
  target_pose1.position.y = currentPose.pose.position.y;
  target_pose1.position.z = currentPose.pose.position.z;
  group.setPoseTarget(target_pose1);
  group.plan(my_plan);
  group.move();
  sleep(5.0);
  

  geometry_msgs::Pose target_pose2 = target_pose1;
  target_pose2.position.y -= 0.1;
  target_pose2.position.z -= 0.1;
  waypoints.push_back(target_pose2);
  
  target_pose2.position.y += 0.2;
  waypoints.push_back(target_pose2);
  
  target_pose2.position.y -= 0.1;
  target_pose2.position.z += 0.1;
  waypoints.push_back(target_pose2);
//   target_pose1.position.x = currentPose.pose.position.x - 0.2;
//   target_pose1.position.y = currentPose.pose.position.y + 0.2;
//   target_pose1.position.z = currentPose.pose.position.z - 0.2;
//   waypoints.push_back(target_pose1);
  
  
  moveit_msgs::RobotTrajectory trajectory;
  double fraction = group.computeCartesianPath(waypoints,
                                             0.01,  // eef_step
                                             0.0,   // jump_threshold
                                             trajectory);

ROS_INFO("Visualizing plan 4 (cartesian path) (%.2f%% acheived)",
      fraction * 100.0);
my_plan.trajectory_ = trajectory;
group.execute(my_plan);

sleep(5.0);
  ros::shutdown();

  return 0;
}










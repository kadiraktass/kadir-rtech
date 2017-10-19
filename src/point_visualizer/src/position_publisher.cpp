#include "ros/ros.h"
#include <geometry_msgs/PointStamped.h>
int main(int argc, char **argv)
{

ros::init(argc, argv, "position_publisher");
 
ros::NodeHandle n;

ros::Publisher position_pub = n.advertise<geometry_msgs::PointStamped>("position", 1000);

ros::Rate loop_rate(10);

int x=1, y=1, z=1;
  while (ros::ok())
  {
	
	geometry_msgs::PointStamped position;

	position.header.stamp = ros::Time::now();
	position.header.frame_id = "position";

	position.point.x = x;
	position.point.y = y;
	position.point.z = z;
 	

	position_pub.publish(position);
	
	
	x = x+1;
	y = y+1;
	z = z+1;
	ros::Duration(1).sleep();
	ros::spinOnce();
 	
	loop_rate.sleep();
	
  }


  return 0;
}

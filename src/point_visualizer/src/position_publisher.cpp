#include "ros/ros.h"
#include <geometry_msgs/PointStamped.h>
#include "std_msgs/String.h"
#include <mouse_reader/mouse_msg.h>

geometry_msgs::PointStamped position;

void mouse_position_Callback(const mouse_reader::mouse_msg msg)
{
  position.header.stamp = ros::Time::now();
  position.header.frame_id = "position";
  position.point.x=msg.x;
  position.point.y=msg.y;
  //position_pub.publish(position);
}

int main(int argc, char **argv)
{

ros::init(argc, argv, "position_publisher");
 
ros::NodeHandle n;

ros::Publisher position_pub = n.advertise<geometry_msgs::PointStamped>("position", 1000);



int x=1, y=1, z=1;

ros::Subscriber sub = n.subscribe("mouse_position", 1000, mouse_position_Callback);

  while (ros::ok())
  {

	position_pub.publish(position);

	
	ros::spinOnce();
 	
	
	
  }


  return 0;
}



#include "ros/ros.h"
//#include <geometry_msgs/PointStamped.h>
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "mouse_reader/mouse_msg.h"
#define MOUSEFILE "/dev/input/event4"

int main(int argc, char **argv)
{

ros::init(argc, argv, "mouse_reader_node");
 
ros::NodeHandle n;

//ros::Publisher position_pub = n.advertise<geometry_msgs::PointStamped>("position", 1000);
ros::Publisher position_pub = n.advertise<mouse_reader::mouse_msg>("position", 1000);
ros::Rate loop_rate(10);
mouse_reader::mouse_msg position;
//geometry_msgs::PointStamped position;
//position.header.frame_id = "position";
//position.point.x =0;
//position.point.y =0;
//position.point.z =0;
position.x =0;
position.y =0;
position.z =0;

  while (ros::ok())
  {

	int fd, left_button, x, y;
	struct input_event ie;

	//position.header.stamp = ros::Time::now();

	if((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
		perror("opening device\n");
		exit(EXIT_FAILURE);
	}

	while(read(fd, &ie, sizeof(struct input_event))){
	//read(fd, &ie, sizeof(struct input_event));
	//printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n",
	//ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value); //code 272 left;273 right;1 up down;0 horizontal
	//position.point.z = 0;
	position.z = 0;
	if(ie.type==1 && ie.code == 272){
		printf("left button is clicked\n");
		//position.point.z = 1;
		position.z = 1;
		//printf("published\n");
		//position_pub.publish(position);
		//printf("published\n");
		}
	if(ie.type==2 && ie.code == 0){
		printf("x relocated by= %d unit\n",ie.value);
		//position.point.x = position.point.x+ ie.value;
		position.x = position.x+ ie.value;
		//position_pub.publish(position);
		//printf("published\n");
		}
	if(ie.type==2 && ie.code == 1){
		printf("y relocated by= %d unit\n",ie.value);
		//position.point.y = position.point.y+ ie.value;
		position.y = position.y+ ie.value;
		//position_pub.publish(position);
		}
	//position_pub.publish(position);
	//printf("published\n");
	position_pub.publish(position);
	}
	
	
	
	ros::spinOnce();
 	
	loop_rate.sleep();
	
  }


  return 0;
}

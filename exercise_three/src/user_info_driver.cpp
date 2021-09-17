#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string.h>
#include <sstream>
 

 int main(int argc, char **argv)
 {
   ros::init(argc, argv, "user_info_driver");
   ros::NodeHandle n;
   ros::Publisher chatter_pub = n.advertise<std_msgs::String>("/raw_data", 1000);
   ros::Rate loop_rate(10);
   int count = 0;
   string name = "Rose";
   int age = 20;
   int height = 170;
   while (ros::ok())
   {
     std_msgs::String msg;
     std::stringstream ss;
     
     ss << "name:" << name << ", age:" << age << ", height:" << height;
     msg.data = ss.str();
     ROS_INFO("%s", msg.data.c_str());
     chatter_pub.publish(msg);
     ros::spinOnce();
     loop_rate.sleep();
     ++count;
   }
   return 0;
 }

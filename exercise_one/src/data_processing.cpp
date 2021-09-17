 #include "ros/ros.h"
 #include "std_msgs/String.h"
 #include <string.h>

int name_start,name_end;
int age_start,age_end;
int height_start,height_end;
string name;
int age;
int height;

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
   //ROS_INFO("I heard: [%s]", msg->data.c_str());
   name_start = msg.find("name:") + 5;
   name_end = msg.find(",");
   name = str(msg[name_start:name_end]);
   age_start = msg.find("age:") + 4;
   age_end = msg.find(",",name_end + 1);
   age = int(msg[age_start:age_end]);
   height_start = msg.find("height:") + 7;
   height_end = len(msg) - 1;
   height = int(msg[height_start:height_end]);
   ROS_INFO("I heard: [%s] \n", name);
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "data_processing");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/raw_data", 1000, chatterCallback);

  ros::spin();

  return 0;
}

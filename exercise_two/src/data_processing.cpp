#include <string.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int name_start,name_end;
int age_start,age_end;
int height_start,height_end;
string name;
int age;
int height;

void chatterCallback(const std_msgs::String::ConstPtr& msg){
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  name_start = msg.find("name:") + 5;
  name_end = msg.find(",");
  name = str(msg[name_start:name_end]);
  age_start = msg.find("age:") + 4;
  age_end = msg.find(",",name_end + 1);
  age = int(msg[age_start:age_end]);
  height_start = msg.find("height:") + 7;
  height_end = len(msg) - 1;
  height = int(msg[height_start:height_end]);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "data_processing");   
  ros::NodeHandle n;   
  ros::Subscriber sub = n.subscribe("/raw_data", 1000, chatterCallback);
  ros::Publisher name_pub = n.advertise<std_msgs::String>("/name", 1000);
  ros::Publisher age_pub = n.advertise<std_msgs::String>("/age", 1000);
  ros::Publisher height_pub = n.advertise<std_msgs::String>("/height", 1000);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok()){
    std_msgs::String name_msg;
    std_msgs::String age_msg;
    std_msgs::String height_msg;

    std::stringstream name_ss, age_ss, height_ss;
    name_ss.clear();
    name_ss << name;
    name_msg.data = name_ss.str();
    ROS_INFO("%s", name_msg.data.c_str());
    name_pub.publish(name_msg);
    age_ss.clear();
    age_ss << age;
    age_msg.data = age_ss.str();
    ROS_INFO("%s", age_msg.data.c_str());
    age_pub.publish(age_msg);
    height_ss.clear();
    height_ss << height;
    height_msg.data = height_ss.str();
    ROS_INFO("%s", height_msg.data.c_str());
    height_pub.publish(height_msg);
    
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  ros::spin();

  return 0;
}
















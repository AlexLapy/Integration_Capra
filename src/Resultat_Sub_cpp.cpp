#include "ros/ros.h"
#include "std_msgs/Float64.h"

void resultat_Callback(const std_msgs::Float64::ConstPtr& msg);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "third_res");

  ros::NodeHandle n;
  
  ros::Subscriber sub = n.subscribe("resultat", 1000, resultat_Callback);

  ros::spin();
  

  return 0;
}

void resultat_Callback(const std_msgs::Float64::ConstPtr& msg)
{
  ROS_INFO("La distance est de : [%.3f]", msg->data);
  
}


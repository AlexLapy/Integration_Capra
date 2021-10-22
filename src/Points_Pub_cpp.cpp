#include "ros/ros.h"
#include "geometry_msgs/Point.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "first_pub");

  ros::NodeHandle n;

  ros::Publisher pub_p1 = n.advertise<geometry_msgs::Point>("point_one", 1000);
  ros::Publisher pub_p2 = n.advertise<geometry_msgs::Point>("point_two", 1000);

  ros::Rate loop_rate(5);

  geometry_msgs::Point p1;//(1, 1, 2);
  geometry_msgs::Point p2;//(0, 0, 0);

  p1.x = 1.0;
  p1.y = 1.0;
  p1.z = 2.0;
  p2.x = 0.0;
  p2.y = 0.0;
  p2.z = 0.0;

  while (ros::ok())
  {

    ROS_INFO("Point 1 : [%.1f, %.1f, %.1f] \n", p1.x, p1.y, p1.z);
    ROS_INFO("Point 2 : [%.1f, %.1f, %.1f] \n", p2.x, p2.y, p2.z);

    pub_p1.publish(p1);
    pub_p2.publish(p2);

    ros::spinOnce();

    loop_rate.sleep();
  }
  return 0;
}
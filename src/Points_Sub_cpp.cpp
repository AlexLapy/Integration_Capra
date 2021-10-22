#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Float64.h"
#include <cmath>

void point_one_Callback(const geometry_msgs::Point::ConstPtr& msg);
void point_two_Callback(const geometry_msgs::Point::ConstPtr& msg);

double pythagore();

std::vector<double> p1(3);
std::vector<double> p2(3);

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "second_sub");

  ros::NodeHandle n;
  
  ros::Subscriber sub = n.subscribe("point_one", 1000, point_one_Callback);
  ros::Subscriber sub_2 = n.subscribe("point_two", 1000, point_two_Callback);

  ros::Publisher pub_resultat = n.advertise<std_msgs::Float64>("resultat", 1000);

  std_msgs::Float64 resultat;
  ros::Rate loop_rate(5);

  while (ros::ok())
  {
    resultat.data = pythagore();

    pub_resultat.publish(resultat);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}

void point_one_Callback(const geometry_msgs::Point::ConstPtr& msg)
{
  ROS_INFO("Point one is  [%.2f, %.2f, %.2f]", msg->x, msg->y, msg->z);
  p1[0] = msg->x;
  p1[1] = msg->y;
  p1[2] = msg->z;
}

void point_two_Callback(const geometry_msgs::Point::ConstPtr& msg)
{
  ROS_INFO("Point two is  [%.2f, %.2f, %.2f]", msg->x, msg->y, msg->z);
  p2[0] = msg->x;
  p2[1] = msg->y;
  p2[2] = msg->z;

}

double pythagore()
{
    double dist = sqrt(pow(p2[0]-p1[0],2.0)+
                       pow(p2[1]-p1[1],2.0)+
                       pow(p2[2]-p1[2],2.0));

    ROS_INFO("La distance est de [%.1f]", dist);                   
    return dist;
}
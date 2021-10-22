#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "integrationv2/points_to_area.h"
#include <cmath>

bool add(integrationv2::points_to_area::Request  &req,
         integrationv2::points_to_area::Response &res)
{

  // Vector_A from p1 to p2, Vector_B from p1 to p3 

  geometry_msgs::Point vector_A;
  geometry_msgs::Point vector_B;

  vector_A.x = req.p2.x - req.p1.x;
  vector_A.y = req.p2.y - req.p1.y;
  vector_A.z = req.p2.z - req.p1.z;

  vector_B.x = req.p3.x - req.p1.x;
  vector_B.y = req.p3.y - req.p1.y;
  vector_B.z = req.p3.z - req.p1.z;

  // Cross product of vec_A and vec_B

  geometry_msgs::Point vector_C;

  vector_C.x = ( vector_A.y * vector_B.z ) - ( vector_B.y * vector_A.z );
  vector_C.y = ( vector_A.x * vector_B.z ) - ( vector_B.x * vector_A.z );
  vector_C.z = ( vector_A.x * vector_B.y ) - ( vector_B.x * vector_A.y );

  // Area of both vec

  float area_of_parallelogram = sqrt(pow(vector_C.x, 2) + pow(vector_C.y, 2) + pow(vector_C.z, 2));
  
  float area_of_triangle = area_of_parallelogram / 2;

  res.area = area_of_triangle;

  ROS_INFO("request: Point one is [%.2f, %.2f, %.2f]", req.p1.x, req.p1.y, req.p1.z);
  ROS_INFO("request: Point two is [%.2f, %.2f, %.2f]", req.p2.x, req.p2.y, req.p2.z);
  ROS_INFO("request: Point three is [%.2f, %.2f, %.2f]", req.p3.x, req.p3.y, req.p3.z);
  
  ROS_INFO("sending back response: [%.3f]", res.area);

/*
  ROS_INFO("sending back response A: [%f, %f, %f]", vector_A.x, vector_A.y, vector_A.z);
  ROS_INFO("sending back response B: [%f, %f, %f]", vector_B.x, vector_B.y, vector_B.z);
  ROS_INFO("sending back response C: [%f, %f, %f]", vector_C.x, vector_C.y, vector_C.z);
*/  
  return true;

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Area_service");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("Area_service", add);
  ROS_INFO("Ready");
  ros::spin();

  return 0;
}
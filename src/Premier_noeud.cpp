#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Float64.h"
#include "integrationv2/points_to_area.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Main");
    if (argc != 10)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }
  ros::NodeHandle n;

  ros::ServiceClient client = n.serviceClient<integrationv2::points_to_area>("Area_service");

  ros::Publisher pub_p1 = n.advertise<geometry_msgs::Point>("point_one", 1000);
  ros::Publisher pub_p2 = n.advertise<geometry_msgs::Point>("point_two", 1000);
  ros::Publisher pub_p3 = n.advertise<geometry_msgs::Point>("point_three", 1000);
  ros::Publisher pub_res = n.advertise<std_msgs::Float64>("res_area", 1000);

  integrationv2::points_to_area srv;  
  std_msgs::Float64 area_of_triangle;

  geometry_msgs::Point point_1;
  geometry_msgs::Point point_2;
  geometry_msgs::Point point_3;

  point_1.x = atof(argv[1]);
  point_1.y = atof(argv[2]);
  point_1.z = atof(argv[3]);

  point_2.x = atof(argv[4]);
  point_2.y = atof(argv[5]);
  point_2.z = atof(argv[6]);

  point_3.x = atof(argv[7]);
  point_3.y = atof(argv[8]);
  point_3.z = atof(argv[9]);

  srv.request.p1.x = point_1.x;
  srv.request.p1.y = point_1.y;
  srv.request.p1.z = point_1.z;

  srv.request.p2.x = point_2.x;
  srv.request.p2.y = point_2.y;
  srv.request.p2.z = point_2.z;

  srv.request.p3.x = point_3.x;
  srv.request.p3.y = point_3.y;
  srv.request.p3.z = point_3.z;


  ros::Rate loop_rate(10);

  while (ros::ok())
  {

   pub_p1.publish(point_1);
   pub_p2.publish(point_2);
   pub_p3.publish(point_3);


   if (client.call(srv))
   {
    area_of_triangle.data = srv.response.area;
    ROS_INFO("Area of the triangle is : %.3f", area_of_triangle.data);
    pub_res.publish(area_of_triangle);
   }
   else
   {
    ROS_ERROR("Failed to call service area");
    return 1;
   }

   ros::spinOnce();

   loop_rate.sleep();
  }

  return 0;
}
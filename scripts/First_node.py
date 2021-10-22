#!/usr/bin/env python

from integrationv2.srv import *
from geometry_msgs.msg import Point
from std_msgs.msg import Float64
import sys
import rospy


def usage():
    return "%s [x y]"%sys.argv[0]

def client():

    if len(sys.argv) == 10:
        p1 = Point(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3]))
        p2 = Point(int(sys.argv[4]),int(sys.argv[5]),int(sys.argv[6]))
        p3 = Point(int(sys.argv[7]),int(sys.argv[8]),int(sys.argv[9]))

    else:
        print(usage())
        sys.exit(1)

    rospy.init_node('Area_Client')

    pub_p1 = rospy.Publisher('point_one', Point, queue_size=10)
    pub_p2 = rospy.Publisher('point_two', Point, queue_size=10)
    pub_p3 = rospy.Publisher('point_two', Point, queue_size=10)
    pub_res = rospy.Publisher('res_area', Float64, queue_size=10)

    pub_p1.publish(p1)
    pub_p2.publish(p2)
    pub_p3.publish(p3)

    rospy.wait_for_service('Area_service')
    try:
        client = rospy.ServiceProxy('Area_service', points_to_area)
        response = client(p1, p2, p3)
        rospy.loginfo(response)
        pub_res.publish(response.area)

    except rospy.ServiceException as e:
        print("Service call failed: %s"%e)


if __name__ == "__main__":

    try:
        client()  
    except rospy.ROSInterruptException:
        pass      
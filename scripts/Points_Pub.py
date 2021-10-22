#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Point

def first():
    pub_p1 = rospy.Publisher('point_one', Point, queue_size=10)
    pub_p2 = rospy.Publisher('point_two', Point, queue_size=10)

    rospy.init_node('first_pub', anonymous=True)
  
    p1 = Point(1,1,2)
    p2 = Point(0,0,0)
    rospy.loginfo(p1)
    rospy.loginfo(p2)

    while not rospy.is_shutdown():

        pub_p1.publish(p1)
        pub_p2.publish(p2)
    
        rospy.Rate(20).sleep()
        
   # rospy.spin()

if __name__ == '__main__':
    try:
        first()
    except rospy.ROSInterruptException:
        pass
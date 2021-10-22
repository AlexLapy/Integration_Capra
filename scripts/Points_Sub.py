#!/usr/bin/env python

import rospy
import math
from std_msgs.msg import Float64
from geometry_msgs.msg import Point
    
class calcu(object):
    
    def __init__(self, pub):
        self.pub = pub
        self.x1 = 0
        self.y1 = 0
        self.z1 = 0
        self.x2 = 0
        self.y2 = 0
        self.z2 = 0
        self.dist = 1


    def callback_1(self, data):
        #rospy.loginfo(data)
        self.x1 = data.x
        self.y1 = data.y
        self.z1 = data.z
        return None

    def callback_2(self, data):
        #rospy.loginfo(data)
        self.x2 = data.x
        self.y2 = data.y
        self.z2 = data.z 
        return self.pythagore(self.pub)

    def pythagore(self,pub):
        self.dist = math.sqrt(pow(self.x2-self.x1,2)+
                              pow(self.y2-self.y1,2)+
                              pow(self.z2-self.z1,2))
        rospy.loginfo(self.dist)                      
        return pub.publish(self.dist)            
        
    
def second():

    rospy.init_node('second_sub', anonymous=True)

    pub_res = rospy.Publisher('resultat', Float64, queue_size=10) 
    calculator = calcu(pub_res)

    rospy.Subscriber("point_one", Point, calculator.callback_1)
    rospy.Subscriber("point_two", Point, calculator.callback_2)

    rospy.spin()

if __name__ == '__main__':
    try:
        second()
    except rospy.ROSInterruptException:
        pass
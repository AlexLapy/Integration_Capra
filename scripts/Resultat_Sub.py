#!/usr/bin/env python

import rospy
from std_msgs.msg import Float64



def callback(data):
    rospy.loginfo(data)
    

def third():

    rospy.init_node('third_res', anonymous=True)

    rospy.Subscriber("resultat", Float64, callback)
    
    rospy.spin()

if __name__ == '__main__':
    
    third()
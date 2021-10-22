#!/usr/bin/env python

from integrationv2.srv import *
from collections import namedtuple
import rospy
from math import sqrt

def handle_find_area_from_vector(req):

    p1 = req.p1
    p2 = req.p2
    p3 = req.p3

    vA = namedtuple('Vector_A', 'x y z')( p2.x - p1.x,
                                          p2.y - p1.y,
                                          p2.z - p1.z )

    vB = namedtuple('Vector_B', 'x y z')( p3.x - p1.x,
                                          p3.y - p1.y,
                                          p3.z - p1.z )

    vC = namedtuple('Vector_C', 'x y z')( vA.y * vB.z - vB.y * vA.z,
                                          vA.x * vB.z - vB.x * vA.z,                       
                                          vA.x * vB.y - vB.x * vA.y )
    
    para = namedtuple('Parallelogram', 'area')(sqrt( vC.x**2 + vC.y**2 + vC.z**2 ))

    tri =  namedtuple('Triangle', 'area')(para.area / 2)


    print(vA)
    print(vB)
    print(vC)

    print('')

    print(para)
    print(tri)

    print("\nRequest: Point one is (%.2f, %.2f, %.2f):" % (p1.x, p1.y, p1.z))
    print("Request: Point two is (%.2f, %.2f, %.2f):" % (p2.x, p2.y, p2.z))
    print("Request: Point three is (%.2f, %.2f, %.2f):"% (p3.x, p3.y, p3.z))

    print("\nSending back response: [%.3f] \n\n" % tri.area)

    return points_to_areaResponse(tri.area)


def area_of_a_triangle_service():

    rospy.init_node('Area_service')
    s = rospy.Service('Area_service', points_to_area, handle_find_area_from_vector)
    print("\nReady to find area of the triangle.\n")
    rospy.spin()


if __name__ == "__main__":
    area_of_a_triangle_service()
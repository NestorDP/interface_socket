#!/usr/bin/env python

import rospy


class SocketInterface:

    def __init__(self):
        rospy.loginfo(rospy.get_caller_id() + "I heard")

    def send_data(senf, msg):
        rospy.loginfo("Success! You just have imported a Python")
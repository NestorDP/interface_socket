#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Image
from std_msgs.msg import String

from interface_socket.ethernet_interface import EthernetInterface


class ImageManipulator:
    def __init__(self):
        rospy.Subscriber("image_raw", Image, self.callback_image)
        self.pub = rospy.Publisher('image_filtered', Image, queue_size=10)

    def callback_image(self, data):
        # rospy.loginfo(rospy.get_caller_id() + "I heard")
        self.pub.publish(data)


def callback_string_test(data):
    skt.send(data)


if __name__ == '__main__':
    rospy.init_node('interface')
    img = ImageManipulator()
    skt = EthernetInterface('127.0.0.1', 5000)

    rospy.Subscriber("string_input", String, callback_string_test)
    pub = rospy.Publisher('string_output', String, queue_size=10)

    # while not rospy.is_shutdown():

    rospy.spin()

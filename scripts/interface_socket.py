#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Image

import clientteste


class ImageManipulator:
    def __init__(self):
        rospy.Subscriber("image_raw", Image, self.callback_image)
        self.pub = rospy.Publisher('image_filtered', Image, queue_size=10)

    def callback_image(self, data):
        # rospy.loginfo(rospy.get_caller_id() + "I heard")
        self.pub.publish(data)


if __name__ == '__main__':
    rospy.init_node('interface_socket')
    img = ImageManipulator()

    a = SocketInterface()

    # while not rospy.is_shutdown():
    rospy.spin()

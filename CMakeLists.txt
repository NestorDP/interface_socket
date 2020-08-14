cmake_minimum_required(VERSION 2.8.3)
project(interface_socket)

find_package(catkin REQUIRED COMPONENTS
  rospy
)

catkin_python_setup()

catkin_package(
 CATKIN_DEPENDS rospy sensor_msgs
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

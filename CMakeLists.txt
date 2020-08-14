cmake_minimum_required(VERSION 2.8.3)
project(interface_socket)

find_package(catkin REQUIRED COMPONENTS
  rospy
)

catkin_python_setup()

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES my_pkg
#  CATKIN_DEPENDS rospy
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

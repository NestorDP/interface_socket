cmake_minimum_required(VERSION 2.8.3)
project(interface_socket)

find_package(catkin REQUIRED COMPONENTS
  rospy
)

catkin_python_setup()

catkin_package(CATKIN_DEPENDS 
  rospy 
  std_msgs
)

install(DIRECTORY launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
  
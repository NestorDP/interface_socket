cmake_minimum_required(VERSION 2.8.3)
project(interface_socket)

find_package(catkin REQUIRED COMPONENTS
  rospy
)

catkin_python_setup()


catkin_install_python(PROGRAMS scripts/myscript
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


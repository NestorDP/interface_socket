cmake_minimum_required(VERSION 2.8.3)
project(interface_socket)

add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

find_library(INTERFACE_LIB NAMES interfacesocket)

catkin_package(
  # INCLUDE_DIRS include
  # LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp sensor_msgs
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(${PROJECT_NAME}_node src/main.cpp)
add_dependencies(${PROJECT_NAME}_node ${catkin_EXPORTED_TARGETS} )
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES} ${INTERFACE_LIB})

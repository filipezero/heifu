cmake_minimum_required(VERSION 2.8.3)
project(heifu)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  mav_msgs
  sensor_msgs
)
catkin_package(CATKIN_DEPENDS
)

#add_message_files(
#   FILES
#   CommandMotorSpeed.msg
#)


include_directories(
   INCLUDE_DIRS include
   LIBRARIES heifu
   CATKIN_DEPENDS roscpp sensor_msgs
   DEPENDS system_lib
   ${catkin_INCLUDE_DIRS}
)

if(CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)
  roslaunch_add_file_check(launch)
endif()

install(DIRECTORY images meshes launch rviz urdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})


add_executable(takeoff src/takeoff.cpp)
target_link_libraries(takeoff ${catkin_LIBRARIES})

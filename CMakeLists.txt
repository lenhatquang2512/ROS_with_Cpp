cmake_minimum_required(VERSION 3.0.2)
project(ROS_with_Cpp)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  geometry_msgs
  nav_msgs
  pcl_conversions
  pcl_ros
  rosbag
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf
  image_transport
  message_generation
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(Eigen3 REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

add_service_files(
  FILES
  AddTwoInts.srv
)

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  geometry_msgs   nav_msgs  sensor_msgs   std_msgs
)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
 INCLUDE_DIRS include 
 LIBRARIES ROS_with_Cpp
 CATKIN_DEPENDS cv_bridge geometry_msgs nav_msgs pcl_conversions pcl_ros rosbag roscpp rospy sensor_msgs std_msgs tf image_transport message_runtime
 DEPENDS system_lib EIGEN3 PCL
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

link_directories(
	include
	${OpenCV_LIBRARY_DIRS}
	${PCL_LIBRARY_DIRS}
)

add_definitions(${PCL_DEFINITIONS})


## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/helloWorld.cpp
# )

add_library(ROS_with_Cpp
  src/lidar_test_data.cpp
)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_dependencies(ROS_with_Cpp ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/helloWorld_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# catkin_install_python(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
# install(TARGETS ${PROJECT_NAME}_node
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark libraries for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_libraries.html
# install(TARGETS ${PROJECT_NAME}
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_helloWorld.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)

add_executable(helloWorld src/helloWorld.cpp)
target_link_libraries(helloWorld ${catkin_LIBRARIES})

add_executable(class_sample_test src/sample_class_main.cpp  src/sample_class.cpp)
target_link_libraries(class_sample_test ${catkin_LIBRARIES})

add_executable(file_test src/file_test.cpp)
target_link_libraries(file_test ${catkin_LIBRARIES})

add_executable(plot_test src/plot_test.cpp)
target_link_libraries(plot_test ${catkin_LIBRARIES})

add_executable(animation_test src/animation_test.cpp)
target_link_libraries(animation_test ${catkin_LIBRARIES})

add_executable(plot_sphere src/plot_sphere.cpp)
target_link_libraries(plot_sphere ${catkin_LIBRARIES})

add_executable(arguments src/arguments.cpp)
target_link_libraries(arguments ${catkin_LIBRARIES})

add_executable(vector src/vector.cpp)
target_link_libraries(vector ${catkin_LIBRARIES})

add_executable(test_pub src/test_pub.cpp)
target_link_libraries(test_pub ${catkin_LIBRARIES})

add_executable(test_sub src/test_sub.cpp)
target_link_libraries(test_sub ${catkin_LIBRARIES})

add_executable(sample_functions src/sample_functions.cpp)
target_link_libraries(sample_functions ${catkin_LIBRARIES})

add_executable(test_class_pub src/test_class_pub.cpp)
target_link_libraries(test_class_pub ${catkin_LIBRARIES})

add_executable(test_class_sub src/test_class_sub.cpp)
target_link_libraries(test_class_sub ${catkin_LIBRARIES})

add_executable(image_publisher src/image_publisher.cpp)
target_link_libraries(image_publisher ${catkin_LIBRARIES} ${OpenCV_LIBS})

add_executable(edge_extraction src/edge_extraction.cpp)
target_link_libraries(edge_extraction ${catkin_LIBRARIES} ${OpenCV_LIBS})

add_executable(tf_broadcaster src/tf_broadcaster.cpp)
target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})

add_executable(tf_listener src/tf_listener.cpp)
target_link_libraries(tf_listener ${catkin_LIBRARIES})

add_executable(turtle_tf2_broadcaster src/turtle_tf2_broadcaster.cpp)
target_link_libraries(turtle_tf2_broadcaster ${catkin_LIBRARIES})

add_executable(turtle_tf2_listener src/turtle_tf2_listener.cpp)
target_link_libraries(turtle_tf2_listener ${catkin_LIBRARIES})

# add_executable(avoid src/avoid.cpp)
# target_link_libraries(avoid ${catkin_LIBRARIES})

add_executable(pcl_ransac_test src/pcl_ransac_test.cpp)
target_link_libraries(pcl_ransac_test ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(pcl_voxelGrid_test src/pcl_voxelGrid_test.cpp)
target_link_libraries(pcl_voxelGrid_test ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(pcl_voxelGrid_class_test src/pcl_voxelGrid_class_test.cpp)
target_link_libraries(pcl_voxelGrid_class_test ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(tf_broadcast_test src/tf_broadcast_test.cpp)
target_link_libraries(tf_broadcast_test ${catkin_LIBRARIES})

add_executable(tf_listen_test src/tf_listen_test.cpp)
target_link_libraries(tf_listen_test ${catkin_LIBRARIES})

add_executable(test_lidar_node src/test_lidar_node.cpp)
target_link_libraries(test_lidar_node ${catkin_LIBRARIES} ROS_with_Cpp)

add_executable(cam_pub_test src/cam_pub_test.cpp)
target_link_libraries(cam_pub_test ${catkin_LIBRARIES} ${OpenCV_LIBS})

add_executable(cam_sub_test src/cam_sub_test.cpp)
target_link_libraries(cam_sub_test ${catkin_LIBRARIES} ${OpenCV_LIBS})

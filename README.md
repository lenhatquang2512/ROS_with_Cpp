
## ROS C++ intro package

### Requirements
* Ubuntu 20.04
* ROS Noetic (ROS1)
* PCL, OpenCV 
* Gnuplot (not actually required, but very easy to use just like matplotlib in Python)

* To install PCL,OpenCV, Gnuplot please run these commands in the terminal (easiest and quickest way to install):

`sudo apt install libpcl-dev`

`sudo apt install libopencv-dev python3-opencv`

`sudo apt install gnuplot`

* To install ROS, please follow the instructions in the ROS wiki.

### Install 

* `mkdir -p /catkin_ws/src`
* `cd ..`
* `catkin_make`
* `cd src`
* `git clone https://github.com/lenhatquang2512/ROS_with_Cpp.git`
* `cd .. & catkin_make`
* `source devel/setup.bash`


### Usage
 * Just read the src codes and run the node in the C++ file you want to run.
 * For example:
 
 `rosrun ROS_with_Cpp image_publisher`
 
 `rosrun ROS_with_Cpp edge_extraction`
 
 * You can test the launch file with tf examples using turtlesim:
 
 `roslaunch ROS_with_Cpp start_demo.launch`
 
 `roslaunch ROS_with_Cpp tf_broadcast_listen_test.launch`
 
 ![](https://github.com/lenhatquang2512/ROS_with_Cpp/blob/main/images/gif/ros_cpp_tf_demo.gif)
 
 
 * There are 2 Python codes to illustrate the "service" property of ROS, these can be tested as well.

### Reason I created this package

Maybe , this is the most intricate "helloWorld" that you will have, since it covers nearly everything that you need to know fundamentally about ROS with Cpp. Some examples can be publisher/subscriber format, service/client system, and some basic Cpp like loops, ifelse, function, class, vector, header files and file I/O are also summerized briefly. More intermediate knowledge like opencv for camera sensor and PCL for LiDAR sensor are also will be fully investigated and studied in the near future. I will continuously update this repository so that it will become the best (hopefully) "helloWorld for all" ROS user. That is my main target goal when creating this repo. 



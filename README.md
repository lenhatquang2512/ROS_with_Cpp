
## ROS C++ intro package

### Requirements
* Ubuntu 20.04
* ROS Noetic
* PCL, OpenCV 
### Install (without catkin)
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
 
 `rosrun helloWorld image_publisher`
 
 `rosrun helloWorld edge_extraction`
 
 * You can test the launch file with tf examples using turtlesim:
 
 `roslaunch helloWorld start_demo.launch`
 
 * There are 2 Python codes to illustrate the "service" property of ROS, these can be tested as well.

### Reason I created this package

Maybe , this is the most intricate "helloWorld" that you will have, since it covers nearly everything that you need to know fundamentally about ROS with Cpp. Some examples can be publisher/subscriber format, service/client system, and some basic Cpp like loops, ifelse, function, class, vector, header files and file I/O are also summerized briefly. More intermediate knowledge like opencv for camera sensor and PCL for LiDAR sensor are also will be fully investigated and studied in the near future. I will continuously update this repository so that it will become the best (hopefully) "helloWorld for all" ROS user. That is my main target goal when creating this repo. 



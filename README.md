
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

* `mkdir -p catkin_ws/src`
* `cd catkin_ws/`
* `catkin_make`
* `cd src`
* `git clone https://github.com/lenhatquang2512/ROS_with_Cpp.git`
* `cd ..`
* `catkin_make`
* `source devel/setup.bash`


### Usage
 * Just read the src codes and run the node in the C++ file you want to run.
 * For example, type `roscore` in the current terminal, open a new terminal, and type (always source devel/setup.bash in a new terminal before running):
 
 `source devel/setup.bash`
 
 `rosrun ROS_with_Cpp animation_test`
 
 ![](https://github.com/lenhatquang2512/ROS_with_Cpp/blob/main/images/gif/ros_with_animation_plot_demo.gif)
 
 `rosrun ROS_with_Cpp plot_test`
 
![](https://github.com/lenhatquang2512/ROS_with_Cpp/blob/main/images/gif/plot_test_demo.png)

To show the image above, simply type:

`cd catkin_ws/`

`gnuplot`

`splot "data.txt"`

`rosrun ROS_with_Cpp plot_sphere`
 
![](https://github.com/lenhatquang2512/ROS_with_Cpp/blob/main/images/gif/plot_sphere.png)
 
 * You can test launch files with tf examples using turtlesim, image publish and edge extraction, or tf broadcast and listen test.
 
 * Test control the simulated turtle:
 
 `roslaunch ROS_with_Cpp helloWorld.launch`
 
 ![](https://github.com/lenhatquang2512/ROS_with_Cpp/blob/main/images/gif/ros_with_cpp_helloWorld_demo.gif)
 
 * You can test your laptop camera by launching:
 
 `roslaunch ROS_with_Cpp camera_pub_sub_test.launch`
 
 ![](https://github.com/lenhatquang2512/ROS_with_Cpp/blob/main/images/gif/cam_test.png)
 
 * Some examples with edge extraction:
 
 `roslaunch ROS_with_Cpp image_publish_edge_extract.launch`
 
 ![](https://github.com/lenhatquang2512/ROS_with_Cpp/blob/main/images/gif/ros_with_cpp_image_edge_demo.gif)
 
 * tf broadcast and listen test and visualise in Rviz:

 `roslaunch ROS_with_Cpp tf_broadcast_listen_test.launch`
 
 ![](https://github.com/lenhatquang2512/ROS_with_Cpp/blob/main/images/gif/ros_cpp_tf_demo.gif)
 
 
 * There are 2 Python codes to illustrate the "service" property of ROS, these can be tested as well.

### Reason I created this package

* Maybe , this is the most intricate "helloWorld" that you will have, since it covers nearly everything that you need to know fundamentally about ROS with Cpp. Some examples can be publisher/subscriber format, service/client system, and some basic Cpp like loops, ifelse, function, class, vector, header files and file I/O are also summerized briefly. More intermediate knowledge like opencv for camera sensor and PCL for LiDAR sensor are also will be fully investigated and studied in the near future. I will continuously update this repository so that it will become the best (hopefully) "helloWorld for all" ROS user. That is my main target goal when creating this repo. 

* You can follow the ROS wiki tutorial along with this repo to understand better about ROS. Usually the ROS tutorial covers too many stuffs but if you want to quicky integrate into a ROS project, this repo is for you.

*Update 29 Jan 2023 : More URDF files, interact with Gazebo, more equivalent Python codes, rosserial with Arduino, etc.. will be added soon. I am thinking even moving to ROS2 as well. Although the name of this repo is "ROS with C++", but I will not limit it to only C++.





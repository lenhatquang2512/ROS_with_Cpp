#include<ros/ros.h>
#include<iostream>
#include<ros_with_cpp/SampleClass.h>

int main(int argc, char **argv)
{
    ros::init(argc,argv,"class_sample_test");
    ros::NodeHandle nh;

    SampleClass object;
    return 0;
}

#include<ros/ros.h>
#include<iostream>
#include<helloWorld/SampleClass.h>

int main(int argc, char **argv)
{
    ros::init(argc,argv,"class_sample_test");
    ros::NodeHandle nh;

    SampleClass object;
    return 0;
}

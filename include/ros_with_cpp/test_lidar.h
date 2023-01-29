#pragma once

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32MultiArray.h>
#include <tf/tf.h>
#include <iostream>
#include <Eigen/Dense>
#include <vector>


class Lidar2DTest
{
private:
    double hz;
    ros::NodeHandle nh;
    ros::Subscriber scan_sub;
    ros::Publisher obstacle_points_pub;
    // sensor_msgs::LaserScan scan;
    std_msgs::Float32MultiArray obstacle_points;
    std::vector<std::vector<float>> obs_list;
    bool scan_updated;
public:
    Lidar2DTest(void);
    // void process(void);
    void spin(void);
    void scan_callback(const sensor_msgs::LaserScanConstPtr&);
    // std::vector<std::vector<float>> scan_to_obs(float x, float y);
    void printObs(const std::vector<std::vector<float>>& vec);
    // ~Lidar2DTest();
};
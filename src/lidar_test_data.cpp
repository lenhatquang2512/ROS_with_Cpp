#include "ros_with_cpp/test_lidar.h"

Lidar2DTest::Lidar2DTest(void):
    nh("~"), scan_updated(false)
{
    nh.param("hz", hz, {20});
    ROS_INFO("=== Lidar2DTest ===");
    
    // Subscribe to the /scan topic
    scan_sub = nh.subscribe("/scan", 1, &Lidar2DTest::scan_callback, this);

    // Advertise the obstacle_points topic
    obstacle_points_pub = nh.advertise<std_msgs::Float32MultiArray>("/obstacle_points", 10);
}

void Lidar2DTest::scan_callback(const sensor_msgs::LaserScanConstPtr &msg)
{
    // scan = *msg;
    scan_updated = true;

    // Clear the previous data
    obstacle_points.data.clear();

    //list of obstacles
    // std::vector<std::vector<float>> obs_list;
    obs_list.clear();

    for (int i = 0; i < msg->ranges.size(); i++)
    {
        // Check if the range is valid
        if (!std::isnan(msg->ranges[i]))
        {
            float angle = msg->angle_min + i * msg->angle_increment;

            // Extract x and y coordinates from the scan data
            float x = msg->ranges[i] * cos(angle);
            float y = msg->ranges[i] * sin(angle);
            std::vector<float> obs_state = {x, y};
            obs_list.push_back(obs_state);

            obstacle_points.data.push_back(x);
            obstacle_points.data.push_back(y);
        }
    }

    // Publish the obstacle points
    obstacle_points_pub.publish(obstacle_points);

    printObs(obs_list);
}

void Lidar2DTest::printObs(const std::vector<std::vector<float>>& vec)
{
    for (const auto& inner_vec : vec)
    {
        for (const auto& value : inner_vec)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}


void Lidar2DTest::spin(void) {
    ros::spin();
}

// void Lidar2DTest::process(void)
// {
//     ros::Rate loop_rate(HZ);

//     while(ros::ok()){
//         ROS_INFO("==========================================");
//         double start = ros::Time::now().toSec();

//         std::vector<std::vector<float>> obs_list;
//         obs_list = scan_to_obs();
//         scan_updated = false;

//         ros::spinOnce();
//         loop_rate.sleep();
//         ROS_INFO_STREAM("loop time: " << ros::Time::now().toSec() - start << "[s]");
//     }

// }
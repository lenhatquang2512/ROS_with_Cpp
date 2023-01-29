#include "ros_with_cpp/test_lidar.h"

/// @brief 
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_lidar_node");
    // std::cout << "hoge" << std::endl;
    Lidar2DTest obj;
    obj.spin();
    return 0;
}

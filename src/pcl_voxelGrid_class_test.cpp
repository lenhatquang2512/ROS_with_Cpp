#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

// Point Cloud Library（PCL)
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/point_cloud.h>

class VoxelGridFilter {
private:
    ros::NodeHandle nh_;
    ros::Subscriber pointsSub_;
    ros::Publisher pointsPub_;
    std::string inputTopicName_, outputTopicName_;
    double filtereResoX_, filtereResoY_, filtereResoZ_;

public:
    VoxelGridFilter(void):
        nh_("~"),
        inputTopicName_("/camera/depth_registered/points"),
        outputTopicName_("/camera/depth_registered/filtered_points"),
        filtereResoX_(0.1),
        filtereResoY_(0.1),
        filtereResoZ_(0.1)
    {
        nh_.param("raw_points_name", inputTopicName_, inputTopicName_);
        nh_.param("filtered_points_name", outputTopicName_, outputTopicName_);
        nh_.param("vgf_reso_x", filtereResoX_, filtereResoX_);
        nh_.param("vgf_reso_y", filtereResoY_, filtereResoY_);
        nh_.param("vgf_reso_z", filtereResoZ_, filtereResoZ_);

        pointsSub_ = nh_.subscribe(inputTopicName_, 1, &VoxelGridFilter::pointsCB, this);

        pointsPub_ = nh_.advertise<sensor_msgs::PointCloud2>(outputTopicName_, 1);
    };

    ~VoxelGridFilter(void) {};

    void spin(void);

    void pointsCB(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &msg);
};

void VoxelGridFilter::spin(void) {
    ros::spin();
}

void VoxelGridFilter::pointsCB(const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr &msg) {

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr inCloud(new pcl::PointCloud<pcl::PointXYZRGB>(*msg));
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr outCloud(new pcl::PointCloud<pcl::PointXYZRGB>());
    pcl::VoxelGrid<pcl::PointXYZRGB> filter;
    filter.setLeafSize(filtereResoX_, filtereResoY_, filtereResoZ_);
    filter.setInputCloud(inCloud);
    filter.filter(*outCloud);

    pointsPub_.publish(outCloud);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "pcl_voxelGrid_class_test");

    VoxelGridFilter vgf;
    vgf.spin();

    return 0;
}
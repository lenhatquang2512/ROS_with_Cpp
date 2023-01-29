#include <ros/ros.h>
#include<std_msgs/Header.h>
#include <sensor_msgs/Image.h>
#include<opencv2/opencv.hpp>
// #include <opencv2/highgui/highgui.hpp>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>

class CamPub
{
private:
    ros::NodeHandle nh;
    std::string cam_topic_name;
    std::string cam_path;
    ros::Rate loopRate;
    image_transport::ImageTransport it;
    image_transport::Publisher imagePub;
    const int CAMERA_INDEX = 0; // 0 reads from your default camera
    
public:
    CamPub(void);
    ~CamPub(void) {};
    void spin(void);
};

CamPub::CamPub(void):
    nh("~"),
    cam_topic_name("/image_raw"),
    // cam_path("/dev/video0"),
    loopRate(10),
    it(nh)
{
    nh.param("cam_topic_name",cam_topic_name,cam_topic_name);
    // nh.param("cam_path",cam_path,cam_path);
    
    std::cout << "Image is being published to the topic" << cam_topic_name << std::endl ;
    imagePub = it.advertise(cam_topic_name,1);
}

void CamPub::spin(void){
    
    // cv::namedWindow("Display Window");
    // cv::VideoCapture capture(CAMERA_INDEX);
    cv::VideoCapture *capture = new cv::VideoCapture(CAMERA_INDEX, cv::CAP_GSTREAMER);

    if (!capture->isOpened()) {
        ROS_ERROR_STREAM("Failed to open camera with index " << CAMERA_INDEX << "!");
        ros::shutdown();
    }

    while (ros::ok())
    {
        ros::spinOnce();

        // cv::Mat image = cv::imread(cam_path,1);
        cv::Mat image;
        *capture >> image;

        if (image.empty()) {
            ROS_ERROR_STREAM("Failed to capture image!");
            ros::shutdown();
        }
        
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",image).toImageMsg();
        imagePub.publish(msg);

        // cv::waitKey(1); // Display image for 1 millisecond
 
        loopRate.sleep();
    }

    // Shutdown the camera
    // capture.release();

}


int main(int argc, char **argv)
{
    ros::init(argc,argv,"cam_pub_test");
    
    CamPub obj;
    obj.spin();

    return 0;
}
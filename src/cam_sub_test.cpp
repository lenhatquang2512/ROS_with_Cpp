#include<ros/ros.h>
#include<std_msgs/Header.h>
#include<sensor_msgs/Image.h>
#include<opencv2/opencv.hpp>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>

class CamSub
{
private:
    ros::NodeHandle nh;
    image_transport::ImageTransport it;
    image_transport::Publisher imagePub;
    image_transport::Subscriber imageSub;
public:
    CamSub(void);
    ~CamSub(void) {};
    void spin(void);
    void imageCB(const sensor_msgs::Image::ConstPtr &msg);
};

CamSub::CamSub(void):
    nh("~"),
    it(nh)
{
    imageSub = it.subscribe("/image_raw",1,&CamSub::imageCB,this);
}

void CamSub::spin(void){
    ros::spin();
}

void CamSub::imageCB(const sensor_msgs::Image::ConstPtr &msg){
    // Pointer used for the conversion from a ROS message to 
    // an OpenCV-compatible image
    cv_bridge::CvImagePtr cv_ptr;
   
    try
    { 
        // Convert the ROS message  
        cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
        return;
    }

    // Store the values of the OpenCV-compatible image
    // into the current_frame variable
    cv::Mat current_frame = cv_ptr->image;
     
    // Display the current frame
    cv::imshow("mycam", current_frame); 
     
    // Display frame for 30 milliseconds
    cv::waitKey(30);
}



int main(int argc, char **argv) {
    ros::init(argc, argv, "cam_sub_test");

    CamSub obj;
    obj.spin();

    return 0;
}
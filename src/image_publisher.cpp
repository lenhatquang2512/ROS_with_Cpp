#include<ros/ros.h>
#include<iostream>
#include<string>
#include<std_msgs/Header.h>
#include<sensor_msgs/Image.h>
#include<opencv2/opencv.hpp>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>

class ImagePublisher
{
private:
    ros::NodeHandle nh_;
    // ros::Publisher imagePub_;
    std::string outputTopicName_;
    ros::Rate loopRate_;
    std::string imageDir_;
    image_transport::ImageTransport it_;
    image_transport::Publisher imagePub_;
public:
    ImagePublisher(void);
    ~ImagePublisher(void){};
    void spin(void);
};

ImagePublisher::ImagePublisher(void):
    nh_("~"),
    outputTopicName_("/image_test"),
    loopRate_(1.0),
    imageDir_("/home/quang_le/intro_ros_ws/src/helloWorld/images/"),
    it_(nh_)
{
    nh_.param("test_msg_name", outputTopicName_, outputTopicName_);
    // imagePub_ = nh_.advertise<sensor_msgs::Image>(outputTopicName_, 1);
    imagePub_ = it_.advertise(outputTopicName_, 1);
}

void ImagePublisher::spin(void)
{
    int imageIdx = 0;
    while (ros::ok())
    {
        ros::spinOnce();
        //start code

        std::string imageFileName = imageDir_+ std::to_string(imageIdx) + ".jpg";
        std::cout << "imageFileName = " << imageFileName.c_str() << std::endl;

        cv::Mat image = cv::imread(imageFileName,1);
        std_msgs::Header header;
        header.stamp = ros::Time::now();
        header.frame_id = "/image";
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(header,"bgr8",image).toImageMsg();
        imagePub_.publish(msg);

        imageIdx++;
        if (imageIdx >4)
        {
            imageIdx = 0;
        }
        
        //end code
        loopRate_.sleep();
    }
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"image_publisher");
    // ros::NodeHandle nh;
    
    ImagePublisher publisher;
    publisher.spin();


    return 0;
}
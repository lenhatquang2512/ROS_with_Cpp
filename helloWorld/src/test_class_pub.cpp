#include <ros/ros.h>
#include <std_msgs/Header.h>

class TestClassPub {
private:
    ros::NodeHandle nh_;
    ros::Publisher headerPub_;
    std::string outputTopicName_;
    ros::Rate loopRate_;

public:
    // コンストラクタです．
    TestClassPub(void):
        nh_("~"),
        outputTopicName_("/test_msg"),
        loopRate_(10.0)
    {
        nh_.param("test_msg_name", outputTopicName_, outputTopicName_);

        headerPub_ = nh_.advertise<std_msgs::Header>(outputTopicName_, 1);
    }

    // デコンストラクタですが何もしません．
    ~TestClassPub(void) {};

    // メインループのプロトタイプ宣言です．
    void spin(void);
};

// メインループです．
// headerをパブリッシュします．
void TestClassPub::spin(void) {
    while (ros::ok()) {
        ros::spinOnce();
        std_msgs::Header header;
        header.stamp = ros::Time::now();
        headerPub_.publish(header);
        printf("Publish time is %lf\n", header.stamp.toSec());
        loopRate_.sleep();
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_class_pub");

    // クラスを宣言してループに入ります．
    TestClassPub node;
    node.spin();

    return 0;
}
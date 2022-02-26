#include <ros/ros.h>
#include <std_msgs/Header.h>

class TestClassSub {
private:
    ros::NodeHandle nh_;
    ros::Subscriber headerSub_;
    std::string inputTopicName_;

public:
    TestClassSub(void):
        nh_("~"),
        inputTopicName_("/test_msg")
    {
        nh_.param("test_msg_name", inputTopicName_, inputTopicName_);

        // クラス内でサブスクライバーを宣言する際は，コールバック関数の記述が変わり，最後にthisが入ります．
        headerSub_ = nh_.subscribe(inputTopicName_, 1, &TestClassSub::headerCB, this);
    }

    ~TestClassSub(void) {};

    // メインループとコールバック関数のプロトタイプ宣言です．
    void spin(void);
    void headerCB(const std_msgs::Header::ConstPtr &msg);
};

// メインループですが，単にros::spin()をするだけです．
void TestClassSub::spin(void) {
    ros::spin();
}

// headerのコールバック関数です．
void TestClassSub::headerCB(const std_msgs::Header::ConstPtr &msg) {
    printf("Subscribe time is %lf\n", msg->stamp.toSec());
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_class_sub");

    // クラスを宣言してメインループに入ります．
    TestClassSub node;
    node.spin();

    return 0;
}
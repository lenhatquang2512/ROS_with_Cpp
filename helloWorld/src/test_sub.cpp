#include <ros/ros.h>
#include <std_msgs/Header.h>

// /test_msgのコールバック関数です．
void headerCB(const std_msgs::Header::ConstPtr &msg) {
    // 受け取ったメッセージ（header）のタイムスタンプを表示します．
    printf("Subscribe time is %lf\n", msg->stamp.toSec());
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_sub");
    ros::NodeHandle nh("~");

    // Subscriberを定義します．これを使ってメッセージを受信します．
    // /test_msgを受信した場合にheaderCBというコールバック関数を実行します．
    ros::Subscriber headerSub = nh.subscribe("/test_msg", 1, headerCB);

    // ROSの受信側は，基本的にメッセージが来た際にコールバック関数を実行します．
    // なので，コールバックの設定だけしたら後はros::spin()で待機します．
    ros::spin();

    return 0;
}
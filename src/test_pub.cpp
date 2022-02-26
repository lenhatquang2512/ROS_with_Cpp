#include <ros/ros.h>

// 使用するメッセージをインクルードします．
// ROSでは基本的にプログラム間でメッセージのやり取りを行いますので，
// メッセージの「型」を理解することがとても大切になります．
#include <std_msgs/Header.h>

int main(int argc, char **argv) {
    // ROSでプログラムするときの最初のおまじないです．
    // test_pubという名前がこのプログラム（ノード）に与えられます（ROSで管理されます）．
    ros::init(argc, argv, "test_pub");

    // ros::NodeHandle nh; と宣言しても良いのですが，nh("~"); としてください．
    // これもおまじないとして覚えておいてください．
    ros::NodeHandle nh("~");

    // Publisherを定義します．これを使って，このプログラムからメッセージを送信します．
    // /test_msgという名前で送信されます（/を付けないと/test_pub/test_msgとなるので注意）．
    // 受信側も受信するためにこの名前を知っておく必要があります．
    // 1は送信のバッファー数です（細かい話はおいておきます）．
    ros::Publisher headerPub = nh.advertise<std_msgs::Header>("/test_msg", 1);

    // スリープ時間を設定します（今回は10Hzです）．
    ros::Rate loopRate(10.0);

    // while (ros::ok()) としておくことで，Ctrl + cが入力されるまで動いてくれます．
    while (ros::ok()) {
        // ROSのメッセージの送受信とかを処理するようなものです．
        // 必ずメインループの中でコールしてください．
        ros::spinOnce();

        // 送信するメッセージを定義します．
        // 今回はheaderのタイムスタンプを現時刻にセットして送信します．
        std_msgs::Header header;
        header.stamp = ros::Time::now();

        // これで実際に送信します．
        headerPub.publish(header);
        printf("Publish time is %lf\n", header.stamp.toSec());

        // 設定した時間スリープします．
        loopRate.sleep();
    }

    return 0;
}
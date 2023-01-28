#include <ros/ros.h>
#include <tf/transform_listener.h>

int main(int argc, char **argv)
{
    ros::init(argc,argv,"tf_listen_test");
    ros::NodeHandle nh("~");

    float hz = 10.0f;
    float duration = 2.0f;
    std::string source_frame = "/map";
    std::string target_frame = "/laser";

    tf::TransformListener tf_listener;
    ros::Rate loopRate(hz);

    while (ros::ok())
    {
        ros::spinOnce();

        //do something
        
        tf::StampedTransform map2Baselink;
        try
        {
            ros::Time target_time = ros::Time::now();
            tf_listener.waitForTransform(source_frame, target_frame, target_time, ros::Duration(duration));
            tf_listener.lookupTransform(source_frame, target_frame, target_time, map2Baselink);
        }
        catch (tf::TransformException ex)
        {
            ROS_ERROR("%s", ex.what());
            continue;
        }


        tf::Quaternion q(map2Baselink.getRotation().x(),
            map2Baselink.getRotation().y(),
            map2Baselink.getRotation().z(),
            map2Baselink.getRotation().w());
        double roll, pitch, yaw;
        tf::Matrix3x3 m(q);
        m.getRPY(roll, pitch, yaw);
        float x = map2Baselink.getOrigin().x();
        float y = map2Baselink.getOrigin().y();
        float z = map2Baselink.getOrigin().z();

        std::cout << "x = " << x << " ,y = " << y << " ,z= " << z << std::endl;

        loopRate.sleep();
    }
    return 0;
}

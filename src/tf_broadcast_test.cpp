#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

/// @brief main function
/// @param argc 
/// @param argv 
/// @return 0
int main(int argc, char **argv)
{
    ros::init(argc,argv,"tf_broadcast_test");
    ros::NodeHandle nh("~");

    float hz = 10.0f;
    float dt = 1.0f/hz;
    float x = 0.0f;
    float y = 0.0f;
    float yaw = 0.0f;
    float v = 0.8f;
    float w = 0.8f;

    ros::Rate loopRate(hz);
    tf::TransformBroadcaster br;

    while (ros::ok())
    {
        ros::spinOnce();

        // do something
        tf::Transform tf;
        tf::Quaternion q;

        x+= v * dt * cos(yaw);
        y+= v * dt * sin(yaw);
        yaw+= w * dt;
        if(yaw < -M_PI)
            yaw += 2.0f * M_PI;
        if(yaw > M_PI)
            yaw -= 2.0f * M_PI;

        tf.setOrigin(tf::Vector3(x,y,0.0));
        q.setRPY(0.0,0.0,yaw);
        tf.setRotation(q);

        br.sendTransform(tf::StampedTransform(tf,
                    ros::Time::now(),"/map","/base_link"));


        loopRate.sleep();
    }
    

    return 0;
}

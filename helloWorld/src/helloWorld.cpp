#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<turtlesim/Pose.h>
#include<std_srvs/Empty.h>

class helloWorld
{
private:
    float x_,y_,theta_,v_,w_;
public:
    helloWorld(void);
    ~helloWorld();
    inline void setPose(float x, float y,float theta);
};

helloWorld::helloWorld(void):
    x_(0.0f),y_(0.0f),theta_(0.0),v_(0.0),w_(0.0)
{
    //do nothing
}

helloWorld::~helloWorld()
{
    //do nothing too
}

inline void helloWorld::setPose(float x,float y,float theta)
{
    x_ = x;
    y_ = y;
    theta_ = theta;
}


void stateCallback(const turtlesim::Pose::ConstPtr &msg)
{
    helloWorld turtleState;
    float x = msg->x;
    float y = msg->y;
    float theta = msg->theta;
    float v = msg->linear_velocity;
    float w = msg->angular_velocity;
    turtleState.setPose(x,y,theta);

    std::cout << "x = " << x << " y = " << y << " theta  = " << theta << std::endl;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"helloWorld");
    ros::NodeHandle nh;

    ros::Publisher cmd_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);
    ros::Subscriber cms_sub = nh.subscribe<turtlesim::Pose>("/turtle1/pose",100,stateCallback);

    ros::ServiceClient resetClient = nh.serviceClient<std_srvs::Empty>("/reset");

    geometry_msgs::Twist velo_msg;

    float publishHz = 10.0;
    ros::Rate loopRate(publishHz);

    double initial_time = ros::Time::now().toSec();
    int i = 0;
    while (ros::ok())
    {
        ros::spinOnce();

        velo_msg.linear.x = 2.0;
        velo_msg.angular.z = 0.7;
        cmd_pub.publish(velo_msg);

        double this_time = ros::Time::now().toSec();

        if((this_time - initial_time) >= 2.0)
        {
            velo_msg.linear.x = 0.0;
            velo_msg.angular.z = 0.0;
            cmd_pub.publish(velo_msg);

            break;
        }

        i++;
        loopRate.sleep();
    }

    std_srvs::Empty reset_srv;
    resetClient.call(reset_srv);
    
    return 0;
}

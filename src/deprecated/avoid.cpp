#include<ros/ros.h>
#include<nav_msgs/OccupancyGrid.h>
#include<gazebo_msgs/ModelStates.h>
#include<std_msgs/Float32MultiArray.h>
// #include<csv_file.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include<string>
#include<cmath>


void quat2rpy(float qx, float qy, float qz, float qw,
                    double *roll, double *pitch, double *yaw) 
{
    // roll (x-axis rotation)
    double sinr_cosp = 2 * (qw * qx + qy * qz);
    double cosr_cosp = 1 - 2 * (qx * qx + qy * qy);
    *roll = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = 2 * (qw * qy - qz * qx);
    if (std::abs(sinp) >= 1)
        *pitch = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        *pitch = std::asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (qw * qz + qx * qy);
    double cosy_cosp = 1 - 2 * (qy * qy + qz * qz);
        *yaw = std::atan2(siny_cosp, cosy_cosp);
}

class Obstacle
{
private:
    ros::NodeHandle nh_;
    ros::Subscriber obstacleSub_;
public:
    std::vector<int> data;
    Obstacle(void):
        nh_("~")
    {
        obstacleSub_ = nh_.subscribe<nav_msgs::OccupancyGrid>("/grid_map", 1, &Obstacle::obstacleCB, this);

    }

    void obstacleCB(const nav_msgs::OccupancyGrid::ConstPtr &msg)
    {
        static int i = 0;
        data[i] = msg->data[i];
        i++;
    }
};


class State
{
private:
    ros::NodeHandle nh_;
    ros::Subscriber stateSub_;
    Eigen::Vector3f current_position;
    Eigen::Vector3f current_orientation;
    float velocity;
public:
    State(void):
        nh_("~")
    {
        current_position(0) =  0;
        current_position(1) = 0;
        current_position(2) = 0;
        current_orientation(0) = 0;
        current_orientation(1) = 0;
        current_orientation(2) = 0;

        stateSub_ = nh_.subscribe<gazebo_msgs::ModelStates>("/gazebo/model_states",1,&State::stateCB,this);
    }

    void stateCB(const gazebo_msgs::ModelStates::ConstPtr &msg)
    {
        current_position(0) = msg->pose[2].position.x;
        current_position(1) = msg->pose[2].position.y;
        current_position(2) = msg->pose[2].position.z;
        velocity = std::pow(msg->twist[2].linear.x,2) + std::pow(msg->twist[2].linear.y,2) +std::pow(msg->twist[2].linear.z,2);

        //orientation
        double roll, pitch, yaw;
        float qx = msg->pose[2].orientation.x;
        float qy = msg->pose[2].orientation.y;
        float qz = msg->pose[2].orientation.z;
        float qw = msg->pose[2].orientation.w;
        quat2rpy(qx, qy, qz, qw, &roll, &pitch, &yaw);

        current_orientation(0) = float(roll);
        current_orientation(1) = float(pitch);
        current_orientation(2) = float(yaw);
    }

};

void check_obstacle(Obstacle obstacle,Eigen::MatrixXf tentacles_set, std::vector<int> *candidate_1,std::vector<int> *candidate_2,std::vector<int> *candidate_3)
{

    bool first_flag = false;
    bool second_flag = false;
    bool third_flag = false;

    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;

    int i = 0, j= 0, k = 0, l=0;

    while (i < (tentacles_set.rows() - 420))
    {
        for (j = 0; j < tentacles_set.cols() ; j++)
        {
            if (obstacle.data[tentacles_set(i,j)] == 100)
            {
                counter1 += 1;
                first_flag = true;
                break;
            }
            
        }

        if (first_flag)
        {
            first_flag = false;
            i+= 421;
        }
        else{
             i+=1;
             j = 0;
             for (k = 0; k < 20; k++)
             {
                for (j = 0; j < tentacles_set.cols(); j++)
                {
                    if (obstacle.data[tentacles_set(i,j)] == 100)
                    {
                        counter2 += 1;
                        second_flag = true;
                        break;
                    }
                }

                if (second_flag)
                {
                    second_flag = false;
                    i+= 21;
                }
                else{
                    i+=1;
                    j = 0;
                    for (l = 0; l < 20; l++)
                    {
                        for (j = 0; j < tentacles_set.cols(); j++)
                        {
                            if (obstacle.data[tentacles_set(i,j)] == 100)
                            {
                                counter3 += 1;
                                third_flag = true;
                                break;
                            }
                        }

                        if (third_flag)
                        {
                            third_flag = false;
                        }
                        else{
                            candidate_1->push_back(i-k-1-l-1);
                            candidate_2->push_back(i-l-1);
                            candidate_3->push_back(i);
                            
                        }

                        i+=1;

                    }

                }
                        
             }
             
        }
        
        
    }

}


int main(int argc, char  **argv)
{
    Eigen::Vector3f goal;
    goal(0) = 10;
    goal(1) = 10;
    goal(2) = 1;

    Eigen::MatrixXf v_low;
    Eigen::MatrixXf v_middle;
    Eigen::MatrixXf v_high;

    ros::init(argc,argv,"create_target");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<std_msgs::Float32MultiArray>("/target",1);

    try
    {
        int x;
        int count_x = 0;
        FILE *fp = fopen("tentacles_v0.csv","r");
        while(fscanf(fp,"%d",&x) != EOF)
        {
            v_low(count_x) = x;
            count_x++;
            std::cout << "Loading_OK_v0: " << v_low.size() << std::endl;
        }
    
        fclose(fp);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "Loading_Error_v0" << std::endl;
    }
    
    try
    {
        int y;
        int count_y = 0;
        FILE *fp = fopen("tentacles_v1.csv","r");
        while(fscanf(fp,"%d",&y) != EOF)
        {
            v_middle(count_y) = y;
            count_y++;
            std::cout << "Loading_OK_v1: " << v_middle.size() << std::endl;
        }
    
        fclose(fp);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "Loading_Error_v1" << std::endl;
    }

    try
    {
        int z;
        int count_z = 0;
        FILE *fp = fopen("tentacles_v2.csv","r");
        while(fscanf(fp,"%d",&z) != EOF)
        {
            v_high(count_z) = z;
            count_z++;
            std::cout << "Loading_OK_v2: " << v_high.size() << std::endl;
        }
    
        fclose(fp);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "Loading_Error_v2" << std::endl;
    }
    
    ros::Rate loopRate(10);
    while (ros::ok())
    {
        ros::spinOnce();


        loopRate.sleep();
    }
    


    return 0;
}




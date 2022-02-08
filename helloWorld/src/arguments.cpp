#include<ros/ros.h>
#include<iostream>
#include<string>

int main(int argc, char **argv)
{
    ros::init(argc,argv,"arguments");
    ros::NodeHandle nh;

    std::cout << "argc = " << argc << std::endl;
    std::cout << "argv[0] = " << argv[0] << std::endl;
    std::cout << "argv[1] = " << argv[1] << std::endl;

    int val1 = atoi(argv[1]);
    printf("%d\n",val1);

    float val2 = atof(argv[2]);
    printf("%f\n",val2);

    // FILE *fp = fopen(argv[1],"r");
    

    return 0;
}
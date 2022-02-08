#include<ros/ros.h>
#include<iostream>
#include<string>
#include<random>

void writeRandom2D(std::string fname)
{
    FILE *fp = fopen(fname.c_str(),"w");

    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> rand(0,99);

    for (int i = 0; i < 100; i++)
    {
        float x = float(rand(mt)) / 100.0f;
        float y = float(rand(mt)) / 100.0f;

        fprintf(fp,"%f %f\n",x,y);
    }

    fclose(fp);
}

void writeRandom3D(std::string fname)
{
    FILE *fp = fopen(fname.c_str(),"w");

    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> rand(0,100);

    for (int i = 0; i < 100; i++)
    {
        float x = float(rand(mt)) / 100.0f;
        float y = float(rand(mt)) / 100.0f;
        float z = float(rand(mt)) / 100.0f;

        fprintf(fp,"%f %f %f\n",x,y,z);
    }

    fclose(fp);
}

void writeSinCurve(std::string fname)
{
    FILE *fp = fopen(fname.c_str(),"w");

    for (float t = 0.0f; t <= 2.0 * M_PI; t+= 0.01f)
    {
        float y = std::sin(t);
        fprintf(fp,"%f %f\n",t,y);
    }

    fclose(fp);
}

void write3DData(std::string fname)
{
    FILE *fp = fopen(fname.c_str(),"w");

    for (float x = -1.0f; x <= 1.0f; x+= 0.1f)
    {
        for (float y = -1.0f; y <= 1.0f; y+= 0.1f)
        {
            float z = std::sin(3.0f * x) * std::cos(3.0f * y);
            fprintf(fp,"%f %f %f\n",x,y,z);
        }

        fprintf(fp,"\n");
    }

    fclose(fp); //make mesh
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"plot_test");
    ros::NodeHandle nh;

    std::string fname = "data.txt";

    // writeRandom2D(fname);
    // writeRandom3D(fname);
    // writeSinCurve(fname);
    write3DData(fname);

    return 0;
}

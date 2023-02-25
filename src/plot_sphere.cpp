#include <iostream>
#include<ros/ros.h>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define pi M_PI

struct Point
{
    float x;
    float y;
    float z;
};

class Plot_path
{
private:
    std::string fname;
    std::vector<Point> v;
    float R;
    float step_theta;
    float step_phi;
public:
    Plot_path(void):
        fname("data_sphere.txt"),
        R(3.0f),
        step_theta(0.1f),
        step_phi(0.1f)
        {
            getVector();
            print_data(fname,v);
            print_vec(v);
            animationPlot(fname);
        };

    void getVector(void);
    void print_data(std::string fname, std::vector<Point> &v);
    void print_vec(const std::vector<Point> &v);
    void animationPlot(std::string fname);
    // ~Plot_path();
    
};

void Plot_path::animationPlot(std::string fname){
    static FILE *gp;
    if(gp == NULL)
    {
        gp = popen("gnuplot -persist","w");
        fprintf(gp,"set yrange [-3.0:3.0]\n");
        fprintf(gp,"set xrange [-3.0:3.0]\n");
        fprintf(gp,"set zrange [-3.0:3.0]\n");
        fprintf(gp, "set colors classic\n");
        fprintf(gp, "set grid\n");
        // fprintf(gp, "set size ratio 1 1\n");
        fprintf(gp, "set xlabel \"X [m]\" \n");
        fprintf(gp, "set ylabel \"Y [m]\" \n");
        fprintf(gp, "set zlabel \"Z [m]\" \n");
        fprintf(gp, "set tics font \"Arial, 14\"\n");
        fprintf(gp, "set xlabel font \"Arial, 14\"\n");
        fprintf(gp, "set ylabel font \"Arial, 14\"\n");
        fprintf(gp, "set zlabel font \"Arial, 14\"\n");
    }

    // fprintf(gp,"splot \"%s\" lt -1 w l t \"Path\"\n",fname.c_str());
    fprintf(gp,"splot \"%s\" w l  \n",fname.c_str());
    fflush(gp);

    fclose(gp);

    int retVal = system("killall -9 gnuplot\n");
}

void Plot_path::print_vec(const std::vector<Point> &v){
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i].x << " " << v[i].y << " " << v[i].z  << std::endl; 
    }

}

void Plot_path::print_data(std::string fname, std::vector<Point> &v){
    std::ofstream MyFile(fname);

    for (int i = 0; i < v.size(); ++i)
    {
        MyFile << v[i].x << " " << v[i].y << " " << v[i].z  << std::endl; 
    }

    MyFile.close();

}

void Plot_path::getVector(void){
    for (float theta = 0; theta <= pi; theta = theta + step_theta)
    {
        for (float phi = 0; phi < 2* pi; phi = phi + step_phi)
        {
            Point p;
            p.x = R * sin(theta) * cos(phi);
            p.y = R * sin(theta) * sin(phi);
            p.z = R * cos(theta);

            v.push_back(p);
        }
    }

}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"plot_sphere");
    ros::NodeHandle nh;

    Plot_path obj;

    return 0;
}
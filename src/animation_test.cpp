#include<ros/ros.h>
#include<iostream>
#include<string>
#include<random>
#include<unistd.h>

void writeFile(std::string fname, double time)
{
    static bool isFirst = true;
    FILE *fp;

    if(isFirst)
    {
        fp = fopen(fname.c_str(),"w");
    }
    else
    {
        fp = fopen(fname.c_str(),"a");
    }

    double y1 = std::sin(time);
    double y2 = std::cos(time);
    fprintf(fp,"%lf %lf %lf\n",time,y1,y2);
    fclose(fp);

    isFirst = false;
}

void animationPlot(std::string fname, double time)
{
    static FILE *gp;
    if(gp == NULL)
    {
        gp = popen("gnuplot -persist","w");
        fprintf(gp,"set yrange [-1.0:1.0]\n");
    }

    fprintf(gp, "set xrange [%lf:%lf]\n",time - 1.0, time + 1.0);

    fprintf(gp,"plot \"%s\" u 1:2 w l t \"sin\",\"%s\" u 1:3 w l t \"cos\"\n",
        fname.c_str(),fname.c_str());
    fflush(gp);
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"animation_test");
    ros::NodeHandle nh;

    std::string fname = "animation_data.txt";
    double time = 0.0;

    for(;;)
    {
        writeFile(fname,time);
        animationPlot(fname, time);
        time += 0.1;
        usleep(100000);

        if(float(time) >= 10.0 ) break;
    }


    return 0;
}

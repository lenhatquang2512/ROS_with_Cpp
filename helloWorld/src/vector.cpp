#include<ros/ros.h>
#include<iostream>
#include<string>
#include<vector>

class Point
{
// private:
//     /* data */
public:
    float x_,y_,z_;
    Point(void) {};
    // ~Point();

    Point(float x, float y, float z):
        x_(x), y_(y), z_(z)
        {}
};



void printVector(std::vector<float> vals)
{

    for (int i = 0; i < (int) vals.size(); i++)
    {
        std::cout << vals[i] << std::endl;
    }

}

void printVector(std::vector<Point> points)
{

    for (int i = 0; i < (int) points.size(); i++)
    {
        std::cout << points[i].x_  << " , "
                  << points[i].y_  << " , " 
                  << points[i].z_  << std::endl;
    }

}

std::vector<float> readFile(std::string fname)
{
    FILE *fp = fopen(fname.c_str(),"r");
    float val;
    std::vector<float> vals;

    while (fscanf(fp,"%f",&val) != EOF)
    {
        vals.push_back(val);
    }

    fclose(fp);
    return vals;
    
}

std::vector<Point> readPoints(std::string fname)
{
    FILE *fp = fopen(fname.c_str(),"r");
    float x,y,z;
    std::vector<Point> points;

    while (fscanf(fp,"%f %f %f",&x,&y,&z) != EOF)
    {
        Point point;
        point.x_ = x;
        point.y_ = y;
        point.z_ = z;
        points.push_back(point);
        // points.push_back(Point(x,y,z));
    }

    fclose(fp);
    return points;
    
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"vector");
    ros::NodeHandle nh;

    // std::vector<int> vals(3);
    // for (int i = 0; i < (int) vals.size(); i++)
    // {
    //     std::cout << vals[i] << std::endl;
    // }

    //--------------------------------
    // std::vector<float> vals;
    // vals.push_back(1.1f);
    // vals.push_back(1.2f);
    // vals.push_back(1.3f);

    // std::cout << (int) vals.size() << std::endl;
    
    // printVector(vals);
    //--------------------------------

    // std::vector<float> vals = readFile("sample.txt");

    //--------------------------------
    std::vector<Point> points;
    points.push_back(Point(0.0f,1.1f,3.4f));
    points.push_back(Point(0.0f,1.2f,3.4f));
    points.push_back(Point(0.0f,1.3f,3.5f));
    std::cout << (int)points.size() << std::endl;
    printVector(points);

    //--------------------------------
    // std::vector<std::vector<int>> image;
    // int width = 320;
    // int height = 240;

    // image.resize(width);
    // for (int u = 0; u < width; u++)
    // {
    //     image[u].resize(height);
    // }

    // for (int u = 0; u < width; u++)
    // {
    //     for (int v = 0; v < height; v++)
    //     {
    //         printf("u = %d, v = %d, val = %d\n",u,v,image[u][v]);
    //     }
        
    // }
    

    return 0;
}
//这里是main的优化
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

#include <iomanip>     // for std::fixed, std::setprecision

const double THRESHOLD = 1.00;
bool distance_flat(double x1 ,double y1 ,double x2 ,double y2)
{
    //优化1 不用开平方，因为平方属于，那也是用二次方来写，就省了sqrt
    double d ;
    d =  (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) ;
   return d< THRESHOLD*THRESHOLD ;
};
struct Point
{
    double x,y;
};

int main()
{
    std::ifstream file("points.txt");
    std::string line;
    std::vector<Point> points;

    std::string middle_x;
    std::string middle_y;

    while(std::getline(file,line))
    {
        std::stringstream ss(line);
        std::getline(ss,middle_x,',');
        std::getline(ss,middle_y,',');
        Point p;
        p.x = std::stod(middle_x);
        p.y = std::stod(middle_y);
        points.push_back(p);
    }
    file.close();

    std::vector< std::vector<int> > clusters;
    std::vector<bool> visited(points.size(),false);
    for(size_t i=0; i<points.size();i++) //不用int i 使用size_z i更规范
    {   
        //先创建一个族
        if(visited[i]) continue;
        std::vector<int> cluster;
        cluster.push_back(i);
        visited[i] = true;
        //判断后续点是不是属于这个族内
        for(size_t j=0; j<cluster.size();j++)
        {
            for(size_t k=0; k<points.size();k++)
            {
                if( (!visited[k])&&(distance_flat (points[cluster[j]].x,points[cluster[j]].y,points[k].x,points[k].y)) )
                {
                    visited[k]=true;
                    cluster.push_back(k);
                }
            }
        }
         clusters.push_back(cluster);
    }
    int id=1;//标记第几个族
    for(const auto& cs:clusters)
    {
        std::cout<<"cluster"<<id<<": " ;
        double sum_x=0;
        double sum_y=0;
        double max_x=points[cs[0]].x; //赋值第一个点，然后跟后续点判断输出 边界最大最小值
        double min_x=points[cs[0]].x;
        double max_y=points[cs[0]].y;
        double min_y=points[cs[0]].y;
        for(const auto& c:cs)
        {
            std::cout<< c<< ',';
            sum_x += points[c].x;
            sum_y += points[c].y;
            if(max_x < points[c].x) max_x = points[c].x; 
            if(min_x > points[c].x) min_x = points[c].x; 
            if(max_y < points[c].y) max_y = points[c].y; 
            if(min_y > points[c].y) min_y = points[c].y; 
        }
        double center_x = sum_x/cs.size();
        double center_y = sum_y/cs.size();
        std::cout << std::fixed << std::setprecision(2);
        std::cout<< "center ("<<center_x<<","<<center_y<<") points: "<<cs.size();
        std::cout<< "  max_x : "<<max_x<<"  min_x : "<<min_x<< "  max_y : "<<max_y<<"  min_y : "<<min_y <<std::endl;
        id++;
    }
    
}






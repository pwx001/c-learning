#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include <cmath>

const double THRESHOLD = 1.00;//threshold

bool distance_flat(double x1 ,double y1 ,double x2 ,double y2)
{
    double d ;
    d = std::sqrt( (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) );
   return d<THRESHOLD;
};

struct Point {
    double x, y; 
};

std::vector< std::vector<int> >  clusters; //用来存储多个族，族里面只放坐标的下标

int main()
{
    std::ifstream file("points.txt");
    std::string line;
    std::vector<Point> points; //因为我需要多个Point结构的点，因此有points最后把每一个点压入就可以
   


    std::string middle_x;
    std::string middle_y;
    while(std::getline(file,line))
    {
        std::stringstream ss(line);
        //getline获取的是字符串，如果想要字符串里面数字，需要转换。拿一个中间量
        std::getline(ss,middle_x,','); 
        std::getline(ss,middle_y,',');
        Point p;
        p.x = std::stod(middle_x);
        p.y = std::stod(middle_y);
        points.push_back(p);
        
    }
    file.close();
    //现在：points包含了所有点，把点丢进来去判断是不是符合了！ 
     std::vector<bool> visited(points.size(),false);
    for(int i=0; i<points.size();i++)
    {   
        //先创建一个族
        if(visited[i]) continue;
        std::vector<int> cluster;
        cluster.push_back(i);
        visited[i] = true;
        //判断后续点是不是属于这个族内
        for(int j=1; j<points.size();j++)
        {
         if(i==j) continue;
         //if( !visited[j] && distance_flat (points[i].x,points[i].y,points[j].x,points[j].y))
         if (distance_flat (points[i].x,points[i].y,points[j].x,points[j].y) )  //这两个条件其实也可以放一起 如果j这个点没放入(为0,那要真就！非)且相距符合
          {
            visited[j] = true;
            cluster.push_back(j);
          }
        }
        //新加入点和其他点是不是继续符合呢  再判断后续点是不是属于这个族内 
        for(int k=1; k< cluster.size(); k++)
        {   //如何让后续新加入点，不去找最开始的点. 现在的cluster至少1个点了 直接k从1开始，因为0是最开始的元素
            for(int j=0;j<points.size();j++ )
            { if(visited[j]) continue;
                if( distance_flat( points[cluster[k]].x,points[cluster[k]].y,points[j].x,points[j].y ) )
                {
                    visited[j]=true;
                    cluster.push_back(j);
                }
            }
        }
        clusters.push_back(cluster);
        //这里写完发现有重复，第一轮和第二轮可以融合在一起
    }
   

   
    for(const auto& a_p: points)
    {   //为a_p.x不是.first eg:是stuct定义的，不像项目1是map类型里面元素是pair
        std::cout<<a_p.x<<" and "<<a_p.y<< std::endl;
    }
    std::cout<<"display point"<< std::endl;

    int id=1;
    for( const auto& cs:clusters)
    { //const auto& 类似 for(auto cs, cs<cluster,cs++) 如果知道内一层为int一般写int比较省，但是都写const auto&都可以
        //其次cs就是进入了clusters里面的一层，cs等于的族了
        std::cout<<"this is cluster"<<id << " : ";
        for(const auto& c : cs) //再来一次 c：cs表示又进入了下一层，c代表里面元素
        {
            std::cout<< c << ","; 
        }
        std::cout<< std::endl;
        id++;
    }

}
//传感器日志统计分析器

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>

int main()
{
    std::ifstream file("sensor_log.csv");
    std::string line;

    std::string timesstamp;
    std::string sensor_id;
    std::string target_type;
    std::string distance;
    std::string speed;

    std::map<std::string,int> m_id;
    std::map<std::string,int> m_type;
    std::map<std::string,float> m_speed;
    float all_distance=0.0;
    int flat=0;


    std::getline(file,line);
    while(std::getline(file,line)) //如果csv文件有空格？
    {
        std::stringstream ss(line);
        std::getline(ss,timesstamp,',');
        std::getline(ss,sensor_id,',');
        std::getline(ss,target_type,',');
        std::getline(ss,distance,',');
        std::getline(ss,speed,',');
        if(!target_type.empty())
        {
            m_type[target_type]++;
        }
        if(!sensor_id.empty())
        {
            m_id[sensor_id]++;
        }
        if(!distance.empty())
        {
            float a_distance = std::stof(distance);
            all_distance +=a_distance;
            flat++;
        }
        if(!speed.empty())
        {
            float a_speed = std::stof(speed);
            m_speed[target_type] +=a_speed;
        }

    }
    file.close();
    for(const auto& target:m_type)  //打印有几类目标，目标有几个
    {
        std::cout<<target.first<<" : "
        << target.second<<std::endl;
        int a = target.second;

    }
    for(const auto& id:m_id)    //打印sensor_id的每种型号出现几次
    {
        std::cout<<id.first<<" : "
        << id.second<<std::endl;
    }
    std::cout<<"average_distance : "<< all_distance/flat << std::endl; //输出的平均距离
    for(const auto& v:m_speed)  //区别开 m_speed[people]返回的定义，数值；而v:是一个新的东西，表示引用，且有first和second，分别表示map的类型和数值（定义）
    {
        int cnt = m_type[v.first];   
        if(cnt >0)
        {
            std::cout<< v.first << " average_speed:"<< v.second/cnt<< std::endl;
        }                 
    }


}
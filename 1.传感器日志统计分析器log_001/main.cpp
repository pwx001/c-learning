#include<iostream>
#include<fstream> //用于对文件进行读写操作
#include<sstream> //将字符串当作流来操作，实现内存中的格式化输入输出
#include<string>
#include <vector> //动态数组
#include <set> //去重
#include <map>  //计算类型出现次数

struct Sensordata //设一个结构体，可以获得一个整体
{
        std::string timestamp;
        std::string sensor_id;
        std::string target_type;
        std::string distance;
        std::string speed;
};



int main()
{
    std::ifstream file("sensor_log.csv");
    std::string line;
    std::vector<Sensordata> all_data;
    std::vector<std::string> v_sensor_id; 
    std::set<std::string> s_sensor_id;
    std::map<std::string, int> m_target_type;

    std::getline(file,line); //在while 前面来一次 就是跳过表头
    while(getline(file,line))
    {
        std::cout<< line << std::endl;
        Sensordata data;
        std::string a1;
        std::string a2;

        std::stringstream ss(line); //将文件一行获取信息放入 ss变量里面
        std::getline(ss,a1,',');
        std::getline(ss,a2,',');
        data.timestamp = a1; //用这个就可以实现，将里面数据进行换位，因为getline，不知道哪个是哪个数据，我们想要制定第一个是什么数据，第二个是什么数据；可以这样
        data.sensor_id = a2;
        std::getline(ss,data.target_type,',');
        std::getline(ss,data.distance,',');
        std::getline(ss,data.speed,',');
        v_sensor_id.push_back(data.sensor_id); //创立一个动态数组，将数据一组一组压进去
        s_sensor_id.insert(data.sensor_id); //类似vector的升级，去掉重复数据
        all_data.push_back(data); 
        if(!data.target_type.empty())  // map的使用方式 获取数据的类型名字，且对于它的各自进行增加。
        {
            m_target_type[data.target_type]++;
        }

    }
    file.close();
    for(const auto& id : s_sensor_id) //遍历方式，&id只是引用，const auto 的前面const表示我不会改数据，只是遍历，节约资源开销
    {
        std::cout<<id<<std::endl;
    }
    for(const auto& data :all_data)
    {
        std::cout<<data.sensor_id<< data.timestamp<< std::endl;
    }
    for(const auto& type: m_target_type)
    {
        std::cout<<type.first<<" :get " << type.second<<" !"<< std::endl;
    }

    

}
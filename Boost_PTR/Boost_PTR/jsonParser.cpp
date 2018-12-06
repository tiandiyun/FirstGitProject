#include "jsonParser.h"
#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <time.h>
#include <iostream>


const std::string file_path = "E:\\test.json";

void read_json_data_from_string(void)
{
    /*
    C++ 中 字符串形式的json串 需要使用 \ 转义 双引号
    */
    std::string str_json = "{\"count\":10,\"people\":[{ \"firstName\": \"Brett\", \"lastName\":\"McLaughlin\", \"email\": \"aaaa\" },{ \"firstName\": \"Jason\", \"lastName\":\"Hunter\", \"email\": \"bbbb\"},{ \"firstName\": \"Elliotte\", \"lastName\":\"Harold\", \"email\": \"cccc\" }]}";
    std::stringstream str_stream(str_json);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(str_stream, root);
    root.put("upid", "001");

    // 插入一个数组
    boost::property_tree::ptree exif_array;
    boost::property_tree::ptree array1, array2, array3;
    array1.put("Make", "NIKON");
    array2.put("DateTime", "2011:05:31 06:47:09");
    array3.put("Software", "Ver.1.01");

    //   exif_array.push_back(std::make_pair("Make", "NIKON"));
    //   exif_array.push_back(std::make_pair("DateTime", "2011:05:31 06:47:09"));
    //   exif_array.push_back(std::make_pair("Software", "Ver.1.01"));

    exif_array.push_back(std::make_pair("", array1));
    exif_array.push_back(std::make_pair("", array2));
    exif_array.push_back(std::make_pair("", array3));

    root.put_child("exifs", exif_array);
    std::stringstream str_stream_temp;
    boost::property_tree::write_json(str_stream_temp, root);
    //write_json(str_stream_temp, root);
    std::string str = str_stream_temp.str();
    std::cout << str << std::endl;

    for (auto it : root)
    {
        auto first = it.first;
        auto second = it.second;
    }
}


void generate_user()
{
    boost::property_tree::ptree root;
    boost::property_tree::ptree items;

    boost::property_tree::ptree item1;
    item1.put("ID", "1");
    item1.put("Name", "wang");
    items.push_back(std::make_pair("1", item1));

    boost::property_tree::ptree item2;
    item2.put("ID", "2");
    item2.put("Name", "zhang");
    items.push_back(std::make_pair("2", item2));

    boost::property_tree::ptree item3;
    item3.put("ID", "3");
    item3.put("Name", "li");
    items.push_back(std::make_pair("3", item3));

    root.put_child("user", items);
    root.put<int>("hh", 0);
    root.put<int>("gg", 1);

    boost::property_tree::write_json(file_path, root/*, std::locale(), false*/);
}


void read_user()
{
    boost::property_tree::ptree root;
    boost::property_tree::ptree items;
    boost::property_tree::read_json<boost::property_tree::ptree>(file_path, root);

    items = root.get_child("user");
    for (boost::property_tree::ptree::iterator it = items.begin(); it != items.end(); ++it)
    {
        //遍历读出数据
        std::string key = it->first;//key ID
        auto second = it->second;
        std::string ID = it->second.get<std::string>("ID");
        std::string Name = it->second.get<std::string>("Name");
        std::cout << "( " << key << ", " << ID << ", " << Name << " )" <<std::endl;
    }

    /*for (boost::property_tree::ptree::iterator it = root.begin(); it != root.end(); ++it)
    {
        auto first = it->first;
        auto second = it->second;
        if (first != "user")
        {
            int v = it->second.get_value<int>();
            std::cout << v << std::endl;
        }
    }*/
    for (auto data : root)
    {
        auto first = data.first;
        auto second = data.second;
        if (first != "user")
        {
            int v = second.get_value<int>();
            std::cout << v << std::endl;

            v = root.get<int>(first);
            std::cout << v << std::endl;
        }
    }
}
//
// Created by yingzi on 2016/11/25.
//

#ifndef CPPSPIDER_URL_H
#define CPPSPIDER_URL_H
#include <string>
#include <iostream>
using namespace std;

class Url {
public:
    //默认构造函数
    Url();
    //构造函数初始化Url
    Url(string url);
    //拷贝构造函数
    //Url(const Url& url2);

    //获取Url中的host
    string getHost();
    //获取Url中的path
    string getPath();

private:
    string host;
    string path;
};


#endif //CPPSPIDER_URL_H

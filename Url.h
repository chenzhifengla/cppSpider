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

    string getUrl();

    string getFormatUrl();

    string getProtocol();
    string getHost();

    int getPort();
    string getPath();

    friend ostream &operator<<(ostream &os, Url &url) {
        os << url.getUrl();
        return os;
    }

    bool operator<(const Url &url) const {
        if (host != url.host) return host < url.host;
        else return path < url.path;
    }

private:
    string url;
    string protocol;
    string host;
    int port;
    string path;

    void initUrl();
};

#endif //CPPSPIDER_URL_H

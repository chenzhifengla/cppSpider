//
// Created by yingzi on 2016/11/25.
//

#ifndef CPPSPIDER_CRAWLER_H
#define CPPSPIDER_CRAWLER_H
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include "Url.h"
#include "Page.h"
using namespace std;

class Crawler {
public:
    //根据指定url下载对应网页
    bool crawlPage(Url url);
    //返回存储的网页数据
    Page getPage();

    //创建与网站的连接
    bool connectPage();
    //向网站发送请求
    bool sendHttpRequest();
    //接收网站返回数据
    bool recvPageResponse();

private:
    Url url;
    Page page;
    int client;
};


#endif //CPPSPIDER_CRAWLER_H

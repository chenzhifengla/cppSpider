//
// Created by yingzi on 2016/11/25.
//

#include "Crawler.h"

bool Crawler::crawlPage(Url url) {
    //先建立与网站的连接
    if(!connectPage()) return false;
    //然后向网站发送请求
    if(!sendHttpRequest()) return false;
    //最后接收网站返回的数据
    if(!recvPageResponse()) return false;

    return true;
}

bool Crawler::connectPage() {
    //建立客户端套接字
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0){
        cout << "socket create failed!" << endl;
        return false;
    }

    //由域名host获取网站主机的ip等信息
    auto hp = gethostbyname(url.getHost().c_str());
    if (!hp){
        cout << "dns analysis failed!" << endl;
        return false;
    }

    //描述套接字地址的结构
    struct sockaddr_in serveraddr;
    //清空该数据结构
    memset(&serveraddr, 0, sizeof(serveraddr));
    //设置属性
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = *((unsigned long*)hp->h_addr);
    //端口设置为80,使满足http协议
    serveraddr.sin_port = htons(80);

    //建立连接
    if(connect(client, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
        cout << "cannot connect to the server!" << endl;
        return false;
    }
    else return true;
}

bool Crawler::sendHttpRequest() {
    //构造请求头部
    string req = "GET " +
                 url.getPath() +
                 " HTTP/1.1\r\nHost:" +
                 url.getHost() +
                 "\r\nUser-Agent:Mozilla/4.0 (compatible: MSIE8.0; Windows NT6.0; Trident/4.0\r\n" +
                 "Connection:Close\r\n\r\n";
    //发送请求头
    if (send(client, req.c_str(), req.size(), 0) < 0){
        cout << "send request failed!" << endl;
        return false;
    }
    else {
        cout << "send request success!" << endl;
        return true;
    }
}

bool Crawler::recvPageResponse() {
    //构造临时数组用于循环接受页面内容
    char buf[100];
    memset(buf, 0, 100);
    //构造临时字符串用于存放页面content
    string content;
    //循环接受页面内容
    while(recv(client, buf, 100, 0) > 0){
        content.append(buf);
        memset(buf, 0, 100);
    }
    if (content.size() == 0){
        cout << "recv from website failed!" << endl;
        return false;
    }
    else {
        page.setUrl(url);
        page.setContent(content);
        cout << "recv from website success!" << endl;
        return true;
    }
}

Page Crawler::getPage() {
    return page;
}
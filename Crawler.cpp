//
// Created by yingzi on 2016/11/25.
//

#include <unistd.h>
#include "Crawler.h"

bool Crawler::crawlPage(Url url) {
    //先建立与网站的连接
    if(!connectPage()) return false;
    //然后向网站发送请求
    if (url.getProtocol() == "http://") {
        if (!sendHttpRequest()) return false;
    } else {
        cout << "cannot deal other protocol now" << endl;
        return false;
    }
    // 接收网站返回的数据
    if (!(recvPageResponse())) return false;
    // 关闭套接字
    close(client);
    return true;
}

bool Crawler::connectPage() {
    //建立客户端TCP套接字
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0){
        cout << "socket create failed!" << endl;
        return false;
    }

    /* // 主机信息结构体
     * struct hostent{
     *     char *h_name;    // 地址的正式名称
     *     char **h_aliases;    // 空字节-地址的预备名称的指针
     *     short h_addrtype;    // 地址类型，通常是AF_INET
     *     short h_length;  // 地址的比特长度
     *     char **h_addr_list;  // 零字节-主机网络地址指针，网络字节顺序
     *  };
     *  #define h_addr h_addr_list[0]   // 表示h_addr_list的第一地址     *
     */
    //由域名host获取网站主机的ip等信息
    struct hostent *hp = gethostbyname(url.getHost().c_str());
    if (!hp){
        cout << "dns analysis failed!" << endl;
        return false;
    }

    /* // 描述套接字地址的结构体
     * struct sockaddr_in{
     *     short sin_family;    // 地址族，一般为AF_INET
     *     unsigned short sin_port; // 端口号，网络字节顺序
     *     struct in_addr sin_addr; // ip地址
     *     unsigned char sin_zero[8];   // 无意思，内存对齐用
     * };
     * // 描述ip地址的结构体
     * typedef uint32_t in_addr_t;  // ip地址采用无符号32位整型
     * struct in_addr{
     *     in_addr_t s_addr;    // ip地址
     * };
     */
    struct sockaddr_in serveraddr;  // 描述套接字地址
    //清空该数据结构
    memset(&serveraddr, 0, sizeof(serveraddr));
    //设置协议族
    serveraddr.sin_family = AF_INET;
    // ip地址为网站主机ip,强制类型转换后取值
    serveraddr.sin_addr.s_addr = *((in_addr_t *) hp->h_addr);
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
        //cout << "send request success!" << endl;
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
        content.append(buf, 99);    // 不加入字符数组最后的\0
        memset(buf, 0, 100);
    }
    if (content.size() == 0){
        cout << "recv from website failed!" << endl;
        return false;
    }
    else {
        page.setUrl(url);
        page.setContent(content);
        //cout << "recv from website success!" << endl;
    }
    return true;
}

Page Crawler::getPage() {
    return page;
}
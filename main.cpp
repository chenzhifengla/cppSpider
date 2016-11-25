//
// Created by yingzi on 2016/11/25.
//
#include <iostream>
#include "Url.h"
#include "Crawler.h"
#include "HtmlParser.h"
using namespace std;

int main(){
    //生成一个初始Url
    Url url("http://www.yingzinanfei.com/2016/10/08/centosfanghuoqiangjiandancaozuo/");

    //生成一个Crawler对象
    Crawler crawler;
    //给定url爬取对应网页
    if(!crawler.crawlPage(url)){
        cout << "crawl page failed!" << endl;
    }
    else{
        cout << "now output the page" << endl;
        cout << crawler.getPage().getContent() << endl;
    }


    //生成一个网页分析器
    HtmlParser htmlParser;
    //给定页面进行分析
    htmlParser.parsePage(crawler.getPage());

    //获得所有分析出的url
    queue<Url> urls = htmlParser.getPageUrls();

    //输出所有url
    while (!urls.empty()){
        url = urls.front();
        urls.pop();
        cout << url.getHost() << url.getPath() << endl;
    }
    return 0;
}

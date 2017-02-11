//
// Created by yingzi on 2016/11/25.
//
#include <iostream>
#include <set>
#include "Url.h"
#include "Crawler.h"
#include "HtmlParser.h"
using namespace std;

int main(){
    //生成一个初始Url
    //Url url("http://www.yingzinanfei.com/2016/10/08/centosfanghuoqiangjiandancaozuo/");
    Url url("http://bbs.byr.cn");

    // url集合
    set<Url> url_set;
    url_set.insert(url);
    // url队列
    queue<Url> url_queue;
    url_queue.push(url);
    // 生成一个Crawler对象
    Crawler crawler;
    // 生成一个Page对象
    Page page;
    while (!url_queue.empty()) {
        // 弹出一个url
        url = url_queue.front();
        url_queue.pop();
        // 爬取该url
        if (!crawler.crawlPage(url)) {
            cout << url.getUrl() << " visit failed" << endl;
        } else {
            cout << url.getUrl() << " visit success" << endl;
            page = crawler.getPage();
        }
        // 该url已访问
        url_set.insert(url);
        // 获得页面上所有url
        vector<string> suburls = page.getSubUrls();
        if (suburls.empty()) {
            cout << "this page has no sub url" << endl;
        }
        // 只要未出现过则加入url队列
        for (string &suburl : suburls) {
            if (url_set.find(suburl) == url_set.end() && suburl.find("bbs.byr.cn") != string::npos) {
                url_queue.emplace(suburl);
            }
        }
    }

    return 0;
}

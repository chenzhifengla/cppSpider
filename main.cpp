//
// Created by yingzi on 2016/11/25.
//
#include <iostream>
#include <set>
#include <queue>
#include "Url.h"
#include "Crawler.h"
using namespace std;

int main(){
    //生成一个初始Url
    //Url url("http://www.yingzinanfei.com/2016/10/08/centosfanghuoqiangjiandancaozuo/");
    Url url("http://www.yingzinanfei.com");
    //Url url("http://bbs.byr.cn");

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
        cout << "visit " << url.getUrl() << endl;

        // 爬取该url
        if (!crawler.crawlPage(url)) {
            cout << "\t" << url.getUrl() << " visit failed" << endl;
        } else {
            page = crawler.getPage();
        }

        // 获得页面上所有url
        vector<Url> suburls = page.getSubUrls();
        cout << "\tsub urls:" << endl;
        // 只要未出现过则加入url队列
        for (Url &suburl : suburls) {
            if (url_set.find(suburl) == url_set.end() && suburl.getHost() == "www.yingzinanfei.com") {
                // 添加到队列中
                url_queue.emplace(suburl);
                // 添加到集合中
                url_set.insert(suburl);
                cout << "\t\t" << suburl << endl;
            }
        }
    }

    return 0;
}

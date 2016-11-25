//
// Created by yingzi on 2016/11/25.
//

#include "Url.h"

Url::Url(){
    host = "";
    path = "/";
}

Url::Url(string url) {
    //如果url以"http://"或"https://"开头，则去掉他
    if (url.find_first_not_of("http://") != 0){
        url = url.substr(7);
    }
    if (url.find_first_not_of("https://") != 0){
        url = url.substr(8);
    }
    //查找第一个"/"出现位置
    auto index = url.find("/");
    //如果url中没有路径,添加"/"，如果有路径，分离Host和path
    if (index == string::npos) {
        host = url;
        path = "/";
    }
    else{
        host = url.substr(0, index);
        path = url.substr(index);
    }
    cout << "Init url success!\thost='" << host << "'\tpath='" << path << "'" << endl;
}

/*Url::Url(const Url& url2){
    host = url2.host;
    path = url2.path;
};*/

string Url::getHost(){
    return host;
}

string Url::getPath(){
    return path;
}
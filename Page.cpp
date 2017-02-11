//
// Created by yingzi on 2016/11/25.
//

#include "Page.h"
#include <regex>

void Page::setUrl(Url url){
    this->url = url;
}

void Page::setContent(string content){
    this->content = content;
}

Url Page::getUrl(){
    return url;
}

string Page::getContent(){
    return content;
}

vector<Url> Page::getSubUrls() {
    string url_pattern("(<a\\s+)(href=\"|\')(([^\\s\"\'])+?)(\"|\')(.*?>)");
    regex r(url_pattern);

    vector<Url> sub_urls;
    // 在content中搜索所有url
    for (sregex_iterator it(content.begin(), content.end(), r), end_it; it != end_it; it++) {
        sub_urls.push_back(Url(it->str(3)));
    }

    return sub_urls;
}
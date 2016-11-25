//
// Created by yingzi on 2016/11/25.
//

#include "Page.h"

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
//
// Created by yingzi on 2016/11/25.
//

#ifndef CPPSPIDER_PAGE_H
#define CPPSPIDER_PAGE_H
#include "Url.h"
#include <string>

class Page {
public:
    void setUrl(Url url);
    void setContent(string content);

    Url getUrl();
    string getContent();

private:
    Url url;
    string content;
};


#endif //CPPSPIDER_PAGE_H

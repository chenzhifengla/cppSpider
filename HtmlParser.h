//
// Created by yingzi on 2016/11/25.
//

#ifndef CPPSPIDER_HTMLPARSER_H
#define CPPSPIDER_HTMLPARSER_H
#include <string>
#include <queue>
#include "Page.h"
using namespace std;

//定义结点状态
using state = int;
//定义转移条件
using condition = int;


class HtmlParser {
public:
    //重写默认构造函数，加入自动机初始化
    HtmlParser();
    //传入一个网页内容，进行Url分析
    void parsePage(Page page);
    //获取网页上获得的所有Url
    queue<Url> getPageUrls();

private:
    Url url;
    string content;
    string link;
    queue<Url> urls;

    //定义自动机结构体
    using stateMachine = struct{state current; };

    //定义最大状态数
    static const int STATENUM = 24;
    //定义最大转移条件数
    static const int CONDITIONS = 21;

    //根据最大状态数定义自动机数组
    stateMachine s[STATENUM];

    //定义转移数组
    vector<vector<state> > transitionTable;

    //检查自动机
    void checkMachineState(stateMachine, char);
    //自动机状态转移
    void stepMachine(stateMachine&, char);
    //转移字符翻译成转移条件
    condition CharToCondition(char);
};


#endif //CPPSPIDER_HTMLPARSER_H

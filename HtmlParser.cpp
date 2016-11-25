//
// Created by yingzi on 2016/11/25.
//

#include "HtmlParser.h"

HtmlParser::HtmlParser(){
    //初始化自动机数组
    for (int i = 0; i < STATENUM; i++){
        s[i].current = i;
    }

    //定义转移数组
    transitionTable = {
    /*           0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 */
    /*           <  a  A  h  H  r  R  e  E  f  F  =     "  '  /  #  >  -  ! other */
    /*0结点*/    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /*1结点*/    0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
    /*2结点*/    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
    /*3结点*/    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0,
    /*4结点*/    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 4, 4,
    /*5结点*/    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0,
    /*6结点*/    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /*7结点*/    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0,
    /*8结点*/    8, 8, 8, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 8, 8, 8,
    /*9结点*/    8, 8, 8, 8, 8,10,10, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 8, 8, 8,
    /*10结点*/   8, 8, 8, 8, 8, 8, 8,11,11, 8, 8, 8, 8, 8, 8, 8, 8, 0, 8, 8, 8,
    /*11结点*/   8, 8, 8, 8, 8, 8, 8, 8, 8,12,12, 8, 8, 8, 8, 8, 8, 0, 8, 8, 8,
    /*12结点*/   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,13,12, 8, 8, 8, 8, 0, 8, 8, 8,
    /*13结点*/   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,13,14,19, 8, 8, 0, 8, 8, 8,
    /*14结点*/  17,17,17,17,17,17,17,17,17,17,17,17,14, 0,17,15, 0, 0,17,17,17,
    /*15结点*/  15,15,15,15,15,15,15,15,15,15,15,15,15,16,15,15,15, 0,15,15,15,
    /*16结点*/   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /*17结点*/  17,17,17,17,17,17,17,17,17,17,17,17,17,18,17,17,17, 0,17,17,17,
    /*18结点*/   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /*19结点*/  20,20,20,20,20,20,20,20,20,20,20,20,19,20, 0,21, 0, 0,20,20,20,
    /*20结点*/  20,20,20,20,20,20,20,20,20,20,20,20,20,20,23,20,20, 0,20,20,20,
    /*21结点*/  21,21,21,21,21,21,21,21,21,21,21,21,21,21,22,21,21, 0,21,21,21,
    /*22结点*/   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /*23结点*/   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
}

void HtmlParser::parsePage(Page page) {
    //先保存待分析页面的url和content
    url = page.getUrl();
    content = page.getContent();

    //创建一个自动机
    stateMachine mymachine = s[0];

    //遍历content
    for (auto it = content.cbegin(); it != content.cend(); it++){
        //检查自动机
        checkMachineState(mymachine, *it);
        //自动机状态转移
        stepMachine(mymachine, *it);
    }
}

queue<Url> HtmlParser::getPageUrls() {
    return urls;
}

void HtmlParser::checkMachineState(stateMachine mymachine, char c){
    state cur = mymachine.current;
    switch (cur){
            //入口处清零
        case 0:
            link.clear();
            break;
            //开始进入超链
        case 14:
        case 19:
            link.clear();
            link.push_back(c);
            break;
            //超链中的正常字符
        case 15:
        case 17:
        case 20:
        case 21:
            link.push_back(c);
            break;
            //超链结束,且为完整超链
        case 18:
        case 23:
            link.pop_back();
            urls.emplace(link);
            break;
            //超链结束，且为不完整超链
        case 16:
        case 22:
            link.pop_back();
            urls.emplace(url.getHost(), link);
            break;
    }
}

void HtmlParser::stepMachine(stateMachine& mymachine, char c){
    condition mycondition = CharToCondition(c);
    state next = transitionTable[mymachine.current][mycondition];
    mymachine = s[next];
}

condition CharToCondition(char c)
{
    if (c == '<') return 0;
    if (c == 'a') return 1;
    if (c == 'A') return 2;
    if (c == 'h') return 3;
    if (c == 'H') return 4;
    if (c == 'r') return 5;
    if (c == 'R') return 6;
    if (c == 'e') return 7;
    if (c == 'E') return 8;
    if (c == 'f') return 9;
    if (c == 'F') return 10;
    if (c == '=') return 11;
    if (c == ' ') return 12;
    if (c == '"') return 13;
    if (c == 39)  return 14;	//single quote
    if (c == '/') return 15;
    if (c == '#') return 16;
    if (c == '>') return 17;
    if (c == '-') return 18;
    if (c == '!') return 19;
    return 20;
}
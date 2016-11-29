//
// Created by root on 16-11-29.
//

#include <stdio.h>
#include <regex.h>  //标准c不支持，Linux常带有此文件

int main(){
    regex_t reg;    //定义一个正则实例
    const char* pattern = "^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*.\\w+([-.]\\w+)*$"; //定义模式串
    regcomp(&reg, pattern, REG_EXTENDED);    //编译正则模式串

    char* buf = "david19842003@gmail.com";   //定义待匹配串
    const size_t nmatch = 1;    //定义匹配结果最大允许数
    regmatch_t pmatch[1];   //定义匹配结果在待匹配串中的下标范围
    int status = regexec(&reg, buf, nmatch, pmatch, 0); //匹配他

    if (status == REG_NOMATCH){ //如果没匹配上
        printf("No Match\n");
    }
    else if (status == 0){  //如果匹配上了
        printf("Match\n");
        for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++){    //遍历输出匹配范围的字符串
            printf("%c", buf[i]);
        }
        printf("\n");
    }
    regfree(&reg);  //释放正则表达式
    return 0;
}
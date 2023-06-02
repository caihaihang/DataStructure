#ifndef SIMPLESTRING_H
#define SIMPLESTRING_H
#include "simplecontainer.h"
#include "usefulfunction.h"
#include <stdlib.h>
#include <iostream>

class SimpleString : public SimpleContainer<char>{
protected:
    int length = 0;
public:
    int getLength(){ return length; }
    //清空数据
    void clear(){ memset(container, 0, containerSize); }
    //获取内部数据
    char *getData(){ return this->container; }
    SimpleString():SimpleContainer<char>(){}
    //从字符串初始化
    SimpleString(const char *str, int len = 0){
        if(len == 0){
            //如果未给出长度,则手动计算
            const char *start = str;
            while(*start != 0)start++;
            containerSize = (int)(start - str + 1);
            this->length = containerSize - 1;
        }else {
            //如果给出长度,则使用给出的长度
            containerSize = len + 1;
            this->length = len;
        }
        container = new char[containerSize];
        memcpy(container, str, containerSize);
        container[this->length] = 0;
    }
    SimpleString(long l){
        long lOrigin = l;
        int width = 0;
        if(l < 0){
            l = -l;
            width += 1;
        }
        else if (l == 0) width = 1;
        while(l!=0){
            width ++;
            l = l / 10;
        }
        containerSize = width + 1;
        length = width;
        container = new char[containerSize];
        sprintf_s(container, containerSize, "%d", lOrigin);
    }
    SimpleString(double d, int decimalWidth = 2){
        long l = (long)d;
        int width = 0;
        if(d < 0){
            l = -l;
            width += 1;
        }
        if (l == 0)width = 1;
        else while(l!=0){
            width ++;
            l = l / 10;
        }
        //计算需要的字符串空间大小 需要小数点和末尾0
        containerSize = width + 2 + decimalWidth;
        length = containerSize - 1;
        //构造格式化字符串
        int decimalWidthLength = 0;//计算小数位数数值宽度
        char *decimalWidthStr = simpleItoa(decimalWidth, decimalWidthLength, 5);//获取转化后的小数位数数值字符串
        //申请格式化字符串所需空间
        char *formatStr = new char[decimalWidthLength + 4];
        formatStr[0] = '%';
        formatStr[1] = '.';
        memcpy(formatStr + 2, decimalWidthStr, decimalWidthLength);
        formatStr[decimalWidthLength + 2] = 'f';
        formatStr[decimalWidthLength + 3] = 0;
        delete decimalWidthStr;
        sprintf_s(container, containerSize, formatStr, d);
        delete formatStr;
    }
    SimpleString(const SimpleString& sstr):SimpleString(sstr.container, sstr.length) {}
    ~SimpleString(){}
};

class SimpleStringBuilder : public SimpleString{
public:
    void append(const char *str, int len = 0);
    void append(SimpleString &sstr);
    SimpleStringBuilder():SimpleString(){}
    SimpleStringBuilder(const char *str, int len = 0):SimpleString(str, len){}
    SimpleStringBuilder(double d, int decimalWidth = 2):SimpleString(d, decimalWidth){}
    SimpleStringBuilder(SimpleString &sstr):SimpleString(sstr){}
    ~SimpleStringBuilder(){}
};
//扩展函数  将字符串常量扩展到末尾
void SimpleStringBuilder::append(const char *str, int len){
    if(len == 0){
        //如果未给出长度,则手动计算
        const char *start = str;
        while(*start != 0)start++;
        len = (int)(start -str);
    }
    int newLength = length + len + 1;
    //如果新字符串所需空间大于当前容器空间,进行扩容
    if(newLength > containerSize){
        expandContainer(newLength);
    }
    memcpy(container + length, str, len);
    length = newLength - 1;
}
//扩展函数  将SimpleString变量的内容扩展到末尾
void SimpleStringBuilder::append(SimpleString &sstr){
    append(sstr.getData(), sstr.getLength());
}
#endif // SIMPLESTRING_H

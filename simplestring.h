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
    //�������
    void clear(){ memset(container, 0, containerSize); }
    //��ȡ�ڲ�����
    char *getData(){ return this->container; }
    SimpleString():SimpleContainer<char>(){}
    //���ַ�����ʼ��
    SimpleString(const char *str, int len = 0){
        if(len == 0){
            //���δ��������,���ֶ�����
            const char *start = str;
            while(*start != 0)start++;
            containerSize = (int)(start - str + 1);
            this->length = containerSize - 1;
        }else {
            //�����������,��ʹ�ø����ĳ���
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
        //������Ҫ���ַ����ռ��С ��ҪС�����ĩβ0
        containerSize = width + 2 + decimalWidth;
        length = containerSize - 1;
        //�����ʽ���ַ���
        int decimalWidthLength = 0;//����С��λ����ֵ���
        char *decimalWidthStr = simpleItoa(decimalWidth, decimalWidthLength, 5);//��ȡת�����С��λ����ֵ�ַ���
        //�����ʽ���ַ�������ռ�
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
//��չ����  ���ַ���������չ��ĩβ
void SimpleStringBuilder::append(const char *str, int len){
    if(len == 0){
        //���δ��������,���ֶ�����
        const char *start = str;
        while(*start != 0)start++;
        len = (int)(start -str);
    }
    int newLength = length + len + 1;
    //������ַ�������ռ���ڵ�ǰ�����ռ�,��������
    if(newLength > containerSize){
        expandContainer(newLength);
    }
    memcpy(container + length, str, len);
    length = newLength - 1;
}
//��չ����  ��SimpleString������������չ��ĩβ
void SimpleStringBuilder::append(SimpleString &sstr){
    append(sstr.getData(), sstr.getLength());
}
#endif // SIMPLESTRING_H

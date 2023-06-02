#include "usefulfunction.h"
#include "simpleexception.h"
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <float.h>
//获取一个整数
//函数的目的   从一个字符串中读出一个整数(不含正负号)
//参数 字符串(只读) 读出的整数值的存储空间
//返回  读完一个整数之后指针所处的位置
const char *_getInt(const char *c, int *out){
    while(*c>='0' && *c<='9'){
        *out = (*out) * 10 + *c - '0';
        c++;
    }
    return c;
}
//函数的目的   从一个字符串中读出一个浮点数(含正负号)
//参数 字符串(只读) 读出的浮点数的存储空间
//返回  读完一个浮点数之后指针所处的位置
const char *_getFloat(const char *c, float *out){
    //计算整数位
    int sign = 1;
    if(*c == '+')c++;
    else if(*c == '-'){
        sign = -1;
        c++;
    }
    int integer = 0;
    while(*c>='0' && *c<='9'){
        integer = integer * 10 + *c - '0';
        c++;
    }
    //计算小数位
    if(*c == '.'){
        c++;
        float decimal = 0.0;
        float positional_right = 1 / 10.0f;
        while(*c>='0' && *c<='9'){
            decimal = decimal + (*c - '0') * positional_right;
            positional_right = positional_right / 10.0f;
            c++;
        }
        *out = sign * (integer + decimal);
    }else {
        //没有小数位直接返回
        *out = (float)sign * integer;
    }
    return c;
}
//函数的目的   从一个字符串中读出一个整数值(支持的格式  可选的'-' + 由'0'到'9'组成的字符串 + 可选的'E'/'e'指数符号 + 由'0'到'9'组成的字符串(与指数符号必须同时存在))
//输入 字符串(只读)
int simpleAtoi(const char *c){
    int sign = 1;
    //判断正负
    if(*c == '+')c++;
    else if(*c == '-'){
        sign = -1;
        c++;
    }
    //获取基数
    int base = 0;
    c = _getInt(c, &base);
    //如果有指数，获取指数
    if(*c == 'e' || *c == 'E'){
        int exponent = 0;
        c = _getInt(c + 1, &exponent);
        return (int)(sign * base * pow(10, exponent));
    }
    else return sign * base;
}
//函数的目的   从一个字符串中读出一个浮点值(支持的格式  可选的'-' + 浮点字面量(由'0'到'9'和'.'组成的字符串,'.'只能出现一次) + 可选的'E'/'e'指数符号 + 可选的'-' + 浮点字面量(与指数符号必须同时存在))
//输入 字符串(只读)
float simpleAtof(const char *c){
    float base = 0.0;
    c = _getFloat(c, &base);
    if (*c == 'e' || *c == 'E') {
        float exponent = 0.0;
        c = _getFloat(c + 1, &exponent);
        return (float)(base * pow(10, exponent));
    }
    else return base;
}
//函数作用  将一段字符串复制到一段更大的空间上,同时删除原字符串占用的空间
//参数   源字符串(动态分配)   宽度,用于输入源字符串宽度并返回新字符串宽度,故使用引用传递
char *allocatNewArray(char *array, int &width){
    //空间不足分配新空间
    char *newArray = new char[width * 2];
    //新分配的空间不会初始化,必须先进行初始化
    memset(newArray, 0, width * 2);
    memcpy(newArray + width, array, width);
    //删除原有空间
    delete []array;
    width = width * 2;
    return newArray;
}
//函数作用  将一个long型数据转换为字符串(正常格式,即由'0'到'9'组成的字符串)
//参数  要转换的long型数据    目标字符串初始宽度,默认为8(不一定为最终宽度,会根据实际需求进行调整)   长度指针(当指针为空时,即不需要获取转换后的字符串长度,如指针非空,则将转换后的字符串长度写入该指针指向的变量)
char *simpleItoa(long in, int &length, int width){
    //判断正负号
    int sign = 1;
    if(in < 0){
        sign = -1;
        in = -in;
    }
    char *array = new char[width];
    //新分配的空间不会初始化,必须先进行初始化
    memset(array, 0, width);
    int index = width - 1;
    while(in != 0){
        if(index < 0){
            index = width - 1;
            array = allocatNewArray(array, width);
        }
        //继续记录数据
        array[index] = '0' + in % 10;
        index--;
        in = in / 10;
    }
    if(sign == -1){
        if(index == -1){
            index = width - 1;
            array = allocatNewArray(array, width);
        }
        array[index] = '-';
        index--;
    }
    length = width - index - 1;
    //复制之后尾部仍有空间,需要置0
    if(index == -1){//如果空间刚好容纳,必须额外分配字符串尾部
        char *newArray = new char[width + 1];
        //新分配的空间不会初始化,必须先进行初始化
        memset(newArray, 0, width + 1);
        memcpy(newArray, array, width);
        delete []array;
        return newArray;
    }else {
        memcpy(array, array + index + 1, length);
        memset(array + (length), 0, index + 1);
        return array;
    }
}
//函数作用  将一个double型数据转换为字符串(正常格式,即由'0'到'9'和'.'组成的字符串)
//参数   要转换的double型数据   目标字符串初始宽度,默认为8(不一定为最终宽度,会根据实际需求进行调整)   小数保留宽度(必须大于零)
char *simpleFtoa(double in, int &length, int decimalWidth, int width){
    //小数位数必须大于零
    if(decimalWidth <= 0)return nullptr;
    //使用round
    long inInteger = (long)round(in * pow(10, decimalWidth));
    //调试代码
//    char s[10];
//    sprintf(s,"%d",inInteger);
//    qDebug()<<s
    char *intArray = simpleItoa(inInteger, length, width);
    length = length + 2;
    char *array = new char[length];
    //新分配的空间不会初始化,必须先进行初始化
    memset(array, 0, length);
    int integerWidth = length - 2 - decimalWidth;
    memcpy(array, intArray, integerWidth);
    array[integerWidth] = '.';
    memcpy(array + integerWidth + 1, intArray + integerWidth, decimalWidth);
    //删除整数缓存
    length = length -1;
    delete []intArray;
    return array;
}

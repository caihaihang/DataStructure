#include "usefulfunction.h"
#include "simpleexception.h"
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <float.h>
//��ȡһ������
//������Ŀ��   ��һ���ַ����ж���һ������(����������)
//���� �ַ���(ֻ��) ����������ֵ�Ĵ洢�ռ�
//����  ����һ������֮��ָ��������λ��
const char *_getInt(const char *c, int *out){
    while(*c>='0' && *c<='9'){
        *out = (*out) * 10 + *c - '0';
        c++;
    }
    return c;
}
//������Ŀ��   ��һ���ַ����ж���һ��������(��������)
//���� �ַ���(ֻ��) �����ĸ������Ĵ洢�ռ�
//����  ����һ��������֮��ָ��������λ��
const char *_getFloat(const char *c, float *out){
    //��������λ
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
    //����С��λ
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
        //û��С��λֱ�ӷ���
        *out = (float)sign * integer;
    }
    return c;
}
//������Ŀ��   ��һ���ַ����ж���һ������ֵ(֧�ֵĸ�ʽ  ��ѡ��'-' + ��'0'��'9'��ɵ��ַ��� + ��ѡ��'E'/'e'ָ������ + ��'0'��'9'��ɵ��ַ���(��ָ�����ű���ͬʱ����))
//���� �ַ���(ֻ��)
int simpleAtoi(const char *c){
    int sign = 1;
    //�ж�����
    if(*c == '+')c++;
    else if(*c == '-'){
        sign = -1;
        c++;
    }
    //��ȡ����
    int base = 0;
    c = _getInt(c, &base);
    //�����ָ������ȡָ��
    if(*c == 'e' || *c == 'E'){
        int exponent = 0;
        c = _getInt(c + 1, &exponent);
        return (int)(sign * base * pow(10, exponent));
    }
    else return sign * base;
}
//������Ŀ��   ��һ���ַ����ж���һ������ֵ(֧�ֵĸ�ʽ  ��ѡ��'-' + ����������(��'0'��'9'��'.'��ɵ��ַ���,'.'ֻ�ܳ���һ��) + ��ѡ��'E'/'e'ָ������ + ��ѡ��'-' + ����������(��ָ�����ű���ͬʱ����))
//���� �ַ���(ֻ��)
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
//��������  ��һ���ַ������Ƶ�һ�θ���Ŀռ���,ͬʱɾ��ԭ�ַ���ռ�õĿռ�
//����   Դ�ַ���(��̬����)   ���,��������Դ�ַ�����Ȳ��������ַ������,��ʹ�����ô���
char *allocatNewArray(char *array, int &width){
    //�ռ䲻������¿ռ�
    char *newArray = new char[width * 2];
    //�·���Ŀռ䲻���ʼ��,�����Ƚ��г�ʼ��
    memset(newArray, 0, width * 2);
    memcpy(newArray + width, array, width);
    //ɾ��ԭ�пռ�
    delete []array;
    width = width * 2;
    return newArray;
}
//��������  ��һ��long������ת��Ϊ�ַ���(������ʽ,����'0'��'9'��ɵ��ַ���)
//����  Ҫת����long������    Ŀ���ַ�����ʼ���,Ĭ��Ϊ8(��һ��Ϊ���տ��,�����ʵ��������е���)   ����ָ��(��ָ��Ϊ��ʱ,������Ҫ��ȡת������ַ�������,��ָ��ǿ�,��ת������ַ�������д���ָ��ָ��ı���)
char *simpleItoa(long in, int &length, int width){
    //�ж�������
    int sign = 1;
    if(in < 0){
        sign = -1;
        in = -in;
    }
    char *array = new char[width];
    //�·���Ŀռ䲻���ʼ��,�����Ƚ��г�ʼ��
    memset(array, 0, width);
    int index = width - 1;
    while(in != 0){
        if(index < 0){
            index = width - 1;
            array = allocatNewArray(array, width);
        }
        //������¼����
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
    //����֮��β�����пռ�,��Ҫ��0
    if(index == -1){//����ռ�պ�����,�����������ַ���β��
        char *newArray = new char[width + 1];
        //�·���Ŀռ䲻���ʼ��,�����Ƚ��г�ʼ��
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
//��������  ��һ��double������ת��Ϊ�ַ���(������ʽ,����'0'��'9'��'.'��ɵ��ַ���)
//����   Ҫת����double������   Ŀ���ַ�����ʼ���,Ĭ��Ϊ8(��һ��Ϊ���տ��,�����ʵ��������е���)   С���������(���������)
char *simpleFtoa(double in, int &length, int decimalWidth, int width){
    //С��λ�����������
    if(decimalWidth <= 0)return nullptr;
    //ʹ��round
    long inInteger = (long)round(in * pow(10, decimalWidth));
    //���Դ���
//    char s[10];
//    sprintf(s,"%d",inInteger);
//    qDebug()<<s
    char *intArray = simpleItoa(inInteger, length, width);
    length = length + 2;
    char *array = new char[length];
    //�·���Ŀռ䲻���ʼ��,�����Ƚ��г�ʼ��
    memset(array, 0, length);
    int integerWidth = length - 2 - decimalWidth;
    memcpy(array, intArray, integerWidth);
    array[integerWidth] = '.';
    memcpy(array + integerWidth + 1, intArray + integerWidth, decimalWidth);
    //ɾ����������
    length = length -1;
    delete []intArray;
    return array;
}

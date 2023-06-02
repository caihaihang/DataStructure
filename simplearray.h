#ifndef SIMPLEARRAY_H
#define SIMPLEARRAY_H
#include "simplecontainer.h"

template <typename T>
class SimpleArray : public SimpleContainer<T>
{
public:
    void clear() override { memset(this->container, 0, sizeof(T) * this->containerSize); }
    //����[]����
    T &operator[](int index);
    //�������������
    SimpleArray():SimpleContainer<T>(){}
    ~SimpleArray(){}
};
// �������ط�ʽ  T &operator[](int index)    ��    const T &operator[](int index) ��һ���ȿɶ�ȡ����޸�,�ڶ���ֻ�ܶ�ȡ
template <typename T>
T &SimpleArray<T>::operator[](int index){
    //���ó�����Χ,��������
    if(index > this->containerSize - 1){
        this->expandContainer(index * 2);
    }
    return this->container[index];
}

#endif // SIMPLEARRAY_H

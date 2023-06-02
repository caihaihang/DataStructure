#ifndef SIMPLEARRAY_H
#define SIMPLEARRAY_H
#include "simplecontainer.h"

template <typename T>
class SimpleArray : public SimpleContainer<T>
{
public:
    void clear() override { memset(this->container, 0, sizeof(T) * this->containerSize); }
    //重载[]符号
    T &operator[](int index);
    //构造和析构函数
    SimpleArray():SimpleContainer<T>(){}
    ~SimpleArray(){}
};
// 两种重载方式  T &operator[](int index)    和    const T &operator[](int index) 第一个既可读取亦可修改,第二个只能读取
template <typename T>
T &SimpleArray<T>::operator[](int index){
    //引用超出范围,进行扩容
    if(index > this->containerSize - 1){
        this->expandContainer(index * 2);
    }
    return this->container[index];
}

#endif // SIMPLEARRAY_H

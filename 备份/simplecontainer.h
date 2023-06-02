#ifndef CONTAINER_H
#define CONTAINER_H
#define DEFAULTSTACKSIZE 50
#include <cstring>

template <typename T>
class SimpleContainer
{
protected:
    //存储容器
    T *container;
    //容器大小
    int containerSize = DEFAULTSTACKSIZE;
    virtual void expandContainer(int newSize = 0);
public:
    virtual void clear() = 0;
    //获取容器大小
    int getSize(){ return containerSize; }
    //构造和析构函数
    SimpleContainer();
    ~SimpleContainer();
};
//构造函数
template <typename T>
SimpleContainer<T>::SimpleContainer(){
//    qDebug()<<containerSize;
    container = new T[containerSize];
    //分配的空间未初始化,进行初始化
    memset(container, 0, containerSize * sizeof(T));
}
//析构函数
template <typename T>
SimpleContainer<T>::~SimpleContainer(){
    delete container;
//    qDebug()<<"析构函数执行";
}
//扩容的统一实现
template <typename T>
void SimpleContainer<T>::expandContainer(int newSize){
    //如果未指定扩容大小,默认扩容为原容器的两倍
    if(newSize == 0)newSize = containerSize * 2;
    //分配新容器
    T *newContainer = new T[newSize];
    //分配的空间未初始化,进行初始化
    memset(newContainer, 0, newSize * sizeof(T));
    //搬移数据
    memcpy(newContainer, container, sizeof(T) * containerSize);
    //释放原占用空间
    delete container;
    container = newContainer;
    //记录新容器大小
    containerSize = newSize;
}
#endif // CONTAINER_H

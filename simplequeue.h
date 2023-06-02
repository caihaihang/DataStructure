#ifndef SIMPLEQUEUE_H
#define SIMPLEQUEUE_H
#include "simplecontainer.h"
#include "simpleexception.h"

template <typename T>
class SimpleQueue : public SimpleContainer<T>
{
private:
    // 队列头
    int head = DEFAULTSTACKSIZE/2;
    // 队列尾
    int tail = DEFAULTSTACKSIZE/2 - 1;
protected:
    void expandContainer(int newSize = 0) override;
public:
    //判空
    bool isEmpty(){ return head == tail + 1; }
    //获取队头位置
    int getHead(){ return head; }
    //获取队尾位置
    int getTail(){ return tail; }
    //入队列
    void push(T value);
    void push_back(T value);
    //出队列
    const T *pop_pointer();
    const T *pop_back_pointer();
    T pop();
    T pop_back();
    //清空队列
    void clear() override { head = this->containerSize/2;tail = head - 1; }
    SimpleQueue():SimpleContainer<T>(){}
    ~SimpleQueue(){}
};
//扩容的统一实现
template <typename T>
void SimpleQueue<T>::expandContainer(int newSize){
    if(newSize == 0)newSize = this->containerSize * 2;
    //分配新容器
    T *newContainer = new T[newSize];
    //分配的空间未初始化,进行初始化  单就队列这个数据结构,可以不用初始化
    //memset(newContainer, 0, newSize * sizeof(T));
    //计算当前位置的中点  将该中点与新容器中点重合
    int pos = tail + (head - tail) / 2;
    //计算旧容器位置与新容器位置的偏移值
    int offset = newSize / 2 - pos;
    memcpy(newContainer + tail + offset, this->container + tail, sizeof(T) * (head - tail + 1));
    //重新设置tail和head
    tail += offset;
    head += offset;
    //重新设置容器和容器大小
    this->container = newContainer;
    this->containerSize = newSize;
}
//头部入队列
template <typename T>
void SimpleQueue<T>::push(T value){
    if(head > this->containerSize - 2){
        expandContainer();
    }
    this->container[head] = value;
    head++;
}
//尾部入队列
template <typename T>
void SimpleQueue<T>::push_back(T value){
    if(tail < 1){
        expandContainer();
    }
    this->container[tail] = value;
    tail--;
}
//头部出队列
template <typename T>
const T *SimpleQueue<T>::pop_pointer(){
    if(head - 1 <= tail){
        return nullptr;
    }
    head--;
    return &(this->container[head]);
}
template <typename T>
T SimpleQueue<T>::pop(){
    if(head - 1 <= tail)throw new SimpleException(3, "队列空出队列");
    head--;
    return this->container[head];
}
//尾部出队列
template <typename T>
const T *SimpleQueue<T>::pop_back_pointer(){
    if(head <= tail + 1){
        return nullptr;
    }
    tail++;
    return &(this->container[tail]);
}
template <typename T>
T SimpleQueue<T>::pop_back(){
    if(head <= tail + 1)throw new SimpleException(3, "队列空出队列");
    tail++;
    return this->container[tail];
}
#endif // SIMPLEQUEUE_H

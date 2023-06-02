#ifndef SIMPLESTACK_H
#define SIMPLESTACK_H
#include "simplecontainer.h"
#include "simpleexception.h"

//对于一个非依赖型名称（不以任何方式依赖于模板参数的名称），在模板声明进行解析的时候就会进行查找。但C++标准中规定（14.6.2 3），一个非受限的名称查找的时候将不会考虑依赖型的基类。
template <typename T>
class SimpleStack : public SimpleContainer<T>
{
private:
    //栈顶位置
    int top = 0;
public:
    //判空
    bool isEmpty(){ return top == 0; }
    //获取栈存储的元素个数
    int getNum(){ return top; }
    //清空栈
    void clear() override { top = 0; }
    //获取栈的原始数据起始位置
    T *originData(){ return this->container; }
    //压栈
    void push(T value);
    //出栈指针
    const T *popPointer();
    //出栈原始数据
    T pop();
    //构造和析构函数
    SimpleStack():SimpleContainer<T>(){}
    ~SimpleStack(){}
};
//入栈函数
template <typename T>
void SimpleStack<T>::push(T value){
    if(top > this->containerSize - 2){
        //即将超出范围,重新分配空间
        this->expandContainer();
    }
    this->container[top] = value;
    top++;
}
//出栈函数
template <typename T>
const T *SimpleStack<T>::popPointer(){
    if(top == 0)return nullptr;
    else {
        top--;
        return &(this->container[top]);
    }
}
//出栈原始数据
template <typename T>
T SimpleStack<T>::pop(){
    if(top == 0)throw new SimpleException(1, "空栈弹出错误");
    else {
        top--;
        return this->container[top];
    }
}



#endif // SIMPLESTACK_H

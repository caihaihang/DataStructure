#ifndef SIMPLESTACK_H
#define SIMPLESTACK_H
#include "simplecontainer.h"
#include "simpleexception.h"

//����һ�������������ƣ������κη�ʽ������ģ����������ƣ�����ģ���������н�����ʱ��ͻ���в��ҡ���C++��׼�й涨��14.6.2 3����һ�������޵����Ʋ��ҵ�ʱ�򽫲��ῼ�������͵Ļ��ࡣ
template <typename T>
class SimpleStack : public SimpleContainer<T>
{
private:
    //ջ��λ��
    int top = 0;
public:
    //�п�
    bool isEmpty(){ return top == 0; }
    //��ȡջ�洢��Ԫ�ظ���
    int getNum(){ return top; }
    //���ջ
    void clear() override { top = 0; }
    //��ȡջ��ԭʼ������ʼλ��
    T *originData(){ return this->container; }
    //ѹջ
    void push(T value);
    //��ջָ��
    const T *popPointer();
    //��ջԭʼ����
    T pop();
    //�������������
    SimpleStack():SimpleContainer<T>(){}
    ~SimpleStack(){}
};
//��ջ����
template <typename T>
void SimpleStack<T>::push(T value){
    if(top > this->containerSize - 2){
        //����������Χ,���·���ռ�
        this->expandContainer();
    }
    this->container[top] = value;
    top++;
}
//��ջ����
template <typename T>
const T *SimpleStack<T>::popPointer(){
    if(top == 0)return nullptr;
    else {
        top--;
        return &(this->container[top]);
    }
}
//��ջԭʼ����
template <typename T>
T SimpleStack<T>::pop(){
    if(top == 0)throw new SimpleException(1, "��ջ��������");
    else {
        top--;
        return this->container[top];
    }
}



#endif // SIMPLESTACK_H

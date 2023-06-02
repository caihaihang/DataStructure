#ifndef SIMPLEQUEUE_H
#define SIMPLEQUEUE_H
#include "simplecontainer.h"
#include "simpleexception.h"

template <typename T>
class SimpleQueue : public SimpleContainer<T>
{
private:
    // ����ͷ
    int head = DEFAULTSTACKSIZE/2;
    // ����β
    int tail = DEFAULTSTACKSIZE/2 - 1;
protected:
    void expandContainer(int newSize = 0) override;
public:
    //�п�
    bool isEmpty(){ return head == tail + 1; }
    //��ȡ��ͷλ��
    int getHead(){ return head; }
    //��ȡ��βλ��
    int getTail(){ return tail; }
    //�����
    void push(T value);
    void push_back(T value);
    //������
    const T *pop_pointer();
    const T *pop_back_pointer();
    T pop();
    T pop_back();
    //��ն���
    void clear() override { head = this->containerSize/2;tail = head - 1; }
    SimpleQueue():SimpleContainer<T>(){}
    ~SimpleQueue(){}
};
//���ݵ�ͳһʵ��
template <typename T>
void SimpleQueue<T>::expandContainer(int newSize){
    if(newSize == 0)newSize = this->containerSize * 2;
    //����������
    T *newContainer = new T[newSize];
    //����Ŀռ�δ��ʼ��,���г�ʼ��  ���Ͷ���������ݽṹ,���Բ��ó�ʼ��
    //memset(newContainer, 0, newSize * sizeof(T));
    //���㵱ǰλ�õ��е�  �����е����������е��غ�
    int pos = tail + (head - tail) / 2;
    //���������λ����������λ�õ�ƫ��ֵ
    int offset = newSize / 2 - pos;
    memcpy(newContainer + tail + offset, this->container + tail, sizeof(T) * (head - tail + 1));
    //��������tail��head
    tail += offset;
    head += offset;
    //��������������������С
    this->container = newContainer;
    this->containerSize = newSize;
}
//ͷ�������
template <typename T>
void SimpleQueue<T>::push(T value){
    if(head > this->containerSize - 2){
        expandContainer();
    }
    this->container[head] = value;
    head++;
}
//β�������
template <typename T>
void SimpleQueue<T>::push_back(T value){
    if(tail < 1){
        expandContainer();
    }
    this->container[tail] = value;
    tail--;
}
//ͷ��������
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
    if(head - 1 <= tail)throw new SimpleException(3, "���пճ�����");
    head--;
    return this->container[head];
}
//β��������
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
    if(head <= tail + 1)throw new SimpleException(3, "���пճ�����");
    tail++;
    return this->container[tail];
}
#endif // SIMPLEQUEUE_H

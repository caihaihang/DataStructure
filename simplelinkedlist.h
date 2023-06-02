#ifndef SIMPLELINKEDLIST_H
#define SIMPLELINKEDLIST_H
#include "simpleexception.h"

/*ʹ��throw�׳��쳣���Ƿ����쳣����
*/

template <typename T>
struct SimpleLinkedListNode{
    T data;
    SimpleLinkedListNode *lastNode;
    SimpleLinkedListNode *nextNode;
    SimpleLinkedListNode<T>(T data, SimpleLinkedListNode* lastNode, SimpleLinkedListNode* nextNode):data(data),lastNode(lastNode),nextNode(nextNode) {}
};

template <typename T>
class SimpleLinkedList{
private:
    SimpleLinkedListNode<T> *head;
    SimpleLinkedListNode<T> *tail;
    SimpleLinkedListNode<T> *cursor;
public:
    //�������
    void clear();
    //���¿�ʼ��ȡ����
    void retrieve(){ cursor = nullptr; }
    //��ȡ��һ������
    const T *getNext();
    //��ȡ��һ������
    const T *getLast();
    //ͷ���������
    void prepend(T value);
    //β���������
    void append(T value);
    //ͷ���Ƴ�����
    T pop();
    //β���Ƴ�����
    T pop_back();
    //�������������
    SimpleLinkedList(){ head = tail = cursor = nullptr; }
    ~SimpleLinkedList(){ clear(); }
};
//ͷ���������
template <typename T>
void SimpleLinkedList<T>::append(T value){
    if(tail == nullptr)head = tail = new SimpleLinkedListNode<T>(value,nullptr,nullptr);
    else {
        tail->nextNode = new SimpleLinkedListNode<T>(value,tail,nullptr);
        tail = tail->nextNode;
    }
}
//β���������
template <typename T>
void SimpleLinkedList<T>::prepend(T value){
    if(head == nullptr)head = tail = new SimpleLinkedListNode<T>(value,nullptr,nullptr);
    else  {
        head->lastNode = new SimpleLinkedListNode<T>(value,nullptr,head);
        head = head->lastNode;
    }
}
//��ȡ��һ������
template <typename T>
const T *SimpleLinkedList<T>::getNext(){
    //����α�Ϊ��,��ͷ����ʼ
    if(cursor == nullptr){
        //���ͷ��Ϊ��,���ؿ�ָ��
        if(head == nullptr)return nullptr;
        else {
            //�α꿪ʼʱָ��ͷ��
            cursor = head;
        }
    }else {
        //�����һ�����ݲ�����,���ؿ�ָ��
        if(cursor->nextNode == nullptr)return nullptr;
        else {
            //�α�ָ����һ��
            cursor = cursor->nextNode;
        }
    }
    //�����α���ָ����
    return &(cursor->data);
}
//��ȡ��һ������
template <typename T>
const T *SimpleLinkedList<T>::getLast(){
    //����α�Ϊ��,��β����ʼ
    if(cursor == nullptr){
        //���β��Ϊ��,���ؿ�ָ��
        if(tail == nullptr)return nullptr;
        else {
            //�α꿪ʼʱָ��ͷ��
            cursor = tail;
        }
    }else {
        //�����һ�����ݲ�����,���ؿ�ָ��
        if(cursor->lastNode == nullptr)return nullptr;
        else {
            //�α�ָ����һ��
            cursor = cursor->lastNode;
        }
    }
    //�����α���ָ����
    return &(cursor->data);
}
//�������
template <typename T>
void SimpleLinkedList<T>::clear(){
    if(head == nullptr)return ;
    else {
        auto nextNode = head->nextNode;
        while(nextNode != nullptr){
            delete head;
            head = nextNode;
            nextNode = head->nextNode;
        }
        delete head;
        head = tail = cursor = nullptr;
    }
}
//ͷ���������
template <typename T>
T SimpleLinkedList<T>::pop(){
    if(head == nullptr)throw new SimpleException(0, "�����Ƴ�����");
    else {
        auto data = head->data;
        auto node = head;
        head = node->nextNode;
        delete node;
        return data;
    }
}
//β���������
template <typename T>
T SimpleLinkedList<T>::pop_back(){
    if(tail == nullptr)throw new SimpleException(0, "�����Ƴ�����");
    else {
        auto data = head->data;
        auto node = head;
        head = node->nextNode;
        delete node;
        return data;
    }
}
#endif // SIMPLELINKEDLIST_H

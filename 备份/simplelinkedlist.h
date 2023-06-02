#ifndef SIMPLELINKEDLIST_H
#define SIMPLELINKEDLIST_H
#include "simpleexception.h"

/*使用throw抛出异常还是返回异常数据
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
    //清空数据
    void clear();
    //重新开始读取数据
    void retrieve(){ cursor = nullptr; }
    //获取下一个数据
    const T *getNext();
    //获取上一个数据
    const T *getLast();
    //头部添加数据
    void prepend(T value);
    //尾部添加数据
    void append(T value);
    //头部移除数据
    T pop();
    //尾部移除数据
    T pop_back();
    //构造和析构函数
    SimpleLinkedList(){ head = tail = cursor = nullptr; }
    ~SimpleLinkedList(){ clear(); }
};
//头部添加数据
template <typename T>
void SimpleLinkedList<T>::append(T value){
    if(tail == nullptr)head = tail = new SimpleLinkedListNode<T>(value,nullptr,nullptr);
    else {
        tail->nextNode = new SimpleLinkedListNode<T>(value,tail,nullptr);
        tail = tail->nextNode;
    }
}
//尾部添加数据
template <typename T>
void SimpleLinkedList<T>::prepend(T value){
    if(head == nullptr)head = tail = new SimpleLinkedListNode<T>(value,nullptr,nullptr);
    else  {
        head->lastNode = new SimpleLinkedListNode<T>(value,nullptr,head);
        head = head->lastNode;
    }
}
//获取下一个数据
template <typename T>
const T *SimpleLinkedList<T>::getNext(){
    //如果游标为空,从头部开始
    if(cursor == nullptr){
        //如果头部为空,返回空指针
        if(head == nullptr)return nullptr;
        else {
            //游标开始时指向头部
            cursor = head;
        }
    }else {
        //如果下一个数据不存在,返回空指针
        if(cursor->nextNode == nullptr)return nullptr;
        else {
            //游标指向下一个
            cursor = cursor->nextNode;
        }
    }
    //返回游标所指数据
    return &(cursor->data);
}
//获取上一个数据
template <typename T>
const T *SimpleLinkedList<T>::getLast(){
    //如果游标为空,从尾部开始
    if(cursor == nullptr){
        //如果尾部为空,返回空指针
        if(tail == nullptr)return nullptr;
        else {
            //游标开始时指向头部
            cursor = tail;
        }
    }else {
        //如果上一个数据不存在,返回空指针
        if(cursor->lastNode == nullptr)return nullptr;
        else {
            //游标指向下一个
            cursor = cursor->lastNode;
        }
    }
    //返回游标所指数据
    return &(cursor->data);
}
//清空数据
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
//头部清除数据
template <typename T>
T SimpleLinkedList<T>::pop(){
    if(head == nullptr)throw new SimpleException(0, "链表移除错误");
    else {
        auto data = head->data;
        auto node = head;
        head = node->nextNode;
        delete node;
        return data;
    }
}
//尾部清除数据
template <typename T>
T SimpleLinkedList<T>::pop_back(){
    if(tail == nullptr)throw new SimpleException(0, "链表移除错误");
    else {
        auto data = head->data;
        auto node = head;
        head = node->nextNode;
        delete node;
        return data;
    }
}
#endif // SIMPLELINKEDLIST_H

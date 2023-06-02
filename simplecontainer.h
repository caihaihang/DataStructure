#ifndef CONTAINER_H
#define CONTAINER_H
#define DEFAULTSTACKSIZE 50
#include <cstring>

template <typename T>
class SimpleContainer
{
protected:
    //�洢����
    T *container;
    //������С
    int containerSize = DEFAULTSTACKSIZE;
    virtual void expandContainer(int newSize = 0);
public:
    virtual void clear() = 0;
    //��ȡ������С
    int getSize(){ return containerSize; }
    //�������������
    SimpleContainer();
    ~SimpleContainer();
};
//���캯��
template <typename T>
SimpleContainer<T>::SimpleContainer(){
//    qDebug()<<containerSize;
    container = new T[containerSize];
    //����Ŀռ�δ��ʼ��,���г�ʼ��
    memset(container, 0, containerSize * sizeof(T));
}
//��������
template <typename T>
SimpleContainer<T>::~SimpleContainer(){
    delete container;
//    qDebug()<<"��������ִ��";
}
//���ݵ�ͳһʵ��
template <typename T>
void SimpleContainer<T>::expandContainer(int newSize){
    //���δָ�����ݴ�С,Ĭ������Ϊԭ����������
    if(newSize == 0)newSize = containerSize * 2;
    //����������
    T *newContainer = new T[newSize];
    //����Ŀռ�δ��ʼ��,���г�ʼ��
    memset(newContainer, 0, newSize * sizeof(T));
    //��������
    memcpy(newContainer, container, sizeof(T) * containerSize);
    //�ͷ�ԭռ�ÿռ�
    delete container;
    container = newContainer;
    //��¼��������С
    containerSize = newSize;
}
#endif // CONTAINER_H

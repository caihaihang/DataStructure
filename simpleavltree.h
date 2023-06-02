#ifndef SIMPLEAVLTREE_H
#define SIMPLEAVLTREE_H
#include "simplequeue.h"
#include "simplestring.h"

template <typename T>
struct SimpleAvlTreeNode{
    T data;
    int depth;
    SimpleAvlTreeNode *parent;
    SimpleAvlTreeNode *lNode;
    SimpleAvlTreeNode *rNode;
    SimpleAvlTreeNode<T>(T data, int depth, SimpleAvlTreeNode* parent, SimpleAvlTreeNode* lNode, SimpleAvlTreeNode* rNode) :data(data), depth(depth), parent(parent), lNode(lNode), rNode(rNode) {}
};
template <typename T>
class SimpleAvlTree{
protected:
    SimpleAvlTreeNode<T> *root = nullptr;
public:
    void lRotate(SimpleAvlTreeNode<T> *currentNode);
    void rRotate(SimpleAvlTreeNode<T> *currentNode);
    void updateDepth(SimpleAvlTreeNode<T> *currentNode);
    void addNode(T data);
    SimpleAvlTreeNode<T> *getRoot(){ return root; }
    void clear(SimpleAvlTreeNode<T> *n);
    SimpleAvlTree(){}
    ~SimpleAvlTree(){ clear(root); }
};
//���ռ�õĿռ�
template <typename T>
void SimpleAvlTree<T>::clear(SimpleAvlTreeNode<T> *n){
    if(n->lNode != nullptr)clear(n->lNode);
    if(n->rNode != nullptr)clear(n->rNode);
    delete n;
}
//��������  Ŀ��:�������ӽڵ�
//��ת����  ��ת���ԭ��ڵ����ڵ���Ȳ���,��ת�������ڵ���Ȳ���,��ת��������Ҫ�ı�,����������
template <typename T>
void SimpleAvlTree<T>::rRotate(SimpleAvlTreeNode<T> *currentNode){
    //������ת�����ڵ�
    SimpleAvlTreeNode<T> *lNode = currentNode->lNode;
    //����ת�����ڵ���ҽڵ�תΪ��ת�����ڵ�
    currentNode->lNode = lNode->rNode;
    if(lNode->rNode != nullptr)lNode->rNode->parent = currentNode;
    //����ת�����ڵ���������ת������λ��
    lNode->parent = currentNode->parent;
    if(currentNode->parent != nullptr){
        if(currentNode->parent->lNode == currentNode)currentNode->parent->lNode = lNode;
        else currentNode->parent->rNode = lNode;
        //���ڵ�Ϊ��˵��Ϊroot�ڵ�
    }else this->root = lNode;
    //��ת���Ϊ��ת�����ڵ�����ҽڵ�
    lNode->rNode = currentNode;
    currentNode->parent = lNode;
}
//��������  Ŀ��:�������ӽڵ�
//��ת����  ��ת���ԭ�ҽڵ���ҽڵ���Ȳ���,��ת������ҽڵ���Ȳ���,��ת��������Ҫ�ı�,����������
template <typename T>
void SimpleAvlTree<T>::lRotate(SimpleAvlTreeNode<T> *currentNode){
    //������ת����ҽڵ�
    SimpleAvlTreeNode<T> *rNode = currentNode->rNode;
    //����ת����ҽڵ����ڵ�תΪ��ת����ҽڵ� ��Ҫ�ýڵ�ǿ�
    currentNode->rNode = rNode->lNode;
    if(rNode->lNode != nullptr)rNode->lNode->parent = currentNode;
    //����ת����ҽڵ���������ת������λ�� ��Ҫ��ת��ĸ��ڵ�ǿ�
    rNode->parent = currentNode->parent;
    if(currentNode->parent != nullptr){
        if(currentNode->parent->lNode == currentNode)currentNode->parent->lNode = rNode;
        else currentNode->parent->rNode = rNode;
        //���ڵ�Ϊ��˵��Ϊroot�ڵ�
    }else this->root = rNode;
    //��ת���Ϊ��ת����ҽڵ������ڵ�
    rNode->lNode = currentNode;
    currentNode->parent = rNode;
}
//���������Ϣ
template <typename T>
void SimpleAvlTree<T>::updateDepth(SimpleAvlTreeNode<T> *currentNode){
    int lNodeDepth = currentNode->lNode == nullptr ? 0 : currentNode->lNode->depth;
    int rNodeDepth = currentNode->rNode == nullptr ? 0 : currentNode->rNode->depth;
    int maxDepth = lNodeDepth >= rNodeDepth ? lNodeDepth : rNodeDepth;
    int depthOffset = lNodeDepth - rNodeDepth;
    //��ߵ���ȸ߳�1����,����
    if(depthOffset > 1){
        rRotate(currentNode);
        updateDepth(currentNode);
    }
    else if(depthOffset < -1){
        lRotate(currentNode);
        updateDepth(currentNode);
    }else if(currentNode->depth == maxDepth + 1){
        return ;
    }
    else {
        currentNode->depth = maxDepth + 1;
        if(currentNode->parent != nullptr)updateDepth(currentNode->parent);
    }
}
//���ӽڵ�
template <typename T>
void SimpleAvlTree<T>::addNode(T data){
    if(this->root == nullptr){//Ĭ�ϵ����ڵ����Ϊ0
        this->root = new SimpleAvlTreeNode<T>(data, 1, nullptr, nullptr, nullptr);
    }else {
        SimpleAvlTreeNode<T> *currentNode = this->root;
        while(true){
            //�Ƚϸ������뵱ǰ�ڵ����ֵ
            if(data >= currentNode->data){
                //������ڵ����ҵ�ǰ�ڵ���ֵΪ��,����
                if(currentNode->rNode == nullptr){
                    currentNode->rNode = new SimpleAvlTreeNode<T>(data, 1, currentNode, nullptr, nullptr);
                    updateDepth(currentNode);
                    return ;
                }else currentNode = currentNode->rNode;//������ڵ��ڵ���ǰ�ڵ���ֵ�ǿ�,�����Ƚ�
            }else {
                //������ڵ����ҵ�ǰ�ڵ���ֵΪ��,����
                if(currentNode->lNode == nullptr){
                    currentNode->lNode = new SimpleAvlTreeNode<T>(data, 1, currentNode, nullptr, nullptr);
                    updateDepth(currentNode);
                    return ;
                    //������ڵ��ڵ���ǰ�ڵ���ֵ�ǿ�,�����Ƚ�
                }else currentNode = currentNode->lNode;
            }
        }
    }
}
class SimpleIntAvlTree : public SimpleAvlTree<int>{
public:
    void iteratorTreeString(SimpleAvlTreeNode<int> *currentNode);
    char *toString();
    char *depthToString();
    SimpleIntAvlTree(){}
    ~SimpleIntAvlTree(){}
};
void SimpleIntAvlTree::iteratorTreeString(SimpleAvlTreeNode<int> *currentNode){
    if(currentNode->lNode != nullptr)iteratorTreeString(currentNode->lNode);
    std::cout << currentNode->data;
    if(currentNode->rNode != nullptr)iteratorTreeString(currentNode->rNode);
}
char *SimpleIntAvlTree::toString(){
    SimpleQueue<SimpleAvlTreeNode<int> *> *ss = new SimpleQueue<SimpleAvlTreeNode<int> *>();
    SimpleQueue<SimpleAvlTreeNode<int> *> *ssNext = new SimpleQueue<SimpleAvlTreeNode<int> *>();
    SimpleQueue<SimpleAvlTreeNode<int> *> *temp = nullptr;
    SimpleAvlTreeNode<int> *n = nullptr;
    ss->push(root);
    SimpleStringBuilder strBuilder;
    SimpleString layerInsideGap = SimpleString(" ");
    SimpleString layerGap = SimpleString("\n");
    while(true){
        while(!ss->isEmpty()){
            n = ss->pop_back();
            if(n->lNode != nullptr)ssNext->push(n->lNode);
            if(n->rNode != nullptr)ssNext->push(n->rNode);
            SimpleString data = SimpleString((long)n->data);
            strBuilder.append(layerInsideGap);
            strBuilder.append(data);
        }
        if(!ssNext->isEmpty()){
            temp = ss;
            ss = ssNext;
            ssNext = temp;
            strBuilder.append(layerGap);
        }else break;
    }
    int length = strBuilder.getLength();
    char *s = new char[length + 1];
    memcpy(s, strBuilder.getData(), length);
    s[length] = 0;
    //�ͷſռ�
    delete ss;
    delete ssNext;
    return s;
}
char *SimpleIntAvlTree::depthToString(){
    SimpleQueue<SimpleAvlTreeNode<int> *> *ss = new SimpleQueue<SimpleAvlTreeNode<int> *>();
    SimpleQueue<SimpleAvlTreeNode<int> *> *ssNext = new SimpleQueue<SimpleAvlTreeNode<int> *>();
    SimpleQueue<SimpleAvlTreeNode<int> *> *temp = nullptr;
    SimpleAvlTreeNode<int> *n = nullptr;
    ss->push(root);
    SimpleStringBuilder strBuilder;
    SimpleString layerInsideGap = SimpleString(" ");
    SimpleString layerGap = SimpleString("\n");
    while(true){
        while(!ss->isEmpty()){
            n = ss->pop_back();
            if(n->lNode != nullptr)ssNext->push(n->lNode);
            if(n->rNode != nullptr)ssNext->push(n->rNode);
            SimpleString data = SimpleString((long)n->depth);
            strBuilder.append(layerInsideGap);
            strBuilder.append(data);
        }
        if(!ssNext->isEmpty()){
            temp = ss;
            ss = ssNext;
            ssNext = temp;
            strBuilder.append(layerGap);
        }else break;
    }
    int length = strBuilder.getLength();
    char *s = new char[length + 1];
    memcpy(s, strBuilder.getData(), length);
    s[length] = 0;
    //�ͷſռ�
    delete ss;
    delete ssNext;
    return s;
}
#endif // SIMPLEAVLTREE_H

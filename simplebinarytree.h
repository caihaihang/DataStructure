#ifndef SIMPLEBINARYTREE_H
#define SIMPLEBINARYTREE_H
#include "simplequeue.h"
#include "simplestring.h"

template <typename T>
struct SimpleBinaryTreeNode{
    T data;
    SimpleBinaryTreeNode *parent;
    SimpleBinaryTreeNode *lNode;
    SimpleBinaryTreeNode *rNode;
    SimpleBinaryTreeNode<T>(T data, SimpleBinaryTreeNode* parent, SimpleBinaryTreeNode* lNode, SimpleBinaryTreeNode* rNode):data(data),parent(parent),lNode(lNode),rNode(rNode){}
};

template <typename T>
class SimpleBinaryTree{
protected:
    SimpleBinaryTreeNode<T> *root = nullptr;
public:
    SimpleBinaryTreeNode<T> *getRoot(){ return root; }
    void clear(SimpleBinaryTreeNode<T> *n);
    SimpleBinaryTree(){}
    ~SimpleBinaryTree(){ clear(root); }
};
//���ռ�õĿռ�
template <typename T>
void SimpleBinaryTree<T>::clear(SimpleBinaryTreeNode<T> *n){
    if(n->lNode != nullptr)clear(n->lNode);
    if(n->rNode != nullptr)clear(n->rNode);
    delete n;
}
//˼��  ��οɱ�
template <typename T>
class SimpleBinarySortTree : public SimpleBinaryTree<T>{
public:
    virtual void addNode(T data);
    SimpleBinarySortTree(){}
    ~SimpleBinarySortTree(){}
};
//���ӽڵ�
template <typename T>
void SimpleBinarySortTree<T>::addNode(T data){
    if(this->root == nullptr){
        this->root = new SimpleBinaryTreeNode<T>(data, nullptr, nullptr, nullptr);
    }else {
        SimpleBinaryTreeNode<T> *currentNode = this->root;
        while(true){
            //�Ƚϸ������뵱ǰ�ڵ����ֵ
            if(data >= currentNode->data){
                //������ڵ����ҵ�ǰ�ڵ���ֵΪ��,����
                if(currentNode->rNode == nullptr){
                    currentNode->rNode = new SimpleBinaryTreeNode<T>(data, currentNode, nullptr, nullptr);
                    return ;
                }else currentNode = currentNode->rNode;//������ڵ��ڵ���ǰ�ڵ���ֵ�ǿ�,�����Ƚ�
            }else {
                //������ڵ����ҵ�ǰ�ڵ���ֵΪ��,����
                if(currentNode->lNode == nullptr){
                    currentNode->lNode = new SimpleBinaryTreeNode<T>(data, currentNode, nullptr, nullptr);
                    return ;
                    //������ڵ��ڵ���ǰ�ڵ���ֵ�ǿ�,�����Ƚ�
                }else currentNode = currentNode->lNode;
            }
        }
    }
}
class SimpleIntBinarySortTree : public SimpleBinarySortTree<int>{
public:
    char *toString();
    SimpleIntBinarySortTree(){}
    ~SimpleIntBinarySortTree(){}
};
char *SimpleIntBinarySortTree::toString(){
    SimpleQueue<SimpleBinaryTreeNode<int> *> *ss = new SimpleQueue<SimpleBinaryTreeNode<int> *>();
    SimpleQueue<SimpleBinaryTreeNode<int> *> *ssNext = new SimpleQueue<SimpleBinaryTreeNode<int> *>();
    SimpleQueue<SimpleBinaryTreeNode<int> *> *temp = nullptr;
    SimpleBinaryTreeNode<int> *n = nullptr;
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
#endif // SIMPLEBINARYTREE_H

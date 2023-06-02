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
//清空占用的空间
template <typename T>
void SimpleBinaryTree<T>::clear(SimpleBinaryTreeNode<T> *n){
    if(n->lNode != nullptr)clear(n->lNode);
    if(n->rNode != nullptr)clear(n->rNode);
    delete n;
}
//思考  如何可比
template <typename T>
class SimpleBinarySortTree : public SimpleBinaryTree<T>{
public:
    virtual void addNode(T data);
    SimpleBinarySortTree(){}
    ~SimpleBinarySortTree(){}
};
//增加节点
template <typename T>
void SimpleBinarySortTree<T>::addNode(T data){
    if(this->root == nullptr){
        this->root = new SimpleBinaryTreeNode<T>(data, nullptr, nullptr, nullptr);
    }else {
        SimpleBinaryTreeNode<T> *currentNode = this->root;
        while(true){
            //比较该数据与当前节点的数值
            if(data >= currentNode->data){
                //如果大于等于且当前节点右值为空,插入
                if(currentNode->rNode == nullptr){
                    currentNode->rNode = new SimpleBinaryTreeNode<T>(data, currentNode, nullptr, nullptr);
                    return ;
                }else currentNode = currentNode->rNode;//如果大于等于但当前节点右值非空,继续比较
            }else {
                //如果大于等于且当前节点左值为空,插入
                if(currentNode->lNode == nullptr){
                    currentNode->lNode = new SimpleBinaryTreeNode<T>(data, currentNode, nullptr, nullptr);
                    return ;
                    //如果大于等于但当前节点左值非空,继续比较
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
    //释放空间
    delete ss;
    delete ssNext;
    return s;
}
#endif // SIMPLEBINARYTREE_H

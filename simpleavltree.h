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
//清空占用的空间
template <typename T>
void SimpleAvlTree<T>::clear(SimpleAvlTreeNode<T> *n){
    if(n->lNode != nullptr)clear(n->lNode);
    if(n->rNode != nullptr)clear(n->rNode);
    delete n;
}
//右旋函数  目的:提升左子节点
//旋转过后  旋转点的原左节点的左节点深度不变,旋转点的新左节点深度不变,旋转点的深度需要改变,并继续更新
template <typename T>
void SimpleAvlTree<T>::rRotate(SimpleAvlTreeNode<T> *currentNode){
    //保留旋转点的左节点
    SimpleAvlTreeNode<T> *lNode = currentNode->lNode;
    //将旋转点的左节点的右节点转为旋转点的左节点
    currentNode->lNode = lNode->rNode;
    if(lNode->rNode != nullptr)lNode->rNode->parent = currentNode;
    //将旋转点的左节点提升到旋转点所在位置
    lNode->parent = currentNode->parent;
    if(currentNode->parent != nullptr){
        if(currentNode->parent->lNode == currentNode)currentNode->parent->lNode = lNode;
        else currentNode->parent->rNode = lNode;
        //父节点为空说明为root节点
    }else this->root = lNode;
    //旋转点成为旋转点的左节点的新右节点
    lNode->rNode = currentNode;
    currentNode->parent = lNode;
}
//左旋函数  目的:提升右子节点
//旋转过后  旋转点的原右节点的右节点深度不变,旋转点的新右节点深度不变,旋转点的深度需要改变,并继续更新
template <typename T>
void SimpleAvlTree<T>::lRotate(SimpleAvlTreeNode<T> *currentNode){
    //保留旋转点的右节点
    SimpleAvlTreeNode<T> *rNode = currentNode->rNode;
    //将旋转点的右节点的左节点转为旋转点的右节点 需要该节点非空
    currentNode->rNode = rNode->lNode;
    if(rNode->lNode != nullptr)rNode->lNode->parent = currentNode;
    //将旋转点的右节点提升到旋转点所在位置 需要旋转点的父节点非空
    rNode->parent = currentNode->parent;
    if(currentNode->parent != nullptr){
        if(currentNode->parent->lNode == currentNode)currentNode->parent->lNode = rNode;
        else currentNode->parent->rNode = rNode;
        //父节点为空说明为root节点
    }else this->root = rNode;
    //旋转点成为旋转点的右节点的新左节点
    rNode->lNode = currentNode;
    currentNode->parent = rNode;
}
//更新深度信息
template <typename T>
void SimpleAvlTree<T>::updateDepth(SimpleAvlTreeNode<T> *currentNode){
    int lNodeDepth = currentNode->lNode == nullptr ? 0 : currentNode->lNode->depth;
    int rNodeDepth = currentNode->rNode == nullptr ? 0 : currentNode->rNode->depth;
    int maxDepth = lNodeDepth >= rNodeDepth ? lNodeDepth : rNodeDepth;
    int depthOffset = lNodeDepth - rNodeDepth;
    //左边的深度高出1以上,左旋
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
//增加节点
template <typename T>
void SimpleAvlTree<T>::addNode(T data){
    if(this->root == nullptr){//默认单个节点深度为0
        this->root = new SimpleAvlTreeNode<T>(data, 1, nullptr, nullptr, nullptr);
    }else {
        SimpleAvlTreeNode<T> *currentNode = this->root;
        while(true){
            //比较该数据与当前节点的数值
            if(data >= currentNode->data){
                //如果大于等于且当前节点右值为空,插入
                if(currentNode->rNode == nullptr){
                    currentNode->rNode = new SimpleAvlTreeNode<T>(data, 1, currentNode, nullptr, nullptr);
                    updateDepth(currentNode);
                    return ;
                }else currentNode = currentNode->rNode;//如果大于等于但当前节点右值非空,继续比较
            }else {
                //如果大于等于且当前节点左值为空,插入
                if(currentNode->lNode == nullptr){
                    currentNode->lNode = new SimpleAvlTreeNode<T>(data, 1, currentNode, nullptr, nullptr);
                    updateDepth(currentNode);
                    return ;
                    //如果大于等于但当前节点左值非空,继续比较
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
    //释放空间
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
    //释放空间
    delete ss;
    delete ssNext;
    return s;
}
#endif // SIMPLEAVLTREE_H

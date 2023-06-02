#include "testfunction.h"
#include "simplestack.h"
#include "simplearray.h"
#include "simplequeue.h"
#include "simplelinkedlist.h"
#include "simplebinarytree.h"
#include "simpleavltree.h"
#include "usefulfunction.h"
#include "simplestring.h"
#include <stdlib.h>
#include <iostream>


//用于测试简单链表
void testSimpleLinkedList(){
    std::cout << "测试简单链表" << std::endl;
    SimpleLinkedList<int> sl = SimpleLinkedList<int>();
    sl.append(3);
    sl.append(2);
    sl.append(1);
    sl.prepend(10);
    sl.prepend(9);
    sl.prepend(8);
    auto data = sl.getNext();
    while(data!=nullptr){
        std::cout << *data << std::endl;
        data = sl.getNext();
    }
//    auto data = sl.getLast();
//    while(data!=nullptr){
//        qDebug()<<*data;
//        data = sl.getLast();
//    }
}
//用于测试简单队列
void testSimpleQueue(){
    std::cout << "测试简单队列" << std::endl;
    SimpleQueue<int> sq = SimpleQueue<int>();
    for(int i = 0; i<30; i++){
        sq.push(i);
    }
    std::cout << sq.getSize() << std::endl;
    std::cout << sq.pop() << std::endl;
}
//用于测试简单栈
void testSimpleStack(){
    std::cout << "测试简单栈" << std::endl;
    SimpleStack<int> ss = SimpleStack<int>();
    for(int i = 0; i<80; i++){
        ss.push(i);
    }
    std::cout << ss.getSize() << std::endl;
    std::cout << ss.pop() << std::endl;
}
//测试简单数组
void testSimpleArray(){
    SimpleArray<int> sa = SimpleArray<int>();
    sa[60] = 100;
    std::cout << sa.getSize();
}
//测试简单字符串
void testSimpleString(){
    SimpleStringBuilder sstrb = SimpleStringBuilder(12345.67f);    
    SimpleString sstr = SimpleString("  ");
    SimpleString sstr1 = SimpleString(12345l);
    SimpleString sstr2 = SimpleString(-12345l);
    SimpleString sstr3 = SimpleString();
    sstrb.append(sstr);
    sstrb.append(sstr1);
    sstrb.append(sstr);
    sstrb.append(sstr2);
    std::cout << sstr.getData() <<" " << sstr.getLength() << " " << sstr.getSize() << std::endl;
    std::cout << sstr1.getData() << " " << sstr1.getLength() << " " << sstr1.getSize() << std::endl;
    std::cout << sstr2.getData() << " " << sstr2.getLength() << " " << sstr2.getSize() << std::endl;
    std::cout << sstr3.getData() << " " << sstr3.getLength() << " " << sstr3.getSize() << std::endl;
    std::cout << sstrb.getData() << " " << sstrb.getLength() << " " << sstrb.getSize() << std::endl;
}
//测试Atoi
void testSimpleAtoi(){
    const char *s1 = "12345";
    const char *s2 = "12345e1";
    const char *s3 = "-12345e2";
    std::cout << simpleAtoi(s1)<<simpleAtoi(s2)<<simpleAtoi(s3);
}
//测试Atof
void testSimpleAtof(){
    const char *s1 = "12345.67";
    const char *s2 = "12345e-1";
    const char *s3 = "-123.45e2.2";
    char s[30];
    sprintf_s(s, 30, "%.2f %.2f %.2f", simpleAtof(s1), simpleAtof(s2), simpleAtof(s3));
    std::cout << s;
}
//测试Itoa
void testSimpleItoa(){
    long l1 = 12345l;
    long l2 = -12345l;
    long l3 = 84569l;
    int length = 0;
    std::cout <<simpleItoa(l1, length)<<length;
    std::cout <<simpleItoa(l2, length)<<length;
    std::cout << simpleItoa(l3, length)<<length;
}
//测试Ftoa
void testSimpleFtoa(){
    double d1 = 12345.67;
    double d2 = -12345.67;
    double d3 = -8952.47;
    int length = 0;
    std::cout << simpleFtoa(d1, length)<<length;
    std::cout << simpleFtoa(d2, length)<<length;
    std::cout << simpleFtoa(d3, length)<<length;
}
//测试SimpleIntBinarySortTree
void testSimpleIntBinarySortTree(){
    SimpleIntBinarySortTree sibst = SimpleIntBinarySortTree();
    sibst.addNode(1);
    sibst.addNode(2);
    sibst.addNode(3);
    std::cout << sibst.toString();
}
//测试SimpleIntAvlTree
void testSimpleIntAvlTree(){
    SimpleIntAvlTree sibst = SimpleIntAvlTree();
//    sibst.addNode(1);
//    sibst.addNode(2);
//    sibst.addNode(3);
    for(int i = 0; i < 8; i ++)sibst.addNode(i);
    for(int i = 14; i > 7; i --)sibst.addNode(i);
    std::cout << sibst.depthToString();
    std::cout << sibst.toString();
    //sibst.iteratorTreeString(sibst.getRoot());
    auto r = sibst.getRoot();
    while(r != nullptr){
        std::cout << r->data;
        r = r->rNode;
    }
    r = sibst.getRoot();
    while(r != nullptr){
        std::cout << r->data;
        r = r->lNode;
    }
}

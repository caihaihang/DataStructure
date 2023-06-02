#ifndef EXCEPTION_H
#define EXCEPTION_H

class SimpleException{
private:
    int _errID;//0--链表移除错误,1--空栈错误,2--小数长度超出范围,3--队列空出队列,4--Ato
    const char *_errMsg;
public:
    SimpleException(int errID, const char* errMsg):_errID(errID),_errMsg(errMsg){}
    int GetErrID() const{
        return _errID;
    }
    const char *what() const{
        return _errMsg;
    }
};

#endif // EXCEPTION_H

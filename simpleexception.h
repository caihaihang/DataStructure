#ifndef EXCEPTION_H
#define EXCEPTION_H

class SimpleException{
private:
    int _errID;//0--�����Ƴ�����,1--��ջ����,2--С�����ȳ�����Χ,3--���пճ�����,4--Ato
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

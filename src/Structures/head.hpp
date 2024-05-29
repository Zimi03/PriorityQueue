#ifndef PRIORITYQUEUE_HEAD_HPP
#define PRIORITYQUEUE_HEAD_HPP
#include "INode.h"
class Head: public INode{
private:
    INode* next;
public:
    Head(){
        next = nullptr;
    }
    INode* getNext() override{
        return next;
    }
    int setNext(INode* _next) override{
        next = _next;
        return 0;
    }
    INode* getPrevious() override{
        return nullptr;
    }
    int setPrevious(INode* _previous) override{
        return 1;
    }
};

#endif //PRIORITYQUEUE_HEAD_HPP

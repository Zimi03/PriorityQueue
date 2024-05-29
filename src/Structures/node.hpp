#ifndef PRIORITYQUEUE_NODE_HPP
#define PRIORITYQUEUE_NODE_HPP
#include "INode.h"
template <typename Data>
class Node: public INode{
private:
    Data data;
    INode* next;

public:
    explicit Node(INode* _next, Data _data): data(_data){
        next = _next;
    }
    INode* getNext() override{
        return next;
    }
    int setNext(INode* _next) override{
     next = _next;
    }
    INode* getPrevious() override{
        return nullptr;
    }
    int setPrevious(INode* _previous) override{
        return 1;
    }
    Data getData(){
        return data;
    }
};

#endif //PRIORITYQUEUE_NODE_HPP

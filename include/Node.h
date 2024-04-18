//
// Created by grzegorz on 22.03.24.
//

#ifndef LISTY_NODE_H
#define LISTY_NODE_H
#include "INode.h"
#include <iostream>
#include "PriorityValue.h"




template <typename Data>
class Node: public INode{
private:
    Data data;
    INode* next;

public:
    explicit Node(INode* _next, Data _data);
    INode* getNext() override;
    int setNext(INode* _next) override;
    INode* getPrevious() override;
    int setPrevious(INode* _previous) override;
    Data getData();
};


#endif //LISTY_NODE_H

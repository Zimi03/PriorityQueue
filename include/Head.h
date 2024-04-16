//
// Created by grzegorz on 22.03.24.
//

#ifndef LISTY_HEAD_H
#define LISTY_HEAD_H
#include "INode.h"


class Head: public INode{
private:
    INode* next;
public:
    Head();
    INode* getNext() override;
    int setNext(INode* next) override;
    INode* getPrevious() override;
    int setPrevious(INode* _previous) override;


};


#endif //LISTY_HEAD_H

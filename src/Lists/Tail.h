//
// Created by grzegorz on 25.03.24.
//

#ifndef LISTY_TAIL_H
#define LISTY_TAIL_H
#include "INode.h"
class Tail:public INode{
private:
    INode* previous; // in the reverse order - means previous
public:
    Tail();
    INode* getNext() override;
    int setNext(INode* next) override;
    INode* getPrevious() override;
    int setPrevious(INode* _previous) override;
};


#endif //LISTY_TAIL_H

//
// Created by grzegorz on 25.03.24.
//

#include "Tail.h"

Tail::Tail() {previous = nullptr;}

INode* Tail::getNext() { return nullptr;}

int Tail::setNext(INode* _next) {
    return 1;
}

INode* Tail::getPrevious() {
    return previous;
}

int Tail::setPrevious(INode* _previous) {
    previous = _previous;
    return 0;
}

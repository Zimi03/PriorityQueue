//
// Created by grzegorz on 22.03.24.
//

#include "Head.h"


Head::Head() {next = nullptr;}


INode* Head::getNext() { return next;}

int Head::setNext(INode* _next) {
    next = _next;
    return 0;
}

INode* Head::getPrevious() {
    return nullptr;
}

int Head::setPrevious(INode* _previous) {
    return 1;
}
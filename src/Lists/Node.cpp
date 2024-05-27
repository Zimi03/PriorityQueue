//
// Created by grzegorz on 22.03.24.
//

#include "Node.h"
template <typename Data>
Node<Data>::Node(INode *_next, Data _data) :  data(_data) {
    next = _next;
}

template <typename Data>
INode* Node<Data>::getNext() {return next;}

template <typename Data>
int Node<Data>::setNext(INode* _next) {
    next = _next;
    return 0;
}

template <typename Data>
INode* Node<Data>::getPrevious() {
    return nullptr;
}

template <typename Data>
int Node<Data>::setPrevious(INode* _previous) {
    return 1;
}

template <typename Data>
Data Node<Data>::getData() {return data;}


template class Node<int>;
template class Node<priorityValue>;
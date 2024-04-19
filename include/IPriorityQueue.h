//
// Created by grzegorz on 19.04.24.
//

#ifndef PRIORITYQUEUE_IPRIORITYQUEUE_H
#define PRIORITYQUEUE_IPRIORITYQUEUE_H
#include "PriorityValue.h"
#include "optional"

class IPriorityQueue{
public:
    virtual ~IPriorityQueue() = 0;
    virtual int insert(priorityValue element) = 0;
    virtual std::optional<priorityValue> extractMax() = 0;
    virtual std::optional<priorityValue> peek() = 0;
    virtual int modifyKey(priorityValue element, int priority) = 0;
};

#endif //PRIORITYQUEUE_IPRIORITYQUEUE_H

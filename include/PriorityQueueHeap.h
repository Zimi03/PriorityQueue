//
// Created by grzegorz on 19.04.24.
//

#ifndef PRIORITYQUEUE_PRIORITYQUEUEHEAP_H
#define PRIORITYQUEUE_PRIORITYQUEUEHEAP_H
#include "IPriorityQueue.h"
#include "BinaryHeap.h"

class PriorityQueueHeap : public IPriorityQueue{
    BinaryHeap* heap = nullptr;
    int size;
    unsigned int count;

public:
    PriorityQueueHeap();
    PriorityQueueHeap(PriorityQueueHeap* to_copy);
    ~PriorityQueueHeap() override;

    int insert(priorityValue element) override;
    std::optional<priorityValue> extractMax() override;
    std::optional<priorityValue> peek() override;
    int modifyKey(priorityValue element, int priority) override;

};


#endif //PRIORITYQUEUE_PRIORITYQUEUEHEAP_H

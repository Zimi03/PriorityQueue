//
// Created by grzegorz on 19.04.24.
//

#include "PriorityQueueHeap.h"

PriorityQueueHeap::PriorityQueueHeap() : count(0) {
    heap = new BinaryHeap();
    size=heap->getSize();
}

PriorityQueueHeap::PriorityQueueHeap(PriorityQueueHeap *to_copy) : count(0){
    heap = new BinaryHeap(to_copy->heap);
    size = heap->getSize();
}

PriorityQueueHeap::~PriorityQueueHeap(){
    delete heap;
}

int PriorityQueueHeap::insert(priorityValue element) {
    heap->insert(priorityValueOrder(element.priority, element.value, count++));
}


std::optional<priorityValue> PriorityQueueHeap::extractMax() {
    heap->extractMax();
}

//
// Created by grzegorz on 19.04.24.
//

#include "PriorityQueueHeap.h"

PriorityQueueHeap::PriorityQueueHeap() {
    heap = new BinaryHeap();
    size=heap->getSize();
}
//
// Created by grzegorz on 18.04.24.
//

#ifndef PRIORITYQUEUE_BINARYHEAP_H
#define PRIORITYQUEUE_BINARYHEAP_H
#include "Dynamic array.h"
//#include "PriorityValueOrder.h"


class BinaryHeap {
    DynamicArray<priorityValueOrder>* heap = nullptr;
    int size = 0;

    int build(DynamicArray<priorityValueOrder>* to_copy);
    int downHeap(int start, int end, int parent);
    int upHeap(int start, int end, int parent);
    int clear();


public:
    BinaryHeap();
    explicit BinaryHeap(BinaryHeap* to_copy);
    ~BinaryHeap();

    void insert(priorityValueOrder element);
    std::optional<priorityValueOrder> extractMax();
    std::optional<priorityValueOrder> findMax();
    std::optional<priorityValueOrder> find(priorityValueOrder element);
    int remove(priorityValue element);

    int modifyKey(priorityValue element, int priority, unsigned int count);
    int increaseKey(priorityValue element, unsigned int count);
    int decreaseKey(priorityValue element, unsigned int count);


    void display();







};


#endif //PRIORITYQUEUE_BINARYHEAP_H

//
// Created by grzegorz on 19.04.24.
//

#pragma once

#include "IPriorityQueue.h"
#include "../Structures/BinaryHeap.hpp"

class PriorityQueueHeap: public IPriorityQueue {
    BinaryHeap *heap = nullptr;
    int size;
    unsigned int counter;

public:
    PriorityQueueHeap() : counter(0) {
        heap = new BinaryHeap();
        size = heap->getSize();
    }

    explicit PriorityQueueHeap(PriorityQueueHeap *to_copy) : counter(0) {
        heap = new BinaryHeap(to_copy->heap);
        size = heap->getSize();
    }

    ~PriorityQueueHeap() override{
        delete heap;
    }
    /**
     * Inserts element in proper place in queue
     * @param element
     */
    void insert(PriorityValue element) override{
        heap->insert(PriorityValueOrder(element.priority, element.value, counter++));
        size = heap->getSize();
    }

    /**
     * Deletes and returns element with highest priority
     * @return extracted element if exists
     * @return std::nullopt if element does not exist
     */
    std::optional<PriorityValue> extractMax() override{
        std::optional<PriorityValueOrder> tmp = heap->extractMax();
        if(tmp == std::nullopt) return std::nullopt;
        else {
            PriorityValue extracted (tmp.value().priority, tmp.value().value);
            size = heap->getSize();
            return extracted;
        }
    }

    /**
     * Returns element with biggest priority
     * @return returns element if exists
     * @return std::nullopt if element does not exist
     */
    std::optional<PriorityValue> peek() override{
        std::optional<PriorityValueOrder> tmp = heap->findMax();
        if(tmp == std::nullopt) return std::nullopt;
        else {
            PriorityValue peeked (tmp.value().priority, tmp.value().value);
            return peeked;
        }
    }

    /**
     * Modifies key of element with given current key and value
     * It also changes counter to new value
     * @param element
     * @param priority
     * @param count
     * @return 0 - success
     * @return 1 - the same priority
     * @return 2 - no such element
     * @return 3 - priority less than zero
     */
    int modifyKey(PriorityValue element, int priority) override{
        return heap->modifyKey(element, priority, counter++);
    }

    /**
     * Returns number of elements in priority queue
     * @return int - size
     */
    int getSize() override{
        return size;
    }

    /**
    * Displays data in queue
    */
    void display() {
        heap->display();
    }
};

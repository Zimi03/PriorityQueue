#include "PriorityQueueHeap.h"

PriorityQueueHeap::PriorityQueueHeap() : counter(0) {
    heap = new BinaryHeap();
    size = heap->getSize();
}

PriorityQueueHeap::PriorityQueueHeap(PriorityQueueHeap *to_copy) : counter(0){
    heap = new BinaryHeap(to_copy->heap);
    size = heap->getSize();
}

PriorityQueueHeap::~PriorityQueueHeap(){
    delete heap;
}

/**
 * Inserts element in proper place in priority queue
 * @param element
 */
void PriorityQueueHeap::insert(priorityValue element) {
    heap->insert(priorityValueOrder(element.priority, element.value, counter++));
}

/**
 * Deletes and returns element with highest priority
 * @return extracted element if exists
 * @return std::nullopt if element does not exist
 */
std::optional<priorityValue> PriorityQueueHeap::extractMax() {
    std::optional<priorityValueOrder> tmp = heap->extractMax();
    if(tmp == std::nullopt) return std::nullopt;
    else {
        priorityValue extracted (tmp.value().priority, tmp.value().value);
        return extracted;
    }
}

/**
 * Returns element with biggest priority
 * @return returns element if exists
 * @return std::nullopt if element does not exist
 */
std::optional<priorityValue> PriorityQueueHeap::peek() {
    std::optional<priorityValueOrder> tmp = heap->findMax();
    if(tmp == std::nullopt) return std::nullopt;
    else {
        priorityValue peeked (tmp.value().priority, tmp.value().value);
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
int PriorityQueueHeap::modifyKey(priorityValue element, int priority) {
    return heap->modifyKey(element, priority, counter++);
}

void PriorityQueueHeap::display() {
    heap->display();
}

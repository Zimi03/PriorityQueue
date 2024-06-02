#ifndef PRIORITYQUEUE_PRIORITYQUEUELIST_HPP
#define PRIORITYQUEUE_PRIORITYQUEUELIST_HPP

#include "IPriorityQueue.h"
#include "../Structures/List(head).hpp"
#include <iostream>

class PriorityQueueList : public IPriorityQueue, private List_h<PriorityValue> {
private:
    int findMax() const {
        INode* it = head->getNext();
        int maxPriority = std::numeric_limits<int>::min();
        int currPriority = -1;
        int maxIndex = 0;

        for (int i = 0; i < size; ++i) {
            currPriority = dynamic_cast<Node<PriorityValue>*>(it)->getData().priority;
            if (currPriority > maxPriority) {
                maxPriority = currPriority;
                maxIndex = i;
            }
            it = it->getNext();
        }
        return maxIndex;
    }

    int findValue(const PriorityValue& element) const {
        INode* it = head->getNext();
        int i = 0;

        while (it != nullptr) {
            if (dynamic_cast<Node<PriorityValue>*>(it)->getData() == element) {
                return i;
            }
            it = it->getNext();
            ++i;
        }
        return -1;
    }

public:
    PriorityQueueList() : List_h<PriorityValue>() {}

    PriorityQueueList(const PriorityQueueList* to_copy) : List_h<PriorityValue>(*to_copy) {}

    void insert(PriorityValue element) override {
        List_h<PriorityValue>::insertFront(std::move(element));
    }

    std::optional<PriorityValue> extractMax() override {
        int index = findMax();
        return List_h<PriorityValue>::remove(index);
    }

    std::optional<PriorityValue> peek() override {
        int index = findMax();
        return List_h<PriorityValue>::get(index);
    }

    int modifyKey(PriorityValue element, int priority) override {
        if (priority < 0) return 3;

        int index = findValue(element);
        if (index == -1) return 2;

        PriorityValue buf = element;
        buf.priority = priority;

        List_h<PriorityValue>::remove(index);
        List_h<PriorityValue>::insertFront(std::move(buf));

        return 0;
    }

    int getSize() override {
        return size;
    }

    void display() const {
        INode* buf = head->getNext();
        while (buf != nullptr) {
            PriorityValue disp = dynamic_cast<Node<PriorityValue>*>(buf)->getData();
            std::cout << disp << std::endl;
            buf = buf->getNext();
        }
    }
};

#endif // PRIORITYQUEUE_PRIORITYQUEUELIST_HPP

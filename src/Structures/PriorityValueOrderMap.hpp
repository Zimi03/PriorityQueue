//
// Created by grzegorz on 27.05.24.
//

#ifndef PRIORITYQUEUE_PRIORITYVALUEORDERMAP_HPP
#define PRIORITYQUEUE_PRIORITYVALUEORDERMAP_HPP

#include "PriorityValueOrder.hpp"

struct PriorityValueOrderMap: public PriorityValueOrder{
    PriorityValueOrderMap(int priority_, int value, unsigned int count): PriorityValueOrder(priority_, value, count) {}
    PriorityValueOrderMap() : PriorityValueOrder() {};


    // Operator ==
    bool operator==(const struct PriorityValueOrderMap& other) const {
        return priority == other.priority && value == other.value && count == other.count;
    }

    // Operator %
    friend int operator%(const PriorityValueOrderMap& pvo, int mod) {
//        return (pvo.priority) % mod + (pvo.value % mod);
        return int(pvo.priority + pvo.value + pvo.count) % mod;
    }

    // Operator /
    friend int operator/(const PriorityValueOrderMap& pvo, int div) {
//        return int((pvo.priority / div) * (pvo.value / div));
        return int((pvo.priority + pvo.value + pvo.count / div));
    }
};

#endif //PRIORITYQUEUE_PRIORITYVALUEORDERMAP_HPP

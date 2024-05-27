//
// Created by grzegorz on 18.04.24.
//

#pragma once
#include <ostream>

struct PriorityValueOrder {
    int priority;
    int value;
    unsigned int count;

    PriorityValueOrder() {
        priority = 0;
        value = 0;
        count = 0;
    }

    PriorityValueOrder(int priority, int value, unsigned int count): priority(priority), value(value), count(count) {}

    // Operator ==
    bool operator==(const struct PriorityValueOrder& other) const {
        return priority == other.priority && value == other.value;
    }

    // Operator przesunięcia bitowego w prawo (wyjście)
    friend std::ostream& operator<<(std::ostream& os, const PriorityValueOrder& p) {
        os << "P: " << p.priority << ", V: " << p.value << ", C: " << p.count;
        return os;
    }

    // Operator <
    friend bool operator<(const PriorityValueOrder& lhs, const PriorityValueOrder& rhs) {
        // Porównujemy priorytety
        if (lhs.priority != rhs.priority) {
            return lhs.priority < rhs.priority;
        }
        // Jeśli priorytety są równe, porównujemy wartości
        return lhs.count >= rhs.count;
    }
    // Operator <
    friend bool operator>(const PriorityValueOrder& lhs, const PriorityValueOrder& rhs) {
        // Porównujemy priorytety
        if (lhs.priority != rhs.priority) {
            return lhs.priority > rhs.priority;
        }
        // Jeśli priorytety są równe, porównujemy wartości
        return lhs.count <= rhs.count;
    }

    // Operator %
    friend int operator%(const PriorityValueOrder& pvo, int mod) {
//        return (pvo.priority) % mod + (pvo.value % mod);
        return (pvo.priority + pvo.value) % mod;
    }

    // Operator /
    friend int operator/(const PriorityValueOrder& pvo, int div) {
//        return int((pvo.priority / div) * (pvo.value / div));
        return int((pvo.priority + pvo.value / div));
    }
};

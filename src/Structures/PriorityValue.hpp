//
// Created by grzegorz on 16.04.24.
//

#pragma once
#include <ostream>

struct PriorityValue {
    int priority;
    int value;

    PriorityValue() {
        priority = 0;
        value = 0;
    }

    PriorityValue(int priority, int value): priority(priority), value(value) {}

    bool operator==(const PriorityValue& other) const {
        return priority == other.priority && value == other.value;
    }

    // Operator przesunięcia bitowego w prawo (wyjście)
    friend std::ostream& operator<<(std::ostream& os, const PriorityValue& p) {
        os << "P: " << p.priority << ", V: " << p.value;
        return os;
    }
};

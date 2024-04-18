//
// Created by grzegorz on 18.04.24.
//

#ifndef PRIORITYQUEUE_PRIORITYVALUEORDER_H
#define PRIORITYQUEUE_PRIORITYVALUEORDER_H
#include <ostream>
struct priorityValueOrder{
    int priority;
    int value;
    unsigned int count;

    // Operator ==
    bool operator==(const struct priorityValueOrder& other) const {
        return priority == other.priority && value == other.value;
    }

    // Operator przesunięcia bitowego w prawo (wyjście)
    friend std::ostream& operator<<(std::ostream& os, const priorityValueOrder& p) {
        os << "P: " << p.priority << ", V: " << p.value << ", C: " << p.count;
        return os;
    }

    // Operator <
    friend bool operator<(const priorityValueOrder& lhs, const priorityValueOrder& rhs) {
        // Porównujemy priorytety
        if (lhs.priority != rhs.priority) {
            return lhs.priority < rhs.priority;
        }
        // Jeśli priorytety są równe, porównujemy wartości
        return lhs.count >= rhs.count;
    }
    // Operator <
    friend bool operator>(const priorityValueOrder& lhs, const priorityValueOrder& rhs) {
        // Porównujemy priorytety
        if (lhs.priority != rhs.priority) {
            return lhs.priority > rhs.priority;
        }
        // Jeśli priorytety są równe, porównujemy wartości
        return lhs.count <= rhs.count;
    }
};

#endif //PRIORITYQUEUE_PRIORITYVALUEORDER_H

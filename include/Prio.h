//
// Created by grzegorz on 16.04.24.
//

#ifndef PROJEKT2SD_PRIO_H
#define PROJEKT2SD_PRIO_H

struct prio{
    int priority;
    int value;

    bool operator==(const prio& other) const {
        return priority == other.priority && value == other.value;
    }
    // Operator przesunięcia bitowego w prawo (wyjście)
    friend std::ostream& operator<<(std::ostream& os, const prio& p) {
        os << "P: " << p.priority << ", V: " << p.value;
        return os;
    }
};

#endif //PROJEKT2SD_PRIO_H

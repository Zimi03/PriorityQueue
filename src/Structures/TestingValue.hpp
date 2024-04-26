#pragma once

#include "PriorityValue.hpp"
#include "../Tools/Utils.hpp"

struct TestingValue : public PriorityValue {
    int newPriority;

    TestingValue() {
        priority = Utils::generateNumber();
        value = Utils::generateNumber();
        newPriority = Utils::generateNumber();
    }
};

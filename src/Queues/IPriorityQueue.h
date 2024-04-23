//
// Created by grzegorz on 19.04.24.
//

#pragma once

#include <optional>
#include "../Structures/PriorityValue.hpp"

class IPriorityQueue{
public:
    virtual ~IPriorityQueue() {};
    virtual void insert(PriorityValue element) = 0;
    virtual std::optional<PriorityValue> extractMax() = 0;
    virtual std::optional<PriorityValue> peek() = 0;
    virtual int modifyKey(PriorityValue element, int priority) = 0;
};

//
// Created by grzegorz on 19.04.24.
//

#pragma once

#include <optional>
#include "../Structures/PriorityValue.hpp"

class IPriorityQueue{
public:
    virtual ~IPriorityQueue() {};
    /**
     * Inserts element in proper place in queue
     * @param element
     */
    virtual void insert(PriorityValue element) = 0;
    /**
     * Deletes and returns element with highest priority
     * @return extracted element if exists
     * @return std::nullopt if element does not exist
    */
    virtual std::optional<PriorityValue> extractMax() = 0;
    /**
     * Returns element with biggest priority
     * @return returns element if exists
     * @return std::nullopt if element does not exist
     */
    virtual std::optional<PriorityValue> peek() = 0;
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
    virtual int modifyKey(PriorityValue element, int priority) = 0;
    /**
     * Returns number of elements in priority queue
     * @return int - size
     */
    virtual int getSize() = 0;
};

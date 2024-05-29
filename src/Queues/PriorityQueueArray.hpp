//
// Created by zimi03 on 23.04.24.
//

#pragma once

#include "IPriorityQueue.h"
#include "../Structures/DynamicArray.hpp"

class PriorityQueueArray: public IPriorityQueue, private DynamicArray<PriorityValue> {
private:
    int findPriority(PriorityValue element) {
        int temp = element.priority;
        int i = 0;
        while (array[i].priority < temp && i < size) {
            i++;
        }
        return i;
    }

    int findValue(PriorityValue element) {
        int i = 0;
        while (array[i] != element && i < size) {
            i++;
        }
        if(i == size) return -1;
        return i;
    }

public:
    PriorityQueueArray() {
        capacity = 5;
        array = new PriorityValue[capacity];
        size = 0;
    }

    PriorityQueueArray(PriorityQueueArray *to_copy) {
        this->capacity = to_copy->getCapacity();
        this->size = to_copy->getSize();
        this->array = new PriorityValue[this->capacity];
        if (this->size != 0) {
            for (int i = 0; i < size; i++) {
                this->array[i] = to_copy->array[i];
            }
        }
    }

    /**
     * Inserts element in proper place in queue
     * @param element
     */
    void insert(PriorityValue element) override{
        int i = findPriority(element);
        DynamicArray<PriorityValue>::insert(i, element);
    }

    /**
     * Deletes and returns element with highest priority
     * @return extracted element if exists
     * @return std::nullopt if element does not exist
    */
    std::optional<PriorityValue> extractMax() override{
        return DynamicArray<PriorityValue>::removeBack();
    }

    /**
     * Returns element with biggest priority
     * @return returns element if exists
     * @return std::nullopt if element does not exist
     */
    std::optional<PriorityValue> peek() override{
        if(size == 0) return std::nullopt;
        return array[size - 1];
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
    int modifyKey(PriorityValue element, int priority) override{
        int i = findValue(element);
        if (priority < 0) return 3;
        if (element.priority == priority) return 1;
        if (i != -1){
            remove(i);
            PriorityValue buf;
            buf.value = element.value;
            buf.priority = priority;
            int j = findPriority(buf);
            DynamicArray<PriorityValue>::insert(j, buf);
            return 0;
        } else return 2;
    }

    /**
     * Returns number of elements in priority queue
     * @return int - size
     */
    int getSize() override{
        return size;
    }

    /**
     * Displays data in queue
     */
    void display() {
        for(int i = 0; i < size; i++) {
//            std::cout << "Value: " << array[i].value << " Priority: " << array[i].priority << std::endl;
            std::cout << i << ". " << array[i] << std::endl;
        }
    }
};

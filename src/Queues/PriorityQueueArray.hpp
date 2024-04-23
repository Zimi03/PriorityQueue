//
// Created by zimi03 on 23.04.24.
//

#pragma once

#include "IPriorityQueue.h"
#include "../Structures/DynamicArray.hpp"

class PriorityQueueArray: public IPriorityQueue, private DynamicArray<PriorityValue>{
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
        int temp = element.value;
        int i = 0;
        while (array[i].value != temp && i < size) {
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

    void insert(PriorityValue element) {
        int i = findPriority(element);
        DynamicArray<PriorityValue>::insert(i, element);
    }

    std::optional<PriorityValue> extractMax() {
        return DynamicArray<PriorityValue>::removeBack();
    }

    std::optional<PriorityValue> peek() {
        return array[size - 1];
    }

    int modifyKey(PriorityValue element, int priority) {
        int i = findValue(element);
        if (i != -1){
            remove(i);
            PriorityValue buf;
            buf.value = element.value;
            buf.priority = priority;
            int j = findPriority(buf);
            DynamicArray<PriorityValue>::insert(j, buf);
        }
        return i;
    }

    void display() {
        for(int i = 0; i < size; i++) {
            std::cout << "Value: " << array[i].value << " Priority: " << array[i].priority << std::endl;
        }
    }
};

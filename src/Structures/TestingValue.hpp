#pragma once

#include "PriorityValue.hpp"
#include "../Tools/Utils.hpp"

/**
 * Struktura przechowująca dane testowe
 */
struct TestingValue : public PriorityValue {
    int newPriority = 0;

    TestingValue(int size) {
        priority = Utils::generateNumber(size*6);
        value = Utils::generateNumber(size);
    }

    TestingValue() : PriorityValue(){
    }

    TestingValue(PriorityValue* &data, int size){
        int index = Utils::generateNumber(size);
        priority = data[index].priority;
        value = data[index].value;
        newPriority = Utils::generateNumber(size*6);
    }
};

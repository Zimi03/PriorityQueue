#include "PriorityQueueList.h"

PQA::~PQA(){
    DynamicArray::~DynamicArray();
}

PQA::PQA() {
    capacity = 5;
    array = new priorityValue[capacity];
    size = 0;
}
PQA::PQA(PQA *to_copy){
    capacity = to_copy->getCapacity();
    size = to_copy->getSize();
    array = new priorityValue[capacity];
    std::optional<priorityValue> value;
    if(size != 0){
        for (int i = 0; i < size; i++){
            value = to_copy->get(i);
            if(value != std::nullopt){
                insertBack(value.value());
            }
        }
    }
}

int PQA::FindPriority(priorityValue element){
    int temp = element.priority;
    int i = 0;
    while (temp > array[i].priority && i < size){
        i++;
    }
    if(array[i].priority > temp){
        return i;
    }else {
        return i + 1;
    }
}

int PQA::FindValue(priorityValue element) {
    int temp = element.value;
    int i = 0;
    while(array[i].value != temp && i < size){
        i++;
    }
    if(array[i].value != temp && i == size-1){
        return -1;
    }else {
        return i;
    }
}

void PQA::insert(priorityValue element) {
    int i = FindPriority(element);
    DynamicArray<priorityValue>::insert(i, element);
}

std::optional<priorityValue> PQA::extractMax() {
    DynamicArray<priorityValue>::removeBack();
}

int PQA::modifyKey(priorityValue element, int priority) {
    int i = FindValue(element);
    if(i != -1){
        remove(i);
        priorityValue buf;
        buf.value = element.value;
        buf.priority = priority;
        int j = FindPriority(buf);
        DynamicArray<priorityValue>::insert(j, buf);
    }
}

std::optional<priorityValue> PQA::peek() {
    return array[size - 1];
}

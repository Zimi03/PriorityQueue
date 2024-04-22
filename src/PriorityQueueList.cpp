#include "PriorityQueueList.h"

PQA::~PQA(){
    DynamicArray::~DynamicArray();
}

PQA::PQA() {

}
PQA::PQA(PQA *to_copy){

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

}

std::optional<priorityValue> PQA::peek() {
    return array[size - 1];
}

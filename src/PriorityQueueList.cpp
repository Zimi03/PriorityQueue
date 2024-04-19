#include "PriorityQueueList.h"

PQL::~PQL(){
    delete list;
}

PQL::PQL(){
    list = new List_h_t<priorityValue>;
    size = list->getSize();
}

PQL::PQL(PQL *to_copy) {
    list = to_copy->list;
    size = to_copy->list->getSize();
}

int PQL::findindex(priorityValue element){
    int temp = element.priority;
    int i = 0;
    while (temp < list->get(i)->priority){
        i++;
    }
    return i;
}

int PQL::insert(priorityValue element) {
    int i = findindex(element);
    list->insert(i, element);
}

std::optional<priorityValue> PQL::extractMax() {
    list->removeFront();
}

int PQL::modifyKey(priorityValue element, int priority) {

}

std::optional<priorityValue> PQL::peek() {

}

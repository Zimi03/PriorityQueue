#include "PriorityQueueList.h"

PQL::~PQL(){
    List_h_t::~List_h_t();
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
    INode* current = head->getNext(); // piszesz reszte tak jakby to była funkcja w list_h_t tylko musisz znaleźć odpowiednio element

    int temp = element.priority;
    int i = 0;
    while (temp < list->get(i)->priority){
        i++;
    }
    return i;
}

int PQL::insert(priorityValue element) {
    int i = find(element);
    List_h_t<priorityValue>::insert(i, element);
}

std::optional<priorityValue> PQL::extractMax() {
    list->removeFront();
}

int PQL::modifyKey(priorityValue element, int priority) {

}

std::optional<priorityValue> PQL::peek() {

}

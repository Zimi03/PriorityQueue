//
// Created by grzegorz on 18.04.24.
//

#include "BinaryHeap.h"


BinaryHeap::BinaryHeap() {
    heap = new DynamicArray<priorityValueOrder>;
    size = heap->getSize();
}

BinaryHeap::BinaryHeap(BinaryHeap *to_copy) {
    build(to_copy->heap);
}

BinaryHeap::~BinaryHeap(){
    delete heap;
}

int BinaryHeap::build(DynamicArray<priorityValueOrder>* to_copy) {
    clear();
    heap = new DynamicArray<priorityValueOrder>(to_copy);
    size = heap->getSize();
    for(int i = size/2-1; i>= 0; i--) { // zaczynam od ostatniego rodzica
        downHeap(0, size-1, i);
    }
    return 0;
}

/**
 * Clears heap
 * @return 0 - cleared and allocated empty heap
 * @return 1 - no heap allocated in structure
 */
int BinaryHeap::clear() {
    if(heap != nullptr){
        delete heap;
        heap = new DynamicArray<priorityValueOrder>;
        return 0;
    } else return 1;
}


int BinaryHeap::downHeap(int start, int end, int parent) {
    int largest = parent;
    int left = start + 2 * (parent - start) + 1;
    int right = start + 2 * (parent - start) + 2;
//    priorityValueOrder largestValue = heap->get(largest)->value; // odczytanie wartosci rodzica
//    priorityValueOrder
    // szukamy dziecka większego od rodzica
    if (left <= end && heap->get(left).value() > heap->get(largest).value()) {
        largest = left;
    }
    if (right <= end && heap->get(right).value() > heap->get(largest).value()) {
        largest = right;
    }
    if (largest != parent) {
        heap->swap(parent, largest); // większe dziecko zamieniane z rodzicem
        downHeap(start, end, largest); // kontynuujemy z pozycji gdzie było to większe dziecko
        return 1;
    } else return 0; // warunek wyjścia - rodzic większy/równy od dzieci

}

int BinaryHeap::upHeap(int start, int end, int child) {
    if(child == 0) return 0;
    int parent = (child-1)/2;

    if(heap->get(child).value() > heap->get(parent).value()){
        heap->swap(child, parent);
        upHeap(start, end, parent);
    }
    return 0;
}


void BinaryHeap::insert(priorityValueOrder element) {
    heap->insertBack(element);
    size = heap->getSize();
    upHeap(0, size-1, size-1); // upHeap od wstawionego elementu
}

/**
 * Deletes and returns element with highest priority
 * @return extracted element if exists
 * @return std::nullopt if element does not exist
 */
std::optional<priorityValueOrder> BinaryHeap::extractMax() {
    heap->swap(0, size-1); // zamiana pierwszego z ostatnim elementem
    std::optional<priorityValueOrder> tmp = heap->removeBack();
    if(tmp == std::nullopt) return std::nullopt;
    else{
        size = heap->getSize();
        downHeap(0, size - 1, 0); // downHeap od korzenia
        return tmp.value();
    }

}

/**
 * Returns element with biggest priority
 * @return returns element if exists
 * @return std::nullopt if element does not exist
 */
std::optional<priorityValueOrder> BinaryHeap::findMax() {
    std::optional<priorityValueOrder> tmp = heap->get(0);
    if(tmp == std::nullopt) return std::nullopt;
    else return tmp.value();
}


//std::optional<priorityValueOrder> BinaryHeap::find(priorityValueOrder element) {
//
//}

/**
 * Removes one element with given priority and value
 * @param element
 * @return 0 - removed
 * @return 1 - no such element
 */
int BinaryHeap::remove(priorityValue element) {
    priorityValueOrder tmp (element.priority, element.value, 0); // znacznik count nie ma wpływu na operacje ==
    int index = heap->find(tmp); // znalezienie miejsca w tablicy do usunięcia
    if(index < 0) return 1;
    else {
        heap->swap(index, size -1); // zamiana znalezionego elementu z ostatnim elementem
        heap->removeBack(); // usunięcie
        size = heap->getSize();
        downHeap(index, size-1,index); // naprawienie warunków kopca
        return 0;
    }
}



/**
 * Modifies key of element with given current key and value
 * It also changes count to new value
 * @param element
 * @param priority
 * @param count
 * @return 0 - success
 * @return 1 - the same priority
 * @return 2 - no such element
 * @return 3 - priority less than zero
 */
int BinaryHeap::modifyKey(priorityValue element, int priority, unsigned int count) {
    if(element.priority == priority) return 1; // jeśli ten sam priorytet
    if(priority < 0) return 3;

    priorityValueOrder old (element.priority, element.value, 0); // znacznik count nie ma wpływu na operacje ==
    int index = heap->find(old); // znalezienie miejsca w tablicy do zmiany

    if(index < 0) return 2;
    else {
        priorityValueOrder curr (priority, element.value, count); // nadanie nowego priorytetu i znacznika count
        heap->change(index, curr); // zaktualizowanie elementu
        if (old.priority > priority) downHeap(index, size -1, index); // naprawienie warunków kopca
        else upHeap(0, index, index); // naprawienie warunków kopca
        return 0;
    }
}
/**
 * Increase key of element with given current key and value by one
 * It also changes count to new value
 * @param element
 * @param count
 * @return 0 - success
 * @return 2 - no such element
 */
int BinaryHeap::increaseKey(priorityValue element, unsigned int count) {
    return modifyKey(element, element.priority + 1, count);
}

/**
 * Decrease key of element with given current key and value by one
 * It also changes count to new value
 * @param element
 * @param count
 * @return 0 - success
 * @return 2 - no such element
 * @return 3 - cannot decrease - priority already is minimum
 */
int BinaryHeap::decreaseKey(priorityValue element, unsigned int count) {
    return modifyKey(element, element.priority - 1, count);
}

/**
 * Returns size of binary heap
 * @return int - size
 */
int BinaryHeap::getSize() {
    return size;
}

void BinaryHeap::display(){
//    std::cout << "Level: " << 0 << std::endl;
//    std::cout << heap->get(0).value() << ", "<< std::endl;

    for(int i = 0, j = 0; i < size; i = i*2+1, j ++){
        std::cout << "Level: " << j << std::endl;
        for(int k = i; k <= 2*i && k < size; k++){
            std::cout << heap->get(k).value() << ", "<< std::endl;
        }
    }
    std::cout << std::endl;
}
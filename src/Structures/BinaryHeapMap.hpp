//
// Created by grzegorz on 18.04.24.
//

#pragma once

#include "DynamicArray.hpp"
#include "PriorityValue.hpp"
#include "PriorityValueOrderMap.hpp"
#include "CuckooHashTable.hpp"


class BinaryHeapMap {
    DynamicArray<PriorityValueOrderMap>* array = nullptr;
    CuckooHashTable<PriorityValueOrderMap, int>* map_index; // mapa priorityValueOrder na indeks w binary heap
    CuckooHashTable<PriorityValue, DynamicArray<unsigned int>*>* map_count; // mapa priorityValue (bez count) na tablice count

    int size = 0;

    void swap(int a, int b){
        if(!array->swap(a, b)) {
            Pair<PriorityValueOrderMap, int>* para1 = map_index->search(array->get(a).value());
            Pair<PriorityValueOrderMap, int>* para2 = map_index->search(array->get(b).value());
            para1->value = a;
            para2->value = b;
        }
    }

    int build(DynamicArray<PriorityValueOrderMap>* to_copy) {
        clear();
        array = new DynamicArray<PriorityValueOrderMap>(to_copy);
        map_index = new CuckooHashTable<PriorityValueOrderMap, int>;
        map_count = new CuckooHashTable<PriorityValue, DynamicArray<unsigned int>*>;

        size = array->getSize();
        for(int i = 0; i < size; i ++){
            PriorityValueOrderMap pvom = array->get(i).value();
            map_index->insert(pvom, i);

            Pair<PriorityValue, DynamicArray<unsigned int>*>* para = map_count->search(PriorityValue(pvom.priority, pvom.value));
            if(para != nullptr){ // jeśli jest klucz w mapie
                para->value->insertBack(pvom.count);
            } else{ // jeśli nie ma klucza w mapie
                DynamicArray<unsigned int>* tmp = new DynamicArray<unsigned int>;
                tmp->insertBack(pvom.count);
                map_count->insert(PriorityValue(pvom.priority, pvom.value), tmp);
            }

        }
        for(int i = size/2-1; i>= 0; i--) { // zaczynam od ostatniego rodzica
            downHeap(0, size-1, i);
        }
        return 0;
    }

    int downHeap(int start, int end, int parent) {
        int largest = parent;
        int left = start + 2 * (parent - start) + 1;
        int right = start + 2 * (parent - start) + 2;
        // PriorityValueOrder largestValue = heap->get(largest)->value; // odczytanie wartosci rodzica
        // PriorityValueOrder
        // szukamy dziecka większego od rodzica
        if (left <= end && array->get(left).value() > array->get(largest).value()) {
            largest = left;
        }
        if (right <= end && array->get(right).value() > array->get(largest).value()) {
            largest = right;
        }
        if (largest != parent) {
            swap(parent, largest); // większe dziecko zamieniane z rodzicem
            downHeap(start, end, largest); // kontynuujemy z pozycji gdzie było to większe dziecko
            return 1;
        } else return 0; // warunek wyjścia - rodzic większy/równy od dzieci
    }

    int upHeap(int start, int end, int child) {
        if (child == 0) return 0;
        int parent = (child-1)/2;

        if(array->get(child).value() > array->get(parent).value()){
            swap(child, parent);
            upHeap(start, end, parent);
        }
        return 0;
    }

    /**
     * Clears heap
     * @return 0 - cleared and allocated empty heap
     * @return 1 - no heap allocated in structure
     */
    int clear() {
        if (array != nullptr) {
            delete array;
            array = new DynamicArray<PriorityValueOrderMap>;
            delete map_index;
            map_index = new CuckooHashTable<PriorityValueOrderMap, int>;
            return 0;
        } else return 1;
    }

    /**
     *
     * @param element
     * @return index - if found
     * @return -1 - if not found
     */
    int find(PriorityValue element){
        Pair<PriorityValue, DynamicArray<unsigned int >*>* pv = map_count->search(element);

        if(pv != nullptr && !pv->value->isEmpty()) { // jeśli jest klucz w mapie  i tablica nie jest pusta to znajdź w tablicy (wartości) count
            unsigned int count = pv->value->get(0).value(); // pierwszy count z tablicy

            auto para = map_index->search(PriorityValueOrderMap(element.priority, element.value, count));
            if (para != nullptr) {
                return para->value; // Zwracamy indeks elementu
            } else {
                return -1; // Element nie został znaleziony
            }

        } else return -1;


    }

public:
    BinaryHeapMap() {
        array = new DynamicArray<PriorityValueOrderMap>;
        map_index = new CuckooHashTable<PriorityValueOrderMap, int>;
        map_count = new CuckooHashTable<PriorityValue, DynamicArray<unsigned int>*>;
        size = array->getSize();
    }

    BinaryHeapMap(BinaryHeapMap *to_copy) {
        build(to_copy->array);
    }

    ~BinaryHeapMap(){
        delete array;
        delete map_index;
        delete map_count;
    }

    void insert(PriorityValueOrderMap element) {
        array->insertBack(element);
        map_index->insert(element, size);
        Pair<PriorityValue, DynamicArray<unsigned int>*>* para = map_count->search(PriorityValue(element.priority, element.value));
        if(para != nullptr){ // jeśli jest klucz w mapie
            para->value->insertBack(element.count); // dodanie do odpowiedniego wpisu w map_count kolejnej wartości count
        } else{ // jeśli nie ma klucza w mapie
            DynamicArray<unsigned int>* tmp = new DynamicArray<unsigned int>;
            tmp->insertBack(element.count);
            map_count->insert(PriorityValue(element.priority, element.value), tmp);
        }
        size = array->getSize();
        upHeap(0, size-1, size-1); // upHeap od wstawionego elementu
    }

    /**
     * Deletes and returns element with highest priority
     * @return extracted element if exists
     * @return std::nullopt if element does not exist
     */
    std::optional<PriorityValueOrder> extractMax() {
        swap(0, size-1); // zamiana pierwszego z ostatnim elementem
        std::optional<PriorityValueOrderMap> tmp = array->removeBack();
        if (tmp == std::nullopt) {
            return std::nullopt;
        } else {
            size = array->getSize();
            downHeap(0, size - 1, 0); // downHeap od korzenia
            map_index->remove(tmp.value());

            Pair<PriorityValue, DynamicArray<unsigned int>*>* para = map_count->search(PriorityValue(tmp.value().priority, tmp.value().value));
            if(para != nullptr) { // jeśli jest klucz w mapie to usuń z tablicy (wartości) count
                int size_para_array = para->value->getSize();
                if(size_para_array == 1) {
                    map_count->remove(PriorityValue(tmp.value().priority, tmp.value().value));

                } else{
                    para->value->removeFront();
                }
//                for (int i = 0; i < size_para_array; i++) {
//                    if (para->value->get(i) == tmp.value().count) {
//                        para->value->remove(i);
//                    }
//                }
//                if(para->value->isEmpty()){ // jeśli tablica jest pusta to usuń cąły wpis z mapy
//                    map_count->remove(PriorityValue(tmp.value().priority, tmp.value().value));
//                }
            }
            return tmp.value();
        }
    }

    /**
     * Returns element with biggest priority
     * @return returns element if exists
     * @return std::nullopt if element does not exist
     */
    std::optional<PriorityValueOrder> findMax() {
        std::optional<PriorityValueOrder> tmp = array->get(0);
        if (tmp == std::nullopt) return std::nullopt;
        else return tmp.value();
    }

    // std::optional<PriorityValueOrder> find(PriorityValueOrder element);

    /**
     * Removes one element with given priority and value
     * @param element
     * @return 0 - removed
     * @return 1 - no such element
     */
    int remove(PriorityValue element) {
//        PriorityValueOrderMap tmp(element.priority, element.value, 0); // znacznik counter nie ma wpływu na operacje ==
        int index = find(element); // znalezienie miejsca w tablicy do usunięcia
        if (index < 0) {
            return 1;
        } else {
            swap(index, size -1); // zamiana znalezionego elementu z ostatnim elementem
            std::optional<PriorityValueOrderMap> tmp = array->removeBack(); // usunięcie
            map_index->remove(tmp.value());
            map_count->remove(element);
            size = array->getSize();
            downHeap(index, size-1,index); // naprawienie warunków kopca
            return 0;
        }
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
    int modifyKey(PriorityValue element, int priority, unsigned int count) {

        if (element.priority == priority) return 1; // jeśli ten sam priorytet
        if (priority < 0) return 3;

        int index = find(element);
        if (index < 0) return 2;
        else {
            // zmiana wartości count w mapie count
            Pair<PriorityValue, DynamicArray<unsigned int>*>* old_pair = map_count->search(element); // element do zmiany
            PriorityValueOrderMap old(element.priority, element.value, old_pair->value->get(0).value()); // stary element przed modyfikacją
            if(old_pair->value->getSize()==1){
                map_count->remove(element); // usuwamy wpis w mapie jeśli jest tam tylko jeden element
            } else{
                old_pair->value->removeFront(); // usuwamy pierwszy element jeśli w tablic jest więcej
            }
            Pair<PriorityValue, DynamicArray<unsigned int>*>* new_pair = map_count->search(PriorityValue(priority, element.value)); // element do zmiany

            if(new_pair != nullptr){ // jeśli jest klucz w mapie
                new_pair->value->insertBack(count);
            } else{ // jeśli nie ma klucza w mapie
                DynamicArray<unsigned int>* tmp = new DynamicArray<unsigned int>;
                tmp->insertBack(count);
                map_count->insert(PriorityValue(priority, element.value), tmp);
            }

            // zmiana wartości w mapie indeksów
            PriorityValueOrderMap curr(priority, element.value, count); // nadanie nowego priorytetu i znacznika counter
            map_index->remove(old);
            map_index->insert(curr, index);

            // zaktualizowanie elementu w kopcu
            array->change(index, curr);

            // naprawa kopca
            if (element.priority > priority) downHeap(index, size -1, index); // naprawienie warunków kopca
            else upHeap(0, index, index); // naprawienie warunków kopca
            return 0;
        }
    }

    /**
     * Increase key of element with given current key and value by one
     * It also changes counter to new value
     * @param element
     * @param count
     * @return 0 - success
     * @return 2 - no such element
     */
    int increaseKey(PriorityValue element, unsigned int count) {
        return modifyKey(element, element.priority + 1, count);
    }

    /**
     * Decrease key of element with given current key and value by one
     * It also changes counter to new value
     * @param element
     * @param count
     * @return 0 - success
     * @return 2 - no such element
     * @return 3 - cannot decrease - priority already is minimum
     */
    int decreaseKey(PriorityValue element, unsigned int count) {
        return modifyKey(element, element.priority - 1, count);
    }

    int getSize() {
        return size;
    }

    void display() {
        //    std::cout << "Level: " << 0 << std::endl;
        //    std::cout << heap->get(0).value() << ", "<< std::endl;
        for (int i = 0, j = 0; i < size; i = i*2+1, j ++) {
            std::cout << "Level: " << j << std::endl;
            for(int k = i; k <= 2*i && k < size; k++){
                std::cout << array->get(k).value() << ", "<< std::endl;
            }
        }
        std::cout << std::endl;
        std::cout << "Mapa indeksow: " << std::endl;
        map_index->display();
        std::cout << "Mapa count: " << std::endl;
        map_count->display();
        std::cout << std::endl;

    }
};


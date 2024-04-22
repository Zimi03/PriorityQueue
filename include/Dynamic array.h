#ifndef LISTY_DYNAMIC_ARRAY_H
#define LISTY_DYNAMIC_ARRAY_H

#include <cstring>
#include "iostream"
#include "optional"
#include "PriorityValue.h"
#include "PriorityValueOrder.h"

template <typename Data>
class DynamicArray {
protected:
    Data *array = nullptr;
    int size;
    int capacity;
public:
    DynamicArray();
    explicit DynamicArray(DynamicArray *to_copy);
    int getSize() ;
    int isEmpty() ;
    int swap(int a, int b);
    int change(int index, Data &new_value);

    int find(Data value) ;
    std::optional<Data> get(int index) ;
    void init(Data data) ;

    void insertFront(Data data) ;
    int insert(int index, Data data) ;
    void insertBack(Data data) ;

    std::optional<Data>removeFront() ;
    std::optional<Data> remove(int index) ;
    std::optional<Data>removeBack();
    void grow();
    void shrink();
    ~DynamicArray() ;
};

#endif //LISTY_DYNAMIC_ARRAY_H

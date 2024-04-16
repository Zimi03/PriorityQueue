#include "Dynamic array.h"
#include "optional"

//basic constructor
template <typename Data>
DynamicArray<Data>::DynamicArray(){
    capacity = 5;
    array = new Data [capacity];
    size = 0;
}

template <typename Data>
DynamicArray<Data>::DynamicArray(DynamicArray *to_copy): size(0), capacity(5) {
    std::optional<Data> value;
    int _size = to_copy->getSize();
    array = new Data [_size];
    if(_size != 0){
        for (int i = 0; i < _size; i++){
            value = to_copy->get(i);
            if(value != std::nullopt){
                insertBack(value.value());
            }
        }
    }
}
//destructor
template <typename Data>
DynamicArray<Data>::~DynamicArray(){
    delete[] array;
}

template <typename Data>
int DynamicArray<Data>::getSize() {return size; } //size getter

template <typename Data>
int DynamicArray<Data>::isEmpty() {
    if (size == 0) return 1;
    else return 0;
}

template <typename Data>
int DynamicArray<Data>::find(Data value){
    for (int i = 0; i < size; i++){
        if(array[i] == value){ //checking if value exists at current index
            return i; // returning index of wanted value
        }
    }
    return -1; // returning -1 if value doesn't exist in array
}

template <typename Data>
std::optional<Data> DynamicArray<Data>::get(int index) {
    if(index >= 0 && index < size) {
        return array[index];
    }else return std::nullopt;
}

/**
 * Init DynamicArray with insertBack - it is necessary for fast initzialization of data structure
 */
template <typename Data>
void DynamicArray<Data>::init(Data data){
    insertBack(data);
}

template <typename Data>
void DynamicArray<Data>::insertFront(Data data){
    if (size == capacity) {
        grow(); // growing array if needed
    }
   for (int i = size - 1; i >= 0; i--) {
        array[i + 1] = array[i]; //copying values to next index
   }

    array[0] = data; // inserting new value at given index
    size ++; // growing size of array
}

template <typename Data>
int DynamicArray<Data>::insert(int index, Data data) {
    if (index == 0 ) {
        insertFront(data);
        return 0;
    }else if(size == index){
        insertBack(data);
        return 0;
    }
    if (index>=0 && index <=size) {
        if (size == capacity) {
            grow(); // growing array if needed
        }
        for (int i = size - 1; i >= index; i--) {
            array[i + 1] = array[i]; //copying values to next index
        }

        array[index] = data; // inserting new value at given index
        size++; // growing size of array
        return 0;
    }
    return 1;
}

template <typename Data>
void DynamicArray<Data>::insertBack(Data data){
    if(size == capacity) grow(); // growing array if needed
    array[size] = data; //inserting value at end
    size++; // growing size of array
}

template <typename Data>
std::optional<Data> DynamicArray<Data>::removeFront() {
    if(size != 0) {
        Data data = array[0];
        for (int i = 0; i < size; i++) {
            array[i] = array[i + 1]; // pushing elements back to fill the gap
        }
        size--; // decreasing size of array
        if(size < (capacity/2)) shrink(); // shrinking array if needed
        return data;
    }else
        return std::nullopt;
}


template <typename Data>
std::optional<Data> DynamicArray<Data>::remove(int index){

    if(index < 0 && index >= size) return std::nullopt;
    if(index == 0) return removeFront();
    Data data = array[index];
        for (int i = index; i < size; i++) {
            array[i] = array[i + 1]; // pushing elements back to fill the gap
        }

        size--; // decreasing size of array
        if(size < (capacity/2)) shrink(); // shrinking array if needed
        return data;
}

template <typename Data>
std::optional<Data> DynamicArray<Data> ::removeBack(){
    if(size == 0) return std::nullopt;
    return remove(size-1);
}

template <typename Data>
void DynamicArray<Data> ::grow() {
    capacity *= 2; // doubling capacity of array
    Data *temp = new Data[capacity]; // creating temp array
    for( int i =0; i< size; i++){
        temp[i] = array[i]; //copying values to temp array
    }
    delete[] array; // dellocating memory of old array
    array = temp; //copying temp array to new array
}

template <typename Data>
void DynamicArray<Data> ::shrink() {
    capacity = size;
    Data *temp = new Data[capacity];
    for (int i = 0; i < size; i++){
        temp[i] = array[i];
    }
    delete[] array;
    array = temp;
}

template class DynamicArray<int>;
template class DynamicArray<prio>;
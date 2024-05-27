#pragma once

#include <cstring>
#include <iostream>
#include <optional>
#include "PriorityValue.hpp"
#include "PriorityValueOrder.hpp"


template <typename T>
class DynamicArray {
protected:
    T *array = nullptr;
    int size = 0;
    int capacity = 5;

public:
    DynamicArray() {
        capacity = 5;
        array = new T[capacity];
        size = 0;
    }

    DynamicArray(int capacity_) {
        capacity = capacity_;
        array = new T[capacity];
        size = 0;
    }


    DynamicArray(DynamicArray *to_copy): size(0), capacity(5) {
        std::optional<T> value;
        int _size = to_copy->getSize();
        array = new T[_size];
        if (_size != 0) {
            for (int i = 0; i < _size; i++) {
                value = to_copy->get(i);
                if (value != std::nullopt) {
                    insertBack(value.value());
                }
            }
        }
    }

    ~DynamicArray() {
        delete[] array;
    }


//    DynamicArray(DynamicArray *to_copy): size(0), capacity(5) {
//        int _size = to_copy->getSize();
//        array = new T[_size];
//        if (_size != 0) {
//            for (int i = 0; i < _size; i++) {
//                std::optional<T> value = to_copy->get(i);
//                if (value != std::nullopt) {
//                    if constexpr (std::is_pointer<T>::value) {
//                        // Tworzymy nowy wskaźnik na podstawie kopiowanego wskaźnika
////                        array[i] = new T (value.value());
//                        array[i] = new std::remove_pointer_t<T>(*value.value());
//                    } else {
//                        array[i] = value.value();
//                    }
//                }
//            }
//            size = _size;
//        }
//    }
//
//    ~DynamicArray() {
//        if (array != nullptr) {
//            if constexpr (std::is_pointer<T>::value) {
//                for (int i = 0; i < size; ++i) {
//                    delete array[i];
//                }
//            }
//        }
//        delete[] array;
//
////
////        if (array != nullptr) {
////            // Sprawdzamy, czy Data jest wskaźnikiem do pojedynczego obiektu
////            if constexpr (std::is_pointer<T>::value && !std::is_array<T>::value) {
////                for (int i = 0; i < size; ++i) {
////                    delete array[i]; // Zwolnienie pamięci dla każdego elementu tablicy
////                }
////            }
////                // Sprawdzamy, czy Data jest wskaźnikiem do tablicy
////            else if constexpr (std::is_pointer<T>::value && std::is_array<std::remove_pointer_t<T>>::value) {
////                for (int i = 0; i < size; ++i) {
////                    if(array[i]!= nullptr)
////                        delete[] array[i]; // Zwolnienie pamięci dla każdej dynamicznej tablicy
////                }
////                delete[] array; // Zwolnienie pamięci dla tablicy
////            } else {
//////                delete[] array; // Zwolnienie pamięci dla tablicy
////            }
////        }
//    }
    /**
     * Returns number of elements in data structure
     * @return size
     */
    int getSize() {
        return size;
    }

    /**
     * Function chcecks if data structure is empty
     * @return 0 - not empty
     * @return 1 - empty
     */
    bool isEmpty() {
        return size == 0;
    }

    int getCapacity() {
        return capacity;
    }

    int swap(int a, int b) {
        if(a >= 0 && a < size && b >= 0 && b < size && a != b) {
            T tmp = array[a];
            array[a] = array[b];
            array[b] = tmp;
            return 0;
        } else return 1;
    }

    /**
     * Chnages element on given index.
     * @return 0 - succes
     * @return 1 - failure
     */
    int change(int index, T &new_value) {
        if(index >= 0 && index < size){
            array[index] = new_value;
            return 0;
        } return 1;
    }

    /**
     * Searches for given data and returns index
     * @param data
     * @return -1 - not found
     * @return >0 - found index
     */
    int find(T value){
        for (int i = 0; i < size; i++) {
            if (array[i] == value) {
                return i;
            }
        }
        return -1;
    }

    /**
     * Returns data on given index
     * @param index
     * @return data - if index ok
     * @return std::nullopt - if index wrong
     */
    std::optional<T> get(int index) {
        if(index >= 0 && index < size) {
            return std::make_optional(array[index]);
        } else return std::nullopt;
    }

    /**
     * Init data structure - it is necessary for fast initzialization of data structure
     */
    void init(T data) {
        insertBack(data);
    }

    /**
     * Inserts element on front
     * @param data
     */
    void insertFront(T data) {
        if (size == capacity) {
            grow();
        }
        for (int i = size - 1; i >= 0; i--) {
            array[i + 1] = array[i];
        }

        array[0] = data;
        size ++;
    }

    /**
     * Inserts element on given index if possible
     * @param data
     * @param index
     * @return 0 - success
     * @return 1 - fail
     */
    int insert(int index, T data) {
        if (index == 0) {
            insertFront(data);
            return 0;
        } else if (size == index) {
            insertBack(data);
            return 0;
        }
        if (index >= 0 && index <= size) {
            if (size == capacity) {
                grow();
            }
            for (int i = size - 1; i >= index; i--) {
                array[i + 1] = array[i];
            }

            array[index] = data;
            size++;
            return 0;
        }
        return 1;
    }

    /**
     * Inserts element to the end of data structure
     * @param data
     */
    void insertBack(T data){
        if (size == capacity) grow();
        array[size] = data;
        size++;
    }

    /**
     * Removes first element from data structure
     * @return data from removed element - if index ok
     * @return std::nullopt - if empty
     */
    std::optional<T> removeFront() {
        if (size != 0) {
            T data = array[0];
            for (int i = 0; i < size; i++) {
                array[i] = array[i + 1];
            }
            size--;
            if (size < (capacity/2)) shrink();
            return std::make_optional(data);
        } else return std::nullopt;
    }

    /**
     * Removes element from the given index from data structure
     * @return data from removed element - if index ok
     * @return std::nullopt - if wrong index
     */
    std::optional<T> remove(int index) {
        if (index < 0 && index >= size) return std::nullopt;
        if (index == 0) return removeFront();
        T data = array[index];
        for (int i = index; i < size; i++) {
            array[i] = array[i + 1];
        }
        size--;
        if(size < (capacity/2)) shrink();
        return std::make_optional(data);
    }

    /**
     * Removes element from the end of data structure
     * @return data from removed element - if index ok
     * @return std::nullopt - if empty
     */
    std::optional<T> removeBack() {
        if (size == 0) return std::nullopt;
        return remove(size-1);
    }

    void grow() {
        capacity *= 2; // doubling capacity of array
        T *temp = new T[capacity]; // creating temp array
        for( int i =0; i< size; i++){
            temp[i] = array[i]; //copying values to temp array
        }
//        if (array != nullptr) {
//            // Sprawdzamy, czy Data jest wskaźnikiem do pojedynczego obiektu
//            if constexpr (std::is_pointer<T>::value && !std::is_array<T>::value) {
//                for (int i = 0; i < size; ++i) {
//                    delete array[i]; // Zwolnienie pamięci dla każdego elementu tablicy
//                }
//            }
//                // Sprawdzamy, czy Data jest wskaźnikiem do tablicy
//            else if constexpr (std::is_pointer<T>::value && std::is_array<std::remove_pointer_t<T>>::value) {
//                for (int i = 0; i < size; ++i) {
//                    if (array[i] != nullptr)
//                        delete[] array[i]; // Zwolnienie pamięci dla każdej dynamicznej tablicy
//                }
//                delete[] array; // Zwolnienie pamięci dla tablicy
//            }
//        }
        delete[] array; // dellocating memory of old array
        array = temp; //copying temp array to new array
    }

    void shrink() {
        if(capacity <= 5) return;
        capacity = size;
        T *temp = new T[capacity];
        for (int i = 0; i < size; i++) {
            temp[i] = array[i];
        }
//        if (array != nullptr) {
//            // Sprawdzamy, czy Data jest wskaźnikiem do pojedynczego obiektu
//            if constexpr (std::is_pointer<T>::value && !std::is_array<T>::value) {
//                for (int i = 0; i < size; ++i) {
//                    delete array[i]; // Zwolnienie pamięci dla każdego elementu tablicy
//                }
//            }
//                // Sprawdzamy, czy Data jest wskaźnikiem do tablicy
//            else if constexpr (std::is_pointer<T>::value && std::is_array<std::remove_pointer_t<T>>::value) {
//                for (int i = 0; i < size; ++i) {
//                    if (array[i] != nullptr)
//                        delete[] array[i]; // Zwolnienie pamięci dla każdej dynamicznej tablicy
//                }
//                delete[] array; // Zwolnienie pamięci dla tablicy
//            }
//        }
        delete[] array;
        array = temp;
    }

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& da) {
        os << "[";
        for (int i = 0; i < da.size; ++i) {
            if constexpr (std::is_pointer<T>::value) {
                if (da.array[i] != nullptr) {
                    os << *da.array[i];
                } else {
                    os << "null";
                }
            } else {
                os << da.array[i];
            }
            if (i != da.size - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }


    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>* array_ptr) {
        if (array_ptr != nullptr) {

            os << "[";
            for (int i = 0; i < array_ptr->size; ++i) {
                if constexpr (std::is_pointer<T>::value) {
                    if (array_ptr->array[i] != nullptr) {
                        os << *array_ptr->array[i];
                    } else {
                        os << "null";
                    }
                } else {
                    os << array_ptr->array[i];
                }
                if (i != array_ptr->size - 1) {
                    os << ", ";
                }
            }

            os << "]";
        } else {
            os << "null";
        }

        return os;
    }
};

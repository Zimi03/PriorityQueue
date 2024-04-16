//
// Created by grzegorz on 22.03.24.
//

#include "List(head).h"

template <typename Data>
inline List_h<Data>::List_h() : size(0) {
    head = new Head();
}

template <typename Data>
inline List_h<Data>::List_h(List_h<Data> *to_copy) : size(0) {
    head = new Head();
    std::optional<Data> value;
    int _size = to_copy->getSize();

    if (_size != 0) {
        for (int i = 0; i < _size; i++) {
            value = to_copy->get(i);
            if(value!=std::nullopt){
                insertBack(value.value());
            }
        }
    }
}
template <typename Data>
inline List_h<Data>::~List_h() {
    clear();
    delete head;
}

/**
 * Function chcecks if list is empty
 * @return 0 - not empty
 * @return 1 - empty
 */
template <typename Data>
inline int List_h<Data>::isEmpty() {
    if(head->getNext() == nullptr) {
        return 1;
    } else return 0;
}

/**
 * Returns number of elements in list
 * @return size
 */
template <typename Data>
inline int List_h<Data>::getSize() {
    return size;
}

/**
 * Removes all elements of the list except for the head element, which points to nullptr.
 */
template <typename Data>
inline void List_h<Data>::clear() {
    INode* current = head->getNext(); // jesli head wskazuje na nullptr - brak elementów
    INode* next = nullptr;

    while (current != nullptr){
        next = current->getNext();
        delete current;
        current = next;
    }

    head->setNext(nullptr);
    size = 0;
}

/**
 * Init list(head) with insertFront - it is necessary for fast initzialization of data structure
 */
template <typename Data>
inline void List_h<Data>::init(Data data){
    insertFront(data);
}

/**
 * Inserts element on front
 * @param data
 */
template <typename Data>
inline void List_h<Data>::insertFront(Data data) {
    INode* buf = new Node<Data>(head->getNext(), data);
    head->setNext(buf);
    size++;
}

/**
 * Inserts element on given index if possible
 * @param data
 * @param index
 * @return 0 - success
 * @return 1 - fail
 */
template <typename Data>
inline int List_h<Data>::insert(int index, Data data) {
    if(index == 0) {
        insertFront(data);
        return 0;
    }

    if(index > 0 && index <= size){
        INode* old = head->getNext();
        for(int i = 0; i < index - 1 ; i++){ // musimy dotrzeć do node o indeksie "index-1"
            old = old->getNext();
        }
        INode* buf = new Node<Data>(old->getNext(), data);
        old->setNext(buf);
        size++;
        return 0;
    }
    return 1;
}


/**
 * Inserts element to the end of list
 * @param data
 */
template <typename Data>
inline void List_h<Data>::insertBack(Data data) {
    if(size == 0) {
        insertFront(data);
    } else {
        INode* old = head->getNext();
        for(int i = 0; i < size - 1 ; i++){ // musimy dotrzeć do ostatniego elementu
            old = old->getNext();
        }
        INode* buf = new Node<Data>(nullptr, data);
        old->setNext(buf);
        size++;
    }

}

/**
 * Removes first element from list
 * @return data from removed element - if index ok
 * @return std::nullopt - if empty
 */
template <typename Data>
inline std::optional<Data> List_h<Data>::removeFront() {
    INode* current = head->getNext(); // jesli head wskazuje na nullptr - brak elementów

    if(current != nullptr)
    {
        INode* next = current->getNext();
        Data data = dynamic_cast<Node<Data>*>(current)->getData();
        delete current;
        head->setNext(next);
        size--;
        return data;
    } else {
        return std::nullopt; // Lista jest pusta, nie ma czego zwrócić.
    }
}

/**
 * Removes element from the given index from list
 * @return data from removed element - if index ok
 * @return std::nullopt - if wrong index
 */
template <typename Data>
inline std::optional<Data> List_h<Data>::remove(int index) {
    if(index >= size || index < 0 ) return std::nullopt;
    if(index == 0) return removeFront();

    INode* current = head->getNext();// jesli head wskazuje na nullptr - brak elementów

    for(int i = 0; i < index - 1 ; i++){ // musimy dotrzeć do node o indeksie "index-1"
        current = current->getNext();
    }
    INode* next = current->getNext();
    Data data = dynamic_cast<Node<Data>*>(next)->getData();
    current->setNext(next->getNext());
    delete next;
    size--;
    return data;
}

/**
 * Removes element from the end of list
 * @return data from removed element - if index ok
 * @return std::nullopt - if empty
 */
template <typename Data>
inline std::optional<Data> List_h<Data>::removeBack() {
    if(size == 0) return std::nullopt;
    return remove(size-1);
}

/**
 * Returns data on given index
 * @param index
 * @return data - if index ok
 * @return std::nullopt - if index wrong
 */
template <typename Data>
inline std::optional<Data> List_h<Data>::get(int index) {
    INode* buf = head->getNext();
    if(index >= 0 && index < size){
        for(int i = 0; i < index; i++){
            buf = buf->getNext();
        }
        return dynamic_cast<Node<Data>*>(buf)->getData();
    } else {
        return std::nullopt;
    }
}

/**
 * Searches for given data and returns index
 * @param data
 * @return -1 - not found
 * @return >0 - found index
 */
template <typename Data>
inline int List_h<Data>::find(Data data) {
    INode* current = head->getNext();// jesli head wskazuje na nullptr - brak elementów
    int i = 0;
    Data found;
    while (i < size){
        found = dynamic_cast<Node<Data>*>(current)->getData();
        if ( found == data) return i;
        else {
            i++;
            current = current->getNext();
        }
    }
    return -1;

}


template class List_h<int>;
template class List_h<prio>;
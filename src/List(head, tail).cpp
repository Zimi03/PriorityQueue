//
// Created by grzegorz on 25.03.24.
//

#include "List(head, tail).h"

template <typename Data>
List_h_t<Data>::List_h_t(): List_h<Data>(){
    tail = new Tail;
}

template <typename Data>
List_h_t<Data>::List_h_t(List_h_t<Data> *to_copy) {
    this->head = new Head();
    tail = new Tail;
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
List_h_t<Data>::~List_h_t() {
    clear();
    delete tail;
}

/**
 * Removes all elements of the list except for the head and tail element, which points to nullptr.
 */
template <typename Data>
void List_h_t<Data>::clear() {
    INode* current = this->head->getNext(); // jesli head wskazuje na nullptr - brak elementów
    INode* next = nullptr;

    while (current != nullptr){
        next = current->getNext();
        delete current;
        current = next;
    }

    this->head->setNext(nullptr);
    tail->setPrevious(nullptr);
    this->size = 0;
}

/**
 * Init list(head, tail) with insertBack - it is necessary for fast initzialization of data structure
 */
template <typename Data>
void List_h_t<Data>::init(Data data){
    insertBack(data);
}

/**
 * Inserts element on front
 * @param data
 */
template <typename Data>
void List_h_t<Data>::insertFront(Data data) {

    INode* buf = new Node<Data>(this->head->getNext(), data);
    this->head->setNext(buf);
    if (this->size == 0){
    tail->setPrevious(buf);
    }
    this->size++;
}

/**
 * Inserts element on given index if possible
 * @param data
 * @param index
 * @return 0 - success
 * @return 1 - fail
 */
template <typename Data>
int List_h_t<Data>::insert(int index, Data data) {
    if(index == 0) {
        insertFront(data);
        return 0;
    } else if (index == this->size) {
        insertBack(data);
        return 0;
    }

    if(index > 0 && index <= this->size){
        INode* old = this->head->getNext();
        for(int i = 0; i < index - 1 ; i++){ // musimy dotrzeć do node o indeksie "index-1"
            old = old->getNext();
        }
        INode* buf = new Node<Data>(old->getNext(), data);
        old->setNext(buf);
        this->size++;
        return 0;
    }
    return 1;
}

/**
 * Inserts element to the end of list
 * @param data
 */
template <typename Data>
void List_h_t<Data>::insertBack(Data data) {
    if(this->size == 0) {
        insertFront(data);
    } else {
        INode* current = tail->getPrevious();
        INode* buf = new Node<Data>(nullptr, data);
        current->setNext(buf);
        tail->setPrevious(buf);
        this->size++;
    }

}

/**
 * Removes first element from list
 * @return data from removed element
 * @return std::nullopt - if empty
 */
template <typename Data>
std::optional<Data> List_h_t<Data>::removeFront() {
    INode* current = this->head->getNext(); // jesli head wskazuje na nullptr - brak elementów

    if(current != nullptr)
    {
        INode* next = current->getNext();
        Data data = dynamic_cast<Node<Data>*>(current)->getData();
        delete current;
        this->head->setNext(next);
        if(this->size==1){
            tail->setPrevious(next);
        }
        this->size--;
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
std::optional<Data> List_h_t<Data>::remove(int index) {
    if(index >= this->size || index < 0 ) return std::nullopt;
    if(index == 0) return removeFront();

    INode* current = this->head->getNext();// jesli head wskazuje na nullptr - brak elementów

    for(int i = 0; i < index - 1 ; i++){ // musimy dotrzeć do node o indeksie "index-1"
        current = current->getNext();
    }
    INode* next = current->getNext();
    Data data = dynamic_cast<Node<Data>*>(next)->getData();
    current->setNext(next->getNext());
    if(index == this->size - 1) {
        tail->setPrevious(current);
    }
    delete next;
    this->size--;
    return data;
}

/**
 * Returns data on given index
 * @param index
 * @return data - if index ok
 * @return std::nullopt - if index wrong
 */
template <typename Data>
std::optional<Data> List_h_t<Data>::get(int index) {
    if(index == this->size - 1 && index >= 0){
        INode* buf = tail->getPrevious();
        return dynamic_cast<Node<Data>*>(buf)->getData();
    }

    INode* buf = this->head->getNext();
    if(index >= 0 && index < this->size){
        for(int i = 0; i < index; i++){
            buf = buf->getNext();
        }
        return dynamic_cast<Node<Data>*>(buf)->getData();
    } else {
        return std::nullopt;
    }
}

template class List_h_t<int>;
template class List_h_t<prio>;
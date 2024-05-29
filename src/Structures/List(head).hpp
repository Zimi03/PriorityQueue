//
// Created by Admin on 29.05.2024.
//

#ifndef PRIORITYQUEUE_LIST_HEAD_HPP
#define PRIORITYQUEUE_LIST_HEAD_HPP
#include "head.hpp"
#include "optional"
#include "node.hpp"
template <typename Data>
class List_h {
protected:
    int size;
    Head *head;
public:
    List_h() : size(0) {
        head = new Head();
    }


    explicit List_h(List_h* to_copy): size(0){
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
    ~List_h(){
        clear();
        delete head;
    }
    int isEmpty(){
        if(head->getNext() == nullptr) {
            return 1;
        } else return 0;
    }
    int getSize(){
        return size;
    }
    void clear(){
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

    void init(Data data){
        insertFront(data);
    }

    void insertFront(Data data){
        INode* buf = new Node<Data>(head->getNext(), data);
        head->setNext(buf);
        size++;
    }
    int insert(int index, Data data){ if(index == 0) {
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
        return 1;}
    void insertBack(Data data){
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

    std::optional<Data> removeFront(){
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
    std::optional<Data> remove(int index){
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
    std::optional<Data> removeBack(){
        if(size == 0) return std::nullopt;
        return remove(size-1);
    }

    std::optional<Data> get(int index){
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
    int find(Data data){
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


};
#endif //PRIORITYQUEUE_LIST_HEAD_HPP

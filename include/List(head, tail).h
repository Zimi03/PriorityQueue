//
// Created by Szymon on 21.03.2024.
//
//int size;
//Head *head;

#ifndef LISTY_LIST_HEAD_TAIL_H
#define LISTY_LIST_HEAD_TAIL_H
#include "Tail.h"
#include "List(head).h"

template <typename Data>
class List_h_t:  public List_h<Data>{ // a może dziedziczenie z klasy LIST(HEAD)
private:
    Tail *tail;

public:
    List_h_t();
    explicit List_h_t(List_h_t* to_copy);
    ~List_h_t() ;

    void clear();
    void init(Data data) ;

    void insertFront(Data data) ;
    int insert(int index, Data data) ;
    void insertBack(Data data) ;

    std::optional<Data> removeFront() ;
    std::optional<Data> remove(int index) ;

    std::optional<Data> get(int index) ;

};
#endif //LISTY_LIST_HEAD_TAIL_H

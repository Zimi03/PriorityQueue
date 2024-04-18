//
// Created by Szymon on 21.03.2024.
//

#ifndef LISTY_LIST_HEAD_H
#define LISTY_LIST_HEAD_H
#include "Node.h"
#include "Head.h"
#include "PriorityValue.h"
#include "optional"


template <typename Data>
class List_h {
protected:
    int size;
    Head *head;
public:
    List_h();
    explicit List_h(List_h* to_copy);
    ~List_h() ;
    int isEmpty() ;
    int getSize() ;
    void clear();
    void init(Data data) ;


    void insertFront(Data data) ;
    int insert(int index, Data data) ;
    void insertBack(Data data) ;

    std::optional<Data> removeFront() ;
    std::optional<Data> remove(int index) ;
    std::optional<Data> removeBack() ;

    std::optional<Data> get(int index) ;
    int find(Data data) ;


};
#endif //LISTY_LIST_HEAD_H

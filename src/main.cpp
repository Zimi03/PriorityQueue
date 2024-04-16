#include <iostream>
#include "List(head).h"
#include "Dynamic array.h"
#include "List(head, tail).h"


using namespace std;


void display(List_h<prio>* list){
    int i = 0;
    optional<prio> value;
    value = list->get(i);
    while(value != nullopt) {
        cout << value.value() << ", ";
        i++;
        value = list->get(i);
    }
    cout << endl;
}


void structure_test(List_h<prio>* lista){
    for(int i = 0; i < 10; i ++){
        lista->insertFront(prio(i,'A'));
    }
    display(lista);

    lista->insert(1, prio(20,'X'));
    display(lista);

    lista->insertBack(prio(30,'Y'));
    display(lista);

    lista->insertFront(prio(40,'Z'));
    display(lista);

    optional<prio> removed = lista->removeFront();
    if (removed==nullopt) {
        cout << "Removed first: NULLOPT" << endl;
    } else {
        cout << "Removed first: " << removed.value() << endl;
    }
    display(lista);

    removed = lista->remove(1);
    if (removed==nullopt) {
        cout << "Removed index 1: NULLOPT" << endl;
    } else {
        cout << "Removed index 1: " << removed.value() << endl;
    }
    display(lista);

    removed = lista->removeBack();
    if (removed==nullopt) {
        cout << "Removed back: NULLOPT" << endl;
    } else {
        cout << "Removed back: " << removed.value() << endl;
    }
    display(lista);

    int found = lista->find(prio(0,'A'));
    cout << "Found 0, A on: " << found << " index" << endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    List_h<prio> lista;
    DynamicArray<prio> arr;
    List_h_t<prio> lista_ht;


    structure_test(&lista_ht);






    return 0;
}

#include <iostream>
#include "List(head).h"
#include "Dynamic array.h"
#include "List(head, tail).h"
#include "BinaryHeap.h"
#include "PriorityQueueHeap.h"


using namespace std;


void display(DynamicArray<priorityValue>* list){
    int i = 0;
    optional<priorityValue> value;
    value = list->get(i);
    while(value != nullopt) {
        cout << value.value() << ", ";
        i++;
        value = list->get(i);
    }
    cout << endl;
}


void structure_test(DynamicArray<priorityValue>* lista){
    for(int i = 0; i < 10; i ++){
        lista->insertFront(priorityValue(i, 'A'));
    }
    display(lista);

    lista->insert(1, priorityValue(20, 'X'));
    display(lista);

    lista->insertBack(priorityValue(30, 'Y'));
    display(lista);

    lista->insertFront(priorityValue(40, 'Z'));
    display(lista);

    optional<priorityValue> removed = lista->removeFront();
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

    int found = lista->find(priorityValue(0, 'A'));
    cout << "Found 0, A on: " << found << " index" << endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    List_h<priorityValue> lista;
    DynamicArray<priorityValue> arr;
    List_h_t<priorityValue> lista_ht;


//    structure_test(&arr);


    PriorityQueueHeap bin;
    int count = 0;
    for(int i = 0; i < 6; i ++) {
        bin.insert(priorityValue(i, 9));
        bin.insert(priorityValue(i, 10));
    }
    bin.display();
    bin.modifyKey(priorityValue(5,9), 4);
    bin.modifyKey(priorityValue(3,10), 5);
//    bin.remove(priorityValue(5, 10));
//    bin.increaseKey(priorityValue(5,10), count++);
//    bin.decreaseKey(priorityValue(1,10), count++);
//    bin.decreaseKey(priorityValue(0,10), count++);



    cout << endl << "MODIFIED" <<endl;
    bin.display();

    PriorityQueueHeap bin2(&bin);

    for(int i = 0; i < 11; i ++) {
        cout << "FIND MAX: " << bin2.peek().value() << endl;
        cout << "EXTRACT MAX: " << bin2.extractMax().value() << endl << endl;
        if(i == 6) bin2.display();
    }
    cout << endl << "bin" <<endl;
    bin.display();
    cout << endl << "bin2" <<endl;
    bin2.display();





    return 0;
}

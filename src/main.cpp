#include <iostream>
#include "Queues/PriorityQueueHeap.hpp"
#include "Queues/PriorityQueueArray.hpp"
#include "Structures/PriorityValue.hpp"

int main() {
    PriorityQueueArray bin;
    int count = 0;
    for(int i = 0; i < 6; i ++) {
        bin.insert(PriorityValue(i, 9));
        bin.insert(PriorityValue(i, 10));
    }
    bin.display();
    bin.modifyKey(PriorityValue(5,9), 4);
    bin.modifyKey(PriorityValue(3,10), 5);
//    bin.remove(PriorityValue(5, 10));
//    bin.increaseKey(PriorityValue(5,10), count++);
//    bin.decreaseKey(PriorityValue(1,10), count++);
//    bin.decreaseKey(PriorityValue(0,10), count++);



    std::cout << std::endl << "MODIFIED" <<std::endl;
    bin.display();

    PriorityQueueArray bin2(&bin);

    for(int i = 0; i < 11; i ++) {
        std::cout << "FIND MAX: " << bin2.peek().value() << std::endl;
        std::cout << "EXTRACT MAX: " << bin2.extractMax().value() << std::endl << std::endl;
        if(i == 6) bin2.display();
    }
    std::cout << std::endl << "bin" <<std::endl;
    bin.display();
    std::cout << std::endl << "bin2" <<std::endl;
    bin2.display();
    return 0;
}

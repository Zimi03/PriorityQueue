#ifndef PRIORITYQUEUE_PRIORITYQUEUELIST_HPP
#define PRIORITYQUEUE_PRIORITYQUEUELIST_HPP
#include "IPriorityQueue.h"
#include "../Structures/List(head).hpp"
#include "iostream"
class PriorityQueueList: public IPriorityQueue, private List_h<PriorityValue>{
private:
    int findMax(){
        INode* it = head->getNext();
        int maxPriority = -1;
        int currPriority = -1;
        int maxIndex = 0;
        for (int i = 0; i < size; i++){
            currPriority = dynamic_cast<Node<PriorityValue>*>(it)->getData().priority;
            if(currPriority >= maxPriority){
                maxPriority = currPriority;
                maxIndex = i;
            }
            it = it->getNext();

        }
        return maxIndex;
    }
    int findValue(PriorityValue element){
        INode* it = head->getNext();
        int temp = element.value;
        int i = 0;
        while (dynamic_cast<Node<PriorityValue>*>(it)->getData().value != temp && i<size){
            it = it->getNext();
            i++;
        }
        if(i == size) return -1;
        return i;
    }
public:
    PriorityQueueList(){
        size = 0;
        head = new Head();
    }
    PriorityQueueList(PriorityQueueList* to_copy){
        size = 0;
        head = new Head();
        std::optional<PriorityValue> value;
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

    ~PriorityQueueList(){
        clear();
        delete head;
    }

    void insert(PriorityValue element) override{
        List_h<PriorityValue>::insertFront(element);
    }
    std::optional<PriorityValue> extractMax() override{
       int index = findMax();
       return List_h<PriorityValue>::remove(index);
    }
    std::optional<PriorityValue> peek() override{
        int index = findMax();
        return List_h<PriorityValue>::get(index);
    }
    int modifyKey (PriorityValue element, int priority) override{
        int index = findValue(element);
        if(priority < 0) return 3;
        if(element.priority == priority) return 1;
        if(index == -1) return 2;
        List_h<PriorityValue>::remove(index);
        PriorityValue buf;
        buf.value = element.value;
        buf.priority = priority;
        List_h<PriorityValue>::insertFront(buf);
    }
    int getSize() override{
        return size;
    }
    void display(){
        INode* buf = head->getNext();
        PriorityValue disp;
        for(int i = 0; i<size;i++){
            disp = dynamic_cast<Node<PriorityValue>*>(buf)->getData();
            std::cout<<disp<<std::endl;
            buf = buf->getNext();
        }
    }


};
#endif //PRIORITYQUEUE_PRIORITYQUEUELIST_HPP

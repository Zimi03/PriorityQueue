#ifndef PRIORITYQUEUE_PRIORITYQUEUELIST_H
#define PRIORITYQUEUE_PRIORITYQUEUELIST_H
#include "IPriorityQueue.h"
#include "List(head, tail).h"
#include "PriorityValue.h"
class PQL : public IPriorityQueue{
private:
   List_h_t<priorityValue>* list = nullptr;
   int size;
   int findindex(priorityValue element);
public:
    ~PQL() override;
    PQL();
    PQL(PQL *to_copy);
    int insert (priorityValue element) override;
    std::optional<priorityValue> extractMax() override;
    std::optional<priorityValue> peek() override;
    int modifyKey(priorityValue element, int priority) override;
};
#endif //PRIORITYQUEUE_PRIORITYQUEUELIST_H

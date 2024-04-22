#ifndef PRIORITYQUEUE_PRIORITYQUEUELIST_H
#define PRIORITYQUEUE_PRIORITYQUEUELIST_H
#include "IPriorityQueue.h"
#include "Dynamic array.h"
#include "PriorityValue.h"
class PQA : public IPriorityQueue, private DynamicArray<priorityValue>{
private:
    int FindPriority(priorityValue element);
    int FindValue(priorityValue element);
public:
    ~PQA() override;
    PQA();
    PQA(PQA *to_copy);
    void insert(priorityValue element) override;
    std::optional<priorityValue> extractMax() override;
    std::optional<priorityValue> peek() override;
    int modifyKey(priorityValue element, int priority) override;
};
#endif //PRIORITYQUEUE_PRIORITYQUEUELIST_H

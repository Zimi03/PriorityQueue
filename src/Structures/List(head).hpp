#ifndef PRIORITYQUEUE_LIST_HEAD_HPP
#define PRIORITYQUEUE_LIST_HEAD_HPP

#include "head.hpp"
#include <memory>
#include "node.hpp"

template <typename Data>
class List_h {
protected:
    int size;
    std::unique_ptr<Head> head;

public:
    List_h() : size(0), head(std::make_unique<Head>()) {}

    // Copy constructor
    List_h(const List_h& to_copy) : size(0), head(std::make_unique<Head>()) {
        int _size = to_copy.getSize();
        for (int i = 0; i < _size; i++) {
            auto value = to_copy.get(i);
            if (value) {
                insertBack(*value);
            }
        }
    }

    virtual ~List_h() {
        clear();
    }

    bool isEmpty() const {
        return head->getNext() == nullptr;
    }

    int getSize() const {
        return size;
    }

    void clear() {
        INode* current = head->getNext();
        while (current != nullptr) {
            INode* next = current->getNext();
            delete current;
            current = next;
        }
        head->setNext(nullptr);
        size = 0;
    }

    void init(Data data) {
        insertFront(data);
    }

    void insertFront(Data data) {
        head->setNext(new Node<Data>(head->getNext(), data));
        size++;
    }

    int insert(int index, Data data) {
        if (index == 0) {
            insertFront(data);
            return 0;
        }

        if (index > 0 && index <= size) {
            INode* current = head->getNext();
            for (int i = 0; i < index - 1; i++) {
                current = current->getNext();
            }
            current->setNext(new Node<Data>(current->getNext(), data));
            size++;
            return 0;
        }
        return 1;
    }

    void insertBack(Data data) {
        if (size == 0) {
            insertFront(data);
        } else {
            INode* current = head->getNext();
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(new Node<Data>(nullptr, data));
            size++;
        }
    }

    std::optional<Data> removeFront() {
        INode* current = head->getNext();
        if (current) {
            INode* next = current->getNext();
            Data data = dynamic_cast<Node<Data>*>(current)->getData();
            delete current;
            head->setNext(next);
            size--;
            return data;
        }
        return std::nullopt;
    }

    std::optional<Data> remove(int index) {
        if (index >= size || index < 0) return std::nullopt;
        if (index == 0) return removeFront();

        INode* current = head->getNext();
        for (int i = 0; i < index - 1; i++) {
            current = current->getNext();
        }
        INode* nodeToRemove = current->getNext();
        current->setNext(nodeToRemove->getNext());
        Data data = dynamic_cast<Node<Data>*>(nodeToRemove)->getData();
        delete nodeToRemove;
        size--;
        return data;
    }

    std::optional<Data> removeBack() {
        if (size == 0) return std::nullopt;
        return remove(size - 1);
    }

    std::optional<Data> get(int index) const {
        if (index < 0 || index >= size) return std::nullopt;

        INode* current = head->getNext();
        for (int i = 0; i < index; i++) {
            current = current->getNext();
        }
        return dynamic_cast<Node<Data>*>(current)->getData();
    }

    int find(Data data) const {
        INode* current = head->getNext();
        for (int i = 0; i < size; i++) {
            if (dynamic_cast<Node<Data>*>(current)->getData() == data) {
                return i;
            }
            current = current->getNext();
        }
        return -1;
    }
};

#endif // PRIORITYQUEUE_LIST_HEAD_HPP

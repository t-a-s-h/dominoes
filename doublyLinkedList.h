#ifndef DLL_HH
#define DLL_HH

#include <iostream>

template<typename T>
class DoublyLinkedList {
    struct Node;
    public:
    int length{0};
    Node* head;
    Node* tail;
    DoublyLinkedList* addtoFront(T*);
    DoublyLinkedList* addtoBack(T*);

    DoublyLinkedList():
        head{nullptr},
        tail{nullptr}{}
    ~DoublyLinkedList() {
        delete head;
    }
};

template<typename T>
struct DoublyLinkedList<T>::Node {
    T* data;
    Node* next;
    Node* prev;
    int index;

    Node(T* data = nullptr): 
        data{data},
        next{nullptr},
        prev{nullptr},
        index{0}{}

    friend class DoublyLinkedList;

    friend bool operator==(Node& l, Node& m) {
      return l == m;
    }
    
    friend bool operator!=(Node& l, Node& m) {
      return !(l == m);
    }
    
    friend bool operator< (Node& l, Node& m) {
      return (l.index < m.index);
    }
    
    friend bool operator> (Node& l, Node& m) {
      return (l.index > m.index);
    }
};

template<typename T> DoublyLinkedList<T>* DoublyLinkedList<T>::addtoFront(T* data) {
    Node* newNode = new Node(data);

    newNode->prev = this->head;
    
    if (this->head) {
        this->head->next = newNode;
    }

    if (!this->tail) {
        this->tail = newNode;
    } else {
        newNode->prev = this->head;
    }

    newNode->index = this->length;
    this->head = newNode;
    
    ++this->length;
    return this;
}

template<typename T> DoublyLinkedList<T>* DoublyLinkedList<T>::addtoBack(T* data) {
    Node* newNode = new Node(data);
    newNode->next = this->tail;
    
    if (this->tail) {
        this->tail->prev = newNode;
    }

    if (!this->head) {
        this->head = newNode;
    } else {
        newNode->next = this->tail;
    }

    newNode->index = this->length;
    this->tail = newNode;
    ++this->length;
    return this;
}

#endif
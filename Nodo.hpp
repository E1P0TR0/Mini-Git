#ifndef __NODO_HPP__
#define __NODO_HPP__

template <typename T>
class Node
{
public: // error con private
    T data;
    Node* next;

public: 
    Node(T _data = nullptr, Node* _next = nullptr) : data(_data), next(_next) {}
    ~Node() = default;
    T getData() { return this->data; }
    Node* getNext() { return this->next; } 
};

#endif
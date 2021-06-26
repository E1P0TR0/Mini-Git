#ifndef __PILA_HPP__
#define __PILA_HPP__

#include "Nodo.hpp"

template <class T>
class Stack
{
private:
    Node<T>* top;
    int size;
public:
    Stack() : top(nullptr), size(0) {}
    
    inline int getSize() const { return this->size; }
    inline bool itsEmpty() const { return top == nullptr; }

    void push(T element);
    T pop();
    void print();
};

template <class T>
void Stack<T>::push(T element)
{
    if(itsEmpty())
    {
        this->top = new Node<T>(element);
    }
    else
        this->top = new Node<T>(element, this->top);
    size++;
}

template <class T>
T Stack<T>::pop()
{
    if(itsEmpty()) return nullptr;
    else
    {
        T data = top->data;
        top = top->next;
        return data;
    }
}

template <class T>
void Stack<T>::print()
{
    if(itsEmpty()) std::cout << "VACIO\n";
    else
    {
        Node<T>* temp = top;
        while(temp != nullptr)
        {
            std::cout << temp->data->getName() << "\n";
            temp = temp->next;
        }
    }
}

#endif
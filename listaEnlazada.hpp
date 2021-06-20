#ifndef __LISTA_ENLAZADA_HPP__
#define __LISTA_ENLAZADA_HPP__

// PARA ALMACENAR USUARIOS

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

template <class T>
class LinkedList
{
private:
    Node<T>* root;
    unsigned int size;

public:
     class Iterator
    {
    private:
        Node<T>* current;
        unsigned int pos;

    public:
        Iterator(Node<T>* _current = nullptr, unsigned int _pos = 0) : current(_current), pos(_pos) {}
        unsigned int getPos() { return pos; }
        void operator ++() {  pos++; current = current->next; }
        bool operator !=(Iterator it) { return pos != it.pos; }
        T operator *() { return current->data; }
    };
public:
    LinkedList() : root(nullptr), size(0) {}
    ~LinkedList();

    inline unsigned int getSize() const { return this->size; }
    inline bool itsEmpty() const { return this->size == 0; }

    void addInitial(T); 
    void addPos(T, unsigned int _pos);
    void addFinal(T);

    T getElement(std::string _name);

    Iterator beginIt() { return Iterator(root, 0); }
    Iterator endIt() { return Iterator(nullptr, size); }

    void printList();
};

template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* current = root;
    while(current != nullptr)
    {
        current = root;
        root = root->next;
        delete current;
    }
}

template <class T>
void LinkedList<T>::addInitial(T element)
{
    Node<T>* newNode = new Node<T>(element, root);
    if(newNode != nullptr)
    {
        root = newNode;
        size++; 
    }
}

template <class T>
void LinkedList<T>::addPos(T element, unsigned int _pos)
{
    if(_pos > size) return;
    if(_pos == 0) addInitial(element);
    else
    {
        Node<T>* current = root;
        for(int i = 1; i < _pos; ++i)
            current = current->next;
        Node<T>* newNode = new Node<T>(element, current->next);
        if(newNode != nullptr)
        {
            current->next = newNode;
            size++;
        }
    }
}

template <class T>
void LinkedList<T>::addFinal(T element) { addPos(element, size); }

template <class T>
T LinkedList<T>::getElement(std::string _name)
{
    for(LinkedList<T>::Iterator it = this->beginIt(); it != this->endIt(); ++it)
    {
        T currentData = *it;
        if(currentData->getName() == _name) 
            return currentData;
    }
    return nullptr;
}

template <class T>
void LinkedList<T>::printList()
{
    std::cout << "List : \n\n";
    for(LinkedList<T>::Iterator it = this->beginIt(); it != this->endIt(); ++it)
    {
        std::cout << "-> Data " + std::to_string(it.getPos() + 1) + "\n";
        T currentData = *it;
        std::cout << currentData->getName();
        std::cout << "\n";
    }
}

#endif
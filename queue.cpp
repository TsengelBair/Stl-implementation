#include <iostream>
#include <queue>
#include <stdexcept> // Для обработки ошибок

template <typename T>
struct Node
{
    Node(T value) : data(value), next(nullptr) {}
    ~Node() {}

    T data;
    Node* next;
};

template <typename T>
class Queue {
public:
    Queue() : _first(nullptr), _last(nullptr), _size(0) {}

    ~Queue() {
        while (!empty()) {
            pop();
        }
    }

    bool empty() const {
        return _size == 0;
    }

    size_t size() const {
        return _size;
    }
    /* 
        stl очередь позволяет мутировать элементы, полученные через front() || back()
        поэтому в текущей реализации методы также не константные
    */
    T& front() {
        if (empty()) throw std::underflow_error("Queue is empty");
        return _first->data;
    }

    T& back() {
        if (empty()) throw std::underflow_error("Queue is empty");
        return _last->data;
    }

    void push(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (empty()) {
            _first = newNode;
            _last = newNode;
        }
        else if (_size == 1) {
            _last = newNode;
            _first->next = _last;
        }
        else {
            _last->next = newNode;
        }

        ++_size;
    }

    void pop() {
        Node<T>* newFirst = _first->next;
        delete _first;
        _first = newFirst;
        --_size;
    }

    void print() const {
        Node<T>* cur = _first;
        for (int i = 0; i < _size; ++i) {
            std::cout << cur->data << " ";
            cur = cur->next;
        }
        std::cout << std::endl;
    }



private:
    Node<T>* _first;
    Node<T>* _last;
    size_t _size;
};


#include <iostream>

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
    Queue() : _first(nullptr), _size(0) {}

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

    void push(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (empty()) {
            _first = newNode;
        }
        else if (_size == 1) {
            _first->next = newNode;
        }
        else {
            /* для получения последнего эл-та перед вставляемым */
            Node<T>* last = _first;
            for (int i = 0; i < _size - 1; ++i) {
                last = last->next;
            }

            last->next = newNode;
        }

        ++_size;
    }

    /* нужно удалить самый первый эл-т, т.е. _first */
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
    size_t _size;
};

int main()
{
    Queue<int>q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.print(); // 1, 2, 3

    q.pop();
    q.pop();
    q.print(); // 3
}


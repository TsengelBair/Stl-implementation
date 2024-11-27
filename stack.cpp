#include <iostream>
#include <stdexcept> // Для обработки ошибок

template <typename T>
struct Node
{
    Node(T value) : data(value), prev(nullptr) {}

    T data;
    Node* prev;
};

/* Стек, представленный односвязным списком с указателями, направленными в обратную сторону */
template <typename T>
class Stack
{
public:
    Stack() : _top(nullptr), _size(0) {}

    ~Stack() {
        while (_top != nullptr) {
            pop();
        }
    }

    bool empty() {
        return _size == 0;
    }

    size_t size() const {
        return _size;
    }

    T& top() {
        if (_top == nullptr) {
            throw std::underflow_error("Stack is empty");
        }
        return _top->data;
    }

    void push(T value) {
        // Создаем новую вершину
        Node<T>* newNode = new Node<T>(value);

        // Указатель prev новой вершины указывает на предыдущую верхнюю вершину
        newNode->prev = _top;

        // Обновляем верхнюю вершину
        _top = newNode;

        ++_size;
    }

    void pop() {
        if (_top == nullptr) {
            throw std::underflow_error("Stack is empty");
        }

        Node<T>* prevTop = _top->prev;

        // Удаляем верхнюю вершину
        delete _top;

        // Обновляем верхнюю вершину на предыдущую
        _top = prevTop;

        --_size;
    }

private:
    Node<T>* _top;
    size_t _size;
};

int main() {

    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    std::cout << stack.top() << std::endl;  // 3

    stack.pop();
    std::cout << stack.top() << std::endl;  // 2

    stack.pop();
    std::cout << stack.top() << std::endl;  // 1

    stack.pop();

    try {
        std::cout << stack.top() << std::endl;  // Ошибка, стек пуст
    }
    catch (const std::underflow_error& e) {
        std::cout << "Error: " << e.what() << std::endl; 
    }

    return 0;
}

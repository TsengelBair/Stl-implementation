#include <iostream>
#include <string>
#include <vector>

/*
    каждая ячейка это связный список (для избежания коллизий)
    последний вставленный элемент является головой списка (т.е. вставка осуществляется в начало списка, а не в конец)
    т.к. в таком случае не нужно итерироваться по всему списку для обновления указателя next у последнего эл-та
*/

struct Node {
    Node(std::string key) : _key(key), _next(nullptr) {}

    std::string _key;
    Node* _next;
};

class HashSet {
public:
    /* по дефолту память выделена под 5 элементов, при нехватке памяти, память будет увеличиваться вдвое в методе realloc() */
    HashSet() : _capacity(5), _array(_capacity, nullptr), _size(0) {}

    ~HashSet() {
        clear();
    }

    void insert(const std::string& key) {
        if (_size == _capacity) {
            realloc();
        }

        int index = hashFunc(key) % _capacity;
        Node* current = _array[index]; /* нода по текущему индексу, если там ничего нет будет nullptr */

        while (current) {
            if (current->_key == key) {
                return; /* такой элемент уже есть в сете */
            }
            current = current->_next;
        }

        /* создаем новую ноду, которая будет головой списка в указанном бакете */
        Node* newNode = new Node(key);
        /* указатель next новой ноды указывает на предыдущую голову */
        newNode->_next = _array[index];
        /* обновляем голову на созданную */
        _array[index] = newNode;

        ++_size;
    }

    void print() {
        for (auto node : _array) {
            while (node) {
                std::cout << node->_key << " ";
                node = node->_next;
            }
            std::cout << std::endl;
        }
    }

    Node* find(const std::string& key) {
        int index = hashFunc(key) % _capacity;
        Node* current = _array[index];

        while (current) {
            if (current->_key == key) {
                return current;
            }
            current = current->_next;
        }

        return nullptr;
    }

private:
    int hashFunc(const std::string& key) {
        int index{ 0 };
        for (int i = 0; i < key.size(); ++i) {
            index += static_cast<int>(key[i]) * (i + 1); /* домножаем на индекс для избежания коллизий */
        }

        return index;
    }

    void realloc() {
        /* увеличиваем емкость в 2 раза */
        int newCapacity = _capacity * 2;
        std::vector<Node*> newArray(newCapacity, nullptr);

        for (int i = 0; i < _capacity; ++i) {
            Node* current = _array[i];
            while (current) {
                /* генерируем индекс в новом массиве */
                int index = hashFunc(current->_key) % newCapacity;

                Node* newNode = new Node(current->_key);
                newNode->_next = newArray[index];
                newArray[index] = newNode;

                /* освобождаем память предыдущего массива */
                Node* tmp = current;
                current = current->_next;
                delete tmp;
            }
        }

        _array = newArray;
        _capacity = newCapacity;
    }

    void clear() {
        for (auto node : _array) {
            while (node) {
                Node* tmp = node->_next;
                delete node;
                node = tmp;
            }
        }
    }

private:
    size_t _capacity; /* текущая емкость массива */
    std::vector<Node*> _array;
    size_t _size; /* кол-во фактических элементов */
};

int main()
{
    HashSet set;
    set.insert("John");
    set.insert("Michael");
    set.insert("Sam");
    set.insert("Mary");
    set.insert("Tom");

    Node* res = set.find("John");
    std::cout << res << std::endl;

    return 0;
}

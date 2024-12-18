#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
    Node(T key) : _key(key), _left(nullptr), _right(nullptr) {}

    T _key;
    Node* _left;
    Node* _right;
};

template<typename T>
class Tree {
public:
    Tree() : _root(nullptr) {}
    ~Tree() {
        Destroy(_root);
    }

    void insert(T key) {
        Node<T>* newNode = new Node<T>(key);
        if (_root == nullptr) {
            _root = newNode;
        }
        else {
            insertInRightPlace(newNode, _root);
        }
    }

    Node<T>* find(T key) {
        Node<T>* res = findNode(key, _root);
        if (res) {
            return res;
        }
        else {
            throw std::runtime_error("Node not found");
        }
    }

    /* при операции удаления обновляется все дерево */
    void remove(T key) {
        _root = removeNode(_root, key);
    }

private:
    void insertInRightPlace(Node<T>* newNode, Node<T>* parent) {
        /* если меньше либо равен родителю, вставляем влево */
        if (newNode->_key <= parent->_key) {
            /*
                проверяем, существует ли узел слева от родителя, если узла нет - обновляем указатель у родителя
                если узел есть, идем глубже (в else)
            */
            if (parent->_left == nullptr) {
                parent->_left = newNode;
            }
            else {
                /* рекурсивно вызываем функцию, передав актуального родителя */
                insertInRightPlace(newNode, parent->_left);
            }
        }
        /* если больше родителя, вставляем вправо */
        else {
            if (parent->_right == nullptr) {
                parent->_right = newNode;
            }
            else {
                insertInRightPlace(newNode, parent->_right);
            }
        }
    }

    Node<T>* findNode(T key, Node<T>* parent) {
        if (key == parent->_key) {
            return parent;
        }
        else if (key < parent->_key) {
            return findNode(key, parent->_left);
        }
        else {
            return findNode(key, parent->_right);
        }
    }

    Node<T>* removeNode(Node<T>* node, T key) {
        if (node == nullptr) return nullptr;
        /*
            ищем нужную вершину рекурсивно по ключу
            базовый случай наступит в else
        */
        if (key < node->_key) {
            node->_left = removeNode(node->_left, key);
        }
        else if (key > node->_key) {
            node->_right = removeNode(node->_right, key);
        }
        /* нужную вершину получили */
        else {
            /* если это лист */
            if (node->_left == nullptr && node->_right == nullptr) {
                delete node;
                return nullptr;
            }
            /* если узел слева отсутствует, заменяем удаляемый узел на его правого ребенка */
            else if (node->_left == nullptr && node->_right != nullptr) {
                Node<T>* tmp = node->_right;
                delete node;
                return tmp;
            }
            /* заменяем на левого ребенка */
            else if (node->_left != nullptr && node->_right == nullptr) {
                Node<T>* tmp = node->_left;
                delete node;
                return tmp;
            }
            /* нужная вершина найдена */
            else {
                /*
                    если у удаляемого узла есть два ребенка, нужно найти максимальный из его левого поддерева
                    либо минимальный из правого поддерева
                */
                Node<T>* maxFromLeft = findMaxFromLeft(node);
                node->_key = maxFromLeft->_key; /* копируем значение */
                node->_left = removeNode(node->_left, maxFromLeft->_key); /* удаляем максимальный узел */
            }
        }
        return node;
    }

    Node<T>* findMaxFromLeft(Node<T>* node) {
        while (node->_left != nullptr) {
            node = node->_left;
        }
        /* максимальный эл-т из левого поддерева */
        return node = node->_right;
    }

    void Destroy(Node<T>* node) {
        if (node) {
            Destroy(node->_left);
            Destroy(node->_right);
            delete node;
        }
    }

private:
    Node<T>* _root;
};
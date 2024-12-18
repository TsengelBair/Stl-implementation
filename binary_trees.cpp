#include <iostream>

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

    void print() {
        std::cout << "Root elem " << _root->_key << "\n";
        std::cout << "Left " << _root->_left->_key << "\n";
        std::cout << "Right " << _root->_right->_key << "\n";
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

int main()
{
    Tree<int>binary_tree;

    binary_tree.insert(10);
    binary_tree.insert(5);
    binary_tree.insert(12);

    binary_tree.print();

    return 0;
}


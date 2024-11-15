template <typename T>
class List {
public:
    List() : head(nullptr), tail(nullptr), m_size(0) {}
    ~List() {
        clear();
    }

    bool empty() const {
        return m_size == 0;
    }

    size_t size() const {
        return m_size;
    }

    void push_front(T val) {
        Node* newHead = new Node(val);
        if (empty()) {
            head = newHead;
            tail = newHead;
        }
        else {
            newHead->next = head;
            head->prev = newHead;
            head = newHead;
        }
        head->prev = nullptr;
        ++m_size;
    };

    void push_back(T val) {
        Node* newTail = new Node(val);
        if (empty()) {
            head = newTail;
            tail = newTail;
        }
        else {
            newTail->prev = tail;
            tail->next = newTail;
            tail = newTail;
        }
        tail->next = nullptr;
        ++m_size;
    }

    void pop_back() {
        if (empty()) {
            return;
        }
        else if (size() == 1) {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
        else {
            Node* prevTail = tail->prev;
            delete tail;
            tail = prevTail;
            tail-> next = nullptr;
        }
        --m_size;
    };

    void pop_front() {
        if (empty()) {
            return;
        }
        else if (size() == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else {
            Node* nextHead = head->next;
            delete head;
            head = nextHead;
            head->prev = nullptr;
        }
        --m_size;
    }

    void insert(size_t pos, T val) {
        if (pos > m_size) {
            throw std::out_of_range("index out of range");
        }
        else if (pos == 0) {
            push_front(val);
        }
        else if (pos == m_size) {
            push_back(val);
        }
        else {
            Node* newNode= new Node(val);
            Node* current = head;

            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }

            newNode->next = current->next;
            newNode->prev = current;
            
            current->next->prev = newNode;
            current->next = newNode;

            ++m_size;
        }
    }

    void erase(size_t pos) {
        if (pos > m_size) {
            throw std::out_of_range("index out of range");
        }
        else if (pos == 0) {
            pop_front();
        }
        else if (pos == m_size) {
            pop_back();
        }
        else {
            Node* current = head;

            for (size_t i = 0; i < pos; ++i) {
                current = current->next;
            }

            if (current->prev) {
                current->prev->next = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }

            delete current;

            --m_size;
        }
    }

    void print() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
    }

    void clear() {
        while (!empty()) {
            pop_back();
        }
    };

private:
    struct Node
    {
        Node(T p_data) : prev(nullptr), next(nullptr), data(p_data) {}

        T data;
        Node* prev;
        Node* next;
    };

    Node* head;
    Node* tail;
    size_t m_size;
};




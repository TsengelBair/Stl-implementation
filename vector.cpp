template <typename T>
class Vector {
public:
	/* По умолчанию выделяем память под 10 элементов */
	Vector() : data(nullptr), m_size(0), m_capacity(0) {
		alloc(10);
	}
	/* В случае явной передачи памяти, выделяем указанное кол-во памяти */
	Vector(size_t capacity) : data(nullptr), m_size(0), m_capacity(0) {
		alloc(capacity);
	};
	/* Выделяем указанное кол-во памяти и инициализируем эл-ты переданным значением */
	Vector(size_t capacity, T default_value) : data(nullptr), m_size(0), m_capacity(0) {
		alloc(capacity);
		m_size = capacity;

		for (int i = 0; i < m_capacity; ++i) {
			data[i] = default_value;
		}
	}
	/* Метод для выделения памяти */
	void reserve(size_t capacity) {
		if (capacity <= m_capacity) return;

		// выделяем новую память, в которую перезаписываем предыдущие значения
		T* newData = new T[capacity];
		for (int i = 0; i < m_size; ++i) {
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		m_capacity = capacity;
	};
	/* Метод для ресайза */
	void resize(size_t size, T val) {
		if (size < m_size) {
			m_size = size;
		}
		else if (size == m_size) {
			return;
		}
		else {
			reserve(size);
			for (int i = m_size; i < size; ++i) {
				data[i] = val;
			}
			m_size = size;
		}
	};

	int size() const {
		return m_size;
	};

	int capacity() const {
		return m_capacity;
	}

	/* Метод получения элемента по индексу */
	T& at(size_t index) {
		if (index >= m_size) {
			throw std::out_of_range("Index out of range");
		}
		return data[index];
	}
	/* Перегрузка оператора [] */
	T& operator[] (size_t index) {
		return at(index);
	}

	T& front() {
		if (m_size == 0) throw std::out_of_range("Vector is empty");
		return data[0];
	};

	T& back() {
		if (m_size == 0) throw std::out_of_range("Vector is empty");
		return data[m_size - 1];
	};

	void push_back(T val) {
		if (m_capacity == m_size) {
			reserve(m_capacity ==  0 ? 1 : m_capacity * 2);
		}
		data[m_size] = val;
		++m_size;
	};
	
	void pop_back() {
		if (m_size == 0) return;

		// Если T требует очистки памяти
		data[m_size - 1].~T(); 

		--m_size;
	}

	void insert(int pos, T val) {
		if (pos > m_size) {
			throw std::out_of_range("Vector is empty");
		}
		
		if (m_size == m_capacity) {
			reserve(m_capacity == 0 ? 1 : m_capacity * 2);
		}

		// Сдвигаем элементы вправо до pos
		for (int i = m_size; i > pos; --i) {
			data[i] = data[i - 1];
		}
		
		data[pos] = val;
		++m_size;
	};

	void erase(int pos) {
		if (pos > m_size) {
			throw std::out_of_range("Vector is empty");
		}

		// Сдвигаем элементы влево до
		for (int i = pos; i < m_size - 1; ++i) {
			data[i] = data[i + 1];
		}

		--m_size;
	}

	void clear() {
		if (data) {
			delete[] data;
			data = nullptr;
		}
		m_capacity = 0;
		m_size = 0;
	};

	void print() {
		std::cout << "Capacity " << m_capacity << "\n";
		std::cout << "Size " << m_size << "\n";

		for (int i = 0; i < m_size; ++i) {
			std::cout << data[i] << " ";
		}
		std::cout << "\n";
	}

	~Vector() {
		clear();
	}

private:
	/* метод аллоцирования памяти по умолчанию */
	void alloc(size_t new_capacity) {
		if (new_capacity == 0) return;

		data = new T[new_capacity](); // () - для инициализации значениями по умолчанию
		m_capacity = new_capacity;
	};

private:
	/* указатель на данные */
	T* data;
	/* размер вектора */
	size_t m_size;
	/* размер выделенной памяти */
	size_t m_capacity;
};

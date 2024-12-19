#include <iostream>
#include <string>
#include <vector>

struct Node {
	Node(std::string key) : _key(key), _nearest(nullptr) {}

	std::string _key;
	Node* _nearest; 
};

class HashSet {
public:
	HashSet() : _array(5, nullptr), _size(0) {}

	~HashSet() {
		clear();
	}

	void insert(const std::string& key) {
		/* аллоцируем новую память с перезаписью имеющихся нод */
		if (_array.size() == _size) {
			realloc();
		}

		int index = hashFunc(key) % _array.size();
		Node* current = _array[index];

		while (current) {
			if (current->_key == key) {
				return; /* ключи совпали */
			}
			current = current->_nearest;
		}

		Node* newNode = new Node(key);
		/* 
			новую ноду добавляем в начало списка, если бакет был пуст, указатель _nearest == nullptr
			если нет, то он будет указывать на самый первый элемент бакета
		*/
		newNode->_nearest = _array[index];
		/* обновляем первый эл-т бакета на новую ноду */
		_array[index] = newNode;

		++_size;
	}

private:
	int hashFunc(const std::string& key) {
		int index{ 0 };
		for (int i = 0; i < key.size(); ++i) {
			index += static_cast<int>(key[i]) * (i + 1); /* домножение на индекс, чтобы было меньше коллизий */
		}

		return index;
	}

	void realloc() {
		size_t newCapacity = _array.size() * 2;
		std::vector<Node*>newArray(newCapacity, nullptr);

		/* т.к. размер массива изменился, все ноды нужно пересчитать (бакеты будут отличаться от предыдущих из-за нового размера) */
		for (int i = 0; i < _array.size(); ++i) {
			Node* current = _array[i];
			/* разместить текущую ноду в новом массиве, в случае если у нее есть соседи, повторить процедуру для них */
			while (current) {
				int index = hashFunc(current->_key) % newCapacity;

				/* тоже самое что и в insert */
				Node* tmp = new Node(current->_key);
				tmp->_nearest = newArray[index];
				newArray[index] = tmp;

				current = current->_nearest;
			}
		}

		clear();
		_array = std::move(newArray);
	}

	void clear() {
		for (auto node : _array) {
			while (node) {
				Node* tmp = node->_nearest;
				delete node;
				node = tmp;
			}
		}
		_array.clear();
	}

private:
	std::vector<Node*>_array;
	size_t _size; /* кол-во эл-ов */
};
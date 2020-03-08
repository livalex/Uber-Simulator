// Copyright[2019] <Livadaru Alexandru-Valentin 313CA>

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <queue>

template <typename Tkey, typename Tvalue>
struct information {
	Tkey key;
	Tvalue value;
};

template <typename Tkey, typename Tvalue>
class Dictionary {
 public:
	int range;
	int quantity;
	std::list<struct information<Tkey, Tvalue>> *Object;

	explicit Dictionary(const int quantity) {
		this->range = 0;
		this->quantity = quantity;
		Object = new std::list<struct information<Tkey, Tvalue>>[quantity];
	}

	Dictionary() {
		this->range = 0;
		this->quantity = 0;
		Object = nullptr;
	}

	void alloc_memory(int quantity) {
		this->quantity = quantity;
		this->Object = new std::list<struct information<Tkey, Tvalue>>[quantity];
	}

	~Dictionary() {
		int j;
		for (j = 0; j < quantity; ++j) {
			while (Object[j].empty() == 0) {
				Object[j].pop_back();
			}
		}
		delete[] Object;
	}

	int hashFunction(Tkey intersection, int quantity) {
		int add;
		add =  2 * intersection.length() - 1;
		return add % quantity;
	}

	void insert(Tkey key, Tvalue value) {
		typename std::list<struct information<Tkey, Tvalue>>::iterator it;
		int flag = 0;
		int j = hashFunction(key, quantity);
		for (it = Object[j].begin(); it != Object[j].end(); ++it) {
			if (it->key == key) {
				it->value = value;
				flag = 1;
			}
		}
		if (flag == 0) {
			struct information<Tkey, Tvalue> node;
			node.key = key;
			node.value = value;
			Object[j].push_back(node);
			++range;
		}
	}

	Tvalue get(Tkey key) {
		typename std::list<struct information<Tkey, Tvalue>>::iterator it;
		int j = hashFunction(key, quantity);
		for (it = Object[j].begin(); it != Object[j].end(); ++it) {
			if (it->key == key) {
				return it->value;
			}
		}
		return Tvalue();
	}
};
#endif  // HASHTABLE_H_

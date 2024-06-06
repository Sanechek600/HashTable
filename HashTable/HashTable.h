#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <list>
template<typename Key, typename Value, template<typename...> class List = std::list>
class HashTable {
	struct Node {
		Key key;
		Value value;
		Node() : key(), value() {}
		Node(const Key& k, const Value& v, bool deleted = false) : key(k), value(v) {}
	};
	std::vector<List<Node>> _table;
	size_t _size = 0;
	const float _loadfactor = 0.75; // Фактор загрузки для изменения размера хеш-таблицы
	size_t _hash_base = 211;

	int hash(const Key& key) const {
		unsigned int hash_value = key % _hash_base;
		return (hash_value) % _table.size();
	}

	void rehash() {
		std::vector<List<Node>> new_table;
		new_table.resize(_table.size() * 1.75);
		_size = 0;
		std::swap(new_table, _table);
		for (size_t i = 0; i < new_table.size(); ++i) {
			for (auto& node : new_table[i]) {
				insert(node.key, node.value);
			}
		}
	}

public:
	HashTable(const size_t size) : _table(size) {}
	HashTable(const HashTable& other) {
		_table = other._table;
		_size = other._size;
	}
	HashTable(const size_t size, const Key& min, const Value& max) : _table(size) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<size_t> dis(min, max);
		for (size_t i = 0; i < size; ++i) {
			Key key = (Key)dis(gen);
			Value value = (Value)dis(gen);
			insert(key, value);
		}
	}
	HashTable& operator=(const HashTable& other) {
		if (this != &other) {
			_table = other._table;
		}
		return *this;
	}
	void print() const {
		for (const auto& list : _table) {
			for (auto& node : list) {
				std::cout << "Key: " << node.key << ", Value: " << node.value << std::endl;
			}
		}
	}
	void insert(const Key& key, const Value& value) {
		if ((float)_size / (float)_table.size() >= _loadfactor) {
			rehash();
		}
		size_t idx = hash(key);
		_table[idx].emplace_back(key, value);
		++_size;
	}
	void insert_or_assign(const Key& key, const Value& value) {
		auto result = search(key);
		if (!result) {
			insert(key, value);
			return;
		}
		*result = value;
	}
	bool contains(const Value& value) const {
		for (auto& list : _table) {
			for (auto& node : list) {
				if (node.value == value) 
					return true;
			}
		}

		return false;
	}
	Value* search(const Key& key) {
		size_t idx = hash(key);
		for (auto& node : _table[idx]) 
			if (node.key == key) 
				return &node.value;
		return nullptr;
	}
	bool erase(const Key& key) {
		size_t idx = hash(key);
		auto& list = _table[idx];
		for (auto it = list.begin(); it != list.end(); ++it) {
			if (it->key == key) {
				list.erase(it);
				--_size;
				return true;
			}
		}
		return false;
	}
	size_t get_size() const {
		return _size;
	}
};
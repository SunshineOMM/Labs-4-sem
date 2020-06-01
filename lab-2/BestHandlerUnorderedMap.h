#pragma once

#include <functional>

template<typename TKey, typename TValue, typename TKeyHash = std::hash<TKey>>
class UnorderedMap {
	struct Node {
		const TKey key;
		TValue value;
		Node *next;

		Node(const TKey &key, const TValue& value) : key(key), value(value), next(nullptr) {}
	};

	Node **_table;
	const std::size_t _count;

	Node **Find(const TKey &key) {
		const auto i = TKeyHash()(key) % _count;
		auto node = _table + i;
		while (*node) {
			if ((*node)->key == key) {
				return node;
			}
			node = &((*node)->next);
		}
		return node;
	}

public:
	static const size_t DEFAULT_SIZE = 17;

	UnorderedMap() : _table(new Node *[DEFAULT_SIZE]), _count(DEFAULT_SIZE) {
		for (std::size_t i = 0; i < _count; ++i) {
			_table[i] = nullptr;
		}
	}

	UnorderedMap(const UnorderedMap &) = delete;

	UnorderedMap &operator=(const UnorderedMap &) = delete;

	~UnorderedMap() {
		// clear();
		delete[] _table;
	}

	bool Insert(const TKey& key, const TValue& value) {
		auto node = Find(key);
		if (*node != nullptr) {
			return false;
		}
		*node = new Node(key, value);
		return true;
	}

	bool Contains(const TKey& key) {
		return *Find(key) != nullptr;
	}

	TValue& GetValue(const TKey& key) {
		return (*Find(key))->value;
	}

	bool Remove(const TKey& key) {
		auto node = Find(key);
		if (*node == nullptr) {
			return false;
		}
		auto tmp = *node;
		*node = (*node)->next;
		delete tmp;
		return true;
	}
	void Clear() {
		for (int i = 0; i < _count; ++i) {
			Node* it = _table[i];
			while (it) {
				Node* tmp = it;
				it = it->next;
				delete tmp;
			}
		}
	}
	void Print(std::ostream& out) {
		for (int i = 0; i < _count; ++i) {
			auto it = _table[i];
			out << i << "\t";
			while (it) {
				out << it->key<<":" <<it->value << "\t";
				it = it->next;
			}
			out << endl;
		}
	}
};

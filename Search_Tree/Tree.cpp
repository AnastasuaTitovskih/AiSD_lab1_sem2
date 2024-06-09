#pragma once

#include <iostream>
#include <stdexcept>
#include <random>
#include <functional>

using namespace std;


template<typename T>
struct Node {
	T val;
	Node<T>* left;
	Node<T>* right;

	Node() : val(0), left(nullptr), right(nullptr) {}
	Node(T v) : val(v), left(nullptr), right(nullptr) {}
};

template<typename T>
class Set {
private:
	Node<T>* _root;

	Node<T>* copy(Node<T>* node) {
		if (node) {
			Node<T>* new_node = new Node<T>(node->val);
			new_node->left = copy(node->left);
			new_node->right = copy(node->right);
			return new_node;
		}
		return nullptr;
	}

	void clear(Node<T>* cur) {
		if (!cur) return;

		clear(cur->left);
		clear(cur->right);
		delete cur;
		cur = nullptr;
	}

	void print(Node<T>* cur) {
		if (cur) {
			print(cur->left);
			cout << cur->val << " ";
			print(cur->right);
		}
	}

	
	void add_inter(Node<T>* node, Set<T>& other, Set<T>& set) {
		if (!node) { return; }
		if (other.contains(node->val)) {
			set.insert(node->val);
		}
		add_inter(node->left, other, set);
		add_inter(node->right, other, set);
	}
	void add_diff(Node<T>* node, Set<T>& other, Set<T>& set) {
		if (!node) { return; }
		if (!other.contains(node->val)) {
			set.insert(node->val);
		}
		add_diff(node->left, other, set);
		add_diff(node->right, other, set);
	}

	bool insert(Node<T>*& node, T key) {
		if (!node) {
			node = new Node<T>(key);
			return true;
		}
		if (node->val > key) {
			return insert(node->left, key);
		}
		else if (node->val < key) {
			return insert(node->right, key);
		}
		return false;
	}

	bool contains(Node<T>* node, T key) {
		if (!node) return false;

		if (node->val > key) return contains(node->left, key);

		else if (node->val < key) return contains(node->right, key);

		return true;
	}

	bool erase(Node<T>*& node, T key) {
		if (!node) return false;

		if (node->val > key) return erase(node->left, key);

		else if (node->val < key) return erase(node->right, key);
		else {
			if (!node->left || !node->right) {
				Node<T>* tmp = node;
				node = (node->left) ? node->left : node->right;
				delete tmp;
			}
			else {
				Node<T>* tmp = node->right;
				while (tmp->left) tmp = tmp->left;
				node->val = tmp->val;
				erase(node->right, tmp->val);
			}
			return true;
		}
	}

public:
	Set() : _root(nullptr) {}

	Set(const Set<T>& other) {
		_root = copy(other._root);
	}

	~Set() {
		clear(_root);
		_root = nullptr;
	}

	Set<T>& operator = (Set<T> other) {
		swap(_root, other._root);
		return *this;
	}

	
	void print() {
		print(_root);
		cout << endl;
	}

	bool insert(T key) {
		return insert(_root, key);
	}

	bool contains(T key) {
		return contains(_root, key);
	}

	bool erase(T key) {
		return erase(_root, key);
	}

	
	Set<T> set_inter(Set<T>& other) {
		Set<T> set;
		add_inter(_root, other, set);
		return set;
	}
	Set<T> set_diff(Set<T>& other) {
		Set<T> set;
		add_diff(_root, other, set);
		add_diff(other._root, *this, set);
		return set;
	}
};

int random(int a, int b) {
	random_device random_device;
	mt19937 generator(random_device());
	uniform_int_distribution<> segment(a, b);
	int x = segment(generator);
	return x;
}

int random_seed(int a, int b, int seed) {
	mt19937 generator(seed);
	uniform_int_distribution<> segment(a, b);
	int x = segment(generator);
	return x;
}


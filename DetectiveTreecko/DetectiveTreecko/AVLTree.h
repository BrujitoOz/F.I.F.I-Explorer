#pragma once
#define max(a,b) (a > b ? a : b) 
#include <functional>
#include <vector>
#include <string> 
using namespace std;
typedef unsigned int uint;
typedef long long int li;
template<typename T>
struct Node {
	T Elem;
	li h;
	li n;
	Node<T>* left;
	Node<T>* right;
	Node(T Elem) : Elem(Elem), h(0), n(1), left(nullptr), right(nullptr) {}
};
template<typename T, typename Comparable = T, T NONE = 0>
class AVLTree {
	Node<T>* root;
	function<Comparable(T)> Key; 
	void Destroy(Node<T>* node) {
		if (node != nullptr) {
			Destroy(node->left);
			Destroy(node->right);
			delete node;
		}
	}
	li Height(Node<T>* node) { return node == nullptr ? -1 : node->h; }
	li Lenght(Node<T>* node) { return node == nullptr ? 0 : node->n; }
	void UpdateHeight(Node<T>* node) {
		node->h = 1 + max(Height(node->left), Height(node->right));
		node->n = 1 + Lenght(node->left) + Lenght(node->right);
	}
	Node<T>* RotLeft(Node<T>* node) {
		Node<T>* NodeAux = node->right;
		node->right = NodeAux->left;
		NodeAux->left = node;
		UpdateHeight(NodeAux->left);
		UpdateHeight(NodeAux);
		return NodeAux;
	}
	Node<T>* RotRight(Node<T>* node) {
		Node<T>* NodeAux = node->left;
		node->left = NodeAux->right;
		NodeAux->right = node;
		UpdateHeight(NodeAux->right);
		UpdateHeight(NodeAux);
		return NodeAux;
	}
	Node<T>* Balance(Node<T>* node) {
		li hl = Height(node->left);
		li hr = Height(node->right);
		if (hl - hr > 1) {
			if (Height(node->left->right) > Height(node->left->left)) {
				node->left = RotLeft(node->left);
			}
			node = RotRight(node);
		}
		else if (hl - hr < -1) {
			if (Height(node->right->left) > Height(node->right->right)) {
				node->right = RotRight(node->right);
			}
			node = RotLeft(node);
		}
		else {
			UpdateHeight(node);
		}
		return node;
	}
	Node<T>* Add(Node<T>* node, T Elem) {
		if (node == nullptr) {
			node = new Node<T>(Elem);
		}
		else {
			if (Key(Elem) < Key(node->Elem)) {
				node->left = Add(node->left, Elem);
			}
			else {
				node->right = Add(node->right, Elem);
			}
			node = Balance(node);
		}
		return node;
	}
	T Find(Node<T>* node, Comparable val) {
		if (node == nullptr) {
			return NONE;
		}
		else if (val == Key(node->Elem)) {
			return node->Elem;
		}
		else if (val < Key(node->Elem)) {
			return Find(node->left, val);
		}
		else {
			return Find(node->right, val);
		}
	}
	void findStarWith(Node<T>* node, Comparable val, function<bool(T, string)> op, vector<T> *list) {
		if (node == nullptr) {
			return;
		}
		else if (op(node->Elem, val)) {
			list->push_back(node->Elem);
			findStarWith(node->left, val, op, list);
			findStarWith(node->right, val, op, list);
		}
		else if (val < Key(node->Elem)) {
			findStarWith(node->left, val,op,list);
		}
		else {
			findStarWith(node->right, val, op, list);
		}
	}
	void findContain(Node<T>* node, Comparable val, function<bool(T, string)> op, vector<T>* list) {
		if (node == nullptr) {
			return;
		}
		else if (op(node->Elem, val)) {
			list->push_back(node->Elem);
		}
		findContain(node->left, val, op, list);
		findContain(node->right, val, op, list);
	}
	void Comp(Node<T>* node, Comparable val, function<bool(T, double)> op, vector<T> *list) {
		if (node == nullptr) {
			return;
		}
		else if (op(node->Elem, val)) {
			list->push_back(node->Elem);
			Comp(node->left, val, op, list);
			Comp(node->right, val, op, list);
		}
		else if (val < Key(node->Elem)) {
			Comp(node->left, val, op, list);
		}
		else {
			Comp(node->right, val, op, list);
		}
	}
	void Comp2(Node<T>* node, Comparable val, function<bool(T, string)> op, vector<T> *list) {
		if (node == nullptr) {
			return;
		}
		else if (op(node->Elem, val)) {
			list->push_back(node->Elem);
			Comp2(node->left, val, op, list);
			Comp2(node->right, val, op, list);
		}
		else if (val < Key(node->Elem)) {
			Comp2(node->left, val, op, list);
		}
		else {
			Comp2(node->right, val, op, list);
		}
	}
	void preorder(Node<T>* node, function<void(T)> proc) {
		if (node != nullptr) {
			proc(node->Elem);
			preorder(node->left, proc);
			preorder(node->right, proc);
		}
	}
	void postorder(Node<T>* node, function<void(T)> proc) {
		if (node != nullptr) {
			postorder(node->left, proc);
			postorder(node->right, proc);
			proc(node->Elem);
		}
	}
	void inorder(Node<T>* node, function<void(T)> proc) {
		if (node != nullptr) {
			inorder(node->left, proc);
			proc(node->Elem);
			inorder(node->right, proc);
		}
	}
	void reversedInorder(Node<T>* node, function<void(T)> proc) {
		if (node != nullptr) {
			reversedInorder(node->right, proc);
			proc(node->Elem);
			reversedInorder(node->left, proc);
		}
	}
public:
	AVLTree(function<Comparable(T)> Key = [](T a) {return a; }) : root(nullptr), Key(Key) {}
	~AVLTree() { Destroy(root); }
	void Add(T Elem) { root = Add(root, Elem); }
	T Find(Comparable val) { return Find(root, val); }
	bool Remove(Comparable val) {
		Node<T>* NodeAux = root;
		Node<T>* Parent;
		bool Left;
		while (NodeAux != nullptr) {
			if (val == key(NodeAux->Elem)) {
				break;
			}
			Parent = NodeAux;
			if (val < key(aux->Elem)) {
				Left = true;
				NodeAux = NodeAux->left;
			}
			else {
				Left = false;
				NodeAux = NodeAux->right;
			}
		}
		if (NodeAux == nullptr) {
			return false;
		}
		if (NodeAux->left == nullptr) {
			if (NodeAux == root) {
				root = NodeAux->right;
			}
			else if (Left) {
				Parent->left = NodeAux->right;
			}
			else {
				Parent->right = NodeAux->right;
			}
			delete NodeAux;
		}
		else {
			Node<T>* NodeAux2 = NodeAux->left;
			while (NodeAux2->right != nullptr) {
				Parent = NodeAux2;
				NodeAux2 = NodeAux2->right;
			}
			if (NodeAux2 == NodeAux2->left) {
				NodeAux->left = NodeAux2->left;
			}
			else {
				Parent->right = NodeAux2->left;
			}
			NodeAux->Elem = NodeAux2->Elem;
			delete NodeAux2;
		}
		delete NodeAux;
		return true;
	}
	vector<T>* findStarWith(Comparable val, function<bool(T, Comparable)> op) {
		vector<T> *result = new vector<T>();
		findStarWith(root, val, op, result);
		return result;
	}
	vector<T>* findContain(Comparable val, function<bool(T, Comparable)> op) {
		vector<T>* result = new vector<T>();
		findContain(root, val, op, result);
		return result;
	}
	vector<T>* Comp(Comparable val, function<bool(T, Comparable)> op) { 
		vector<T> *result2 = new vector<T>();
		Comp(root, val, op, result2);
		return result2;
	}
	vector<T>* Comp2(Comparable val, function<bool(T, Comparable)> op) { 
		vector<T> *result66 = new vector<T>();
		Comp2(root, val, op, result66);
		return result66;
	}
	li Size() { return Lenght(root); }
	li Height() { return Height(root); }
	void preorder(function<void(T)> proc) { preorder(root, proc); }
	void postorder(function<void(T)> proc) { postorder(root, proc); }
	void inorder(function<void(T)> proc) { inorder(root, proc); }
	void reversedInorder(function<void(T)> proc) { reversedInorder(root, proc); }
};
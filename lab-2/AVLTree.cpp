#include <vector>
#include <iostream>

using namespace std;
template <typename T>
class AVLTree{
struct Node // структура для представления узлов дерева
{
	T _key;
	Node* _left;
	Node* _right;
	int _height;	
	Node(T& k):_key(k),_left(nullptr),_right(nullptr),_height(1) {}
};
Node* _root;

void Destroy(Node* root) {
	if (root != nullptr)
	{
		if (root->_right != nullptr) {
			Node* r = root->_right;
			Destroy(r);
		}
		if (root->_left != nullptr) {
			Node* l = root->_left;
			Destroy(l);
		}
		delete root;
		root = nullptr;
	}
}
uint8_t GetHeiht(Node* p)
{
	return p ? p->_height : 0;
}
int GetBalance(Node* p)
{
	return GetHeiht(p->_right) - GetHeiht(p->_left);
}
void UpdateHeight(Node* p)
{
	unsigned char hl = GetHeiht(p->_left);
	unsigned char hr = GetHeiht(p->_right);
	p->_height = (hl > hr ? hl : hr) + 1;
}
Node* RotateRight(Node* p) // правый поворот вокруг p
{
	Node* q = p->_left;
	p->_left = q->_right;
	q->_right = p;
	UpdateHeight(p);
	UpdateHeight(q);
	return q;
}
Node* RotateLeft(Node* q) // левый поворот вокруг q
{
	Node* p = q->_right;
	q->_right = p->_left;
	p->_left = q;
	UpdateHeight(q);
	UpdateHeight(p);
	return p;
}
Node* balance(Node* p) // балансировка узла p
{
	UpdateHeight(p);
	if (GetBalance(p) == 2)
	{
		if (GetBalance(p->_right) < 0)
			p->_right = RotateRight(p->_right);
		return RotateLeft(p);
	}
	if (GetBalance(p) == -2)
	{
		if (GetBalance(p->_left) > 0)
			p->_left = RotateLeft(p->_left);
		return RotateRight(p);
	}
	return p; // балансировка не нужна
}
Node* findmin(Node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->_left ? findmin(p->_left) : p;
}
Node* removemin(Node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->_left == 0)
		return p->_right;
	p->_left = removemin(p->_left);
	return balance(p);
}

Node* find(T key, Node* p) {
	if (p == nullptr) return nullptr;
	if (key < p->_key) return find(key, p->_left);
	if (key > p->_key) return find(key, p->_right);
	else return p;
}
Node* insert(T k, Node* p) // вставка ключа k в дерево с корнем p
{
	if (!p) return new Node(k);
	if (k < p->_key)
		p->_left = insert(k, p->_left);
	else {
		if (k > p->_key) {
			p->_right = insert(k, p->_right);
		}
	}
	return balance(p);
}
Node* remove(T k, Node* p) // удаление ключа k из дерева p
{

	if (!p) return 0;
	if (k < p->_key)
		p->_left = remove(k, p->_left);
	else if (k > p->_key)
		p->_right = remove(k, p->_right);
	else //  k == p->key 
	{
		Node* q = p->_left;
		Node* r = p->_right;
		delete p;
		if (!r) return q;
		Node* min = findmin(r);
		min->_right = removemin(r);
		min->_left = q;
		return balance(min);
	}
	return balance(p);
}

void print( int level, Node* p, std::ostream& out)
{
	if (p)
	{
		print(level + 1, p->_right,out);
		for (int i = 0; i < level; i++) cout << "   ";
		out << p->_key << endl;
		print(level + 1,p->_left,out);
	}
}
public:

AVLTree() :_root(nullptr) {}
AVLTree(const AVLTree& tr) = delete;
AVLTree& operator=(const AVLTree& tr) = delete;
~AVLTree() {
	Destroy(_root);
}

void insert(const T& k) {
	_root = insert(k, _root);
}
bool find(const T& k) {
	return find(k, _root) != nullptr;
}
void remove(const T& k) {
	auto f = find( k,_root);
	if (f) remove(k, _root);
}
void print(std::ostream& out) {
	print(0, _root,out);
}
};

#include <vector>
#include <iostream>

using namespace std;
template<typename T>
struct Node {
	T _data;
	Node* _next;
	Node(): _data(0), _next(nullptr){}
	Node(const T data): _data(data), _next(nullptr) {}
};

template<typename T>
class IteratorUnordSet {
	typename vector<Node<T>*>::iterator _it;
	
public:
	IteratorUnordSet() :_it(nullptr) {} 
	IteratorUnordSet(const IteratorUnordSet<T>& iterator) :_it(iterator._it) {} 
	IteratorUnordSet(typename vector<Node<T>*>::iterator it) { 
		_it = it; 
	}

	IteratorUnordSet<T>& operator++() {
		_it++;
		return *this;
	}
	

	Node<T>& operator*() {
		return *(*_it);
	}
	Node<T>& operator*()const {
		return *(*_it);
	}
	typename vector<Node<T>*>::iterator operator&()const {
		return _it;
	}


	bool operator==(IteratorUnordSet<T> iterator) {

		 if( _it==iterator._it ) return true;
		 return false;
	}
	bool operator!=(IteratorUnordSet<T> iterator) {
		return !(*this == iterator);
	}

	bool operator==(std::nullptr_t null) {
		if(_it==nullptr ) return true; 
		return false;
	}
	bool operator!=(std::nullptr_t null) {
		return !(this == nullptr);
	}
	bool operator<( IteratorUnordSet<T> iterator){
		 if(_it < iterator._it )return true; 
		 return false;
	}
	bool operator>( IteratorUnordSet<T> iterator) {
		return !(*this < iterator || *this == iterator);
	}
	
	IteratorUnordSet<T> operator+=(int ind) {		
		if (!this) return *this;
		for (int i = 0; i < ind; ++i) {
			(*this)._it++;
		}
		return *this;
	}	
	
	IteratorUnordSet<T> operator+( int ind) {	
		*this->_it += ind;
		return *this;
	}

};








template<typename T>
int HashFunction(T k)
{
	return (k % 10);
}
template<typename T>
bool CompareFunc(T a, T b, int(*_hash)(T)) {
	return _hash(a) == _hash(b);
}

template<typename T>
class UnorderedSet {
	

	size_t _bucketCount;
	vector<Node<T>*> _arr;
	int(*_hash)(T);
	bool(*_comp)(T, T, int(*_hash)(T));
public:
	
	UnorderedSet(int bucketCount) :_bucketCount(10), _arr(vector<Node<T>*>(10)), _hash(HashFunction), _comp(CompareFunc) {}
	UnorderedSet(vector<T>& vec):_bucketCount(10), _arr(vector<Node<T>*>(10)), _hash(HashFunction), _comp(CompareFunc){								
		auto beg(vec.begin());		
		while (beg != vec.end()) {
			insert(*beg);			
			beg++;
		}		
	}
	~UnorderedSet() {
		clear();
	}

	UnorderedSet(UnorderedSet<T>& un) :_bucketCount(un._bucketCount), _arr(vector<Node<T>*>(un._arr)), _hash(un._hash), _comp(un._comp) {}
	UnorderedSet<T>& operator=(UnorderedSet<T>& un) {
		if (this == &un) return *this;
		_arr.~vector();
		_bucketCount = un._bucketCount;
		_arr = un._arr;
		_hash = un._hash;
		_comp = un._comp;
		vector<Node<T>*> _arr = vector<Node<T>*>(un._arr);
	}

	int getSize() {
		return (int)_bucketCount;
	}
	void clear() {
		_bucketCount = 0;
		_arr.~vector();
		_hash = nullptr;
		_comp = nullptr;
	}
	int bucketSize(IteratorUnordSet<T> it) {
		if (*it == nullptr) return 0;
		Node<T> el = *it;
		int count = 1;
		
		while (el._next != nullptr) {
			el = el._next;
			count++;
		}
		return count;
	}

	IteratorUnordSet<T> begin(){
		return IteratorUnordSet<T>(_arr.begin());  
	}
	IteratorUnordSet<T> end(){
		 IteratorUnordSet<T> res(_arr.end());  
		 return res;
	}

	void insert(T ins) {
		
		int ind = _hash(ins);
		if (_arr[ind] == nullptr) {
			_arr[ind] = new Node<T>(ins);
		}
		else {
			bool in = true;
			Node<T>* ptrNode = _arr[_hash(ins)];
			while (ptrNode->_next != nullptr) {
				if (ptrNode->_data == ins) in = false;
				ptrNode = ptrNode->_next;
			}
			if(in && ptrNode->_data != ins) ptrNode->_next = new Node<T>(ins);
		}
	}
	IteratorUnordSet<T> find(T f) {
		typename vector<Node<T>*>::iterator beg = &begin();
		Node<T>* fZap = _arr[_hash(f)];		
		while (fZap != nullptr) {
			if (f == fZap->_data) return beg+ _hash(f);
			fZap = fZap->_next;
		}
		return end();
	}
	void remove(T rem) {
		Node<T>* zap = new Node<T>(rem);
		IteratorUnordSet<T> end=this->end();
		IteratorUnordSet<T> f = find(rem);
		if (f == this->end()) return;
		Node<T>* prev = &(*f);
		Node<T>* rZap = &(*f);
		while (rZap != nullptr) {
			if (rZap->_data == rem) {
				if (rZap == &(*f)) *f = *(rZap)->_next;
				else {
					if (rZap->_next == nullptr) prev->_next = nullptr;					
					else prev->_next = rZap->_next;					
				}
				delete rZap;
				return;
			}
				prev = rZap;
				rZap = rZap->_next;
		}


	}
	void print(std::ostream& out)const {
		for (int i = 0; i < _arr.size();++i) {
			Node<T>* node = _arr[i];
			while (node != nullptr) {
				out << node->_data << " ";
				node = node->_next;
			}
			out << endl;
		}

	}
};

template<typename T>
bool operator==(UnorderedSet<T>& un1, UnorderedSet<T>& un2) {
	if (un1.getSize() != un2.getSize()) return false;
	IteratorUnordSet<T> iterator1(un1.begin());
	IteratorUnordSet<T> iterator2(un2.begin());
	while (iterator1 != un1.end()) {
		if (&(iterator1.operator*) != &(iterator2.operator*)) return false;
		else {
			++iterator1;
			++iterator2;
		}
	}
	return true;

};
template<typename T>
bool operator!=(UnorderedSet<T>& un1, UnorderedSet<T>& un2) {
	return !(un1 == un2);
}


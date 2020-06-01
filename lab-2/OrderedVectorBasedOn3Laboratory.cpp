#include <vector>
//#include "..\lab-1\Sort.cpp"
#include <iostream>
using namespace std;


template<class Iterator>
void user_swap(Iterator it1, Iterator it2) {
	auto bucket = *it1;
	*it1 = *it2;
	*it2 = bucket;
}

template< class Iterator>
void QuickSort(Iterator begin, Iterator end) {
	if (end - begin == 1) {// при условии, когда между end и begin останется 1 элемент(условие нужно для ситуации, когда уже нельзя выбрать опорный элемент, так как всего 2 свободных),
						   //сравниваем begin и begin+1 и при необходимости меняем
		if (*(end - 1) < *begin) user_swap(begin, end - 1);
		return;
	}
	auto pivot = begin;// выбираем опорный элемент, в нашем случае - это первый элемент
	auto r = end - 1;// так как в первый вызов вункции передаётся элемент за последним
	auto l = begin;

	while (r >= l) {// повторяем до тех пор, пока r не зайдёт за l
		while (*r >= *pivot && r > begin) --r;// двигаемся справа налево и останавливаемся на элементе меньшим, чем pivot
		while (*l <= *pivot && l < end - 1) ++l;// двигаемся слева направо и останавливаемся на элементе большем, чем pivot
		if (r > l) user_swap(l, r);// меняем найденные элементы местами
		if (r == l) break;// условие прекращения while (когда уже не нужно будет ничего менять)
	}
	user_swap(r, pivot);//меняем местами самый правый элемент из тех, что меньше pivot с самим pivot
	if (begin < r)
		QuickSort(begin, r);// запускакем рекурсию начиная от начала, до опорного элемента
	if (end > r + 1)
		QuickSort(r + 1, end);// запускакем рекурсию начиная от опорного элемента невключительно до конца
}

template<typename Node>
class IteratorV final {
	Node* _node;
public:
	IteratorV() :_node(nullptr) {}
	IteratorV(const IteratorV<Node>& iterator) :_node(iterator._node) {}
	IteratorV(Node* const  node) :_node(node) {}

	IteratorV<Node>& operator++() {
		_node++;
		return *this;
	}
	IteratorV<Node>& operator--() {
		_node--;
		return *this;
	}
	IteratorV<Node> operator++(int) {
		IteratorV<Node> prev(*this);
		_node++;
		return prev;
	}
	IteratorV<Node> operator--(int) {
		IteratorV<Node> next(*this);
		_node--;
		return next;
	}

	Node& operator*() {
		return *_node;
	}
	Node& operator*()const {
		return *_node;
	}

	bool operator==(const IteratorV<Node>& iterator)const {
		return _node == iterator._node;
	}
	bool operator!=(const IteratorV<Node>& iterator)const {
		return _node != iterator._node;
	}
	bool operator==(std::nullptr_t null)const {
		return _node == null;
	}
	bool operator!=(std::nullptr_t null)const {
		return !(this == nullptr);
	}

	bool operator<(const IteratorV<Node>& iterator)const {
		return _node < iterator._node;
	}
	bool operator>(const IteratorV<Node>& iterator)const {
		return !(_node < iterator._node || _node == iterator._node);
	}
	bool operator>=(const IteratorV<Node>& iterator)const {
		return (_node > iterator._node || _node == iterator._node);
	}
	bool operator<=(const IteratorV<Node>& iterator)const {
		return (_node < iterator._node || _node == iterator._node);
	}

};

template<typename Node>// Операция begin() + index ругалась на то, что не сушествует операции для левостороннего зачения IteratorV<Node>, решил убрав в определении ф & 
IteratorV<Node> operator+(IteratorV<Node> iterator, const int ind) {
	IteratorV<Node> iter(iterator);
	iter += ind;
	return  iter;
}
template<typename Node>
IteratorV<Node> operator+=(IteratorV<Node>& it, const int num) {
	if (it == nullptr) {
		return it;
	}

	for (int i = 0; i < num; ++i) {
		it++;
	}

	return it;
}
template<typename Node>
IteratorV<Node> operator-(IteratorV<Node>& iterator, const int ind) {
	IteratorV<Node> iter(iterator);
	iter -= ind;
	return  iter;
}
template<typename Node>
IteratorV<Node> operator-=( IteratorV<Node>& it, const int ind) {
	if (it == nullptr) {
		return it;
	}

	for (int i = 0; i < ind; ++i) {
		it--;
	}

	return it;
}
template<typename Node>
int operator-(const IteratorV<Node> iterator1, const IteratorV<Node>& iterator2) {
	IteratorV<Node> itb;
	IteratorV<Node> ite;
	bool f = false;
	if (iterator1 > iterator2) {
		ite = iterator1;
		itb = iterator2;
	}
	else {
		if (iterator1 < iterator2) {
			itb = iterator1;
			ite = iterator2;
			f = true;
		}
		else return 0;
	}
	int count = 0;
	while (1) {
		if (itb == ite) {
			if(!f) return count;
			else return -count;
		}
		++itb;
		++count;
	}	
}


template<typename Node>
class OrderedVector {
	Node* _ptr;
	size_t _size;

	void sort() {
		QuickSort(this->begin(), this->end());
	}
	IteratorV<Node> insertS(IteratorV<Node>& it, const Node& node) {
		if (it == nullptr&&this == nullptr)
		{
			return it;
		}
		IteratorV<Node>iter(it);
		if (it > end() || it < begin()) throw"Ошибка вставки";
		OrderedVector res(new Node[_size + 1], (int)_size + 1);
		IteratorV<Node> counter = begin();
		int index = 0;
		for (; counter != iter; ++counter)
		{
			++index;
		}
		int counterInt = 0;
		for (auto i = 0; i < _size + 1; ++i) {
			if (i != index) {
				res[i] = _ptr[counterInt];
				counterInt++;
			}
			else
				res[i] = node;
		}
		*this = res;
		it = begin() + index;
		return it;
	}

public:
	 OrderedVector()noexcept :_ptr(nullptr), _size(0) {}
	 OrderedVector(Node* OrderedVector, const int size) :_ptr(OrderedVector), _size(size) {}
	 OrderedVector(const int size) {
		_size = size;
		_ptr = new Node[_size];
	 }	 
	 OrderedVector(vector<Node>& v) {
		 _size = v.size();
		 _ptr = new Node[_size];
		 for (int i = 0; i < _size; ++i) {
			 _ptr[i] = v[i];
		 }
		 sort();
	 }

	~OrderedVector() {
		clear();
	}

	OrderedVector(const OrderedVector<Node>& OrderedVector) :_ptr(new Node[OrderedVector._size]), _size(OrderedVector._size) {
		for (int i = 0; i < _size; ++i) {
			_ptr[i] = OrderedVector._ptr[i];
		}
	}
	OrderedVector<Node>& operator=(const OrderedVector<Node>& OrderedVector){
		if (this == &OrderedVector) return *this;
		if (_ptr) delete _ptr;
		_ptr = new Node[OrderedVector._size];
		_size = OrderedVector._size;
		for (int i = 0; i < _size; ++i) {
			_ptr[i] = OrderedVector._ptr[i];
		}
		return *this;
	}

	OrderedVector(OrderedVector<Node>&& tOrderedVector) :_ptr(tOrderedVector._ptr), _size(tOrderedVector._size) {
		tOrderedVector._ptr = nullptr;
		tOrderedVector._size = 0;
	}
	OrderedVector<Node>& operator=(OrderedVector<Node>&& tOrderedVector) {
		if (_ptr) delete _ptr;
		_ptr = tOrderedVector._ptr;
		_size = tOrderedVector._size;
		tOrderedVector._ptr = nullptr;
		tOrderedVector._size = 0;
	}


	Node& at(const int ind) {
		if (ind >= _size || ind < 0) throw"Ошибка доступа к элементу";
	}
	Node& at(const int ind)const {
		if (ind >= _size || ind < 0) throw"Ошибка доступа к элементу";
	}

	Node& operator[](const int ind) {
		return _ptr[ind];
	}
	Node& operator[](const int ind)const {
		return _ptr[ind];
	}

	Node& front() {
		return _ptr[0];
	}

	Node& back() {
		return _ptr[_size - 1];
	}

	Node* data()const {
		if (_ptr) return &front;
		else return nullptr;
	}

	IteratorV<Node> begin()const{
		return IteratorV<Node>(_ptr);
	}

	IteratorV<Node> end()const{
		return IteratorV<Node>(_ptr + _size);
	}

	bool empty()const noexcept {
		if (begin() == end()) return true;
		else return false;
	}

	size_t size()const noexcept {
		return _size;

	}

	void clear() noexcept {
		delete[] _ptr;
		_ptr = nullptr;
		_size = 0;
	}

	void insert(Node ins) {
		IteratorV<Node> beg = begin();
		IteratorV<Node> end = this->end();
		IteratorV<Node> middle = beg + (_size / 2);
		while (beg != end - 1) {
			if (*middle >= ins) {
				if (middle - 1 == beg) {
					insertS(beg, ins);
					return;
				}
				else if (*(middle - 1) <= ins) {
					insertS(middle, ins);
					return;
				}

			}
			else if (*middle <= ins) {
				if (middle == end - 1) {
					insertS(end, ins);
					return;
				}
				else if (*(middle + 1) >= ins) {
					insertS(*&(middle + 1), ins);
					return;
				}
			}

			if (*middle < ins) {
				beg = middle;
				middle += (end - beg) / 2;
			}
			else {
				if (*middle > ins) {
					end = middle;
					middle -= (end - beg) / 2;
				}
			}
		}
	}

	IteratorV<Node> erase(IteratorV<Node>& it) {
		if (begin() == end()) throw "Ошибка удаления элемента";
		OrderedVector<Node> res(new Node[_size - 1], (int)_size - 1);
		IteratorV<Node> counter = begin();
		int ind = 0;
		while (counter != end() && counter!=it) {
			counter++;
			ind++;
		}
		for (int i = 0; i < ind; ++i) {
			res._ptr[i] = _ptr[i];
		}
		if (counter != end()) {
			for (int i = ind+1; i < _size; ++i) {
				res._ptr[i-1] = _ptr[i];
			}
			*this = res;
			return counter++;
		}
		else {
			*this = res;
			return end();
		}
	}
	
	void print(std::ostream& out)const {
		for (int i = 0; i < _size;++i) {
			out << _ptr[i] << " ";
		}
		out << endl;
	}

	void remove(Node rem) {
		auto rez = this->find(rem);
		if (rem == *(rez)) this->erase(rez);
	}

	IteratorV<Node> find(Node f) {
		auto beg = this->begin();
		auto end = this->end();
		auto middle = beg + (_size/ 2);
		while (beg <= end) {
			if (*middle < f) {
				beg = middle;
				middle += (end - beg) / 2;
			}
			else {
				if (*middle > f) {
					if (*(middle - 1) == f) return middle - 1;
					end = middle;
					middle -= (end - beg) / 2;
				}
				else return middle;
			}
		}
		return this->end();
	}
};

template<typename Node>
bool operator==(const OrderedVector<Node> OrderedVector1, const OrderedVector<Node> OrderedVector2) {
	if (OrderedVector1.size() != OrderedVector2.size()) return false;
	IteratorV<Node> iterator1(OrderedVector1.begin());
	IteratorV<Node> iterator2(OrderedVector2.begin());
	while (iterator1 != OrderedVector1.end()) {
		if (*iterator1 != *iterator2) return false;
		else {
			iterator1++;
			iterator2++;

		}
	}
	return true;
}
template<typename Node>
bool operator!=(const OrderedVector<Node> OrderedVector1, const OrderedVector<Node> OrderedVector2) {
	return OrderedVector1 == OrderedVector2;
}
template<typename Node>
bool operator>(const OrderedVector<Node> OrderedVector1, const OrderedVector<Node> OrderedVector2) {
	IteratorV<Node> start;
	IteratorV<Node> finish;
	if (OrderedVector1._size > OrderedVector2._size) {
		start=OrderedVector1.begin();
		finish=OrderedVector1.end();
	}
	else {
		start=OrderedVector2.begin();
		finish=OrderedVector2.end();
	}
	IteratorV<Node> iterator1(OrderedVector1.begin());
	IteratorV<Node> iterator2(OrderedVector2.begin());
	while (start != finish) {
		if (iterator1 > iterator2) return true;
		iterator1++;
		iterator2++;
	}
	return false;
}
template<typename Node>
bool operator<(const OrderedVector<Node> OrderedVector1, const OrderedVector<Node> OrderedVector2) {
	return !(OrderedVector1 > OrderedVector2);
}
template<typename Node>
bool operator>=(const OrderedVector<Node> OrderedVector1, const OrderedVector<Node> OrderedVector2) {
	return (OrderedVector1 > OrderedVector2 || OrderedVector1 == OrderedVector2);
}
template<typename Node>
bool operator<=(const OrderedVector<Node> OrderedVector1, const OrderedVector<Node> OrderedVector2) {
	return (OrderedVector1 < OrderedVector2 || OrderedVector1 == OrderedVector2);
}


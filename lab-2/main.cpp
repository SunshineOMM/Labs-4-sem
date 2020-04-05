#include<iostream>
#include <vector>

#include "AVLTree.cpp"
#include "OrderedVectorBasedOn3Laboratory.cpp"
#include "UnorderedSet.cpp"



void printTestName(const char* s) {
	for (int i = 0; i < 100; ++i) {
		cout << '=';
	}
	cout << endl;
	cout << "\t\t\t\t\t\t\t Test " << s;
	cout << endl;
	for (int i = 0; i < 100; ++i) {
		cout << '=';
	}
	cout << endl;
}

template<typename T>
void printStdVector(vector<T> v, const char* name) {
	cout << name << " =  ";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << endl;
}

int main() {
	//===============================================================================================================================================
	//																Тест UnorderedSet		
	//===============================================================================================================================================

	printTestName("UnorderedSet");

	vector<int> v1 = { 0,1,2,3,4,5,6,7,8,9,11,13,15,17,19,6 };
	UnorderedSet<int> un1(v1);
	un1.print(cout);
	cout << endl;

	un1.insert(99);
	un1.print(cout);
	cout << endl;

	un1.remove(99);
	un1.print(cout);
	cout << endl;

	//===============================================================================================================================================
	//																Тест OrderedVector		
	//===============================================================================================================================================
	printTestName("OrderedVector");
	vector<char> v2 = { 'f','j','h','b','k','r','m','g','h','t' };
	printStdVector(v2, "vc");

	OrderedVector<char> ov(v2);
	OrderedVector<char> ov2(v2);

	cout << "ov=ov2 =" << (ov == ov2) << endl;
	cout << endl;

	cout << "ov=";
	ov.print(cout);
	cout << endl;

	cout << "Testing remove" << endl;
	ov.remove('b');
	ov.print(cout);

	ov.remove('k');
	ov.print(cout);

	ov.remove('t');
	ov.print(cout);

	cout << "Testing insert" << endl;
	ov.insert('a');
	ov.print(cout);

	ov.insert('g');
	ov.print(cout);

	ov.insert('z');
	ov.print(cout);

	cout << "ov!=ov2 =" << (ov != ov2) << endl;

	//===============================================================================================================================================
	//																Тест AVLTree		
	//===============================================================================================================================================
	printTestName("AVLTree");

	vector<int> v3 = { 0,1,2,3,4,5,6,7,8,9,11,13,15,17,19,6 };
	AVLTree<int> a;
	for (int i = 0; i < v3.size(); ++i) {
		a.insert(v3[i]);
	}
	a.print(cout);

	cout << "insert 99" << endl;
	a.insert(99);
	a.print(cout);

	cout << "insert 99" << endl;
	a.insert(99);
	a.print(cout);

	cout << "remove 99" << endl;
	a.remove(99);
	a.print(cout);
	system("PAUSE");
}
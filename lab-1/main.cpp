#define _CRT_SECURE_NO_WARNINGS
#include <chrono> 
#include<iostream>
#include "Sort.cpp"


int main(){

//===============================================================================================================================================
//																Тест Сортировок		
//===============================================================================================================================================

typedef void(*pfn_MyFuncType)(typename vector<int>::iterator, typename vector<int>::iterator);
vector<pfn_MyFuncType> func = { SortByCelection ,BubbleSort ,ShellSort ,QuickSort };
for (int f = 0; f < 5; ++f) {
	cout << f << endl;
	for (int l = 0; l < 100; ++l) {
		cout << "-";
	}
	cout << endl;
	for (int n = 100; n < 6000; n = n + 1000) {

		vector<int> Arr(n);
		for (int i = 0; i < n; ++i) {
			Arr[i] = rand() % 100;
		}
		cout << "n=" << n << endl;


		auto start = chrono::high_resolution_clock::now();


		func[f](Arr.begin(), Arr.end());

		auto finish = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = finish - start;
		cout << "Elapsed time: " << elapsed.count() << " s\n";


		cout << endl;
		cout << endl;
		cout << endl;

	}
}
// NaturalTwoWayMergingSortingKnut сортировка по Кнуту
for (int l = 0; l < 100; ++l) {
	cout << "-";
}
for (int n = 100; n < 6000; n = n + 1000) {
	vector<int> Arr(n);
	for (int i = 0; i < n; ++i) {
		Arr[i] = rand() % 100;
	}

	cout << "n=" << n << endl;


	auto start = chrono::high_resolution_clock::now();


	NaturalTwoWayMergingSortingKnut<typename vector<int>::iterator, int>(Arr.begin(), Arr.end());

	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;
	cout << "Elapsed time: " << elapsed.count() << " s\n";


	cout << endl;
	cout << endl;
	cout << endl;
}

//mergeSort более адекватная
vector<int> v(10);
for (int i = 0; i < v.size(); ++i) {
	v[i] = rand() % 10;
}
for (int i = 0; i < v.size(); ++i) {
	cout << v[i] << " ";
}
cout << endl;


mergeSort(v);


for (int i = 0; i < v.size(); ++i) {
	cout << v[i] << " ";
}
cout << endl;
}
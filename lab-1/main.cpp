#define _CRT_SECURE_NO_WARNINGS
#include <chrono> 
#include<iostream>
#include <string>
#include "Sort.cpp"


int main(){

//===============================================================================================================================================
//																Тест Сортировок		
//===============================================================================================================================================

//typedef void(*pfn_MyFuncType)(typename vector<int>::iterator, typename vector<int>::iterator);
//vector<pfn_MyFuncType> func = { SortByCelection ,BubbleSort ,ShellSort ,QuickSort };
//vector<string> funcName = { "SortByCelection","BubbleSort","ShellSort","QuickSort"};
//for (int f = 0; f < 5; ++f) {
//	cout << funcName[f] << endl;
//	for (int l = 0; l < 100; ++l) {
//		cout << "-";
//	}
//	cout << endl;
//	for (int n = 100; n < 6000; n = n + 1000) {
//
//		vector<int> Arr(n);
//		for (int i = 0; i < n; ++i) {
//			Arr[i] = rand() % 100;
//		}
//		cout << "n=" << n << endl;
//
//
//		auto start = chrono::high_resolution_clock::now();
//
//
//		func[f](Arr.begin(), Arr.end());
//
//		auto finish = chrono::high_resolution_clock::now();
//		chrono::duration<double> elapsed = finish - start;
//		cout << "Elapsed time: " << elapsed.count() << " s\n";
//
//
//		cout << endl;
//		cout << endl;
//		cout << endl;
//
//	}
//}
// NaturalTwoWayMergingSortingKnut сортировка по Кнуту
	cout << "NaturalTwoWayMergingSorting"<<endl;
for (int l = 0; l < 100; ++l) {
	cout << "-";
}
for (int n = 100; n < 6000; n = n + 1000) {
	vector<int> Arr(n);
	for (int i = 0; i < n; ++i) {
		Arr[i] = rand() % 100;
	}

	cout <<endl<< "n=" << n << endl;


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




//===============================================================================================================================================
//																Тест Сортировоки ьинарными вставками	
//===============================================================================================================================================


	/*int a[] = { 6,4,2,967,47,4,834,8,6,42,8 };
	int n = 11;
	for (int i = 0; i < n; ++i) {
		a[i] = rand() % 10;
	}
	for (int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;


	myShakerSort(a,n,cout);


	for (int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;*/


	//===============================================================================================================================================
	//																Тест Шейкерной Сортировоки 		
	//===============================================================================================================================================


    //setlocale(LC_ALL, "rus");

    //int size = 11;
    //int A []={ 6,4,2,967,47,4,834,8,6,42,8 };

    //for (int k = 0; k < size; k++)
    //{
    //    cout << A[k] << " | ";
    //}

    //myShakerSort(A, size,cout); // сортировка

    //cout << "\nМассив после сортировки:\n";
    //for (int k = 0; k < size; k++)
    //{
    //    cout << A[k] << " | ";
    //}
    //cout << endl;


}
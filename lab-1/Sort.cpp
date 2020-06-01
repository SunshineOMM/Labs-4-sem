#include <vector>
#include <iostream>

using namespace std;
template<class Iterator>
void user_swap(Iterator it1, Iterator it2) {
	auto bucket = *it1;
	*it1 = *it2;
	*it2 = bucket;
}

template< class Iterator>
void SortByCelection(Iterator begin, Iterator end) {
	for (auto i = begin; i < end - 1; ++i) {
		Iterator min = i;
		for (Iterator j = i + 1; j < end; ++j)
		{
			if (*j < *min)
				min = j;
		}
		user_swap(min, i);
	}
}

template< class Iterator>
void BubbleSort(Iterator begin, Iterator end) {
	
	for (Iterator i = begin; i < end - 1; ++i) {
		for (Iterator j = begin; j < end - 1; ++j) {
			if (*j > *(j + 1)) user_swap(j, j + 1);
		}
	}
}

template< class Iterator>
void ShellSort(Iterator begin, Iterator end) {

	{
		for (int gap = (end - begin) / 2; gap != 0; gap /= 2)
		{
			for (auto i = begin + gap; i < end; ++i)
			{
				for (auto j = i; j >= begin + gap; j -= gap) {//i=begin+gap
					if (*(j - gap) > *j)
						user_swap(j, j - gap);
				}
			}
		}
	}
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

//Реализация из Кнута 
template<class Iterator, typename T>
void NaturalTwoWayMergingSortingKnut(Iterator begin, Iterator end) {
	bool s = 0;// 1
	vector<T> v(end - begin);
	auto i = begin;
	auto j = end - 1;
	auto k = v.begin();
	auto l = v.end() - 1;
	bool f = 1;
	int d = 1;

	do {//2
		if (s == 0) {
			i = begin;
			j = end - 1;
			k = v.begin();
			l = v.end() - 1;
		}
		else {
			if (s == 1) {
				i = v.begin();
				j = v.end() - 1;
				k = begin;
				l = end - 1;
			}
		}
		f = 1;
		d = 1;
		while (i != j) {//условие на отсев 13 действия
			if (*i > *j) {//3 
				*k = *j;//8
				k += d;
				--j;
				if (*(j + 1) <= *j) {//9
					continue;// переход к 3
				}
				else {
					do {//10
						*k = *i;
						k += d;
						++i;  //11							 												
					} while (*(i - 1) <= *i);
					//12
					f = 0;
					d = -d;
					swap(k, l);
					continue;// переход к шагу 3

				}
			}
			else {//*i < *j   4
				*k = *i;
				k += d;
				++i;// 5
				if (*(i - 1) <= *i) {
					continue;//переход к шагу 3
				}
				else {
					do {//6
						*k = *j;
						k += d;
						--j;
					} while (*(j + 1) <= *j);//7
					f = 0;// 12
					d = -d;
					swap(k, l);
					continue;// переход к шагу 3	 
				}
			}

		}
		if (i == j) {// это всё ещё 3 пункт
			*k = *i;
			if (f == 0) {//13
				s = 1 - s;
				//переход к шагу 2(автоматически)
			}
			if (s == 0) {
				auto be2 = v.begin();
				auto be1 = begin;
				while (be1 != end) {
					auto bucket1 = be1;
					auto bucket2 = be2;
					swap(be1, be2);
					be1 = bucket1;
					be2 = bucket2;
					be1++;
					be2++;
				}
			}
		}

	} while (!f);
}

//Более адекватная

inline void merge(vector<int>& start, vector<int>& result, int& i, int& j, int& k, int& l, int& rb, int& re, bool f) {// функция слияния двух отсортированных массивов (i,j)-индексы левой части массива start
																													  //(k,l)-индексы правой части массива start (rb,re)- индексы результирующего массива 
																													  //f- флаг направления записи в результирующий массив
	if (f) {// эта ветка сработает если нужно записывать в результирующий массив слева направо
		while (i <= j && k <= l) {// слияние массивов, до тех пор пока один не кончится
			if (start[i] >= start[l]) {
				result[rb] = start[l];
				rb++;
				l--;
			}
			else {
				result[rb] = start[i];
				rb++;
				i++;
			}
		}
		for (; i <= j; ++i) {//дозапись оставшегося массива в результирующий
			result[rb] = start[i];
			rb++;
		}
		for (; l >= k; --l) {//дозапись оставшегося массива в результирующий
			result[rb] = start[l];
			rb++;
		}

	}
	else {// а эта, если нужно записывать в результирующий массив справа налево
		while (i <= j && k <= l) {// слияние массивов, до тех пор пока один не кончится
			if (start[i] >= start[l]) {
				result[re] = start[l];
				re--;
				l--;
			}
			else {
				result[re] = start[i];
				re--;
				i++;
			}
		}
		for (; i <= j; ++i) {//дозапись оставшегося массива в результирующий
			result[re] = start[i];
			re--;
		}
		for (; l >= k; --l) {//дозапись оставшегося массива в результирующий
			result[re] = start[l];
			re--;
		}

	}
	j = i;// возврат индексов на исходные позиции
	k = l;
}
inline void sequenceLength(vector<int>& v, int& j, int& k) {// поиск максимальной возрастающей последовательности слева и справа
	while (j<v.size()-1 && v[j] <= v[j + 1]) {
		j++;
	}
	while ( k>0 && j != k - 1 &&v[k] <= v[k - 1]) {
		k--;
	}
}
inline void mergeSort(vector<int>& v) {
	vector<int> helpV(v.size());// формирование вспомогательного массива
	// задание начальных условий
	int rb = 0;
	int re = v.size() - 1;
	int i = 0, j = 0;
	int k = v.size() - 1, l = v.size() - 1;

	//начало большого цикла
	 do{
		 // выставление в исходные позиции значений на каждом проходе цикла
		 i = 0;
		 j = 0;
		 k = v.size() - 1;
		 l = v.size() - 1;
		 rb = 0;
		 re = v.size() - 1;
		 
		 while (j < k) {// повторяем пока в результате слияния не получится полный массив

			 // сливаем в левую часть массива
			 sequenceLength(v, j, k);//подсчёт длины возрастающей последовательности 
			 if (j == l) break;// проверка условия на завершение сортировки(произойдёт когда возрастающая слева последовательность закончится в конце массива)
			 merge(v, helpV, i, j, k, l, rb, re, 1);// слияние
			 
			 if (j >= k) break;// выход при условии, что в результате слияния получился полный массив
			 
			 // сливаем в правую часть массива
			 sequenceLength(v, j, k);
			 if (j == l) break;
			 merge(v, helpV, i, j, k, l, rb, re, 0);			 
			 			 
		 }
		 if (j == l) break;// проверка условия на завершение сортировки(произойдёт когда возрастающая слева последовательность закончится в конце массива)
		std::swap(v, helpV);		
	 } while (j != l);// проверка условия на завершение сортировки(произойдёт когда возрастающая слева последовательность закончится в конце массива)
}


// Для практики
inline void sort_bin_insert_for_practice(int* a, int n) // Сортировка бинарными вставками

{
	int x, left, right, sred;

	for (int i = 1; i < n; i++)

	{

		if (a[i - 1] > a[i])

		{

			x = a[i]; // x – включаемый элемент

			left = 0; // левая граница отсортированной части массива

			right = i - 1; // правая граница отсортированной части массива

			do {

				sred = (left + right) / 2; // sred – новая "середина" последовательности

				if (a[sred] < x) left = sred + 1;

				else right = sred - 1;

			} while (left <= right); // поиск ведется до тех пор, пока левая граница не окажется правее правой границы

			for (int j = i - 1; j >= left; j--) a[j + 1] = a[j];

			a[left] = x;

		}

	}

}

inline void sort_simple_insert(int* m, int n)

{

	int j, r;

	for (int i = 1; i < n; i++)

	{

		r = m[i]; // Запоминаем текущий элемент в промежуточной переменной

		j = i - 1;

		while (j >= 0 && m[j] > r) // Ищем новое место вставки,

		{
			m[j + 1] = m[j]; j--;
		} // сдвигая на 1 элемент вправо

		m[j + 1] = r; // На освободившееся место вставляется элемент

	}

}

 

//ф-ция для обмена значений ячеек
inline void swapEl(int* arr, int i)
{
	int buff;
	buff = arr[i];
	arr[i] = arr[i - 1];
	arr[i - 1] = buff;
}
//ф-ция "шейкер"-сортировки
inline void myShakerSort(int* arr, int size,ostream& out)
{
	int leftMark = 1;
	int rightMark = size - 1;
	while (leftMark <= rightMark)
	{
		for (int i = rightMark; i >= leftMark; i--)
			if (arr[i - 1] > arr[i]) swapEl(arr, i);
		leftMark++;


		for (int i = leftMark; i <= rightMark; i++)
			if (arr[i - 1] > arr[i]) swapEl(arr, i);
		rightMark--;

		cout << " " << leftMark - 1; // просмотр количества итераций "(ut8)\nИтерация: "
	}
}
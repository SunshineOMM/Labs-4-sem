#include <vector>

using namespace std;
template<class Iterator>
void user_swap(Iterator it1, Iterator it2) {
	auto bucket = *it1;
	*it1 = *it2;
	*it2 = bucket;
}

template< class Iterator>
void SortByCelection(Iterator begin, Iterator end) {
	cout << "SortByCelection" << endl;
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
	cout << "BubbleSort" << endl;
	for (Iterator i = begin; i < end - 1; ++i) {
		for (Iterator j = begin; j < end - 1; ++j) {
			if (*j > *(j + 1)) user_swap(j, j + 1);
		}
	}
}

template< class Iterator>
void ShellSort(Iterator begin, Iterator end) {
	cout << "ShellSort" << endl;
	{
		for (int gap = (end - begin) / 2; gap != 0; gap /= 2)
		{
			for (auto i = begin + gap; i < end; ++i)
			{
				for (auto j = i; j >= begin + gap; j -= gap) {
					if (*(j - gap) > *j)
						user_swap(j, j - gap);
				}
			}
		}
	}
}

template< class Iterator>
void QuickSort(Iterator begin, Iterator end) {
	if (end - begin == 1) {
		if (*(end - 1) < *begin) user_swap(begin, end - 1);
		return;
	}
	auto pivot = begin;
	auto r = end - 1;
	auto l = begin;

	while (r >= l) {
		while (*r >= *pivot && r > begin) --r;
		while (*l <= *pivot && l < end - 1) ++l;
		if (r > l) user_swap(l, r);
		if (r == l) break;
	}
	user_swap(r, pivot);
	if (begin < r)
		QuickSort(begin, r);
	if (end > r + 1)
		QuickSort(r + 1, end);
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
	cout << "That's all!";
}

//Более адекватная
inline void merge(vector<int>& start, vector<int>& result, int& i, int& j, int& k, int& l, int& rb, int& re, bool f) {

	if (f) {// эта ветка сработает если нужно записывать в результирующий массив слева направо
		while (i <= j && k <= l) {
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
		for (; i <= j; ++i) {
			result[rb] = start[i];
			rb++;
		}
		for (; l >= k; --l) {
			result[rb] = start[l];
			rb++;
		}

	}
	else {// а эта, если нужно записывать в результирующий массив справа налево
		while (i <= j && k <= l) {
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
		for (; i <= j; ++i) {
			result[re] = start[i];
			re--;
		}
		for (; l >= k; --l) {
			result[re] = start[l];
			re--;
		}

	}
	j = i;
	k = l;
}
inline void sequenceLength(vector<int>& v, int& j, int& k) {
	while (j<v.size()-1 && v[j] <= v[j + 1]) {
		j++;
	}
	while ( k>0 && j != k - 1 &&v[k] <= v[k - 1]) {
		k--;
	}
}
inline void mergeSort(vector<int>& v) {
	vector<int> helpV(v.size());
	int rb = 0;
	int re = v.size() - 1;
	int i = 0, j = 0;
	int k = v.size() - 1, l = v.size() - 1;
	int  cycle = 0;

	//начало большого цикла
	 do{
		 i = 0;
		 j = 0;
		 k = v.size() - 1;
		 l = v.size() - 1;
		 rb = 0;
		 re = v.size() - 1;
		 
		 while (j < k) {
			 			 
			 sequenceLength(v, j, k);//подсчёт длины возрастающей последовательности 
			 if (j == l) break;// проверка условия на завершение сортировки
			 merge(v, helpV, i, j, k, l, rb, re, 1);			 
			 
			 if (j >= k) break;
			 

			 sequenceLength(v, j, k);
			 if (j == l) break;// проверка условия на завершение сортировки
			 merge(v, helpV, i, j, k, l, rb, re, 0);			 
			 			 
		 }
		 if (j == l) break;
		cycle++;
		std::swap(v, helpV);		
	 } while (j != l);
}



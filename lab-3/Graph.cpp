#include <string> 
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

struct Locality {
	string _name;
	size_t _count;
	size_t _state;
	Locality() :_name(""), _count(0), _state(0) {}
	Locality(string name, int count, int state) :_name(name), _count(count), _state(state) {}
};

class Graph {
	vector<Locality> _citiesVec;
	vector<vector<double>> _adjMatrix;
	int findVertex(Locality& city)const {
		for (int i = 0; i < _citiesVec.size(); ++i) {
			if (_citiesVec[i]._name == city._name) return i;
		}
		return -1;
	}
	int findVertex(string name)const {
		for (int i = 0; i < _citiesVec.size(); ++i) {
			if (_citiesVec[i]._name == name) return i;
		}
		return -1;
	}
	void deepRecursiveSearch(int line, ostream& out) {
		out << _citiesVec[line]._name << "\t";
		_citiesVec[line]._state = 1;
		for (int i = 0; i < _adjMatrix[line].size(); ++i) {
			if (_citiesVec[i]._state == 0 && _adjMatrix[line][i] != 0) deepRecursiveSearch(i, out);
		}
	}
	void reset() {
		for (int i = 0; i < _citiesVec.size(); ++i) {
			_citiesVec[i]._state = 0;
		}
	}
public:
	Graph() : _citiesVec(*new vector<Locality>(0)), _adjMatrix(*new vector<vector<double>>(0, vector<double>(0))) {}
	Graph(vector<Locality> citiesVec, vector<vector<double>> adjMatrix) : _citiesVec(citiesVec), _adjMatrix(adjMatrix) {}
	Graph(size_t sitiesNumbers) :_citiesVec(sitiesNumbers), _adjMatrix(sitiesNumbers, vector<double>(sitiesNumbers)) {}

	void AddVertex(string name, size_t count, size_t state) {
		if (findVertex(name) != -1) throw string("A city with the given name is already present");
		_citiesVec.push_back(*new Locality(name, count, state));
		for (int i = 0; i < _adjMatrix.size(); ++i) {
			_adjMatrix[i].push_back(0);
		}
		_adjMatrix.push_back(*new vector<double>(_citiesVec.size()));

	}
	void AddVertex(Locality& city) {
		AddVertex(city._name, city._count, city._state);
	}
	void AddEdge(string nameStart, string nameFinish, double way) {
		int indBeg = findVertex(nameStart);
		int indEnd = findVertex(nameFinish);
		if (indBeg == -1 || indEnd == -1) throw string("It is impossible to connect these two cities, perhaps they are not in the graph");
		_adjMatrix[indBeg][indEnd] = way;
	}
	void AddEdge(Locality& prev, Locality& next, double way) {
		AddEdge(prev._name, next._name, way);
	}


	void RemoveVertex(Locality& city) {
		RemoveVertex(city);
	}
	void RemoveVertex(string name) {
		int ind = findVertex(name);
		if (ind == -1) throw string("Deletion is not possible, a city with the same name does not exist");
		_citiesVec.erase(_citiesVec.begin() + ind);
		_adjMatrix.erase(_adjMatrix.begin() + ind);
		for (int i = 0; i < _adjMatrix.size(); ++i) {
			_adjMatrix[i].erase(_adjMatrix[i].begin() + ind);
		}
	}
	void RemoveEdge(Locality& prev, Locality& next) {
		RemoveEdge(prev._name, next._name);
	}
	void RemoveEdge(string nameStart, string nameFinish) {
		int indBeg = findVertex(nameStart);
		int indEnd = findVertex(nameFinish);
		if (indBeg == -1 || indEnd == -1) throw string("Deletion is not possible, pairs of cities with such names do not exist");
		_adjMatrix[indBeg][indEnd] = 0;
	}

	void editingVertex(Locality& oldCity, Locality& newCity) {
		editingVertex(oldCity._name, newCity._name, newCity._count, newCity._state);
	}
	void editingVertex(string nameOldCity, string nameNewCity, size_t count, size_t state) {
		int ind = findVertex(nameOldCity);
		if (ind == -1) throw string("Editing is not possible, cities with the same name do not exist");
		_citiesVec[ind]._name = nameOldCity;
		_citiesVec[ind]._count = count;
		_citiesVec[ind]._state = state;
	}
	void editingEdge(Locality& prev, Locality& next, double way) {
		editingEdge(prev._name, next._name, way);
	}
	void editingEdge(string nameStart, string nameFinish, double way) {
		int indBeg = findVertex(nameStart);
		int indEnd = findVertex(nameFinish);
		if (indBeg == -1 || indEnd == -1) throw string("Editing is not possible, pairs of cities with such names do not exist");
		_adjMatrix[indBeg][indEnd] = way;
	}

	void print(std::ostream& out)const {
		out << "City name:" << "\t\t" << "City population" <<  endl;
		for (int i = 0; i < _citiesVec.size(); ++i) {
			out << i << "\t" << _citiesVec[i]._name << "\t\t" << _citiesVec[i]._count << endl;
		}
		out << endl;
		out << endl;
		for (int i = 0; i < _adjMatrix.size(); ++i) {
			out << "\t" << i;
		}
		out << endl;
		out << endl;
		for (int i = 0; i < _adjMatrix.size(); ++i) {
			out << i << "\t";
			for (int j = 0; j < _adjMatrix[i].size(); ++j) {
				out << _adjMatrix[i][j] << "\t";
			}
			out << endl;
		}
		out << endl;
	}


	void deepRecursiveSearch(std::ostream& out, string city)
	{
		out << endl;
		out << endl;
		out << endl;
		out << "DEEP RECURSIVE SEARCH REGARDING " + city + ":" << endl;
		out << endl;

		int ind = findVertex(city);
		if (ind == -1) throw string("It is not possible to search the graph, a city with the same name does not exist");
		deepRecursiveSearch(ind, out);

		reset();
		out << endl;
		out << endl;
		out << endl;
	}

	void deepNonRrecursiveSearch(std::ostream& out, string city) {
		out << endl;
		out << endl;
		out << endl;
		out << "DEEP NON RECURSIVE SEARCH REGARDING " + city + ":" << endl;
		out << endl;
		int line = findVertex(city);
		if (line == -1) throw string("It is not possible to search the graph, a city with the same name does not exist");
		stack<int> stack;

		stack.push(line);
		while (!stack.empty())
		{
			line = stack.top();
			stack.pop();
			if (_citiesVec[line]._state == 2) continue;
			_citiesVec[line]._state = 2;
			for (int i = 0; i < _adjMatrix[line].size(); ++i)
			{
				if (_citiesVec[i]._state != 2 && _adjMatrix[line][i] != 0)
				{
					stack.push(i);
					_citiesVec[i]._state = 1;
				}
			}

			out << _citiesVec[line]._name << "\t";
		}
		reset();
		out << endl;
		out << endl;
		out << endl;
	}

	void wideSearch(std::ostream& out, string city) {
		out << endl;
		out << endl;
		out << endl;
		out << "WIDE SEARCH REGARDING " + city + ":" << endl;
		out << endl;
		int line = findVertex(city);
		if (line == -1) throw string("It is not possible to search the graph, a city with the same name does not exist");
		queue<int> queue;

		queue.push(line);
		while (!queue.empty()) {
			line = queue.front();
			queue.pop();
			if (_citiesVec[line]._state == 2) continue;
			_citiesVec[line]._state = 2;
			for (int i = 0; i < _adjMatrix[line].size(); ++i) {
				if (_citiesVec[i]._state != 2 && _adjMatrix[line][i] != 0) {
					queue.push(i);
					_citiesVec[i]._state = 1;
				}
			}
			out << _citiesVec[line]._name << "\t";
		}
		reset();

		out << endl;
		out << endl;
		out << endl;
	}

	int findNextMinVertex(int line, vector<double>& vec) {
		double minWay = vec[0];
		int minV = 0;
		for (int i = 0; i < vec.size(); ++i) {
			if (vec[i] < minWay && _citiesVec[i]._state!=2) {
				minWay = vec[i];
				minV = i;
			}
		}
		return minV;
	}
	
	double findNextMinWay(int line, vector<double>& vec) {
		double minWay = vec[0];
		for (int i = 0; i < vec.size(); ++i) {
			if (vec[i] < minWay && _citiesVec[i]._state!=2) {
				minWay = vec[i];
			}
		}
		return minWay;
	}

	vector<string> DijkstraAlgorithm(string nameStart, string nameFinish, double& way) {
		int indStart = findVertex(nameStart);
		int indFinish = findVertex(nameFinish);
		vector<double > d = *new vector<double>(_citiesVec.size(), 0);		
		vector<int> verVect = *new vector<int>(_adjMatrix.size());

		queue<int> q;
		q.push(indStart);

		// инициализаци€ вектора d
		for (int i = 0; i < d.size(); ++i) {
			d[i] = _adjMatrix[indStart][i];
			if (d[i] == 0) d[i] = numeric_limits<double>::max();
		}

		while (!q.empty()) {
			
			int ind = q.front();	//ƒостаЄм очередной индекс города			
			q.pop();
			
			
			if (_citiesVec[ind]._state == 2) continue;	// ≈сли город уже посещалс€, то переходим к следующему
				_citiesVec[ind]._state = 2;	
				// Ќаходим следующий ближайший город, помещаем его в очередь
				int nextVertex = findNextMinVertex(ind,d);	
				q.push(nextVertex);
				// ќбновл€ем(не всегда) значенни€ таблицы рассто€ни€ у городов, которые не посетили
				for (int j = 0; j < _citiesVec.size(); ++j) {

					if (_citiesVec[j]._state != 2 ) {
						if (d[j] > d[ind] + (_adjMatrix[ind][j] == 0 ? numeric_limits<double>::max() : _adjMatrix[ind][j])) {
							verVect[j]= ind;	// —охран€ем путь
							d[j] = d[ind] + (_adjMatrix[ind][j] == 0 ? numeric_limits<double>::max() : _adjMatrix[ind][j]);
						}
					}

				}
				
		}
		reset();

		d[indStart] = 0;
		way = d[indFinish];
		vector<string> result = *new vector<string>(0);
		if (d[indFinish] != numeric_limits<double>::max()) {
			while (indStart != indFinish) {
				result.insert(result.begin(), _citiesVec[indFinish]._name);
				indFinish = verVect[indFinish];
			}
			result.insert(result.begin(), _citiesVec[indStart]._name);
		}
			
		return result;		
	}

	vector<string> BellmanFord(string nameStart, string nameFinish, double& way) {
		int indStart = findVertex(nameStart);
		int indFinish = findVertex(nameFinish);
		vector<double > d = *new vector<double>(_citiesVec.size(), numeric_limits<double>::max());
		vector<double > dNew = *new vector<double>(_citiesVec.size(), numeric_limits<double>::max());
		vector<int> verVect = *new vector<int>(_adjMatrix.size());
		d[indStart] = 0;
		for (int k = 0; k < _citiesVec.size() - 1; ++k) {
			bool stop = true;
			for (int i = 0; i < _citiesVec.size(); ++i) {
				if (i == indStart) continue;
				dNew[i] = d[i];
				for (int j = 0; j < _citiesVec.size(); ++j) {
					if (_adjMatrix[j][i] == 0) continue;
					if (d[j] + (_adjMatrix[j][i] == 0 ? numeric_limits<double>::max() : _adjMatrix[j][i]) < dNew[i]) {
						dNew[i] = (_adjMatrix[j][i] == 0 ? numeric_limits<double>::max() : _adjMatrix[j][i]);
						verVect[i] = j;
					}					
					stop = false;
				}
			}
			for (int i = 0; i < _citiesVec.size(); ++i) {
				if(i== indStart) continue;
				d[i] = dNew[i];
			}
			if (stop) break;
		}

		way = numeric_limits<double>::max();
		vector<string> result = *new vector<string>(0);
		if (d[indFinish] != numeric_limits<double>::max()) {
			way = 0;
			while (indStart != indFinish) {
				way += d[indFinish];
				result.insert(result.begin(), _citiesVec[indFinish]._name);
				indFinish = verVect[indFinish];
			}
			result.insert(result.begin(), _citiesVec[indStart]._name);
		}
		
		return result;
	}
};
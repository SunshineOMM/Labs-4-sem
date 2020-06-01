#pragma once

#include <stdexcept>
#include<limits>
#include <algorithm>

// TVertex,TEdge - легковесные!
// Поэтому без всяких const
// Graph<Locality*,double>
template<typename TVertex, typename TEdge>
class GraphBest {
public:
	struct Edge {
		TVertex dstVertex;
		TEdge edge;
		Edge(TVertex dstVertex, TEdge edge) :dstVertex(dstVertex), edge(edge) {}
	};
private:
	struct EdgeNode {
		Edge edge;
		EdgeNode* next;
		EdgeNode(Edge edge, EdgeNode* next) : edge(edge), next(next) {}
	};

	struct Vertex {
		TVertex vertex;
		EdgeNode* edges;
		Vertex() :edges(nullptr) {}
		Vertex(TVertex vertex) : vertex(vertex), edges(nullptr) {}
	};

	Vertex* _graph;
	std::size_t _count;

	std::size_t FindVertexIndex(TVertex vertex)const  {
		for (std::size_t i = 0; i < _count; ++i) {
			if (_graph[i].vertex == vertex) {
				return i;
			}
		}
		return _count;
	}
	
	EdgeNode** Find(TVertex srcvertex,TVertex dstvertex) {
		auto srcvertexIndex = FindVertexIndexOrThrow(srcvertex);
		EdgeNode** it = &_graph[srcvertexIndex].edges;
		while (*it) {
			if ((*it)->edge.dstVertex == dstvertex) return it;
			it = &((*it)->next);
		}
		return it;
	}
	/*void Clear(Vertex& vertex) {
		EdgeNode* it = vertex.edges;
		while (it) {
			auto tmp = it;
			it = it->next;
			delete tmp;
		}
	}*/

public:

	GraphBest() : _graph(nullptr), _count(0) {}

	std::size_t FindVertexIndexOrThrow(TVertex vertex)const {
		const auto index = FindVertexIndex(vertex);
		if (index == _count) throw std::invalid_argument("Vertex not found!");
		return index;
	}

	std::size_t GetVertexCount() const {
		return _count;
	}

	TVertex GetVertex(std::size_t index)const {
		return _graph[index].vertex;
	}

	void AddVertex(TVertex vertex) {
		const auto index = FindVertexIndex(vertex);
		if (index != _count) throw std::invalid_argument("Vertex already exist!");
		auto graph = new Vertex[_count + 1];
		for (std::size_t i = 0; i < _count; ++i) {
			graph[i] = _graph[i];
		}
		graph[_count] = Vertex(vertex);
		delete[] _graph;
		_graph = graph;
		++_count;
	}

	void AddEdge(TVertex srcvertex, TVertex dstvertex, TEdge edge) {
		const auto srcIndex = FindVertexIndexOrThrow(srcvertex);
		const auto dstIndex = FindVertexIndexOrThrow(dstvertex);
		Edge e(dstvertex, edge);
		_graph[srcIndex].edges = new EdgeNode(e, _graph[srcIndex].edges);
	}

	void EraseVertex(TVertex vertex) {
		const auto index = FindVertexIndexOrThrow(vertex);
		auto graph = new Vertex[_count - 1];
		for (std::size_t i = 0; i < index; ++i) {
			graph[i] = _graph[i];
		}
		for (std::size_t i = index + 1; i < _count; ++i) {
			graph[i - 1] = _graph[i];
		}
		// Утечка памяти!!!
		/*for (std::size_t i = 0; i < _count; ++i) {
			this->Clear(_graph[i]);
		}*/
		delete[] _graph;
		_graph = graph;
		--_count;
		
		for (std::size_t i = 0; i < _count; ++i) {
			EraseEdge(_graph[i].vertex, vertex);
		}
		
	}

	void EraseEdge(TVertex srcvertex, TVertex dstvertex) {
		EdgeNode** node = Find(srcvertex, dstvertex);
		while (*node) {			
			auto tmp = *node;
			*node = (*node)->next;
			delete tmp;
			node = Find(srcvertex, dstvertex);
		}	
	}

	void EditingVertex(TVertex vertex,TVertex newVertex) {
		auto vertexIndex = FindVertexIndexOrThrow(vertex);
		_graph[vertexIndex].vertex = newVertex;

		for (std::size_t i = 0; i < _count; ++i) {
			EdgeNode** node = Find(_graph[i].vertex, vertex);

			while (*node) {
				(*node)->edge.dstVertex = newVertex;
				node = Find(_graph[i].vertex, vertex);
			}
		}
	}

	void EditingEdge(TVertex srcvertex, TVertex dstvertex, TEdge newedge) {
		auto vertexIndex = FindVertexIndexOrThrow(srcvertex);
		auto node = Find(srcvertex, dstvertex);
		while (*node && (*node)->edge.edge != newedge) {
			(*node)->edge.edge = newedge;
			node = &((*node)->next);
			node = Find(_graph[vertexIndex].vertex, dstvertex);
		}
	}

	void Print(std::ostream& out) {
		for (size_t vertexIndex = 0; vertexIndex < _count; ++vertexIndex) {
			auto vertex = _graph[vertexIndex].vertex;
			cout << vertex;
			for (size_t edgeIndex = 0; edgeIndex < this->GetEdgeCount(vertex); ++edgeIndex) {
				auto edge = this->GetEdge(vertex, edgeIndex);
				out << "\t" << edge.dstVertex << ": " << edge.edge << endl;
			}
			out << endl;
		}
	}

	std::size_t GetEdgeCount(TVertex srcvertex)const {
		std::size_t count = 0;
		auto node = _graph[FindVertexIndexOrThrow(srcvertex)].edges;
		while (node) {
			++count;
			node = node->next;
		}
		return count;
	}

	Edge GetEdge(TVertex srcvertex, std::size_t  index)const {
		std::size_t count = 0;
		auto node = _graph[FindVertexIndexOrThrow(srcvertex)].edges;
		for (std::size_t i = 0; i < index; ++i) {
			node = node->next;
		}
		return node->edge;
	}

	
};


//Алгоритмы
template<typename TVertex,typename TEdge,typename TFunctional>
void DepthFirstSearch(const GraphBest<TVertex, TEdge>& graph, TVertex begin,TFunctional f) {
	const auto n = graph.GetVertexCount();
	auto visited = new bool[n];
	auto stack = new std::size_t[n];
	std::size_t stackSize = 0; 
	for (std::size_t i = 0; i < n; ++i) {
		visited[i] = 0;
	}

	try {
		const auto beginIndex = graph.FindVertexIndexOrThrow(begin);
		stack[stackSize++] = beginIndex;
		visited[beginIndex] = true;

		while (stackSize > 0) {
			const auto vertexIndex = stack[--stackSize];
			const auto vertex = graph.GetVertex(vertexIndex);			
			f(vertex);
			const auto edgeCount = graph.GetEdgeCount(vertex);
			for (std::size_t edgeIndex = 0; edgeIndex < edgeCount; ++edgeIndex) {
				const auto dstIndex =graph.FindVertexIndexOrThrow(graph.GetEdge(vertex, edgeIndex).dstVertex);
				if (!visited[dstIndex]) {
					stack[stackSize++] = dstIndex;
					visited[dstIndex] = true;
				}
			}
		}



	}
	catch (...) {

		delete[] visited;
		delete[] stack;
		throw;
	}
	delete[] visited;
	delete[] stack;
}


template<typename TVertex, typename TEdge, typename TFunctional>
void BreadthFirstSearch(const GraphBest<TVertex, TEdge>& graph, TVertex begin, TFunctional f) {
	const auto n = graph.GetVertexCount();
	auto visited = new bool[n];
	auto queue = new std::size_t[n];
	std::size_t push = 0;
	std::size_t pop = 0;
	for (std::size_t i = 0; i < n; ++i) {
		visited[i] = 0;
	}

	try {
		const auto beginIndex = graph.FindVertexIndexOrThrow(begin);
		queue[push++] = beginIndex;
		visited[beginIndex] = true;

		while (push!=pop) {
			const auto vertexIndex = queue[pop++];
			const auto vertex = graph.GetVertex(vertexIndex);
			f(vertex);
			const auto edgeCount = graph.GetEdgeCount(vertex);
			for (std::size_t edgeIndex = 0; edgeIndex < edgeCount; ++edgeIndex) {
				const auto dstIndex = graph.FindVertexIndexOrThrow(graph.GetEdge(vertex, edgeIndex).dstVertex);
				if (!visited[dstIndex]) {
					queue[push++] = dstIndex;
					visited[dstIndex] = true;
				}
			}
		}



	}
	catch (...) {

		delete[] visited;
		delete[] queue;
		throw;
	}
	delete[] visited;
	delete[] queue;
}

template<typename TEdge>
struct DefaultEdgeWeight {
	float operator()(TEdge edge) {
		return static_cast<float>(edge);
	}
};


const auto INFINITY_DISTANCE = std::numeric_limits<float>::infinity();

template<typename TVertex, typename TEdge, typename TEdgeWeight = DefaultEdgeWeight<TEdge>>  
float Dijkstra(const GraphBest<TVertex, TEdge>& graph, TVertex begin, TVertex end,TVertex* path,std::size_t* pathLenght) {
	const auto n = graph.GetVertexCount();
	auto u = new bool[n];
	auto d = new float[n];
	auto p = new std::size_t[n];
	for (std::size_t i = 0; i < n; ++i) {
		d[i] = INFINITY_DISTANCE;
		u[i] = false;
		p[i] = n;
	}

	try {
		auto beginIndex = graph.FindVertexIndexOrThrow(begin);
		d[beginIndex] = 0;

		for (std::size_t i = 0; i < n; ++i) {
			//ЭТАП 1: Выбрать непомеченную вершину с минимальным расстоянием
			std::size_t selectedIndex = n;
			float selectedDistance = INFINITY_DISTANCE;
			for (std::size_t j = 0; j < n; ++j) {
				if (!u[j] && d[j] < selectedDistance) {
					selectedIndex = j;
					selectedDistance = d[j];					
				}
			}
			if (selectedIndex == n) break;

			u[selectedIndex] = true;


			//ЭТАП 2: Для всех смежных рёбер выбранной вершины провести релаксацию
			const auto selectedVertex = graph.GetVertex(selectedIndex);
			const auto edgeCount = graph.GetEdgeCount(selectedVertex);
			for (std::size_t j = 0; j < edgeCount; ++j) {
				const auto edge = graph.GetEdge(selectedVertex,j);
				const auto dstVertex = edge.dstVertex;
				const auto dstIndex = graph.FindVertexIndexOrThrow(dstVertex);
				const auto distance = d[selectedIndex] + TEdgeWeight()(edge.edge); 
					if (distance < d[dstIndex]) {
						d[dstIndex] = distance;
						p[dstIndex] = selectedIndex;
					}
			}


		}
		const auto endIndex = graph.FindVertexIndexOrThrow(end);
		const auto distance = d[endIndex];
		*pathLenght = 0;
		if (distance != INFINITY_DISTANCE && path != nullptr) {			
			auto cuttentIndex = endIndex;
			while (cuttentIndex != beginIndex) {
				path[(*pathLenght)++] = graph.GetVertex(cuttentIndex);
				cuttentIndex = p[cuttentIndex];
			}
			path[(*pathLenght)++] = begin;
			std::reverse(path, path + *pathLenght);
		}

		delete[] d;
		delete[] u;
		delete[] p;

		return distance;
	}
	catch (...) {
		delete[] d;
		delete[] u;
		delete[] p;
		throw;
	}
	

}



template<typename TVertex, typename TEdge, typename TEdgeWeight = DefaultEdgeWeight<TEdge>>
float BellmanFord(const GraphBest<TVertex, TEdge>& graph, TVertex begin, TVertex end, TVertex* path, std::size_t* pathLenght) {
	const auto n = graph.GetVertexCount();
	auto d = new float[n];
	auto p = new std::size_t[n];
	for (std::size_t i = 0; i < n; ++i) {
		d[i] = INFINITY_DISTANCE;
		p[i] = n;
	}

	try {
		auto beginIndex = graph.FindVertexIndexOrThrow(begin);
		d[beginIndex] = 0;

		for (std::size_t i = 0; i < n-1; ++i) {
			// Перебираем все рёбра
			for (std::size_t vertexIndex = 0; vertexIndex < n; ++vertexIndex) {
				const auto vertex = graph.GetVertex(vertexIndex);
				const auto edgeCount = graph.GetEdgeCount(vertex);
				for (std::size_t j = 0; j < edgeCount; ++j) {
					const auto edge = graph.GetEdge(vertex, j);
					const auto dstVertex = edge.dstVertex;
					const auto dstIndex = graph.FindVertexIndexOrThrow(dstVertex);
					const auto distance = d[vertexIndex] + TEdgeWeight()(edge.edge);
					if (distance < d[dstIndex]) {
						d[dstIndex] = distance;
						p[dstIndex] = vertexIndex;
					}
				}

			}
		}

		const auto endIndex = graph.FindVertexIndexOrThrow(end);
		const auto distance = d[endIndex];
		*pathLenght = 0;
		if (distance != INFINITY_DISTANCE && path != nullptr) {
			auto cuttentIndex = endIndex;
			while (cuttentIndex != beginIndex) {
				path[(*pathLenght)++] = graph.GetVertex(cuttentIndex);
				cuttentIndex = p[cuttentIndex];
			}
			path[(*pathLenght)++] = begin;
			std::reverse(path, path + *pathLenght);
		}

		delete[] d;
		delete[] p;

		return distance;
	}
	catch (...) {
		delete[] d;
		delete[] p;
		throw;
	}


}


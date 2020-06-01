#include<iostream>
#include"Graph.cpp"
#include "BestHandlerGraph.h"

using namespace std;
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

int main() {
	//===============================================================================================================================================
	//																Тест Graph		
	//===============================================================================================================================================
	printTestName("Graph");
	try {
		Graph g = Graph();
		//Вставка городов
		g.AddVertex("Samara", 1200000, 0);
		g.AddVertex("Moscow", 12000000, 0);
		g.AddVertex("Saint-Peterburg", 5000000, 0);
		g.AddVertex("Kazan", 1200000, 0);
		g.AddVertex("Arkhangelsk", 350000, 0);
		g.AddVertex("Novosibirsk", 1500000, 0);
		g.AddVertex("Vladivostok", 600000, 0);
		g.AddVertex("Ekaterinburg", 1400000, 0);
		g.AddVertex("Vorkuta", 200000, 0);

		//Вставка дорог
		g.AddEdge("Samara", "Moscow", 1000);
		g.AddEdge("Samara", "Saint-Peterburg", 1800);
		g.AddEdge("Samara", "Kazan", 450);
		g.AddEdge("Moscow", "Saint-Peterburg", 705);
		g.AddEdge("Samara", "Novosibirsk", 2500);
		g.AddEdge("Novosibirsk", "Vladivostok", 5500);
		g.AddEdge("Saint-Peterburg","Arkhangelsk", 1100);
		g.AddEdge("Vladivostok", "Kazan", 8200);
		g.AddEdge("Moscow", "Kazan", 1300);
		g.AddEdge("Saint-Peterburg", "Kazan", 2000);
		g.AddEdge("Kazan", "Moscow", 1300);
		g.AddEdge("Samara", "Ekaterinburg", 1100);
		g.AddEdge("Ekaterinburg", "Novosibirsk", 1100);
		g.AddEdge("Arkhangelsk", "Vorkuta", 5000);
		g.AddEdge("Novosibirsk", "Vorkuta", 4000);

		//===============================================================================================================================================
		//																Тест Print		
		//===============================================================================================================================================
		printTestName("Print");

		g.print(cout);

		//===============================================================================================================================================
		//																Тест Deep Recursive Search		
		//===============================================================================================================================================
		printTestName("Deep Recursive Search");

		g.deepRecursiveSearch(cout,"Samara");

		//===============================================================================================================================================
		//																Тест Deep Non Rrecursive Search		
		//===============================================================================================================================================
		printTestName("Deep Non Rrecursive Search");

		g.deepNonRrecursiveSearch(cout,"Samara");

		//===============================================================================================================================================
		//																Тест Wide Search		
		//===============================================================================================================================================
		printTestName("Wide Search");

		g.wideSearch(cout, "Samara");



		//===============================================================================================================================================
		//																Тест Dijkstra Algorithm		
		//===============================================================================================================================================
		printTestName("Dijkstra Algorithm");


		double wayD = 0;
		vector<string> vD = g.DijkstraAlgorithm("Samara", "Vorkuta", wayD);

		for (auto& it : vD) {
			cout << " " << it;
			if (it != *(vD.end() - 1)) cout << "---->";
		}
		if (wayD == numeric_limits<double>::max()) cout << "Path not found";
		else cout << " Total way: " << wayD;
		cout << endl;
		cout << endl;


		wayD = 0;
		vD= g.DijkstraAlgorithm("Arkhangelsk", "Samara", wayD);

		for (auto& it : vD) {
			cout << " " << it;
			if (it != *(vD.end() - 1)) cout << "---->";
		}
		if (wayD == numeric_limits<double>::max()) cout << "Path not found";
		else cout << " Total way: " << wayD;
		cout << endl;
		cout << endl;



		wayD = 0;
		vD = g.DijkstraAlgorithm("Arkhangelsk", "Arkhangelsk", wayD);

		for (auto& it : vD) {
			cout << " " << it;
			if (it != *(vD.end() - 1)) cout << "---->";
		}
		if (wayD == numeric_limits<double>::max()) cout << "Path not found";
		else cout << " Total way: " << wayD;
		cout << endl;
		cout << endl;

		
		//===============================================================================================================================================
		//																Тест Bellman Ford Algorithm		
		//===============================================================================================================================================
		printTestName("Bellman Ford Algorithm");

		double wayB = 0;
		vector<string> vB = g.BellmanFord("Samara", "Vorkuta", wayB);

		for (auto& it : vB) {
			cout << " " << it;
			if (it != *(vB.end() - 1)) cout << "---->";
		}
		if (wayB == numeric_limits<double>::max()) cout << "Path not found";
		else cout << " Total way: " << wayB;
		cout << endl;

		cout << endl;
		cout << endl;

		wayB = 0;
		vB = g.BellmanFord("Arkhangelsk", "Samara", wayB);

		for (auto& it : vB) {
			cout << " " << it;
			if (it != *(vB.end() - 1)) cout << "---->";
		}
		if (wayB == numeric_limits<double>::max()) cout << "Path not found";
		else cout << " Total way: " << wayB;
		cout << endl;
		cout << endl;

		wayB = 0;
		vB = g.BellmanFord("Arkhangelsk", "Arkhangelsk", wayB);

		for (auto& it : vB) {
			cout << " " << it;
			if (it != *(vB.end() - 1)) cout << "---->";
		}
		if (wayB == numeric_limits<double>::max()) cout << "Path not found";
		else cout << " Total way: " << wayB;
		cout << endl;


	}
	catch (string s) {
		cout <<"EXCEPTION: "+ s << endl;
	}


	//===============================================================================================================================================
	//																Тест GraphBest		
	//===============================================================================================================================================
	printTestName("GraphBest");

	GraphBest<char, double> graph;

	printTestName("AddVertex");
	graph.AddVertex('a');
	graph.AddVertex('b');
	graph.AddVertex('c');
	graph.AddVertex('d');
	graph.Print(cout);

	cout << endl;
	cout << endl;
	cout << endl;


	printTestName("AddEdge");
	graph.AddEdge('a', 'b', 3);
	graph.AddEdge('a', 'c', 2);
	graph.AddEdge('c', 'b', 4);
	graph.AddEdge('a', 'd', 3);
	graph.AddEdge('b', 'd', 4);
	graph.AddEdge('b', 'a', 7);
	graph.AddEdge('d', 'a', 1);
	graph.Print(cout);

	cout << endl;
	cout << endl;
	cout << endl;

	printTestName("EraseVertex");
	graph.EraseVertex('c');
	graph.Print(cout);

	cout << endl;
	cout << endl;
	cout << endl;

	printTestName("EraseEdge");
	graph.EraseEdge('a', 'b');
	graph.Print(cout);




	printTestName("EditingVertex");
	graph.EditingVertex('a','q');
	graph.Print(cout);



	printTestName("EditingEdge");
	graph.EditingEdge('b', 'q',15);
	graph.Print(cout);


	//===============================================================================================================================================
	//																Тест алгоритмы GraphBest		
	//===============================================================================================================================================

	
	GraphBest<char, double> graphNew;
	graphNew.AddVertex('a');
	graphNew.AddVertex('b');
	graphNew.AddVertex('c');
	graphNew.AddVertex('d');
	graphNew.AddVertex('e');
	graphNew.AddVertex('f');
	graphNew.AddVertex('g');
	graphNew.AddVertex('k');
	graphNew.AddVertex('m');
	graphNew.AddVertex('n');
	graphNew.AddVertex('h');

	graphNew.AddEdge('a', 'b', 1);
	graphNew.AddEdge('a', 'f', 1);
	graphNew.AddEdge('b', 'c', 1);
	graphNew.AddEdge('b', 'e', 5);
	graphNew.AddEdge('c', 'd', 6);
	graphNew.AddEdge('e', 'd', 1);
	graphNew.AddEdge('e', 'g', 10);
	graphNew.AddEdge('e', 'h', 1);
	graphNew.AddEdge('h', 'e', 1);
	graphNew.AddEdge('h', 'g', 1);
	graphNew.AddEdge('f', 'g', 1);
	graphNew.AddEdge('g', 'k', 1);
	graphNew.AddEdge('g', 'h', 1);
	graphNew.AddEdge('g', 'e', 10);
	graphNew.AddEdge('k', 'm', 1);
	graphNew.AddEdge('m', 'n', 1);
	graphNew.AddEdge('n', 'd', 1);

	printTestName("DepthFirstSearch");
	DepthFirstSearch(graphNew, 'a', [](auto vertex) {
		cout << vertex << ' ';
	});
	cout << endl;

	printTestName("BreadthFirstSearch");
	BreadthFirstSearch(graphNew, 'a', [](auto vertex) {
		cout << vertex << ' ';
	});
	cout << endl;

	printTestName("Dijkstra");
	char path[11];
	size_t lenght = 0;
	cout << Dijkstra(graphNew,'a','d', path,&lenght) << ": ";
	for (size_t i = 0; i < lenght; ++i) {
		cout << path[i] << " ";
	}
	cout << endl;


	printTestName("BellmanFord");
	char pathNew[11];
	size_t lenghtNew = 0;
	cout << BellmanFord(graphNew, 'a', 'd', pathNew, &lenghtNew) << ": ";
	for (size_t i = 0; i < lenght; ++i) {
		cout << pathNew[i] << " ";
	}
	cout << endl;

	system("PAUSE");
}
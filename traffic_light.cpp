#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
public:
	typedef size_t Vertex;
	virtual vector<Vertex> getNeibours(Vertex v, int countVertecies) = 0;
	virtual void addEdge(Vertex from, Vertex to, int countVertecies) = 0;

};

class AdjMatrixGraph : public Graph {

public:
	vector<Vertex> getNeibours(Vertex v, int countVertecies) override {
		vector<Vertex> neibours;
		for (Vertex u = 0; u < countVertecies; u++) {
			if (has_edge[v][u]) {
				neibours.push_back(u);
			}
		}
		return neibours;
	}
	void addEdge(Vertex from, Vertex to, int countVertecies) override {
		has_edge[from][to] = 1;
	}
	AdjMatrixGraph(size_t countVerrecies, size_t countEdges) {
		Vertex from, to;
		vector<bool> stringofMatrix;
		for (int i = 0; i < countVerrecies; ++i) {
			has_edge.push_back(stringofMatrix);
		}
		for (int i = 0; i < countEdges; ++i) {
			std::cin >> from >> to;
			addEdge(from, to, countVerrecies);
			addEdge(to, from, countVerrecies);
		}
	}

private:
	std::vector<std::vector<bool>> has_edge;
};

class AdjListsGraph : public Graph {
public:
	vector<Vertex> getNeibours(Vertex v, int countVertecies) override {
		return adj_lists[v];
	}
	void addEdge(Vertex from, Vertex to, int countVertecies) override {
		adj_lists[from].push_back(to);
	}
	AdjListsGraph(size_t countVerrecies, size_t countEdges) {
		Vertex from, to;
		std::vector<Vertex> stringofMatrix;
		for (size_t i = 0; i <= countVerrecies; ++i) {
			adj_lists.push_back(stringofMatrix);
		}
		for (int i = 0; i < countEdges; ++i) {
			std::cin >> from >> to;
			addEdge(from, to, countVerrecies);
			addEdge(to, from, countVerrecies);
		}
	}
	size_t getNumberofVertecies() {
		return adj_lists.size();
	}
private:
	std::vector<std::vector<Vertex>> adj_lists;
};


namespace GraphProcessing {

}

void trafficLight(AdjListsGraph listGraph) {
	size_t countVertecies = listGraph.getNumberofVertecies();
	for (size_t i = 1; i < countVertecies; ++i) {
		cout << listGraph.getNeibours(i, countVertecies).size() << " ";
	}
}


int main() {
	size_t countVertecies, countEdge;
	std::cin >> countVertecies >> countEdge;
	AdjListsGraph listGraph = AdjListsGraph(countVertecies, countEdge);
	trafficLight(listGraph);
	return 0;
}

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
	AdjMatrixGraph(size_t countVerrecies) {
		bool is_edge;
		vector<bool> stringofMatrix;
		for (size_t i = 0; i < countVerrecies; ++i) {
			has_edge.push_back(stringofMatrix);
		}
		for (Vertex from = 0; from < countVerrecies; ++from) {
			for (Vertex to = 0; to < countVerrecies; ++to) {
				std::cin >> is_edge;
				if (is_edge) {
					addEdge(from, to, countVerrecies);
				}
			}
		}
	}
	size_t getNumberofVertecies() {
		return has_edge.size();
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
		std::vector<Vertex> t;
		for (int i = 0; i < countVerrecies; ++i) {
			adj_lists.push_back(t);
		}
		for (int i = 0; i < countEdges; ++i) {
			std::cin >> from >> to;
			addEdge(from, to, countVerrecies);
			addEdge(to, from, countVerrecies);
		}
	}
	AdjListsGraph(size_t countVerrecies) {
		Vertex from, to;
		bool is_edge;
		vector<Vertex> stringofMatrix;
		for (size_t i = 0; i < countVerrecies; ++i) {
			adj_lists.push_back(stringofMatrix);
		}
		for (size_t from = 0; from < countVerrecies; ++from) {
			for (size_t to = 0; to < countVerrecies; ++to) {
				std::cin >> is_edge;
				if (is_edge) {
					addEdge(from, to, countVerrecies);
				}
			}
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
	for (size_t i = 0; i < countVertecies; ++i) {
		cout << listGraph.getNeibours(i, countVertecies).size() << " ";
	}
}

int GetNumberofVertecies(AdjListsGraph listGraph) {
	size_t NumberofCrossroads = 0;
	size_t NumberofVertecies = listGraph.getNumberofVertecies();
	for (size_t i = 0; i < NumberofVertecies; ++i) {
		NumberofCrossroads += listGraph.getNeibours(i, NumberofVertecies).size();
	}
	NumberofCrossroads = NumberofCrossroads / 2;
	return NumberofCrossroads;
}


int main() {
	int CountVertecies;
	std::cin >> CountVertecies;
	AdjListsGraph listGraph(CountVertecies);
	std::cout << GetNumberofVertecies(listGraph);
	return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
public:
	typedef size_t Vertex;
	virtual vector<Vertex> getNeibours(Vertex v, int countVertecies) = 0;
	virtual void addEdge(Vertex from, Vertex to, int countVertecies) = 0;
	virtual size_t getNumberofVertecies() = 0;

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
	size_t getNumberofVertecies() override {
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

	size_t getNumberofVertecies() override {
		return adj_lists.size();
	}
private:
	std::vector<std::vector<Vertex>> adj_lists;
};


namespace GraphProcessing {


	void trafficLight(Graph &listGraph) {
		size_t countVertecies = listGraph.getNumberofVertecies();
		for (size_t i = 0; i < countVertecies; ++i) {
			cout << listGraph.getNeibours(i, countVertecies).size() << " ";
		}
	}

	int GetNumberofVertecies(Graph &listGraph) {
		size_t NumberofCrossroads = 0;
		size_t NumberofVertecies = listGraph.getNumberofVertecies();
		for (size_t i = 0; i < NumberofVertecies; ++i) {
			NumberofCrossroads += listGraph.getNeibours(i, NumberofVertecies).size();
		}
		NumberofCrossroads = NumberofCrossroads / 2;
		return NumberofCrossroads;
	}

	void dfs_visit(Graph &listGraph, size_t v, vector<size_t> &blacks, vector<size_t> &time_in, vector<size_t> &time_out, vector<size_t> &colour, size_t &timer) {
		size_t countVertecies = listGraph.getNumberofVertecies();
		time_in[v] = timer++;
		colour[v] = 1;
		vector<size_t> Neighbours = listGraph.getNeibours(v, countVertecies);
		for (auto iter = Neighbours.begin(); iter != Neighbours.end(); ++iter) {
			if (colour[*iter] == 0) {
				cout << *iter << endl;
				dfs_visit(listGraph, *iter, blacks, time_in, time_out, colour, timer);
			}
		}
		colour[v] = 2;
		time_out[v] = timer++;
		blacks.push_back(v);
	}

	void dfs(Graph &listGraph, size_t v, vector<size_t> &blacks) {
		size_t timer = 0;
		size_t numberofVertecies = listGraph.getNumberofVertecies();
		vector<size_t> time_in(numberofVertecies, 0);
		vector<size_t> time_out(numberofVertecies, 0);
		vector<size_t> colour(numberofVertecies, 0);
		time_in[v] = timer++;
		colour[v] = 1;
		size_t countVertecies = listGraph.getNumberofVertecies();
		vector<size_t> Neighbours = listGraph.getNeibours(v, countVertecies);
		for (auto iter = Neighbours.begin(); iter != Neighbours.end(); ++iter) {
			if (colour[*iter] == 0) {
				dfs_visit(listGraph, *iter, blacks, time_in, time_out, colour, timer);
			}
		}
		colour[v] = 2;
		time_out[v] = timer++;
		blacks.push_back(v);
	}


}

using namespace GraphProcessing;


int main() {
	size_t countVertecies, start;
	std::cin >> countVertecies >> start;
	AdjListsGraph listGraph(countVertecies);
	vector<size_t> blacks;
	start--;
	dfs(listGraph, start, blacks);
	std::cout << blacks.size();
	getchar();
	getchar();
	return 0;
}
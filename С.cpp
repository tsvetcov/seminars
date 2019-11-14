#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

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
			std::cin >> to;
			addEdge(i, to - 1, countVerrecies);
		}
		//for (int i = 0; i < adj_lists.size(); ++i) {
		//cout << i << adj_lists[i].size() << adj_lists[i][0] << endl;
		//	}
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
		for (int i = 0; i < adj_lists.size(); ++i) {
			cout << i << adj_lists[i].size();
		}
	}

	size_t getNumberofVertecies() override {
		return adj_lists.size();
	}
private:
	std::vector<std::vector<Vertex>> adj_lists;
};


namespace GraphProcessing {

	void dfs_visit(Graph &listGraph, size_t &v, vector<size_t> &blacks, vector<int> &colour, size_t &result) {
		size_t countVertecies = listGraph.getNumberofVertecies();
		size_t vert = v;
		colour[v] = 1;
		vert = listGraph.getNeibours(vert, countVertecies)[0];
		if ((blacks[vert] == -1) && (colour[vert] == 0)) {
			dfs_visit(listGraph, vert, blacks, colour, result);
			blacks[vert] = v;
			colour[vert] = 2;
			//cout << vert;
		}
		if (blacks[vert] == blacks[v]) {
			result++;
			//cout << endl;
			//break;
		}
		//if (blacks[vert] != -1) {
		//	return result;
		//}
		//cout << endl;
		//cout << result << "uuu" << endl;
		//return result;
	}

	bool Pigs(Graph &listGraph) {
		size_t countVertecies = listGraph.getNumberofVertecies();
		size_t result = 0;
		size_t cycles = 0;
		vector<size_t> blacks(countVertecies, -1);
		vector<int> colour(countVertecies, 0);
		for (size_t i = 0; i < countVertecies;++i) {
			if (blacks[i] == -1) {
				blacks[i] = -1;
				//cout << cycles << "ppp";
				dfs_visit(listGraph, i, blacks, colour, result);
				//cout << result << "oooo" << endl;
			}
		}
		cout << result;
		return result;
	}
}

using namespace GraphProcessing;


int main() {
	size_t countPigs;
	std::cin >> countPigs;
	AdjListsGraph listGraph(countPigs, countPigs);
	Pigs(listGraph);
	getchar();
	getchar();
	return 0;
}
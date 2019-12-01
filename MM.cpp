#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <climits>

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
		adj_lists[to].push_back(from);
	}
	AdjListsGraph(size_t countVerrecies, size_t countEdges) {
		Vertex from, to;
		std::vector<Vertex> t;
		for (int i = 0; i < countVerrecies; ++i) {
			adj_lists.push_back(t);
		}
		for (int i = 0; i < countEdges; ++i) {
			std::cin >> from >> to;
			addEdge(from - 1, to - 1, countVerrecies);
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

	void dfs_visit(Graph &listGraph, size_t &v, vector<size_t> &tin, vector<size_t> &colour, set<size_t> &checkpoints, vector<size_t> &fup, size_t &timer, vector<bool> &is_point, vector<size_t> &points, size_t p = -1) {
		size_t countVertecies = listGraph.getNumberofVertecies();
		bool is_vert_root = (p == v);
		colour[v] = 1;
		tin[v] = fup[v] = ++timer;
		size_t children = 0;
		vector<size_t> Neighbours = listGraph.getNeibours(v, countVertecies);
		for (int i = 0; i < Neighbours.size(); ++i) {
			size_t to = Neighbours[i];
			if (p == to) {
				continue;
			}
			if (colour[to] == 1) {
				fup[v] = std::min(fup[v], tin[to]);
			}
			if (colour[to] == 0) {
				//cout << "oooooooo";
				dfs_visit(listGraph, to, tin, colour, checkpoints, fup, timer, is_point, points, v);
				fup[v] = std::min(fup[v], fup[to]);
				++children;
				if ((fup[to] >= tin[v]) && p != -1) {
					is_point[v] = true;
				}
			}

		}
		if (p == -1 && children >= 2) {
			is_point[v] = true;
		}
		return;
	}

	vector<size_t> find_checkpoints(Graph &listGraph) {
		size_t n_of_ch = 0;
		vector<size_t> points;
		//cout << "uuuuuuuu";
		const size_t maxSize = UINT_MAX;;
		size_t countVert = listGraph.getNumberofVertecies();
		vector<bool> is_point(countVert, false);
		vector<size_t> colour(countVert, 0);
		vector<size_t> tin(countVert, maxSize);
		vector<size_t> fup(countVert, maxSize);
		set<size_t> checkpoints;
		size_t timer = 0;
		size_t v = 0;
		size_t p = -1;
		for (size_t i = 0;i < countVert;++i) {
			if (colour[i] == 0) {
				//cout << "ppppppp";
				dfs_visit(listGraph, i, tin, colour, checkpoints, fup, timer, is_point, points, p);
			}
		}
		for (size_t i = 0;i < countVert;++i) {
			if (is_point[i]) {
				points.push_back(i);
			}
		}
		return points;
	}

}

using namespace GraphProcessing;


int main() {
	size_t countVertecies, countEdges, start, finish;
	std::cin >> countVertecies >> countEdges;
	//std::cin >> start >> finish;
	AdjListsGraph listGraph(countVertecies, countEdges);
	vector<size_t> points = find_checkpoints(listGraph);
	cout << points.size() << endl;
	for (int i = 0; i < points.size(); ++i) {
		cout << points[i] + 1 << endl;
	}
	return 0;
}
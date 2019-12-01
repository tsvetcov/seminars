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

class DSU {
public:
	vector<int> parent;
	vector<int> range;
	vector<int> sum;
	DSU(size_t countVertecies) {
		for (int i = 0;i < countVertecies;++i) {
			parent.push_back(i);
			range.push_back(1);
			sum.push_back(0);
		}
	}
	void make_set(int v) {
		parent[v] = v;
		range[v] = 1;
	}
	int find_set(int v) {
		if (parent[v] == v) {
			return v;
		}
		else {
			int to = find_set(parent[v]);
			sum[to] += sum[v];
			sum[v] = 0;
			parent[v] = to;
			return to;
		}
	}
	void union_set(int left, int right) {
		left = find_set(left);
		right = find_set(right);
		if (range[left] < range[right]) {
			swap(left, right);
		}
		parent[right] = left;
		sum[left] += sum[right];
		sum[right] = 0;
		if (range[left] == range[right]) {
			++range[left];
		}
	}
};


namespace GraphProcessing {
}

using namespace GraphProcessing;


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t countVertecies, countEdges, start, finish;
	std::cin >> countVertecies >> countEdges;
	int code, weight;
	DSU islands = DSU(countVertecies);
	size_t components = countVertecies;
	for (int j = 0;j < countEdges;++j) {
		cin >> code;
		if (code == 1) {
			cin >> start >> finish >> weight;

			if (islands.find_set(start - 1) != islands.find_set(finish - 1)) {
				islands.union_set(start - 1, finish - 1);
			}
			int p = islands.find_set(start - 1);
			islands.sum[p] += weight;
		}
		if (code == 2) {
			cin >> start;
			int vert = islands.find_set(start - 1);
			cout << islands.sum[vert] << endl;
		}
	}
	//cout << components;
	getchar();
	getchar();
	return 0;
}
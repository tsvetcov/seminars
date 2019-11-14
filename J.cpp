#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>

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

// vert = y*len + x 

class TableGraph : public Graph {
public:
	vector<Vertex> getNeibours(Vertex v, int countVert) override {
		size_t l = len;
		size_t b = bright;
		size_t y = v / l;
		size_t x = v % l;
		vector<Vertex> neigh;
		if ((l == 1) && (b == 1)) {
			return neigh;
		}
		if ((b == 1)) {
			if (x == 0) {
				neigh.push_back(1);
				return neigh;
			}
			if (x == l - 1) {
				neigh.push_back(l - 2);
				return neigh;
			}
			if ((x > 0) && (x < (l - 1))) {
				neigh.push_back(x - 1);
				neigh.push_back(x + 1);
				return neigh;
			}
		}
		if ((l == 1)) {
			if (y == 0) {
				neigh.push_back(1);
				return neigh;
			}
			if (y == b - 1) {
				neigh.push_back(b - 2);
				return neigh;
			}
			if ((y > 0) && (y < (b - 1))) {
				neigh.push_back(y - 1);
				neigh.push_back(y + 1);
				return neigh;
			}
		}
		if ((x == 0) && (y == 0)) {
			neigh.push_back(1);
			neigh.push_back(len);
			return neigh;
		}
		if ((x == (l - 1)) && (y == 0)) {
			neigh.push_back(l * 2 - 1);
			neigh.push_back(l - 2);
			return neigh;
		}
		if ((x == 0) && (y == (b - 1))) {
			neigh.push_back(y*(len)+x + 1);
			neigh.push_back((y - 1)*(len)+x);
			return neigh;
		}
		if ((x == (l - 1)) && (y == (b - 1))) {
			neigh.push_back(y*(len)+x - 1);
			neigh.push_back((y - 1)*(len)+x);
			return neigh;
		}
		if (x == (l - 1)) {
			neigh.push_back(y*(len)+x - 1);
			neigh.push_back((y + 1)*(len)+x);
			neigh.push_back((y - 1)*(len)+x);
			return neigh;

		}
		if (x == 0) {
			neigh.push_back(y*(len)+x + 1);
			neigh.push_back((y + 1)*(len)+x);
			neigh.push_back((y - 1)*(len)+x);
			return neigh;

		}
		if (y == (b - 1)) {
			neigh.push_back(y*(len)+x - 1);
			neigh.push_back(y*(len)+x + 1);
			neigh.push_back((y - 1)*(len)+x);
			return neigh;
		}
		if (y == 0) {
			neigh.push_back(y*(len)+x - 1);
			neigh.push_back(y*(len)+x + 1);
			neigh.push_back((y + 1)*(len)+x);
			return neigh;

		}
		else {
			neigh.push_back(y*(len)+x - 1);
			neigh.push_back(y*(len)+x + 1);
			neigh.push_back((y + 1)*(len)+x);
			neigh.push_back((y - 1)*(len)+x);
			return neigh;
		}
	}

	void addEdge(Vertex from, Vertex to, int countVertecies) override {
		//adj_lists[from].push_back(to);
		//adj_lists[to].push_back(from);
	}
	TableGraph(size_t leng, size_t br) {
		len = leng;
		bright = br;
	}

	size_t getNumberofVertecies() override {
		return len * bright;
	}
private:
	size_t len;
	size_t bright;
};


namespace GraphProcessing {

	void bfs_visit(Graph &listGraph, size_t start, queue<size_t> &q, vector<bool> &used, vector<size_t> &ancestors, vector<size_t> &dist, set<size_t> &one) {
		size_t countVert = listGraph.getNumberofVertecies();
		q.push(start);
		//cout << start << "start" << endl;
		used[start] = true;
		ancestors[start] = -1;
		while (!q.empty()) {
			size_t to = q.front();
			q.pop();
			//cout << to << "to";
			vector<size_t> neighbours = listGraph.getNeibours(to, countVert);
			for (int i = 0;i < neighbours.size();++i) {
				size_t vert = neighbours[i];
				if (!used[vert]) {
					q.push(vert);
					used[vert] = true;
					ancestors[vert] = to;
					if (one.count(to) != 0) {
						dist[to] = 0;
					}
					dist[vert] = dist[to] + 1;
					if (one.count(vert) != 0) {
						dist[vert] = 0;
					}
					//cout << "vert" << vert << dist[to] << dist[vert]<<endl;

				}
			}
		}
	}

	void bfs(Graph &listGraph, size_t start) {
		size_t countVert = listGraph.getNumberofVertecies();
		queue<size_t> q;
		q.push(start);
		set<size_t> one;
		vector<size_t> dist(countVert, 0);
		vector<bool> used(countVert, false);
		vector<size_t> ancestors(countVert, -1);
		bfs_visit(listGraph, start, q, used, ancestors, dist, one);
	}

	void getPath(Graph &listGraph, size_t start, size_t finish) {
		size_t countVert = listGraph.getNumberofVertecies();
		queue<size_t> q;
		q.push(start);
		set<size_t> one;
		vector<bool> used(countVert, false);
		vector<size_t> ancestors(countVert, -1);
		vector<size_t> dist(countVert, 0);
		bfs_visit(listGraph, start, q, used, ancestors, dist, one);
		if (!used[finish]) {
			cout << -1;
		}
		else {
			vector<size_t> path;
			for (size_t v = finish; v != -1; v = ancestors[v]) {
				path.push_back(v);
			}
			reverse(path.begin(), path.end());
			cout << path.size() - 1 << endl;
			for (size_t k = 0; k < path.size();++k) {
				cout << path[k] + 1 << " ";
			}
		}
	}

	void Table(size_t brigth, size_t length) {
		int val;
		size_t countVert = length * brigth;
		vector<size_t> ones;
		TableGraph listGraph(length, brigth);
		queue<size_t> q;
		set<size_t> one;
		vector<bool> used(countVert, false);
		vector<size_t> ancestors(countVert, -1);
		vector<size_t> dist(countVert, 0);
		for (int i = 0;i < brigth;++i) {
			for (int j = 0;j < length;++j) {
				cin >> val;
				if (val == 1) {
					q.push(i*length + j);
					ones.push_back(i*length + j);
					one.insert(i*length + j);
				}
			}
		}
		//cout << q.size();
		size_t start = q.front();
		//cout << "yyyyyy" << endl;
		bfs_visit(listGraph, start, q, used, ancestors, dist, one);
		for (int i = 0; i < ones.size();++i) {
			dist[ones[i]] = 0;
		}
		for (int i = 0;i < (brigth - 1);++i) {
			for (int j = 0;j < (length - 1);++j) {
				cout << dist[i*length + j] << " ";
			}
			cout << dist[i*length + length - 1];
			cout << endl;
		}
		for (int j = 0;j < length;++j) {
			cout << dist[(brigth - 1)*length + j] << " ";
		}
	}
}

using namespace GraphProcessing;


int main() {
	size_t countVertecies, countEdges, start, finish;
	std::cin >> countVertecies >> countEdges;
	Table(countVertecies, countEdges);
	getchar();
	getchar();
	return 0;
}
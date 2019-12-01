#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <climits>

using namespace std;

const static int INF = INT_MAX;

class Graph {
public:
	typedef size_t Vertex;
	virtual vector<Vertex> getNeibours(Vertex v, int countVertecies) = 0;
	virtual void addEdge(Vertex from, Vertex to, int countVertecies, int weight) = 0;
	virtual size_t getNumberofVertecies() = 0;
	virtual vector<vector<int>> getMatrix() = 0;

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
	void addEdge(Vertex from, Vertex to, int countVertecies, int weight) override {
		has_edge[from][to] = weight;
	}
	AdjMatrixGraph(size_t countVerrecies, size_t countEdges) {
		Vertex from, to;
		int weight;
		vector<int> stringofMatrix;
		for (int i = 0; i < countVerrecies; ++i) {
			has_edge.push_back(stringofMatrix);
		}
		for (int i = 0; i < countEdges; ++i) {
			std::cin >> from >> to >> weight;
			addEdge(from, to, countVerrecies, weight);
		}
	}
	AdjMatrixGraph(size_t countVerrecies) {
		int weight;
		vector<int> stringofMatrix(countVerrecies, INF);
		for (size_t i = 0; i < countVerrecies; ++i) {
			has_edge.push_back(stringofMatrix);
		}
		for (Vertex from = 0; from < countVerrecies; ++from) {
			for (Vertex to = 0; to < countVerrecies; ++to) {
				std::cin >> weight;
				//cout << weight;
				if (weight != -1) {
					addEdge(from, to, countVerrecies, weight);
				}
				if (weight == (-1)) {
					addEdge(from, to, countVerrecies, INF);
				}
			}
		}
	}
	size_t getNumberofVertecies() override {
		return has_edge.size();
	}

	vector<vector<int>> getMatrix() {
		return has_edge;
	}
private:
	std::vector<std::vector<int>> has_edge;
};


namespace GraphProcessing {

	vector<vector<int>> Floyd(Graph &grap) {
		vector<vector<int>> dist = grap.getMatrix();
		size_t countVert = grap.getNumberofVertecies();
		/*for (int i=0;i< countVert;++i) {
		for (int j=0;j< countVert;++j) {
		cout << dist[i][j] << " ";
		}
		cout << endl;
		}*/
		for (int k = 0;k < countVert;++k) {
			for (int i = 0;i < countVert;++i) {
				for (int j = 0;j < countVert;++j) {
					if (dist[i][k] < INF && dist[k][j] < INF) {
						dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
						//cout << dist[0][1] << dist[i][k] << dist[k][j] << endl;
					}
				}
			}
		}
		return dist;
	}
}

using namespace GraphProcessing;


int main() {
	size_t countVertecies, start, finish;
	std::cin >> countVertecies >> start >> finish;
	AdjMatrixGraph listGraph(countVertecies);
	vector<vector<int>> dist = Floyd(listGraph);

	if (dist[start - 1][finish - 1] < (INF - 100)) {
		cout << dist[start - 1][finish - 1];
	}
	else {
		cout << -1;
	}
	getchar();
	getchar();
	return 0;
}
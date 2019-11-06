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
	virtual vector<pair<Vertex, int>> getNeibours(Vertex v, int countVertecies) = 0;
	virtual void addEdge(Vertex from, Vertex to, int countVertecies, int weight) = 0;
	virtual size_t getNumberofVertecies() = 0;

};

class AdjListsGraph : public Graph {
public:
	vector<pair<Vertex, int>> getNeibours(Vertex v, int countVertecies) override {
		return adj_lists[v];
	}
	void addEdge(Vertex from, Vertex to, int weight, int countVertecies) override {
		adj_lists[from].push_back(make_pair(to, weight));
	}
	AdjListsGraph(size_t countVerrecies, size_t countEdges) {
		Vertex from, to;
		int weight;
		std::vector<pair<Vertex, int>> t;
		for (int i = 0; i < countVerrecies; ++i) {
			adj_lists.push_back(t);
		}
		for (int i = 0; i < countEdges; ++i) {
			std::cin >> from >> to >> weight;
			addEdge(from - 1, to - 1, weight, countVerrecies);
			//addEdge(to - 1, from - 1, weight, countVerrecies);
		}
	}
	AdjListsGraph(size_t countVerrecies) {
		Vertex from, to;
		bool is_edge;
		vector<pair<Vertex, int>> stringofMatrix;
		for (size_t i = 0; i < countVerrecies; ++i) {
			adj_lists.push_back(stringofMatrix);
		}
		for (size_t from = 0; from < countVerrecies; ++from) {
			for (size_t to = 0; to < countVerrecies; ++to) {
				int weight;
				std::cin >> weight;
				addEdge(from, to, weight, countVerrecies);
			}
		}
	}

	size_t getNumberofVertecies() override {
		return adj_lists.size();
	}
private:
	std::vector<std::vector<pair<Vertex, int>>> adj_lists;
};


namespace GraphProcessing {
	int Prime_tree(Graph &listGraph) {
		const int INF = 2000000;
		size_t countVertecies = listGraph.getNumberofVertecies();
		vector<int> minEdge(countVertecies, INF);
		vector<size_t> sel_edge(countVertecies, INF);
		minEdge[0] = 0;
		set<pair<int, int>> heap;
		heap.insert(make_pair(0, 0));
		for (int i = 0; i < countVertecies; ++i) {
			if (heap.empty()) {
				break;
			}
			int v = heap.begin()->second;
			heap.erase(heap.begin());
			if (sel_edge[v] != INF) {
			}
			vector<pair<size_t, int>> neighbours = listGraph.getNeibours(v, countVertecies);
			for (size_t j = 0; j < neighbours.size(); ++j) {
				size_t to = neighbours[j].first;
				int cost = neighbours[j].second;
				if (cost < minEdge[to]) {
					heap.erase(make_pair(minEdge[to], to));
					minEdge[to] = cost;
					sel_edge[to] = v;
					//cout << v << " " << minEdge[to] << " " << cost << " " << to << endl;
					heap.insert(make_pair(minEdge[to], to));
				}
			}

		}
		int result = 0;
		for (int i = 0; i < minEdge.size(); ++i) {
			result += minEdge[i];
			//cout << i << minEdge[i] << endl;
		}
		cout << result;
		return result;

	}

	vector<int> Ford_Bellman(Graph &listGraph) {
		const static size_t INF = 99999;
		size_t countVertecies = listGraph.getNumberofVertecies();
		vector<int> distance(countVertecies, INF);
		distance[0] = 0;
		for (size_t i = 0; i < countVertecies; ++i) {
			for (size_t j = 0; j < countVertecies; ++j) {
				vector<pair<size_t, int>> neighbours = listGraph.getNeibours(j, countVertecies);
				for (size_t k = 0; k < neighbours.size();++k) {
					if (distance[neighbours[k].first] > distance[j] + neighbours[k].second) {
						distance[neighbours[k].first] = distance[j] + neighbours[k].second;
					}
				}
			}
		}
		return distance;
	}



}

using namespace GraphProcessing;


int main() {
	size_t countVertecies, countEdges;
	std::cin >> countVertecies >> countEdges;
	AdjListsGraph listGraph(countVertecies, countEdges);
	vector<int> dist = Ford_Bellman(listGraph);
	for (size_t i = 0; i < dist.size() - 1; ++i) {
		if (dist[i] < 98000) {
			cout << dist[i] << " ";
		}
		else {
			cout << 30000 << " ";
		}
	}
	if (dist[dist.size() - 1] < 98000) {
		cout << dist[dist.size() - 1];
	}
	else {
		cout << 30000;
	}
	getchar();
	getchar();
	return 0;
}
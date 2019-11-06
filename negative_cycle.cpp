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
				if (weight < 100000) {
					addEdge(from, to, weight, countVerrecies);
				}
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

	void Relax(Graph &listGraph, vector<int> &distance, vector<int> &ancestors) {
		size_t countVertecies = listGraph.getNumberofVertecies();
		int result = -1;
		for (size_t j = 0; j < countVertecies; ++j) {
			vector<pair<size_t, int>> neighbours = listGraph.getNeibours(j, countVertecies);
			for (size_t k = 0; k < neighbours.size();++k) {
				//cout << k << j << distance[neighbours[k].first] << distance[j] + neighbours[k].second << endl;
				if (distance[neighbours[k].first] > distance[j] + neighbours[k].second) {
					//cout << "ppp" << distance[neighbours[k].first];
					distance[neighbours[k].first] = distance[j] + neighbours[k].second;
					//cout << neighbours[k].first << distance[neighbours[k].first];
					ancestors[neighbours[k].first] = j;
					result = neighbours[k].first;

				}
			}
		}
	}



	vector<int> Ford_Bellman(Graph &listGraph, vector<int> &ancestors) {
		const static size_t INF = 99999;
		size_t countVertecies = listGraph.getNumberofVertecies();
		vector<int> distance(countVertecies + 1, INF);
		//vector<int> ancestors(countVertecies, INF);
		int result = -1;
		distance[0] = 0;
		for (size_t i = 0; i < countVertecies + 1; ++i) {
			for (size_t j = 0; j < countVertecies; ++j) {
				vector<pair<size_t, int>> neighbours = listGraph.getNeibours(j, countVertecies);
				for (size_t k = 0; k < neighbours.size();++k) {
					if (distance[neighbours[k].first] > distance[j] + neighbours[k].second) {
						distance[neighbours[k].first] = distance[j] + neighbours[k].second;
						ancestors[neighbours[k].first] = j;
						result = neighbours[k].first;

					}
				}
			}
		}
		//if (result == -1) {
		//	cout << "NO";
		//}
		//else {
		//	cout << "YES" << endl;

		//}
		return distance;
	}

	vector<size_t> FindNegativaCycle(Graph &listGraph, vector<int> &ancestors, size_t &vert) {
		size_t countVert = listGraph.getNumberofVertecies();
		size_t current_vertex = vert;
		vector<bool> used(countVert + 1, false);
		while (!used[current_vertex]) {
			used[current_vertex] = true;
			current_vertex = ancestors[current_vertex];
		}
		vector<size_t> negative_cycle;
		size_t cycle_end = current_vertex;
		negative_cycle.push_back(cycle_end);
		current_vertex = ancestors[current_vertex];
		while (current_vertex != cycle_end) {
			negative_cycle.push_back(current_vertex);
			current_vertex = ancestors[current_vertex];
		}
		negative_cycle.push_back(cycle_end);
		return negative_cycle;

	}

	vector<size_t> negative_cycle(Graph &listGraph) {
		const static size_t INF = 0;
		size_t countVertecies = listGraph.getNumberofVertecies();
		vector<int> ancestors(countVertecies + 1, INF);
		vector<int> dist = Ford_Bellman(listGraph, ancestors);
		vector<int> distance_relax = dist;
		//cout << dist[1] << "mmmm";
		Relax(listGraph, distance_relax, ancestors);
		//cout << distance_relax[1] << dist[1] << "yyyy";
		size_t start_Cycle = -1;
		//cout << countVertecies;
		for (size_t i = 0; i < countVertecies + 1;++i) {
			//cout << dist[i] << distance_relax[i] << endl;
			if (dist[i] != distance_relax[i]) {
				//cout << i << dist[i] << distance_relax[i] << "uuuuu" << endl;
				start_Cycle = i;
				break;
			}
		}

		vector<size_t> result;
		if (start_Cycle == -1) {
			//cout << "oooo";
			return result;
		}
		result = FindNegativaCycle(listGraph, ancestors, start_Cycle);
		return { result.rbegin(), result.rend() };

	}



}

using namespace GraphProcessing;


int main() {
	size_t countVertecies, countEdges;
	std::cin >> countVertecies;
	AdjListsGraph listGraph(countVertecies);
	vector<size_t> cycle = negative_cycle(listGraph);
	if (cycle.empty()) {
		cout << "NO";
	}
	else {
		cout << "YES" << endl;
		cout << cycle.size() << endl;
		for (size_t i = 0; i < cycle.size(); ++i) {
			cout << cycle[i] + 1 << " ";

		}
	}
	getchar();
	getchar();
	return 0;
}
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
	virtual vector<pair<Vertex, pair<int, int>>> getNeibours(Vertex v, int countVertecies) = 0;
	virtual void addEdge(Vertex from, Vertex to, int departure_time, int arrival_time) = 0;
	virtual size_t getNumberofVertecies() = 0;

};

class AdjListsGraph : public Graph {
public:
	vector<pair<Vertex, pair<int, int>>> getNeibours(Vertex v, int countVertecies) override {
		return adj_lists[v];
	}
	void addEdge(Vertex from, Vertex to, int departure_time, int arrival_time) override {
		adj_lists[from].push_back(make_pair(to, make_pair(departure_time, arrival_time)));
	}
	AdjListsGraph(size_t countVerrecies, size_t countEdges) {
		Vertex from, to;
		int arrival_time, departure_time;
		std::vector<pair<Vertex, pair<int, int>>> t;
		for (int i = 0; i < countVerrecies; ++i) {
			adj_lists.push_back(t);
		}
		for (int i = 0; i < countEdges; ++i) {
			std::cin >> from >> departure_time >> to >> arrival_time;
			addEdge(from - 1, to - 1, departure_time, arrival_time);
		}
	}


	size_t getNumberofVertecies() override {
		return adj_lists.size();
	}
private:
	std::vector<std::vector<pair<Vertex, pair<int, int>>>> adj_lists;
};


namespace GraphProcessing {

	vector<int> Ford_Bellman(Graph &listGraph, size_t start, size_t countEdges) {
		const static size_t INF = std::numeric_limits<int>::max();
		size_t countVertecies = listGraph.getNumberofVertecies();
		vector<int> distance(countVertecies, INF);
		vector<size_t> ancestors(countVertecies, -1);
		vector<int> arrivals(countVertecies, INF);
		distance[start] = 0;
		arrivals[start] = 0;
		for (size_t i = 0; i < countEdges; ++i) {
			for (size_t j = 0; j < countVertecies; ++j) {
				vector<pair<size_t, pair<int, int>>> neighbours = listGraph.getNeibours(j, countVertecies);
				for (size_t k = 0; k < neighbours.size();++k) {
					//cout << arrivals[j] << neighbours[k].first << distance[neighbours[k].first] << neighbours[k].second.first <<" " << neighbours[k].second.second<< " " <<(neighbours[k].second.second - arrivals[j])<< endl;
					if ((distance[neighbours[k].first] >= distance[j] + (neighbours[k].second.second - arrivals[j])) && (neighbours[k].second.first >= arrivals[j])) {
						//cout << "ppp";
						distance[neighbours[k].first] = distance[j] + neighbours[k].second.second - arrivals[j];
						arrivals[neighbours[k].first] = neighbours[k].second.second;
					}
				}
			}
		}
		return distance;
	}



}

using namespace GraphProcessing;


int main() {
	size_t countVertecies, countEdges, start, finish;
	std::cin >> countVertecies >> start >> finish >> countEdges;
	AdjListsGraph listGraph(countVertecies, countEdges);
	vector<int> dist = Ford_Bellman(listGraph, start - 1, countEdges);
	cout << dist[finish - 1];
	getchar();
	getchar();
	return 0;
}
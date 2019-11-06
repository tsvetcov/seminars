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


namespace GraphProcessing {


	void trafficLight(Graph &listGraph) {
		size_t countVertecies = listGraph.getNumberofVertecies();
		for (size_t i = 0; i < countVertecies; ++i) {
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

	bool dfs_visit(Graph &listGraph, size_t v, vector<size_t> &blacks, vector<size_t> &time_in, vector<size_t> &time_out, vector<size_t> &colour, size_t &timer, size_t &cycle_st, size_t &cycle_end, vector<size_t> &ancestors) {
		size_t countVertecies = listGraph.getNumberofVertecies();
		time_in[v] = timer++;
		colour[v] = 1;
		vector<size_t> Neighbours = listGraph.getNeibours(v, countVertecies);
		for (auto iter = Neighbours.begin(); iter != Neighbours.end(); ++iter) {
			//cout << *iter << colour[*iter] << " ";
			if (colour[*iter] == 0) {
				ancestors[*iter] = v;
				//cout << v << *iter << endl;
				if (dfs_visit(listGraph, *iter, blacks, time_in, time_out, colour, timer, cycle_st, cycle_end, ancestors)) return true;
			}
			else {
				if (colour[*iter] == 1) {
					cycle_st = *iter;
					cycle_end = v;
					//cout << v << *iter << endl;
					//cout << cycle_st << cycle_end << ancestors[1] << endl;
					return true;
				}
			}
		}
		colour[v] = 2;
		time_out[v] = timer++;
		//cout << v << " ";
		blacks.push_back(v);
		return false;
	}



	bool dfs(Graph &listGraph, size_t v, vector<size_t> &blacks) {
		size_t timer = 0;
		size_t numberofVertecies = listGraph.getNumberofVertecies();
		size_t cycle_st = -1;
		size_t cycle_end = -1;
		vector<size_t> ancestors(numberofVertecies, -1);
		vector<size_t> time_in(numberofVertecies, 0);
		vector<size_t> time_out(numberofVertecies, 0);
		vector<size_t> colour(numberofVertecies, 0);
		return dfs_visit(listGraph, v, blacks, time_in, time_out, colour, timer, cycle_st, cycle_end, ancestors);
	}

	vector<size_t> topological_sort_if_no_cycle(Graph &listGraph) {
		size_t timer = 0;
		size_t numberofVertecies = listGraph.getNumberofVertecies();
		size_t cycle_st = -1;
		size_t cycle_end = -1;
		vector<size_t> ancestors(numberofVertecies, -1);
		vector<size_t> time_in(numberofVertecies, 0);
		vector<size_t> time_out(numberofVertecies, 0);
		vector<size_t> colour(numberofVertecies, 0);
		vector<size_t> blacks;
		for (auto iter = 0; iter < numberofVertecies; ++iter) {
			if (colour[iter] == 0) {
				dfs_visit(listGraph, iter, blacks, time_in, time_out, colour, timer, cycle_st, cycle_end, ancestors);
			}
		}
		reverse(blacks.begin(), blacks.end());
		return blacks;
	}

	void isCycle(Graph &listGraph) {
		size_t countVertecies = listGraph.getNumberofVertecies();
		size_t timer = 0;
		size_t cycle_st = -1;
		size_t cycle_end = -1;
		vector<size_t> ancestors(countVertecies, -1);
		size_t numberofVertecies = listGraph.getNumberofVertecies();
		vector<size_t> time_in(numberofVertecies, 0);
		vector<size_t> time_out(numberofVertecies, 0);
		vector<size_t> colour(numberofVertecies, 0);
		vector<size_t> blacks(countVertecies, 0);
		bool isCycle = false;
		for (auto iter = 0; iter < countVertecies; ++iter) {
			if (dfs_visit(listGraph, iter, blacks, time_in, time_out, colour, timer, cycle_st, cycle_end, ancestors)) {
				break;
			}
		}
		if (cycle_st == -1) {
			cout << "NO";
		}

		else {
			cout << "YES" << endl;
			vector<size_t> cycle;
			for (auto i = cycle_end; i != cycle_st; i = ancestors[i]) {
				cycle.push_back(i);
			}
			cycle.push_back(cycle_st);
			reverse(cycle.begin(), cycle.end());
			if (cycle.size() == 1) {
				cout << cycle_st + 1 << " " << cycle_end + 1 << " ";
			}
			else {
				for (auto iter = cycle.begin(); iter != cycle.end(); iter++) {
					cout << *iter + 1 << " ";
				}
			}
		}
	}

	void topological_sort(Graph &listGraph) {
		size_t countVertecies = listGraph.getNumberofVertecies();
		size_t timer = 0;
		size_t cycle_st = -1;
		size_t cycle_end = -1;
		vector<size_t> ancestors(countVertecies, -1);
		size_t numberofVertecies = listGraph.getNumberofVertecies();
		vector<size_t> time_in(numberofVertecies, 0);
		vector<size_t> time_out(numberofVertecies, 0);
		vector<size_t> colour(numberofVertecies, 0);
		vector<size_t> blacks(countVertecies, 0);
		bool isCycle = false;
		for (auto iter = 0; iter < countVertecies; ++iter) {
			isCycle = isCycle | dfs_visit(listGraph, iter, blacks, time_in, time_out, colour, timer, cycle_st, cycle_end, ancestors);
		}
		if (!isCycle) {
			vector<size_t> answer = topological_sort_if_no_cycle(listGraph);
			for (size_t i = 0; i < answer.size(); ++i) {
				cout << answer[i] + 1 << " ";
			}
		}

		else {
			cout << -1;
		}
	}
}

using namespace GraphProcessing;


int main() {
	size_t countVertecies, countEdges;
	std::cin >> countVertecies >> countEdges;
	AdjListsGraph listGraph(countVertecies, countEdges);
	isCycle(listGraph);
	getchar();
	getchar();
	return 0;
}
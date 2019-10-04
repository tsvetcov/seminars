#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef size_t vertex;
/*class vertex {
private:
int id;
public:
int getId() {
return id;
}
vertex(int _id);
bool operator<(vertex a) const {
return (id < a.getId());
}
};

/vertex::vertex(int _id) :
id(_id)
{}

class edge {
public:
vertex start, finish;
double weight;
edge(int s, int f);
};

edge::edge(int s, int f) :
start(s)
, finish(f)
{
weight = 1;

}*/

class GraphAlgorithms {
	//virtual int CountVertex();
};

class Graph :public GraphAlgorithms {
public:
	Graph(int countVertex, int CountEdge);
	int CountVertex();
	bool dfs(vertex v);
	bool topological_sort(int CountVertex);
private:
	std::vector <vector<vertex>> gr;
};

Graph::Graph(int countVertex, int CountEdge) {
	int start, finish;
	vector<vertex> t;
	for (int i = 0; i < countVertex; ++i) {
		gr.push_back(t);
	}
	for (vertex i = 0; i < CountEdge; ++i) {
		std::cin >> start >> finish;
		gr[start - 1].push_back(finish - 1);
	}
}

int n;
vector<vertex> cl(150);
vector<vertex> p(150, -1);
int cycle_st, cycle_end;
vector<vertex> ans(150);
vector<bool> used(150);

bool Graph::dfs(vertex v) {
	cl[v] = 1;
	for (size_t i = 0; i<gr[v].size(); ++i) {
		vertex to = gr[v][i];
		if ((cl[to] == 0)) {
			p[to] = v;
			//std::cout << v << to << std::endl;
			if (dfs(to))  return true;
		}
		else if (cl[to] == 1) {
			cycle_end = v;
			cycle_st = to;
			//cout << "ppppppp";
			return true;
		}
	}
	cl[v] = 2;
	ans.push_back(v);
	for (int i = 0; i<ans.size(); ++i) {
		//std::cout << ans[i] << endl;
	}
	return false;
}

bool Graph::topological_sort(int CountVertex) {
	bool cycle;
	for (int i = 0; i<CountVertex; ++i)
		cl[i] = 0;
	ans.clear();
	for (int i = 0; i < CountVertex; ++i) {
		if (cl[i] == 0) {
			cycle = dfs(i);
			if (cycle == 1) {
				return true;
			}
		}
	}
	reverse(ans.begin(), ans.end());
	return cycle;
}

int Graph::CountVertex() {
	int r = 0;
	for (auto i = gr.begin(); i != gr.end(); ++i) {
		//auto y = gr[i];
		r += i->size();
		//cout << i->size();
	}
	return r;
}

int main() {
	int CountVertex, CountEdge;
	std::cin >> CountVertex >> CountEdge;
	Graph g(CountVertex, CountEdge);
	bool cycle = g.topological_sort(CountVertex);
	//cout << endl;
	//cout << endl;
	//cout << ans.size();
	if (cycle) {
		std::cout << "No";
		//std::cout << cycle << std::endl;
	}
	else {
		std::cout << "Yes" << std::endl;
		for (auto iter = ans.begin(); iter != ans.end(); ++iter) {
			std::cout << *iter + 1 << " ";
		}
	}
	return 0;
}
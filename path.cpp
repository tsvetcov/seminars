#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const static int MAXN = 1000000;
vector<vector<int>> vert;

int enter1[MAXN];
int enter2[MAXN];
const static int BigNumber = 8888888;

using namespace std;

typedef size_t vertex;

class GraphAlgorithms {
	//virtual int CountVertex();
};
queue<vertex> q;
class Graph :public GraphAlgorithms {
public:
	Graph(int countVertex);
	int CountVertex();
	bool dfs(vertex v);
	void bfs(vertex v);
	bool topological_sort(int CountVertex);
private:
	std::vector <vector<vertex>> gr;
};


Graph::Graph(int CountVertex) {
	int start, finish;
	int one;
	vector<vertex> t;
	for (int i = 0; i < CountVertex; ++i) {
		gr.push_back(t);
	}
	for (vertex i = 0; i < CountVertex; ++i) {
		for (vertex j = 0; j < CountVertex; ++j) {
			std::cin >> one;
			if (one != 0) {
				gr[i].push_back(j);
			}
		}
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
			if (dfs(to))  return true;
		}
		else if (cl[to] == 1) {
			cycle_end = v;
			cycle_st = to;
			return true;
		}
	}
	cl[v] = 2;
	ans.push_back(v);
	for (int i = 0; i<ans.size(); ++i) {
	}
	return false;
}

vector<vertex> path;
vector<vertex> d(150);
//vector<bool> used(150);
void Graph::bfs(vertex start) {
	q.push(start);
	used[start] = true;
	for (int i = 0; i < 150; ++i) {
		p[i] = BigNumber;
	}
	p[start] = -1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < gr[v].size(); ++i) {
			int temp = gr[v][i];
			if (!used[temp]) {
				used[temp] = true;
				q.push(temp);
				d[temp] = d[v] + 1;
				p[temp] = v;
			}
		}
	}
}

int main() {
	vertex CountVertex, m;
	cin >> CountVertex;
	Graph gr = Graph(CountVertex);
	int a, b;
	int start, finish;
	cin >> start >> finish;
	start--;
	finish--;
	gr.bfs(start);
	vector<int> path;
	int temp = finish;
	if (!used[temp]) {
		cout << -1;
	}
	else {
		for (int k = temp; k != -1; k = p[k]) {
			path.push_back(k);
		}
		reverse(path.begin(), path.end());
		cout << path.size() - 1 << endl;
		if (path.size() != 1) {
			for (auto iter = path.begin(); iter != path.end(); iter++) {
				cout << *iter + 1 << " ";
			}
		}
	}

	getchar();
	getchar();
	return 0;
}
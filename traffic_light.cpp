#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//template <class T>
typedef size_t vertex;

class Graph {
public:
	Graph(int m, int countV);
	int coun();
private:
	std::vector<vector<vertex>> gr;
};

Graph::Graph(int m, int countV) {
	vertex start, finish;
	vector<vertex> t;
	for (int i = 0; i < countV; ++i) {
		gr.push_back(t);
	}
	for (int i = 0; i < m; ++i) {
		std::cin >> start >> finish;
		gr[start - 1].push_back(finish - 1);
		gr[finish - 1].push_back(start - 1);


	}
}
int Graph::coun() {
	int r = 0;
	for (auto i = gr.begin(); i != gr.end(); ++i) {
		cout << i->size() << " ";
	}
	return 0;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	Graph g(m, n);
	int w = g.coun();
	return 0;
}
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//template <class T>
class vertex {
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

vertex::vertex(int _id) :
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

}

class Graph {
public:
	Graph(int countV);
	int coun();
private:
	std::map < vertex, std::map<vertex, edge>> gr;
};

Graph::Graph(int countV) {
	int temp;
	map<vertex, edge> t;
	for (int i = 0; i < countV; ++i) {
		gr[vertex(i)] = t;
	}
	for (int i = 0; i < countV; ++i) {
		//cout << endl;
		for (int j = 0; j < countV; ++j) {
			std::cin >> temp;
			//cout << temp;
			if (temp != 0) {
				gr[vertex(i)].insert(make_pair(vertex(j), edge(i, j)));
				gr[vertex(j)].insert(make_pair(vertex(i), edge(j, i)));
				//cout << gr[vertex(1)].size() << " ";
			}
		}
	}
}
int Graph::coun() {
	int r = 0;
	for (auto i = gr.begin(); i != gr.end(); ++i) {
		auto y = i->first;
		r += gr[y].size();
		//cout << gr[y].size();
	}
	return r;
}

int main() {
	int n;
	std::cin >> n;
	Graph g(n);
	int w = g.coun();
	std::cout << w / 2;
	return 0;
}
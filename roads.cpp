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
	Graph(int countVertex);
	int CountVertex();
private:
	std::vector <vector<vertex>> gr;
};

Graph::Graph(int countVertex) {
	int temp;
	vector<vertex> t;
	for (int i = 0; i < countVertex; ++i) {
		gr.push_back(t);
	}
	for (int i = 0; i < countVertex; ++i) {
		for (int j = 0; j < countVertex; ++j) {
			std::cin >> temp;
			if (temp != 0) {
				gr[i].push_back(j);
				//gr[j].push_back(i);
			}
		}
	}
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
	int n;
	std::cin >> n;
	Graph g(n);
	int w = g.CountVertex();
	std::cout << w / 2;
	return 0;
}
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef size_t vertex;

class GraphAlgorithms {
	virtual void Abstr(void) = 0;
};

class Graph :public GraphAlgorithms {
public:
	void Abstr(void) { std::cout << " call function graph.Abstr();"; }
	Graph(int countVertex);
	int CountVertex();
	Graph(int start, int finish);
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
			}
		}
	}
}

Graph::Graph(int start, int finish) {
	int Quotent, b, Reminder;
	vector<vertex> u;
	for (int j = 0; j < 10001; ++j) {
		gr.push_back(u);
	}
	for (int i = 1000; i <= 9999; ++i) {
		int Number = i;
		if (Number % 10 == 0) continue;
		Number = Number / 10;
		if (Number % 10 == 0) continue;
		Number = Number / 10;
		if (Number % 10 == 0) continue;
		Number = Number / 10;
		if (Number % 10 == 0) continue;
		Number = Number / 10;

		if (i / 1000 != 9) {
			Reminder = ((i / 1000) + 1) * 1000 + i % 1000;
			gr[i].push_back(Reminder);
		}
		if (i % 10 != 1) {
			Reminder = (i % 10) - 1 + (i / 10) * 10;
			gr[i].push_back(Reminder);
		}
		Quotent = i % 1000;
		b = i / 1000;
		Reminder = Quotent * 10 + b;
		gr[i].push_back(Reminder);
		Quotent = i % 10;
		b = i / 10;
		int Reminder = Quotent * 1000 + b;
		gr[i].push_back(Reminder);
	}
}
int Graph::CountVertex() {
	int r = 0;
	for (auto i = gr.begin(); i != gr.end(); ++i) {
		r += i->size();
	}
	return r;
}

const static int MAXN = 1000000;
vector<vector<int>> a;
const static int BigNumber = 888888888;


int enter1[MAXN];
int enter2[MAXN];
int main() {
	int start, finish;
	cin >> start >> finish;
	Graph mainGraph=Graph(start, finish);
	vector<bool> used(MAXN);
	queue<int> q;
	q.push(start);
	used[start] = true;
	vector<int> p(10000), d(10000);
	for (int i = 0; i < 10000; ++i) {
		p[i] = BigNumber;
	}
	p[start] = -1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < a[v].size(); ++i) {
			int temp = a[v][i];
			if (!used[temp]) {
				used[temp] = true;
				q.push(temp);
				d[temp] = d[v] + 1;
				p[temp] = v;
			}
		}
	}
	vector<int> path;
	int temp = finish;
	if (used[temp] == false) {
		cout << start << endl;
		cout << finish << endl;
		exit(finish);
	}
	else {
		for (int k = temp; k != -1; k = p[k]) {
			path.push_back(k);
		}
		reverse(path.begin(), path.end());
		if (start != finish) {
			if (path.size() != 0) {
				for (auto iter = path.begin(); iter != path.end(); iter++) {
					cout << *iter << endl;
				}
			}
		}
	}
	if (start == finish) {
		cout << start << endl;
		cout << start << endl;
	}

	getchar();
	getchar();
	return 0;
}
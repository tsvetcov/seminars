#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;


int main() {
	int m, n;
	vector<vector<int>> table;
	vector<int> u;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		table.push_back(u);
	}
	int temp;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> temp;
			table[i].push_back(temp);
		}
	}
	int s;
	vector<int> val(m*n + 2);
	vector<vector<int>> a;
	vector<int> h(m*n);
	for (int i = 0; i < (n*m + 2); ++i) {
		a.push_back(h);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			s = 1 + i * m + j;
			val[s] = table[i][j];
			if (i != 0) {
				a[s].push_back(1 + (i - 1) * m + j);
			}
			if (i != n) {
				a[s].push_back(1 + (i + 1) * m + j);
			}
			if (j != 0) {
				a[s].push_back(i * m + j);
			}
			if (j != m) {
				a[s].push_back(2 + i * m + j);
			}
		}
	}
	vector<bool> used(m*n);
	vector<bool> d(m*n);
	queue<int> q;
	for (int i = 0; i < val.size(); ++i) {
		if (val[i] == 1) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int j = 0; j < a[v].size(); ++j) {
			int to = a[v][j];
			if (!used[to]) {
				used[to] = true;
				d[to] = d[v] + 1;

			}
		}
	}
	for (int i = 0; i < val.size(); ++i) {
		if (val[i] == 1) {
			d[i] = 0;
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << d[1 + i * m + j] << " ";

		}
		cout << endl;
	}
	return 0;
};
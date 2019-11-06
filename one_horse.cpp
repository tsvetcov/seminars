#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const static int MAXN = 1000000;
vector<vector<int>> a;


int enter1[MAXN];
int enter2[MAXN];
int main() {
	int n;
	cin >> n;
	int r, b;
	vector<int> u;
	int startx, starty, finishx, finishy;
	cin >> startx >> starty >> finishx >> finishy;
	int start = n * (startx - 1) + (starty - 1);
	int finish = n * (finishx - 1) + (finishy - 1);
	//cout << start << " " << finish << endl;
	for (int j = 0; j < n*n; ++j) {
		a.push_back(u);
	}
	// number of cell in (i, j) is (n - 1)*i + j
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i - 2 >= 0) {
				if (j + 1 < n) {
					a[(n*i + j)].push_back(n*(i - 2) + j + 1);
				}
				if (j - 1 >= 0) {
					a[(n*i + j)].push_back(n*(i - 2) + j - 1);
				}

			}
			if (i + 2 < n) {
				if (j + 1 < n) {
					a[n*i + j].push_back(n*(i + 2) + j + 1);
				}
				if (j - 1 >= 0) {
					a[n*i + j].push_back(n*(i + 2) + j - 1);
				}

			}
			if (i - 1 >= 0) {
				if (j + 2 < n) {
					a[(n*i + j)].push_back(n*(i - 1) + j + 2);
				}
				if (j - 2 >= 0) {
					a[n*i + j].push_back(n*(i - 1) + j - 2);
				}

			}
			if (i + 1 < n) {
				if (j + 2 < n) {
					a[(n*i + j)].push_back(n*(i + 1) + j + 2);
				}
				if (j - 2 >= 0) {
					a[n*i + j].push_back(n*(i + 1) + j - 2);
				}

			}

		}
	}
	//for (int i = 0; i< a[12].size(); ++i) {
	//	cout << a[12][i] << endl;
	//}
	//start--;
	//finish--;
	//cout << start << " " << finish << endl;
	vector<bool> used(n*n);
	queue<int> q;
	q.push(start);
	used[start] = true;
	vector<int> p(n*n), d(n*n);
	for (int i = 0; i < n*n; ++i) {
		p[i] = 888888888;
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
	if (!used[temp]) {
		cout << -1;
	}
	else {
		for (int k = temp; k != -1; k = p[k]) {
			path.push_back(k);
		}
		reverse(path.begin(), path.end());
		cout << path.size() - 1 << endl;
		if (path.size() != 0) {
			for (auto iter = path.begin(); iter != path.end(); iter++) {
				cout << (*iter / n) + 1 << " " << (*iter%n) + 1 << endl;
			}
		}
	}

	getchar();
	getchar();
	return 0;
}
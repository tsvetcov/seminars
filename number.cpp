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
	int start, finish;
	cin >> start >> finish;
	int r, b, pp;
	vector<int> u;
	for (int j = 0; j < 10001; ++j) {
		a.push_back(u);
	}
	for (int i = 1000; i <= 9999; ++i) {
		int hh = i;
		if (hh % 10 == 0) continue;
		hh = hh / 10;
		if (hh % 10 == 0) continue;
		hh = hh / 10;
		if (hh % 10 == 0) continue;
		hh = hh / 10;
		//cout << hh << " " << i << endl;
		if (hh % 10 == 0) continue;
		hh = hh / 10;

		if (i / 1000 != 9) {
			pp = ((i / 1000) + 1) * 1000 + i % 1000;
			//cout << pp << endl;
			a[i].push_back(pp);
		}
		if (i % 10 != 1) {
			pp = (i % 10) - 1 + (i / 10) * 10;
			//cout << pp << endl;
			a[i].push_back(pp);
		}
		r = i % 1000;
		b = i / 1000;
		pp = r * 10 + b;
		//cout <<i << " " <<  r << " " << pp << endl;
		a[i].push_back(pp);
		r = i % 10;
		b = i / 10;
		int pp = r * 1000 + b;
		//cout << pp << endl;
		a[i].push_back(pp);
	}
	//for (int i = 0; i< a[12].size(); ++i) {
	//	cout << a[12][i] << endl;
	//}
	//start--;
	//finish--;
	//cout << start << " " << finish << endl;
	vector<bool> used(10000);
	queue<int> q;
	q.push(start);
	used[start] = true;
	vector<int> p(10000), d(10000);
	for (int i = 0; i < 10000; ++i) {
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
		//cout << path.size() - 1 << endl;
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
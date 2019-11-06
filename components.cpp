#include <iostream>
#include <vector>


using namespace std;

vector<vector<int>> a;
vector<vector<int>> comp;
vector<int> co;
bool used[100000];
void dfs(int v) {
	used[v] = true;
	co.push_back(v);
	for (vector<int>::iterator it = a[v].begin(); it != a[v].end(); ++it) {
		if (!used[*it]) {
			dfs(*it);
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> uu;
	for (int i = 0; i<n; ++i) {
		a.push_back(uu);
	}
	int b, c;
	for (int i = 0; i < m; ++i) {
		cin >> b >> c;
		a[b - 1].push_back(c - 1);
		a[c - 1].push_back(b - 1);
	}
	for (int j = 0; j<n;++j) {
		if (!used[j]) {
			comp.push_back(co);
			co.clear();
			//co.push_back(j);
			dfs(j);
		}
	}
	comp.push_back(co);
	cout << comp.size() - 1 << endl;
	for (int i = 1; i < comp.size(); i++) {
		cout << comp[i].size() << endl;
		for (vector<int>::iterator iter = comp[i].begin(); iter != comp[i].end(); ++iter) {
			cout << *iter + 1 << " ";
		}
		cout << endl;
	}
	getchar();
	getchar();
	return 0;

}
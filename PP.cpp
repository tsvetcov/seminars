#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> prefix_func(string s) {
	int strLen = (int)s.length();
	vector<int> res(strLen);
	for (int i = 1;i < strLen;++i) {
		int j = res[i - 1];
		while (j > 0 && s[i] != s[j]) {
			j = res[j - 1];
		}
		if (s[i] == s[j]) {
			++j;
		}
		res[i] = j;
	}
	return res;
}

int main() {
	string s;
	cin >> s;
	vector<int> res = prefix_func(s);
	for (int i = 0; i < res.size(); ++i) {
		cout << res[i] << " ";
	}
	getchar();
	return 0;
};
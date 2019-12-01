#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> z_func(string s) {
	int strLen = (int)s.length();
	vector<int> z(strLen);
	for (int i = 1, l = 0, r = 0; i<strLen; ++i) {
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < strLen && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	z[0] = strLen;
	return z;
}

int main() {
	string s;
	cin >> s;
	vector<int> res = z_func(s);
	for (int i = 0; i < res.size(); ++i) {
		cout << res[i] << " ";
	}
	getchar();
	return 0;
};
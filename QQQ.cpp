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

vector<int> KMP(string str, string pattern) {
	vector<int> found;
	string common_str = pattern;
	common_str += '#';
	common_str += str;
	vector<int> prefix = prefix_func(common_str);
	size_t pattern_len = (size_t)pattern.length();
	for (int i = 0; i<prefix.size();++i) {
		if (prefix[i] == pattern_len) {
			found.push_back(i - 2 * pattern_len);
		}
	}
	return found;
}

int main() {
	string str, pattern;
	cin >> str >> pattern;
	vector<int> res = KMP(str, pattern);
	for (int i = 0; i < res.size(); ++i) {
		cout << res[i] << std::endl;
	}
	getchar();
	return 0;
};
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
vector<string> SplitIntoWords(const string& s) {
	vector<string> result;
	for (auto strstart = begin(s); strstart < end(s);) {
		auto i = find(strstart, end(s), ' ');
		result.push_back(string(strstart, i));
		strstart = i + 1;
	}
	return result;
}

int main() {
	string s = "C Cpp Java Python";

	vector<string> words = SplitIntoWords(s);
	cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			cout << "/";
		}
		cout << *it;
	}
	cout << endl;
	system("pause");
	return 0;
}
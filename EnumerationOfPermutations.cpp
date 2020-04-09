#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

inline void CreateRange(vector<int>& v) {
	iota(v.begin(), v.end(), 1);
	reverse(v.begin(), v.end());
}

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	CreateRange(v);
	do{
		for (int num : v) 
			cout << num << ' ';
		cout << endl;
	} while (prev_permutation(v.begin(), v.end()));
	system("pause");
	return 0;
}
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;
template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border){
	auto it = find_if(begin(elements), end(elements), [border](const T& elem) {return elem > border;});
	vector<T> tmp;
	for (auto i = it; i != end(elements); i++)
		tmp.push_back(*i);
	return tmp;
}

int main() {
	for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) 
		cout << x << " ";
	cout << endl;

	string to_find = "Python";
	cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
	system("pause");
	return 0;
}
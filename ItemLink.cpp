#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& dict, Key key) {
	try {return dict.at(key);}
	catch (const out_of_range& exception) { throw runtime_error("Out of Range error"); }
}

int main() {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
	system("pause");
	return 0;
}
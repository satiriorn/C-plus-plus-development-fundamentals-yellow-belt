#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

template<typename T> T Sqr(T value);
template<typename T> vector<T> Sqr(const vector<T>& value);
template <typename First, typename Second>pair<First, Second> Sqr(const pair< First, Second>& j);
template <typename Key, typename Value>map<Key, Value> Sqr(const map<Key, Value>& j);

template<typename T> inline T Sqr(T value) { return value * value; }

template <typename T> 
inline vector<T> Sqr(const vector<T>& value) {
	vector<T> result;
	for (const T& x : value)
		result.push_back(Sqr(x));
	return result;
}

template <typename First, typename Second>
inline pair<First, Second> Sqr(const pair< First, Second>& j) {return{ Sqr(j.first), Sqr(j.second) };}

template <typename Key, typename Value>
inline map<Key, Value> Sqr(const map<Key, Value>& j) {
	map<Key, Value> result;
	for (const auto&[key, value] : j)
		result[key] = Sqr(value);
	return result;
}


int main() {
	// Пример вызова функции
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	system("pause");
	return 0;
}
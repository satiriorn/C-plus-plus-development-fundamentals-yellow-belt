#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin < 2)
		return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	auto it1 = begin(elements) + elements.size() / 3;
	auto it2 = it1 + elements.size() / 3;

	MergeSort(std::begin(elements), it1);
	MergeSort(it1, it2);
	MergeSort(it2, std::end(elements));

	vector<typename RandomIt::value_type> tmp;

	merge(std::begin(elements), it1, it1, it2, back_inserter(tmp));
	merge(tmp.begin(), tmp.end(), it2, end(elements), range_begin);
}

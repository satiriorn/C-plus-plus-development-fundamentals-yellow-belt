#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

int main() {
	deque<string> s;
	int n, x;
	string operation, num = " ";
	cin >> x;
	cin >> n;
	s.push_front(to_string(x));
	for (int i = 0; i < n; i++) {
		cin >> operation;
		cin >> num;
		s.push_front("(");
		s.push_back(") ");
		s.push_back(operation+" "+ num);
	}
	for (const string& f : s) 
		cout << f;

	system("pause");
	return 0;
}
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};
/*
bool IsPalindrom(string s) {
	for (size_t i = 0; i < s.size() / 2; ++i) 
		if (s[i] != s[s.size() - i - 1]) 
			return false;
	return true;
}
*/

void Palindrom() {
	Assert(IsPalindrom(""), "empty string is a palindrome");
	Assert(IsPalindrom("j"), "one letter string is a palindrome");
	Assert(IsPalindrom("madam"), "madam is a palindrome");
	Assert(IsPalindrom("maDam"), "MaDam is a palindrome");
	Assert(IsPalindrom("m a D a m"), "`m a d a m` is a palindrome");
	Assert(IsPalindrom("  MADAM  "), "`  MADAM  ` is a palindrome");
}
void NoPalindrom() {
	Assert(!IsPalindrom("MmadamS"), "MadaM is not a palindrome");
	Assert(!IsPalindrom("abXYba"), "abXYba is not a palindrome");
	Assert(!IsPalindrom("God is long dead while you think it exists"), "`God is long dead while you think it exists` is not a palindrome because spaces do not match");
	Assert(!IsPalindrom("MADAM   "), "`MADAM   ` is not a palindrome");
	Assert(!IsPalindrom("  MADAM"), "`  MADAM` is not a palindrome");
	Assert(!IsPalindrom("Mmadam"), "Madam is not a palindrome");
	Assert(!IsPalindrom("madamM"), "madaM is not a palindrome");
	Assert(!IsPalindrom("was it a car or a cat i saw"),"`was it a car or a cat i saw` is not a palindrome because spaces do not match");
}
void TestIsPalindrom() {
	NoPalindrom();
	Palindrom();
}

int main() {
	TestRunner runner;
	runner.RunTest(TestIsPalindrom, "TestIsPalindrom");
	return 0;
}
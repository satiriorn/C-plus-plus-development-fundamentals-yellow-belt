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
		if (!hint.empty()) 
			os << " hint: " << hint;
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
		}
		catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
		catch (...) {
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
int GreatestCommonDivisor(int a, int b) {
	return (b == 0) ? a : GreatestCommonDivisor(b, a % b);
}

class Rational {
public:
	Rational() { 
		num = 0;
		den = 1;
	}
	Rational(int new_numerator, int new_denominator) {
		const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
		num = new_numerator / gcd;
		den = new_denominator / gcd;
		if (den < 0) {
			den = -den;
			num = -num;
		}
	}

	int Numerator() const {return num;}

	int Denominator() const {return den;}

private:
	int num, den;
};
Rational operator / (Rational a, Rational b) {
	if (b.Numerator() == 0) throw domain_error("domain_error");
	return Rational((a.Numerator() * b.Denominator()), (a.Denominator() * b.Numerator()));
}
istream& operator >> (istream& stream, Rational& r) {
	int p, q;
	if (stream >> p && stream.ignore(1) && stream >> q) 
		r = { p, q };
	return stream;
}
ostream& operator << (ostream& stream, const Rational& r) {
	stream << r.Numerator() << "/" << r.Denominator();
	return stream;
}
*/
void AboveZero() {
	AssertEqual(Rational(1, 1).Numerator(), 1);
	AssertEqual(Rational(1, 1).Denominator(), 1);
	AssertEqual(Rational(2, 3).Numerator(), 2);
	AssertEqual(Rational(2, 3).Denominator(), 3);
}
void ReductionRational() {
	AssertEqual(Rational(14, 76).Numerator(), 7);
	AssertEqual(Rational(12, 42).Denominator(), 7);
}
void RationalNULL() {
	AssertEqual(Rational().Numerator(), 0);
	AssertEqual(Rational().Denominator(), 1);
}
void NegativeNum() {
	AssertEqual(Rational(-9, -3).Numerator(), 3);
	AssertEqual(Rational(-9, -3).Denominator(), 1);
}
void IntermediaNegative() {
	AssertEqual(Rational(-10, 5).Numerator(), -2);
	AssertEqual(Rational(-10, 5).Denominator(), 1);
	AssertEqual(Rational(5, -10).Numerator(), -1);
	AssertEqual(Rational(5, -10).Denominator(), 2);
}
void NoStandatSituation(){
	AssertEqual(Rational(0, 100).Numerator(), 0);
	AssertEqual(Rational(0, 100).Denominator(), 1);
    AssertEqual(Rational(2147483647, 2147483647).Numerator(), 1);
	AssertEqual(Rational(2147483647, 2147483647).Denominator(), 1);
}
void TestRational() {
	AboveZero();
	ReductionRational();
	RationalNULL();
	NegativeNum();
	IntermediaNegative();
	NoStandatSituation();
}

int main() {
	TestRunner runner;
	runner.RunTest(TestRational, "TestRational");
	system("pause");
	return 0;
}
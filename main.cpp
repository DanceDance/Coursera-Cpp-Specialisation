#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric> 

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

class Rational {
public:

  Rational() : numerator_(0), denominator_(1) {}

  Rational(int numerator, int denominator) {
    if (numerator == 0) {
      numerator_ = 0;
      denominator_ = 1;
      return;
    }
    bool negative = false;
    if ((numerator < 0 && denominator >= 0) || (numerator >= 0 && denominator < 0))
      negative = true;

    numerator = abs(numerator);
    denominator = abs(denominator);
    int gcd_nd = gcd(numerator, denominator);
    numerator /= gcd_nd;
    denominator /= gcd_nd;
    numerator_ = numerator;
    denominator_ = denominator;
    if (negative)
      numerator_ = -numerator_;
  }

  int Numerator() const {
    return numerator_;
  }

  int Denominator() const {
    return denominator_;
  }
  private:
  int numerator_;
  int denominator_;
};

void TestDefaultConstructor() {
  Rational r;
  AssertEqual(r.Numerator(), 0, "DefaultContrustor1");  
  AssertEqual(r.Denominator(), 1, "DefaultContrustor2");
}

void TestGcd() {
  Rational r;

  r = Rational(10, 20);
  AssertEqual(r.Numerator(), 1, "Gcd1");
  AssertEqual(r.Denominator(), 2, "Gcd2");

  r = Rational(15, 45);
  AssertEqual(r.Numerator(), 1, "Gcd3");
  AssertEqual(r.Denominator(), 3, "Gcd4");

  r = Rational(5, 17);
  AssertEqual(r.Numerator(), 5, "Gcd5");
  AssertEqual(r.Denominator(), 17, "Gcd6");

  r = Rational(6, 9);
  AssertEqual(r.Numerator(), 2, "Gcd7");
  AssertEqual(r.Denominator(), 3, "Gcd8");
}

void TestSign() {
  Rational r;

  r = Rational(-5, 20);
  AssertEqual(r.Numerator(), -1, "Sign1");
  AssertEqual(r.Denominator(), 4, "Sign2");

  r = Rational(-10, -45);
  AssertEqual(r.Numerator(), 2, "Sign3");
  AssertEqual(r.Denominator(), 9, "Sign4");

  r = Rational(12, -40);
  AssertEqual(r.Numerator(), -3, "Sign5");
  AssertEqual(r.Denominator(), 10, "Sign6");
}

void TestZeroNumerator() {
  Rational r(0, 999);
  AssertEqual(r.Numerator(), 0, "ZeroNumerator1");
  AssertEqual(r.Denominator(), 1, "ZeroNumerator2");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
  runner.RunTest(TestGcd, "TestGcd");
  runner.RunTest(TestSign, "TestSign");
  runner.RunTest(TestZeroNumerator, "TestZeroNumerator");
  return 0;
}

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

bool IsPalindrom(const string& str) {
  for (int i = 0; i < (int)str.size() / 2; i++) {
    if (str[i] != str[(int) str.size() - i - 1])
      return false;
  }
  return true;
}

void TestPredefined() {
  Assert(IsPalindrom(""), "Empty String");
  Assert(IsPalindrom("a"), "a");
  Assert(!IsPalindrom("abc"), "abc");
  Assert(!IsPalindrom(" aaa"), " aaa");
  Assert(!IsPalindrom("aabcaa"), "aabcaa");
  Assert(!IsPalindrom("aaabcdaaa"), "aaabcdaaa");
  Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");
  Assert(IsPalindrom(",,..,,"), ",,..,,");
  Assert(IsPalindrom(",,.,,"), ",,.,,");
  Assert(!IsPalindrom("AbBa"), "AbBa");
  Assert(IsPalindrom("      "), "      ");
  Assert(!IsPalindrom("AAAaaa"), "AAAaaa");
  Assert(IsPalindrom(" AAA "), " AAA ");
  Assert(!IsPalindrom("aaaabcdeaaaa"), "aaaabcdeaaaa");
}

void TestDifferentLength() {
  for (int l = 2; l < 100; l++) {
    string s(l, ' ');
    for (int i = 0; i < l; i++) {
      s[i] = (char)i;
    }
    Assert(!IsPalindrom(s), "LengthTest: " + to_string(l));
  }
}

void TestDifferentCharacters() {
  for (char c = 0; c < 127; c++) {
    string s10(10, c);
    string s11(11, c);
    Assert(IsPalindrom(s10), "s10, character: " + to_string(c));
    Assert(IsPalindrom(s11), "s11, character: " + to_string(c));
  }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestPredefined, "TestPredefined");
  runner.RunTest(TestDifferentLength, "TestDifferentLength");
  runner.RunTest(TestDifferentCharacters, "TestDifferentCharacters");
  return 0;
}

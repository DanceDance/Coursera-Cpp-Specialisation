#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  int n = range_end - range_begin;
  if (n < 2)
    return;
  vector<typename RandomIt::value_type> tmp(make_move_iterator(range_begin), make_move_iterator(range_end));
  MergeSort(begin(tmp), begin(tmp) + n/3);
  MergeSort(begin(tmp) + n/3, begin(tmp) + 2 * n / 3);
  MergeSort(begin(tmp) + 2 * n / 3, end(tmp));
  vector<typename RandomIt::value_type> tmp2;
  merge(make_move_iterator(begin(tmp)), make_move_iterator(begin(tmp)) + n/3, make_move_iterator(begin(tmp)) + n/3, make_move_iterator(begin(tmp)) + 2 * n / 3, back_inserter(tmp2));
  merge(make_move_iterator(begin(tmp2)), make_move_iterator(end(tmp2)), make_move_iterator(begin(tmp)) + 2 * n / 3, make_move_iterator(end(tmp)), range_begin);
}

class StringNonCopyable : public string {
public:
  using string::string;
  StringNonCopyable(string&& other) : string(move(other)) {}
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  vector<string> strings_original = {"b", "c", "a"};
  vector<StringNonCopyable> strings(make_move_iterator(begin(strings_original)), make_move_iterator(end(strings_original)));
  MergeSort(begin(strings), end(strings));
  ASSERT(is_sorted(begin(strings), end(strings)));
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestNoCopy);
  return 0;
}

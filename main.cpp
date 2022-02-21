#include <algorithm> 
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <numeric>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  int n = range_end - range_begin;
  if (n < 2)
    return;
  vector<typename RandomIt::value_type> tmp(range_begin, range_end);
  MergeSort(begin(tmp), begin(tmp) + n/3);
  MergeSort(begin(tmp) + n/3, begin(tmp) + 2 * n / 3);
  MergeSort(begin(tmp) + 2 * n / 3, end(tmp));
  vector<typename RandomIt::value_type> tmp2;
  merge(begin(tmp), begin(tmp) + n/3, begin(tmp) + n/3, begin(tmp) + 2 * n / 3, back_inserter(tmp2));
  merge(begin(tmp2), end(tmp2), begin(tmp) + 2 * n / 3, end(tmp), range_begin);
}


int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
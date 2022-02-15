#include "sum_reverse_sort.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int Sum(int x, int y) {
  return x + y;
}

string Reverse(string s) {
  string s_copy = s;
  reverse(s_copy.begin(), s_copy.end());
  return s_copy;
}

void Sort(vector<int>& nums) {
  sort(begin(nums), end(nums));
}

// int main() {
//   cout << "Sum(5, 10): " << Sum(5, 10) << "\n";
//   cout << "Reverse(\"Hello World\"): " << Reverse("Hello World") << "\n";
//   vector<int> nums{4,5,-2,2};
//   Sort(nums);
//   cout << "Sort({4,5,-2,2}): ";
//   for (auto &x : nums) 
//     cout << x << " ";
//   cout << "\n"; 
// }

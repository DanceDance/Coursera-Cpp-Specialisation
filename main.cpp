#include <algorithm> 
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  iota(begin(a), end(a), 1);
  reverse(begin(a), end(a));
  do {
    for (const int &x : a)
      cout << x << " ";
    cout << "\n";
  } while (prev_permutation(begin(a), end(a)));

  return 0;
}

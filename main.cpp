#include "test_runner.h"

#include <list>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

int main() {
  list<int> l;
  map<int, list<int>::iterator> mp;

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int num, before_num;
    cin >> num >> before_num;
    auto it = l.end();
    auto mp_it = mp.find(before_num);
    if (mp_it != mp.end()) {
      it = mp_it->second;
    }
    mp[num] = l.insert(it, num);
  }
  for (auto &x : l)
    cout << x << "\n";
  return 0;
}

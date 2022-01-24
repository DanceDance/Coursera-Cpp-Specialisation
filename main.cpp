#include <bits/stdc++.h>
using namespace std;

template <typename K, typename V>
V& GetRefStrict(map<K, V>& mp, const K& k) {
  auto it = mp.find(k);
  if (it == mp.end())
    throw runtime_error("Element not found");
  return it->second;
}

int main() {
  map<int, string> m = {{0, "value"}};
  string& item = GetRefStrict(m, 1);
  item = "newvalue";
  cout << m[0] << endl; // выведет newvalue

} 
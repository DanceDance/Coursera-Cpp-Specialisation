#include <bits/stdc++.h>
using namespace std;

template <typename T> vector<T> Sqr(const vector<T> &v);
template <typename K, typename V> map<K, V> Sqr(const map<K, V> &mp);
template <typename F, typename S> pair<F, S> Sqr(const pair<F, S> &p);
template <typename T> T Sqr(const T& t);

template <typename T>
vector<T> Sqr(const vector<T> &v) {
  vector<T> res;
  res.reserve(v.size());
  for (const auto &x : v)
    res.push_back(Sqr(x));
  return res;
}

template <typename K, typename V>
map<K, V> Sqr(const map<K, V> &mp) {
  map<K, V> res;
  for (const auto &[k, v] : mp)
    res[k] = Sqr(v);
  return res;
}

template <typename F, typename S>
pair<F, S> Sqr(const pair<F, S> &p) {
  return {Sqr(p.first), Sqr(p.second)};
}

template <typename T> T Sqr(const T& t) {
  return t * t;
}

int main() {
  map<int, pair<int, int>> map_of_pairs = {
  {4, {2, 2}},
  {7, {4, 3}}
  };
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }

} 
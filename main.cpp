#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, r;
  cin >> n >> r;
  
  uint64_t total_weight = 0;

  for (int i = 0; i < n; i++) {
    int w, h, d;
    cin >> w >> h >> d;
    total_weight += static_cast<uint64_t>(w) * h * d * r;
  }

  cout << total_weight;
} 
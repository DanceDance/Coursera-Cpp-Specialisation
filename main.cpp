#include <cstdint>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
  int n;
  std::cin >> n;
  std::vector<int64_t> days_temp(n);
  for (auto &x : days_temp)
    std::cin >> x;
  int64_t avg = std::accumulate(begin(days_temp), end(days_temp), 0ll);
  avg /= static_cast<int64_t>(days_temp.size());
  std::vector<int64_t> filtered_days;
  for (int i = 0; i < n; i++)
    if (days_temp[i] > avg)
      filtered_days.push_back(i);
  std::cout << filtered_days.size() << '\n';
  for (auto &x : filtered_days)
    std::cout << x << " ";
} 
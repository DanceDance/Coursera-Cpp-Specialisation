#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>

using namespace std;

class ReadingManager {
public:
  ReadingManager() : progress_(MAX_PAGE + 1) {}

  void Read(int user_id, int page_count) {
    auto it = users_.find(user_id);
    if (it != end(users_)) {
      progress_[it->second]--;
    }
    users_[user_id] = page_count;
    progress_[page_count]++;
  }

  double Cheer(int user_id) const {
    auto user_it = users_.find(user_id);
    if (user_it == end(users_))
      return 0;
    if (users_.size() == 1)
      return 1;
    int less_users = 0;
    for (int i = 0; i < user_it->second; i++) {
      less_users += progress_[i];
    }
    return static_cast<double>(less_users) / (users_.size() - 1);
  }

private:
  static const int MAX_PAGE = 1000;
  map<int, int> users_;
  vector<int> progress_;
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
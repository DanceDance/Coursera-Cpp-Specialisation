#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <tuple>

using namespace std;

class BookingManager {
public:
  void Book(int64_t time, const string& hotel_name, int client_id, int room_count) {
    int64_t old_time = time - SECONDS_IN_DAY;
    ProcessOldTime(old_time);
    AddEntry(time, hotel_name, client_id, room_count);
  }

  int Clients(const string& hotel_room) const {
    auto client_it = clients_.find(hotel_room);
    if (client_it == end(clients_)) {
      return 0;
    }
    return client_it->second.size();
  }

  int Rooms(const string& hotel_room) const {
    auto room_it = rooms_.find(hotel_room);
    if (room_it == end(rooms_)) {
      return 0;
    }
    return room_it->second;
  }

private:
  static const int SECONDS_IN_DAY = 86'400;
  set<tuple<int64_t, string, int, int>> entries_;
  map<string, map<int, int>> clients_; // Key: hotel_name, value: (client_id, number of clients)
  map<string, int> rooms_;

  void ProcessOldTime(int64_t old_time) {
    for (auto it = begin(entries_); it != end(entries_);) {
      const auto& [time, hotel_name, client_id, room_count] = *it;
      if (time > old_time)
        return;
      RemoveEntry(time, hotel_name, client_id, room_count);
      it = entries_.erase(it);
    }
  }

  void AddEntry(int64_t time, const string& hotel_name, int client_id, int room_count) {
    clients_[hotel_name][client_id]++;
    rooms_[hotel_name] += room_count;
    entries_.insert({time, hotel_name, client_id, room_count});
  }

  void RemoveEntry(int64_t time, const string& hotel_name, int client_id, int room_count) {
    // Handle clients
    auto hotel_it = clients_.find(hotel_name);
    auto client_it = hotel_it->second.find(client_id);
    client_it->second--;
    if (client_it->second == 0) {
      hotel_it->second.erase(client_it);
    }
    if (hotel_it->second.empty()) {
      clients_.erase(hotel_it);
    }
    // Handle rooms
    auto room_it = rooms_.find(hotel_name);
    room_it->second -= room_count;
    if (room_it->second == 0) {
      rooms_.erase(room_it);
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  BookingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    if (query_type == "BOOK") {
      int64_t time;
      string hotel_name;
      int client_id;
      int room_count;
      cin >> time >> hotel_name >> client_id >> room_count;
      manager.Book(time, hotel_name, client_id, room_count);
    } else if (query_type == "CLIENTS") {
      string hotel_name;
      cin >> hotel_name;
      cout << manager.Clients(hotel_name) << '\n';
    } else if (query_type == "ROOMS") {
      string hotel_name;
      cin >> hotel_name;
      cout << manager.Rooms(hotel_name) << '\n';
    } else {
      cerr << "Unknown query type: " << query_type << '\n';
    }
  }

  return 0;
}
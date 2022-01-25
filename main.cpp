#include <bits/stdc++.h>
#include <variant>
using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

const map<string, QueryType> StringTypeToEnum {
  {"NEW_BUS", QueryType::NewBus}, 
  {"BUSES_FOR_STOP", QueryType::BusesForStop},
  {"STOPS_FOR_BUS", QueryType::StopsForBus},
  {"ALL_BUSES", QueryType::AllBuses}
};

template <typename T>
istream &operator >> (istream &is, vector<T> &v) {
  int n;
  is >> n;
  vector<T> newv(n);
  for (auto &x : newv)
    cin >> x;
  v = newv;
  return is;
}

istream& operator >> (istream& is, Query& q) {
  string type;
  is >> type;
  if (StringTypeToEnum.count(type) == 0) {
    throw runtime_error("Type unknown: " + type);
  }
  q.type = StringTypeToEnum.at(type);
  switch (q.type) {
    case QueryType::NewBus:
      is >> q.bus;
      is >> q.stops;
      break;
    case QueryType::BusesForStop:
      is >> q.stop;
      break;
    case QueryType::StopsForBus:
      is >> q.bus;
      break;
    case QueryType::AllBuses:
      break;
  }
  return is;
}

template <typename T>
ostream& operator << (ostream &out, const vector<T> &v) {
  bool first = true;
  for (const auto &x : v) {
    if (!first)
      out << " ";
    first = false;
    out << x;
  }

  return out;
}

struct BusesForStopResponse {
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses.empty())
    os << "No stop";
  else {
    os << r.buses;
  }
  return os;
}

struct StopsForBusResponse {
  vector<pair<string, vector<string>>> value;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.value.empty())
    os << "No bus";
  else {
    bool first = true;
    for (const auto &[stop, buses] : r.value) {
      if (!first)
        os << "\n";
      first = false;
      os << "Stop " << stop << ": ";
      if (buses.empty()) {
        os << "no interchange";
      } else {
        os << buses;
      }
    }
  }
  return os;
}

struct AllBusesResponse {
  vector<pair<string, vector<string>>> value;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.value.empty()) {
    os << "No buses";
  } else {
    bool first = true;
    for (const auto &[bus, stops] : r.value) {
      if (!first)
        os << '\n';
      first = false;
      os << "Bus " << bus << ": " << stops;
    }
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const auto &stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse resp;
    const auto it = stops_to_buses.find(stop);
    if (it == stops_to_buses.end())
      return resp;
    resp.buses = it->second;
    return resp;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    StopsForBusResponse resp;
    if (buses_to_stops.count(bus) == 0)
      return resp;
    for (const string &stop : buses_to_stops.at(bus)) {
      vector<string> other_buses;
      if (stops_to_buses.count(stop) == 1) {
        for (const string &other_bus : stops_to_buses.at(stop)) {
          if (other_bus != bus)
            other_buses.push_back(other_bus);
        }
      }
      
      resp.value.emplace_back(stop, other_buses);
    }
    return resp;
  }

  AllBusesResponse GetAllBuses() const {
    AllBusesResponse resp;
    for (const auto &bus_item: buses_to_stops) {
      resp.value.push_back(bus_item);
    }
    return resp;
  }

private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}

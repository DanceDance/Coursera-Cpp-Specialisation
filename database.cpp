
#include "database.h"
#include "util.h"

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>

using namespace std;

void Database::Add(const Date &date, const string& event) {
  if (events_set[date].count(event))
    return;
  events[date].push_back(event);
  events_set[date].insert(event);
}

void Database::Print(ostream &os) const {
  for (const auto &[date, date_events] : events) {
    for (const auto &event : date_events) {
      os << date << " " << event << "\n";
    }
  }
}

string Database::Last(const Date& date) const {
  auto it = events.upper_bound(date);
  if (it == begin(events))
    return "No entries";
  it--;
  ostringstream os;
  os << make_pair(it->first, it->second.back());
  return os.str();
}
#pragma once

#include "date.h"

#include <string>
#include <iostream>
#include <utility> 
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;

class Database {
public:

  void Add(const Date &date, const string& event);
  void Print(ostream &os) const;

  template<class Predicate>
  vector<pair<Date, string>> FindIf(const Predicate& p) const {
    vector<pair<Date, string>> result;
    for (const auto &[date, date_events] : events) {
      for (const auto &event : date_events) {
        if (p(date, event))
          result.emplace_back(date, event);
      }
    }
    return result;
  }

  template<class Predicate>
  int RemoveIf(const Predicate& p) {
    int removed = 0;
    for (auto &events_it : events) {
      const Date& date = events_it.first;
      auto & date_events = events_it.second;
      auto remove_it = stable_partition(
        begin(date_events), end(date_events), [&date, &p] (const string &event) {
          return !p(date, event);
      });
      removed += end(date_events) - remove_it;
      for (auto it = remove_it; it != end(date_events); it++)
        events_set[date].erase(*it);
      date_events.erase(remove_it, end(date_events));
    }

    for (auto it = begin(events); it != end(events);) {
      if (it->second.empty())
        it = events.erase(it);
      else
        ++it;
    }

    for (auto it = begin(events_set); it != end(events_set);) {
      if (it->second.empty())
        it = events_set.erase(it);
      else
        ++it;
    }
    return removed;
  }

  string Last(const Date& date) const;

private:
  map<Date, vector<string>> events;
  map<Date, set<string>> events_set;
};
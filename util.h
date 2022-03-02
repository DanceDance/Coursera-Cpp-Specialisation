#pragma once

#include <iostream>
#include <utility> 

using namespace std;

template<class L, class R>
ostream& operator<< (ostream& os, const pair<L, R>& p) {
  os << p.first << " " << p.second;
  return os;
}

inline string ParseEvent(istream& is) {
  string line;
  std::getline(is >> std::ws, line);
  return line;
}
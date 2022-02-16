#pragma once

#include "responses.h"

#include <iostream>
#include <vector>
#include <string>

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

istream& operator >> (istream& is, Query& q);
ostream& operator << (ostream& os, const StopsForBusResponse& r);
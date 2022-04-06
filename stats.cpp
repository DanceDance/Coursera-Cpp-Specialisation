#include "stats.h"
#include "http_request.h"

#include <sstream>
#include <string>
#include <string_view>
#include <iostream>

using namespace std;

Stats::Stats() {
  for (auto x : valid_methods_)
    method_stats_[x] = 0;
  for (auto x : valid_uris_)
    uri_stats_[x] = 0;
}

void Stats::AddMethod(string_view method) {
  auto it = method_stats_.find(method);
  if (it != method_stats_.end()) {
    it->second++;
  }
  else {
    method_stats_[unknown_method_]++;
  }
}

void Stats::AddUri(string_view uri) {
  auto it = uri_stats_.find(uri);
  if (it != uri_stats_.end())
    it->second++;
  else
    uri_stats_[unknown_uri_]++;
}

const map<string_view, int>& Stats::GetMethodStats() const {
  return method_stats_;
}

const map<string_view, int>& Stats::GetUriStats() const {
  return uri_stats_;
}

HttpRequest ParseRequest(string_view line) {
  line.remove_prefix(std::min(line.find_first_not_of(" "), line.size()));
  string_view method, uri, protocol;
  size_t space_pos = line.find(' ');
  method = line.substr(0, space_pos);
  line.remove_prefix(space_pos + 1);
  space_pos = line.find(' ');
  uri = line.substr(0, space_pos);
  line.remove_prefix(space_pos + 1);
  protocol = line;
  return {method, uri, protocol};
}
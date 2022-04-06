#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <string>
using namespace std;

class Stats {
public:
  Stats();
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
private:
  static constexpr string_view unknown_method_ = "UNKNOWN";
  static constexpr string_view unknown_uri_ = "unknown";
  static constexpr string_view valid_methods_[] = {"GET", "POST", "PUT", "DELETE", unknown_method_};
  static constexpr string_view valid_uris_[] = {"/", "/order", "/product", "/basket", "/help", unknown_uri_};
  map<string_view, int> method_stats_;
  map<string_view, int> uri_stats_;
};

HttpRequest ParseRequest(string_view line);

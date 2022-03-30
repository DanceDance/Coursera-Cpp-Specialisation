#include "test_runner.h"
#include <string>
#include <list>
#include <map>
#include <string_view>

using namespace std;

class Translator {
public:
  void Add(string_view source, string_view target) {
    source = AddString(source);
    target = AddString(target);
    forward_db_[source] = target;
    backward_db_[target] = source;
  }
  string_view TranslateForward(string_view source) const {
    auto it = forward_db_.find(source);
    if (it == forward_db_.end())
      return "";
    return it->second;
  }
  string_view TranslateBackward(string_view target) const {
    auto it = backward_db_.find(target);
    if (it == backward_db_.end())
      return "";
    return it->second;
  }

private:
  map<string_view, string_view> forward_db_;
  map<string_view, string_view> backward_db_;
  map<string_view, string_view> words_db_;
  list<string> string_db_;

  string_view AddString(string_view str) {
    auto it = words_db_.find(str);
    if (it == words_db_.end()) {
      string_db_.emplace_back(str);
      words_db_[string_db_.back()] = string_db_.back();
      return string_db_.back();
    }
    return it->second;
  }
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));
  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  
  translator.Add(string("okno"), string("window1"));
  ASSERT_EQUAL(translator.TranslateForward("okno"), "window1");
  translator.Add(string("okno"), string("window2"));
  ASSERT_EQUAL(translator.TranslateForward("okno"), "window2");
  translator.Add(string("okno"), string("window3"));
  ASSERT_EQUAL(translator.TranslateForward("okno"), "window3");

  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}

#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = int;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
    id_to_object_[id_] = move(object);
    priorities_[0].insert(id_);
    return id_++;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
    for (auto &it = range_begin; it != range_end; it++) {
      int id = Add(move(*it));
      *ids_begin++ = id;
    }  
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
    return id_to_object_.count(id);
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
    return id_to_object_.at(id);
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
    int new_priority = ++id_to_priority_[id];
    int old_priority = new_priority - 1;
    priorities_[old_priority].erase(id);
    priorities_[new_priority].insert(id);
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
    const auto &[max_priority, max_priority_objects] = *priorities_.rbegin();
    int max_priority_object_id = *max_priority_objects.rbegin();
    return {id_to_object_.at(max_priority_object_id), max_priority};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
    auto &[max_priority, max_priority_objects] = *priorities_.rbegin();
    int max_priority_object_id = *max_priority_objects.rbegin();
    max_priority_objects.erase(max_priority_object_id);
    id_to_priority_.erase(max_priority_object_id);
    pair<T, int> ret = {move(id_to_object_[max_priority_object_id]), max_priority};
    id_to_object_.erase(max_priority_object_id);
    while (!priorities_.empty() && priorities_.rbegin()->second.empty())
      priorities_.erase(prev(priorities_.end()));
    return ret;
  }

  void Log() {
    cerr << "Id: " << id_ << "\n";
    cerr << "id_to_object: " << "\n";
    for (auto &[k, v] : id_to_object_)
      cerr << k << " " << v << "\n";
    cerr << "---\n";
    cerr << "id_to_priority_:" << "\n";
    for (auto &[k, v] : id_to_priority_)
      cerr << k << " " << v << "\n";
    cerr << "---\n";
    cerr << "priorities_:" << "\n";
    for (auto &[k, v] : priorities_) {
      cerr << k << ": ";
      for (auto &vv : v)
        cerr << vv << " ";
      cerr << "\n";
    }
    cerr << "---\n";
  }

private:
  int id_ = 0;
  map<int, T> id_to_object_;
  map<int, int> id_to_priority_;
  map<int, set<int>> priorities_;
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");
  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    ASSERT(strings.IsValid(white_id));
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

void TestAddRange() {
  vector<StringNonCopyable> strings;
  StringNonCopyable s1("a");
  strings.push_back(move(s1));
  PriorityCollection<StringNonCopyable> strings_priority;
  
  vector<int> ids;
  strings_priority.Add(begin(strings), end(strings), back_inserter(ids));
  
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}

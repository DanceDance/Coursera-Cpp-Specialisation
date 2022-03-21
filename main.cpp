#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
    auto ptr = TryAllocate();
    if (ptr == nullptr) {
      ptr = new T;
      in_use.insert(ptr);
    }
    return ptr;
  }

  T* TryAllocate() {
    if (freed.empty())
      return nullptr;
    auto ptr = freed.front();
    freed.pop_front();
    in_use.insert(ptr);
    return ptr;
  }

  void Deallocate(T* object) {
    auto it = in_use.find(object);
    if (it == in_use.end())
      throw invalid_argument("Deallocation failed, object is not in use.");
    freed.push_back(*it);
    in_use.erase(it);
  }

  ~ObjectPool() {
    for (auto ptr : in_use)
      delete ptr;
    for (auto ptr : freed)
      delete ptr;
  }

private:
  deque<T*> freed;
  set<T*> in_use;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}

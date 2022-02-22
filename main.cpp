#include <algorithm> 
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <numeric>
#include <iterator>

using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border) {
      auto it = numbers.lower_bound(border);
      if (it == begin(numbers))
        return it;
      auto pit = prev(it);
      if (it == end(numbers))
        return pit;
      if (abs(*pit - border) <= abs(*it - border))
        return pit;
      return it;
    }

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;

  set<int> one_element {5};
  cout << *FindNearestElement(one_element, 3) << " " << *FindNearestElement(one_element, 6) << "\n";
  return 0;
}
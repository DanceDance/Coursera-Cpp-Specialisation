#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
  auto it = numbers.end();
  it = find_if(begin(numbers), end(numbers), 
      [] (const int &x) { return x < 0; });
  while (it != begin(numbers)) {
    it--;
    cout << *it << " ";
  }
}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}
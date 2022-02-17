#include <algorithm> 
#include <string>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
  vector<string> res;
  auto start_it = s.begin();
  while (true) {
    auto end_it = find(start_it, end(s), ' ');
    res.push_back({start_it, end_it});
    start_it = end_it;
    if (start_it == end(s))
      break;
    start_it++;
  }
  return res;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}
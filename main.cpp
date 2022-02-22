#include <algorithm> 
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <numeric>
#include <iterator>
#include <sstream>
#include <map>

using namespace std;

int main() {
  static map<string, int> priority {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2}  
  };
  string first_var;
  cin >> first_var;
  int n;
  cin >> n;
  vector<string> vars(n);
  vector<string> ops(n);

  for (int i = 0; i < n; i++) {
    cin >> ops[i];
    cin >> vars[i];    
  }
  int parentheses_count = 0;
  stringstream right;
  right << first_var;

  for (int i = 0; i < n; i++) {
    if (i > 0 && priority[ops[i - 1]] < priority[ops[i]]) {
      right << ')';
      parentheses_count++;
    }
    right << ' ' << ops[i] << ' ' << vars[i];
  }
  cout << string(parentheses_count, '(');
  cout << right.str();
  return 0;
}
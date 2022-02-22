#include <algorithm> 
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <numeric>
#include <iterator>

using namespace std;

int main() {
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
  cout << string(n, '(');
  cout << first_var;
  for (int i = 0; i < n; i++) {
    cout << ')' << ' ' << ops[i] << ' ' << vars[i];
  }
  return 0;
}
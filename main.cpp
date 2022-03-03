#include "test_runner.h"

#include <ostream>
#include <string>
using namespace std;

#define PRINT_VALUES(out, x, y) (out) << (x) << endl << (y) << endl

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
    output = ostringstream();
    PRINT_VALUES(output, 25 + 5, string("red ") + "belt");
    ASSERT_EQUAL(output.str(), "30\nred belt\n");
  }, "PRINT_VALUES usage example");
  return 0;
}

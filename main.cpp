#include <algorithm> 
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

/*
Median age = 40
Median age for females = 40
Median age for males = 55
Median age for employed females = 40
Median age for unemployed females = 80
Median age for employed males = 55
Median age for unemployed males = 78
*/

void PrintStats(vector<Person> persons) {
  cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << "\n";
  auto it = partition(begin(persons), end(persons), [](const Person& p) {return p.gender == Gender::FEMALE; });
  cout << "Median age for females = " << ComputeMedianAge(begin(persons), it) << "\n";
  it = partition(begin(persons), end(persons), [](const Person& p) {return p.gender == Gender::MALE; });
  cout << "Median age for males = " << ComputeMedianAge(begin(persons), it) << "\n";
  it = partition(begin(persons), end(persons), [](const Person& p) {
    return p.gender == Gender::FEMALE && p.is_employed; 
    });
  cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), it) << "\n";
  it = partition(begin(persons), end(persons), [](const Person& p) {
    return p.gender == Gender::FEMALE && !p.is_employed; 
    });
  cout << "Median age for unemployed females = " << ComputeMedianAge(begin(persons), it) << "\n";    
  it = partition(begin(persons), end(persons), [](const Person& p) {
    return p.gender == Gender::MALE && p.is_employed; 
    });
  cout << "Median age for employed males = " << ComputeMedianAge(begin(persons), it) << "\n";
  it = partition(begin(persons), end(persons), [](const Person& p) {
    return p.gender == Gender::MALE && !p.is_employed; 
    });
  cout << "Median age for unemployed males = " << ComputeMedianAge(begin(persons), it) << "\n";
}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}
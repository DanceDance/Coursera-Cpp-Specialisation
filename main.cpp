#include "phone_number.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


using namespace std;


/* Принимает строку в формате +XXX-YYY-ZZZZZZ
    Часть от '+' до первого '-' - это код страны.
    Часть между первым и вторым символами '-' - код города
    Всё, что идёт после второго символа '-' - местный номер.
    Код страны, код города и местный номер не должны быть пустыми.
    Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

    Примеры:
    * +7-495-111-22-33
    * +7-495-1112233
    * +323-22-460002
    * +1-2-coursera-cpp
    * 1-2-333 - некорректный номер - не начинается на '+'
    * +7-1233 - некорректный номер - есть только код страны и города
*/
PhoneNumber::PhoneNumber(const string &international_number) {
  if (international_number.empty())
    throw invalid_argument("Empty string");
  if (international_number[0] != '+')
    throw invalid_argument("Number doesn't start with +");

  vector<int> minuses;

  for (int i = 1; i < (int)international_number.size(); i++) {
    if (international_number[i] == '+') {
      throw invalid_argument("More than one plus in a string");
    }

    if (international_number[i] == '-') {
      if (minuses.size() < 2)
        minuses.push_back(i);
    }
  }
  if (minuses.size() < 2) {
    throw invalid_argument("Too few minuses in a string: " + to_string(minuses.size()));
  }

  country_code_ = international_number.substr(1, minuses[0] - 1);
  city_code_ = international_number.substr(minuses[0] + 1, minuses[1] - minuses[0] - 1);
  local_number_ = international_number.substr(minuses[1] + 1);
  if (country_code_.empty() || city_code_.empty() || local_number_.empty()) 
    throw invalid_argument("One of the number parts is empty.");

}

string PhoneNumber::GetCountryCode() const {
  return country_code_;
}
string PhoneNumber::GetCityCode() const {
  return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
  return local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
  return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}
  


// ostream& operator<< (ostream &os, const PhoneNumber& pn) {
//   os << "Country code: " << pn.GetCountryCode() << ", city code: " << pn.GetCityCode() <<
//     ", local number: " << pn.GetLocalNumber() << ", int number: " << pn.GetInternationalNumber();
//   return os;
// }

// int main() {
//   vector<string> examples {"+7-495-111-22-33", "+7-495-1112233", "+323-22-460002", "+1-2-coursera-cpp", "1-2-333", "+7-1233"};
//   for (const auto &s : examples) {
//     try {
//       cout << "Running example: " << s << "\n";
//       PhoneNumber pn(s);      
//       cout << pn << "\n";
//     } catch (const exception& e) {
//       cout << "Got exception: " << e.what() << "\n";
//     }
//   }

// }
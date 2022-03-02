#include "date.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

Date::Date() : year_(0), month_(0), day_(0) {}

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

int Date::GetYear() const {
  return year_;
}

int Date::GetMonth() const {
  return month_;
}

int Date::GetDay() const {
  return day_;
}

istream& operator>> (istream& stream, Date& in) {
  int year, month, day;
  char sep1, sep2;
  stream >> year >> sep1 >> month >> sep2 >> day;
  if (!stream || sep1 != '-' || sep2 != '-') {
    throw WrongDateFormatException();
  }
  if (stream.rdbuf()->in_avail())
    throw WrongDateFormatException();
  in = Date(year, month, day);
  return stream;
}

Date ParseDate(istream &stream) {
  string date_str;
  stream >> date_str;
  stringstream ss(date_str);
  Date date;
  ss >> date;
  return date;
}

ostream& operator<< (ostream& stream, const Date& out) {
  stream << setw(4) << setfill('0') << out.GetYear() << '-';
  stream << setw(2) << setfill('0') << out.GetMonth() << '-';
  stream << setw(2) << setfill('0') << out.GetDay();
  return stream;
}

bool operator==(const Date& lhs, const Date& rhs) {
  return lhs.GetYear() == rhs.GetYear() &&
         lhs.GetMonth() == rhs.GetMonth() &&
         lhs.GetDay() == rhs.GetDay();
}

bool operator!=(const Date& lhs, const Date& rhs) {
  return !(operator==(lhs, rhs));
}

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() != rhs.GetYear())
    return lhs.GetYear() < rhs.GetYear();
  if (lhs.GetMonth() != rhs.GetMonth())
    return lhs.GetMonth() < rhs.GetMonth();
  return lhs.GetDay() < rhs.GetDay();
}


bool operator>(const Date& lhs, const Date& rhs) {
  return operator<(rhs, lhs);
}

bool operator<=(const Date& lhs, const Date& rhs) {
  return !(operator>(lhs, rhs));
}

bool operator>=(const Date& lhs, const Date& rhs) {
  return !(operator<(lhs, rhs));
}
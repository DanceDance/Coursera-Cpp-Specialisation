#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Date {
public:
  Date();
  Date(int year, int month, int day);
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;

private:
  int year_;
  int month_;
  int day_;
};

Date ParseDate(istream &is);

ostream& operator<< (ostream &os, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

class WrongDateFormatException : public runtime_error {
  public:
    WrongDateFormatException(const std::string& what = "") : std::runtime_error(what) {}
};
class InvalidDateException : public runtime_error {
  public:
    InvalidDateException(const std::string& what = "") : std::runtime_error(what) {}  
};
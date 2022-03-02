#pragma once

#include "date.h"

#include <string>
#include <memory>

enum class Comparison {
  Less, LessOrEqual, Greater, GreaterOrEqual, Equal, NotEqual
};

std::ostream& operator << (std::ostream& os, const Comparison& obj);

enum class LogicalOperation {
  Or, And
};

class Node {
public:
  virtual bool Evaluate(const Date& d, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
  virtual bool Evaluate(const Date& d, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
  DateComparisonNode(Comparison cmp, const Date& date);

  virtual bool Evaluate(const Date& d, const string& event) const override;

private:
  const Date date_;
  const Comparison cmp_;
};

class EventComparisonNode : public Node {
public:
  EventComparisonNode(Comparison cmp, const string& event);

  virtual bool Evaluate(const Date& d, const string& event) const override;

private:
  const string event_;
  const Comparison cmp_;
};

class LogicalOperationNode : public Node {
public:
  LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right);

  virtual bool Evaluate(const Date& d, const string& event) const override;

private:
  const shared_ptr<Node> left_;
  const shared_ptr<Node> right_;
  const LogicalOperation op_;
};
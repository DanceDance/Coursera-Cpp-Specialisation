#include "node.h"

#include <iostream>
#include <type_traits>

using namespace std;

std::ostream& operator << (std::ostream& os, const Comparison& obj) {
   os << static_cast<std::underlying_type<Comparison>::type>(obj);
   return os;
}

bool EmptyNode::Evaluate(const Date& d, const string& event) const {
  return true;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date& date)
  : date_(date),  cmp_(cmp) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
  switch (cmp_) {
    case Comparison::Less:
      return date < date_;
    case Comparison::LessOrEqual:
      return date <= date_;
    case Comparison::Greater:
      return date > date_;
    case Comparison::GreaterOrEqual:
      return date >= date_;
    case Comparison::Equal:
      return date == date_;
    case Comparison::NotEqual:
      return !(date == date_);
  }
  return true;
}

EventComparisonNode::EventComparisonNode(Comparison cmp, const string& event)
  : event_(event), cmp_(cmp) {}

bool EventComparisonNode::Evaluate(const Date& d, const string& event) const {
  switch (cmp_) {
    case Comparison::Less:
      return event < event_;
    case Comparison::LessOrEqual:
      return event <= event_;
    case Comparison::Greater:
      return event > event_;
    case Comparison::GreaterOrEqual:
      return event >= event_;
    case Comparison::Equal:
      return event == event_;
    case Comparison::NotEqual:
      return !(event == event_);
  }
  return true;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation op, 
  shared_ptr<Node> left, shared_ptr<Node> right)
  : left_(left), right_(right), op_(op) {}

bool LogicalOperationNode::Evaluate(const Date& d, const string& event) const {
  if (op_ == LogicalOperation::Or)
    return left_->Evaluate(d, event) || right_->Evaluate(d, event);
  else
    return left_->Evaluate(d, event) && right_->Evaluate(d, event);
}

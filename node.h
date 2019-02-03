#pragma once

#include <memory>

#include "date.h"

enum class Comparison
{
    Less, LessOrEqual, 
    Greater, GreaterOrEqual,
    Equal, NotEqual
};

enum class LogicalOperation
{
    Or, And
};

class Node
{
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node
{
public:
    EmptyNode() {}
    
    bool Evaluate(const Date& date, const string& event) const override 
    { 
        (void) date; (void) event;
        return true;
    }
};

class DateComparisonNode : public Node
{
public:
    DateComparisonNode(Comparison cmp, const Date& date)
        : cmp_(cmp), date_(date)
    {}

    bool Evaluate(const Date& date, const string& event) const override;

private:
    const Comparison cmp_;
    const Date date_;
};

class EventComparisonNode : public Node
{
public:
    EventComparisonNode(Comparison cmp, const string& event)
        : cmp_(cmp), event_(event)
    {}

    bool Evaluate(const Date& date, const string& event) const override;

private:
    const Comparison cmp_;
    const string event_;
};

class LogicalOperationNode : public Node
{
public:
    LogicalOperationNode(LogicalOperation op, shared_ptr<Node> left, shared_ptr<Node> right)
        : op_(op), left_(left), right_(right) 
    {}

    bool Evaluate(const Date& date, const string& event) const override;

private:
    const LogicalOperation op_;
    const shared_ptr<Node> left_;
    const shared_ptr<Node> right_;
};
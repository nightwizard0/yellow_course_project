#pragma once

#include <vector>
#include <list>
#include <algorithm>

#include "date.h"

class Entry
{
    const Date date_;
    const string event_;

public:
    Entry() {}
    Entry(const Date& date, const string& event = "")
        : date_(date), event_(event)
    {}

    Date date() const { return date_; }
    string event() const { return event_; }
};

bool operator<(const Entry& a, const Entry& b);
bool operator==(const Entry& a, const Entry& b);
ostream& operator<<(ostream& os, const Entry& entry);

class Database
{
public:
    using EntryList = vector<Entry>;

    void Add(const Date& date, const string& event);
    void Print(ostream& os) const;

    template<class Predicate>
    int RemoveIf(Predicate p) 
    { 
        size_t size = db_.size();
        
        db_.remove_if([&](const Entry& item)
        {
            return p(item.date(), item.event());
        });

        return static_cast<int>(size - db_.size());    
    }

    template<class Predicate>
    EntryList FindIf(Predicate p) const
    { 
        EntryList result;

        for (auto next_it = db_.cbegin(); next_it != db_.cend(); )
        {
            auto it = find_if(next_it, db_.cend(), [&](const Entry& item)
            {
                return p(item.date(), item.event());
            });

            next_it = it;

            if (it != db_.cend())
            {
                result.push_back(*it);
                next_it = next(it);
            }
        }

        return result;
    }

    Entry Last(const Date& date) const;

private:
    list<Entry> db_;
};
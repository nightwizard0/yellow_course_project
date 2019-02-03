#pragma once

#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <set>

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

    Date date()         const { return date_; }
    string event()      const { return event_; }
    string tostring()   const { return date_.tostring() + " " + event_; }
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
        int count = 0;

        vector<Date> clean;

        for (auto& [date, events] : db_)
        {
            count += events.RemoveIf(date, p);

            if (events.IsEmpty())
                clean.push_back(date);
        }

        for (const auto& date : clean)
            db_.erase(date);        

        return count;
    }

    template<class Predicate>
    EntryList FindIf(Predicate p) const
    { 
        EntryList result;

        for (const auto& item : db_)
        {
            auto events = item.second.Events();

            for (const auto& event : events)
            {
                if (p(item.first, event))
                    result.emplace_back(item.first, event);
            }
        }

        return result;
    }

    Entry Last(const Date& date) const;

private:

    class EventList
    {
        vector<string> events_;
        set<string> cache_;

        public:

        void Add(const string& event)
        {
            events_.push_back(event);
            cache_.insert(event);          
        }

        bool Contains(const string& event)  const { return cache_.count(event) != 0; }
        const vector<string>& Events()      const { return events_; }
        string Last()                       const { return events_.back(); }
        bool IsEmpty()                      const { return events_.empty(); }

        void Print(ostream& os, const Date& date) const;

        template <typename Predicate>
        int RemoveIf(const Date& date, Predicate p)
        {
            auto it = stable_partition(events_.begin(), events_.end(), [&](const string& elem)
            {
                return !p(date, elem);
            });

            if (it == events_.end())
                return 0;

            int count = 0;

            for (auto it_next = it; it_next != events_.end(); it_next++)
            {
                cache_.erase(*it_next);
                count++;
            }

            events_.erase(it, events_.end());

            return count;
        }

    };

    map<Date, EventList> db_;
};
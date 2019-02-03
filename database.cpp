#include "database.h"

#include <algorithm>

bool operator<(const Entry& a, const Entry& b)
{
    return a.date() < b.date();
}

bool operator==(const Entry& a, const Entry& b)
{
    return a.date() == b.date() && a.event() == b.event();
}

ostream& operator<<(ostream& os, const Entry& entry)
{
    os << entry.date() << " " << entry.event();
    return os;
}

void Database::EventList::Print(ostream& os, const Date& date) const
{
    for (const auto& event : events_)
        os << date << " " << event << endl;
}

void Database::Add(const Date& date, const string& event)
{  
    auto it = db_.find(date);

    if (it != db_.end())
    {
        auto& events = it->second;

        if (events.Contains(event))
            return;
        
        events.Add(event);
    }
    else
    {
        db_[date].Add(event);
    }
}

void Database::Print(ostream& os) const
{
    for (const auto& [date, events] : db_)
    {
        events.Print(os, date);
    }
}

Entry Database::Last(const Date& date) const
{
    if (db_.empty())
        throw invalid_argument("Empty database");

    auto it = db_.lower_bound(date);

    if (it == db_.cbegin() && date < it->first)
        throw invalid_argument("No entries for requested date");

    if (it == db_.cend() || it->first != date)
        it = prev(it);

    return Entry(it->first, it->second.Last());
} 
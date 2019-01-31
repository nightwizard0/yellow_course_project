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

void Database::Add(const Date& date, const string& event)
{
    Entry item(date, event);

    auto it = lower_bound(db_.cbegin(), db_.cend(), item);

    if (it != db_.cend() && *it == item)
        return ;

    auto next_it = upper_bound(it, db_.cend(), item);

    if (find(it, next_it, item) != next_it)
        return ;
    
    db_.insert(next_it, item);
}

void Database::Print(ostream& os) const
{
    for (const auto& entry : db_)
    {
        os << entry << endl;
    }
}

Entry Database::Last(const Date& date) const
{
    Entry item(date);

    if (db_.empty())
        throw invalid_argument("Empty database");

    auto it = lower_bound(db_.cbegin(), db_.cend(), item);

    if (it == db_.cbegin() && item < *it)
        throw invalid_argument("No entries for requested date");

    for (; it != db_.cend() && (*it).date() == date; it++);
    
    return *prev(it);
} 
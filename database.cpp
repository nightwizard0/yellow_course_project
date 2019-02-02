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
    auto cache_key = item.tostring();

    if (cache_.find(cache_key) != cache_.cend())
        return ;

    auto it = upper_bound(db_.cbegin(), db_.cend(), item);
    
    db_.insert(it, item);

    cache_[cache_key] = true;
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
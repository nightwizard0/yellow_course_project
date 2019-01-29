#include "database.h"

#include <algorithm>

ostream& operator<<(ostream& os, const Entry& entry)
{
    os << entry.date << " " << entry.event;
    return os;
}

void Database::Add(const Date& date, const string& event)
{
    auto& ref = db_[date];

    if (find(ref.cbegin(), ref.cend(), event) != ref.cend())
        return ;

    ref.push_back(event); 
}

void Database::Print(ostream& os)
{
    for (const auto& [date, events] : db_)
    {
        for (const auto& event : events)
        {
            os << date << " " << event << endl;
        }
    }
}

Entry Database::Last(const Date& date)
{
    (void) date;
    return Entry();
} 
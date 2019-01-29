#pragma once

#include <vector>
#include <map>

#include "date.h"

struct Entry
{
    Date date;
    string event;
};

ostream& operator<<(ostream& os, const Entry& entry);

class Database
{
public:
    using EntryList = vector<Entry>;

    void Add(const Date& date, const string& event);
    void Print(ostream& os);

    template<class Predicate>
    int RemoveIf(Predicate p) { (void) p; return 0; }

    template<class Predicate>
    EntryList FindIf(Predicate p) { (void) p; return EntryList(); }

    Entry Last(const Date& date); 

private:
    map<Date, vector<string>> db_;
};
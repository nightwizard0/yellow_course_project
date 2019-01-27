#pragma once

#include <iostream>

using namespace std;

class Date
{
public:
    Date(int year, int month, int day) : Year(year), Month(month), Day(day)
    {}

    const int Year, Month, Day;
};

Date ParseDate(istream& is);
ostream& operator<<(ostream& os, const Date& date);
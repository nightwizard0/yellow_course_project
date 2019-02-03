#pragma once

#include <iostream>

using namespace std;

class Date
{
public:
    Date() : Year(1), Month(1), Day(1) 
    {}

    Date(int year, int month, int day) : Year(year), Month(month), Day(day)
    {}

    const int Year, Month, Day;

    string tostring() const;
};

Date ParseDate(istream& is);

ostream& operator<<(ostream& os, const Date& date);
bool operator<(const Date& d1, const Date& d2);
bool operator==(const Date& d1, const Date& d2);
bool operator!=(const Date& d1, const Date& d2);
bool operator<=(const Date& d1, const Date& d2);
bool operator>(const Date& d1, const Date& d2);
bool operator>=(const Date& d1, const Date& d2);
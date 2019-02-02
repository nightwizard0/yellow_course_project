#include <string>
#include <stdexcept>
#include <iomanip>
#include <sstream>

#include "date.h"


Date ParseDate(istream& is)
{
    string s_year, s_month;

    getline(is, s_year, '-');
    getline(is, s_month, '-');

    int day, month, year;
    is >> day;

    month = stoi(s_month);
    year = stoi(s_year);

    if (day < 1 || day > 31 || month < 1 || month > 12)
        throw invalid_argument("Invalid date: " + s_year + "-" + s_month + "-" + to_string(day));

    return Date(year, month, day);
}

ostream& operator<<(ostream& os, const Date& date)
{
    os << setfill('0') << setw(4) << date.Year << '-';
    os << setfill('0') << setw(2) << date.Month << '-';
    os << setfill('0') << setw(2) << date.Day;

    return os;
}

bool operator<(const Date& d1, const Date& d2)
{
    if (d1.Year < d2.Year)
        return true;

    if (d1.Year > d2.Year)
        return false;

    if (d1.Month > d2.Month)
        return false;

    if (d1.Month < d2.Month)
        return true;

    return d1.Day < d2.Day;
}

bool operator==(const Date& d1, const Date& d2)
{
    return d1.Year == d2.Year && d1.Month == d2.Month && d1.Day == d2.Day;
}

bool operator!=(const Date& d1, const Date& d2) 
{ 
    return !(d1 == d2); 
}

bool operator<=(const Date& d1, const Date& d2) 
{ 
    return (d1 < d2) || (d1 == d2); 
}

bool operator>(const Date& d1, const Date& d2) 
{ 
    return (d1 != d2) && !(d1 < d2); 
}

bool operator>=(const Date& d1, const Date& d2) 
{ 
    return (d1 > d2) || (d1 == d2); 
}

string Date::tostring() const 
{
    ostringstream ss; ss << *this;
    return ss.str();
}
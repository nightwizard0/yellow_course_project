#include <string>
#include <stdexcept>
#include <iomanip>

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
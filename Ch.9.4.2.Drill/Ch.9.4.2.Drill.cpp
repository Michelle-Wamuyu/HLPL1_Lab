#include "std_lib_facilities.h"

// - define a Date called 'tomorrow' by copying 'today' and using add_day()

struct Date {
    int y, m, d;                    // year, month, day
    Date(int y, int m, int d);      // check for valid date and initialize
    void add_day(int n);            // increase the Date by n days
};
Date::Date(int yy, int mm, int dd)
    :y{ yy }, m{ mm }, d{ dd }
{
    if (m < 1 || 12 < m) error("invalid month");
    if (d < 1 || 31 < d) error("invalid day");
}
void Date::add_day(int n)
{
    d += n;
    if (d > 31) d %= 31;
}
ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}
int main()
try {
    Date today(1978, 6, 25);
    Date tomorrow = today;
    tomorrow.add_day(1);
    cout << today << '\n'
        << tomorrow << '\n';
    //Date bad_day(2004, 13, -5);
}
catch (exception& e) {
    cerr << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "unknown error" << '\n';
    return 2;
}
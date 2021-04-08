#include "std_lib_facilities.h"

// - define a Date called 'today' initialized to June 25, 1978

struct Date {
    int y;
    int m;
    int d;
};
void init_day(Date& dd, int y, int m, int d)
{
    if (m < 1 || m > 12)
        error("Invalid month!");
    if (d < 1 || d > 31)
        error("Invalid day!");
    dd.y = y;
    dd.m = m;
    dd.d = d;
}
void add_day(Date& dd, int n)
{
    dd.d += n;
    if (dd.d > 31) dd.d %= 31;
}
ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}
int main()
{
    Date today;
    init_day(today, 1978, 6, 25);
    Date tomorrow = today;
    add_day(tomorrow, 1);
    cout << today << '\n'
        << tomorrow << '\n';
    //Date bad_day;
    //init_day(bad_day, 2004, 13, -5);
}

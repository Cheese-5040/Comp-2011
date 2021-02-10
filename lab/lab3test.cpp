#include <iostream>

using namespace std;

// Task 1
// determine whether a year is a leap year
int is_leap_year(int year)
{
    int leap_year = 69;
    if (year % 4 == 0)
    {
        if ( year % 100 == 0){
            if (year % 400 == 0){
                leap_year = 1;
            }
            else{
                leap_year =0;
            }
        }
        else{
            leap_year =1;
        }
    }
    else{
        leap_year =0;
    }
    return leap_year;
}

// Task 2
// return number of days in a month
int get_num_month_days(int year, int month)
{
    int days = 0;
    int leap_year = is_leap_year(year);

    switch (month)
    {
    case 1:
        days = 31;
        break;
    case 2:
        if (leap_year == 1)
        {
            days = 29;
        }
        else
        {
            days = 28;
        }
        break;

    case 3:
        days = 31;
        break;
    case 4:
        days = 30;
        break;
    case 5:
        days = 31;
        break;
    case 6:
        days = 30;
        break;
    case 7:
        days = 31;
        break;
    case 8:
        days = 31;
        break;
    case 9:
        days = 30;
        break;
    case 10:
        days = 31;
        break;
    case 11:
        days = 30;
        break;
    case 12:
        days = 31;
        break;
    default:
        days = 0;
        break;
    }

    return days;
}

// Task 3
// return the anchor day of a century
int get_anchor_century(int year)
{
    int century = year / 100;
    int remainder = century % 4;
    int anchor_century;
    switch (remainder)
    {
    case 0:
        // if divisible by 4, then the doomsday is tuesday
        anchor_century = 2;
        break;
    case 1:
        // remainder 1, century doomsday is sunday
        anchor_century = 0;
        break;
    case 2:
        // remainder 2, century doomsday is a friday
        anchor_century = 5;
        break;
    case 3:
        // remainder 3, century doomsday is a wednesday
        anchor_century = 3;
        break;
    default:
        anchor_century = 69;
        break;
    }
    return anchor_century;
}

// Task 4
// return the weekday after offset
int offset_weekday(int weekday, int offset)
{
    int adjusted_offset;
    int adjusted_weekday;

    // if (offset < 0)
    // {
    //     adjusted_offset = -offset % 7;                            //make offset to only weekday differnece
    //     adjusted_weekday = ((weekday - adjusted_offset) + 7) % 7; // make sure no negative weekday by addign 7 and reducing to the weekday by modolus 7
    // }
    // else if (offset > 0)
    // {
    //     adjusted_offset = offset % 7;                       //make offset to only weekday differnece
    //     adjusted_weekday = (weekday + adjusted_offset) % 7; // make sure no negative weekday by addign 7 and reducing to the weekday by modolus 7
    // }
    adjusted_weekday = ((weekday + offset) %7 + 7) %7;
    return adjusted_weekday;
}

// Task 5
// return the anchor day of a year (the weekday of doomsdays)
int get_anchor_year(int year, int anchor_century)
{
    int century_code = get_anchor_century(year);
    int century = year / 100;                      // get the century for calculation
    int non_century_number = year - century * 100; // get years beside century

    int division = non_century_number / 12;    //finding the integer division of 12
    int remainder = non_century_number % 12;   //finding the remainder of the ddivision
    int division_of_remainder = remainder / 4; //finding the int division of the remainder

    int total, anchor_year;

    total = century_code + division + remainder + division_of_remainder;
    anchor_year = total % 7; // finding the anchor year

    return anchor_year; //return anchor day of the year
}

// Task 6
// return the doomsday in a month
int get_doomsday(int year, int month)
{
    int leap_year = is_leap_year(year); // get leap year
    int doomsday;

    switch (month)
    {
    case 1:
        if (leap_year == 0)
        {
            doomsday = 3;
        }
        else if (leap_year == 1)
        {
            doomsday = 4;
        }
        break;
    case 2:
        if (leap_year == 0)
        {
            doomsday = 28;
        }
        else if (leap_year == 1)
        {
            doomsday = 29;
        }
        break;
    case 3:
        doomsday = 14;
        break;
    case 4:
        doomsday = 4;
        break;
    case 5:
        doomsday = 9;
        break;
    case 6:
        doomsday = 6;
        break;
    case 7:
        doomsday = 11;
        break;
    case 8:
        doomsday = 8;
        break;
    case 9:
        doomsday = 5;
        break;
    case 10:
        doomsday = 10;
        break;
    case 11:
        doomsday = 7;
        break;
    case 12:
        doomsday = 12;
        break;
    default:
        doomsday = 420;
        break;
    }

    return doomsday;
}

// Task 7
// return the weekday of a date
int get_weekday(int year, int month, int day)
{
    int anchor_day = get_anchor_year(year, get_anchor_century(year));
    int month_doomsday = get_doomsday(year, month);
    int difference, final_day;

    difference = day - month_doomsday;
    final_day = offset_weekday(anchor_day, difference);

    return final_day;
}
// print the calendar of the month containing the date
void print_calendar(int year, int month, int day)
{
    // print title
    cout << "==========================================================" << endl;
    cout << "Doomsday Calendar, in memorial of John Conway (1937-2020)." << endl;
    cout << "==========================================================" << endl;
    cout << "\t\t\t" << year << "-" << month << endl;
    cout << "Sun\tMon\tTus\tWed\tThu\tFri\tSat" << endl;
    // print blank spaces
    int weekday = get_weekday(year, month, 1);
    for (int i = 0; i < weekday; i++)
    {
        cout << "\t";
    }
    // print dates
    int num_month_days = get_num_month_days(year, month);
    for (int date = 1; date <= num_month_days; date++)
    {
        // print date
        cout << date;
        if (date == day)
            cout << "*";
        // formating
        if (date < num_month_days)
        {
            if (weekday == 6)
                cout << endl;
            else
                cout << "\t";
        }
        else
            cout << endl;
        // update weekday
        weekday = offset_weekday(weekday, 1);
    }
    cout << "==========================================================" << endl;
}

int main()
{
    int year, month, day;
    cout << "Please input the date ('year month day'): ";
    cin >> year >> month >> day;
    cout << "anchor day of the century is "<<  get_anchor_century(year) << endl;
    cout << "doomsday for the year is : "<< get_anchor_year(year, get_anchor_century(year))<< endl;
    cout << " the weekday for this date is : "<< get_weekday(year, month, day)<< endl;
    cout << "the number of days in this month is : "<< get_num_month_days(year, month)<< endl;
    cout << offset_weekday(get_weekday(year, month, day),5)<< endl;
    print_calendar(year, month, day);

    return 0;
}
#include "Date.h"
#include <iostream>
using namespace std;

ostream &operator<<(ostream &output,const Date &date)
{
    output<<date.year<<"-"<<date.month<<"-"<<date.day;
    return output;
}

istream &operator>>(istream &input,Date &date)
{
    input>>date.year;
    input.ignore();
    input>>date.month;
    input.ignore();
    input>>date.day;
    return input;
}

Date::Date()
{
    //ctor
    try {
        setDate(1990,1,1);
    }
    catch(MyException &e) {
        cout<<e.what()<<endl;
    }
}

Date::Date(int y,int m,int d)
{
    try {
        setDate(y,m,d);
    }
    catch(MyException &e) {
        cout<<e.what()<<endl;
    }
}

Date::~Date()
{
    //dtor
}

Date::Date(const Date& a)
    :year(a.year),month(a.month),day(a.day)
{

}

void Date::setDate(int y,int m,int d)
{
    year=y;month=m;day=d;
    if(!checkdate()){
        year=1990;month=1;day=1;
        throw MyException("    EXCPTION: The date you input is invalid! The date will be set with default.");
    }
}

bool Date::checkdate() const
{
    bool flag=true;
    if(year<0)return false;
    if(month<1||month>12)return false;
    if(day<1||day>maxDayEveryMonth())return false;
    return flag;
}

unsigned int Date::maxDayEveryMonth() const
{
    switch(month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        if(isLeapYear())return 29;
        else return 28;
    default:
        return 0;
    }
}

int Date::getYear() const
{
    return year;
}

int Date::getMonth() const
{
    return month;
}

int Date::getDay() const
{
    return day;
}

bool Date::isLeapYear() const
{
    if((year%4==0 && year%100!=0) || year%400==0 || (year>=3200 && year%3200==0 && year%172800==0)){
        return true;
    }
    else{
        return false;
    }
}

void Date::nextDay()
{
    day++;
    if(!checkdate()){
        day=1;month++;
        if(!checkdate()){
            month=1;year++;
        }
    }
}

//void Date::print() const
//{
//    cout<<year<<"-"<<month<<"-"<<day<<endl;
//}

Date& Date::operator++()
{
    day++;
    nextDay();
    return *this;
}

Date Date::operator++(int)
{
    Date tmp=*this;
    nextDay();
    return tmp;
}

Date& Date::operator+(int num)
{
    day+=num;
    if(day>maxDayEveryMonth()) {
        day-=maxDayEveryMonth();
        month++;
        if(month>12) {
            month=1;
            year++;
        }
    }
    return *this;
}

void Date::printLeapYear() const
{
    cout<<getYear()<<" is a leap year or not?\n";
    if(isLeapYear())cout<<getYear()<<" is a leap year.\n";
    else cout<<getYear()<<" is not a leap year.\n";
}

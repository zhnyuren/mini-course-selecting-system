#ifndef DATE_H
#define DATE_H
#include <iostream>
#include "MyException.h"

class Date
{
    friend std::ostream &operator<<(std::ostream &,const Date &);
    friend std::istream &operator>>(std::istream &,Date &);
    public:
        Date();
        Date(int,int,int);
        virtual ~Date();
        Date(const Date&);
        void setDate(int,int,int);
        unsigned int maxDayEveryMonth() const;
        int getYear() const;
        int getMonth() const;
        int getDay() const;
        bool isLeapYear() const;
        void printLeapYear() const;
        void nextDay();
//        void print() const;
        Date& operator++();
        Date operator++(int);
        Date& operator+(int);

    protected:

    private:
        unsigned int year;
        unsigned int month;
        unsigned int day;
        bool checkdate() const;
};

#endif // DATE_H

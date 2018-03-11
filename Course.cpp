#include "Course.h"
#include <string>
#include <iomanip>
using namespace std;

ostream& operator<<(ostream &output,const Course& course)
{
    output<<"Course number: "<<left<<setw(4)<<course.courseNum<<"  Course name: "<<left<<setw(25)<<course.name<<"Course credit: "<<left<<setw(4)<<course.creditHour<<"³É¼¨£º"<<left<<setw(5)<<course.getScore();
    return output;
}

Course::Course()
{
    //ctor
}

Course::Course(const int _courseNum,const string& _name,const int _creditHour)
    :courseNum(_courseNum),name(_name),creditHour(_creditHour)
{

}

Course::~Course()
{
    //dtor

}

const string& Course::getCourseName() const
{
    return name;
}

int Course::getCourseCredit() const
{
    return creditHour;
}

int Course::getCourseNum() const
{
    return courseNum;
}

void Course::setCourseName(const string& _name)
{
    name=_name;
}

void Course::setCourseCredit(const int _creditHour)
{
    creditHour=_creditHour;
}

void Course::setCourseNum(const int _courseNum)
{
    courseNum=_courseNum;
}

void Course::setScore()
{

}
z

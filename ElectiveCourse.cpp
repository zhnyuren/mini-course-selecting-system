#include "ElectiveCourse.h"
#include <string>
#include <iostream>
using namespace std;

ElectiveCourse::ElectiveCourse()
{
    //ctor
}

ElectiveCourse::ElectiveCourse(const int num,const string& n,const int h)
    :Course(num,n,h)
{

}

ElectiveCourse::~ElectiveCourse()
{
    //dtor
}

void ElectiveCourse::setScore(const char a)
{
    if(a!='A'&&a!='B'&&a!='C'&&a!='D'&&a!='E') cout<<"Wrong input! Please enter A/B/C/D/E!\n";
    else grade=a;
}

int ElectiveCourse::getScore() const
{
    switch(grade) {
        case 'A': return 95;
        case 'B': return 85;
        case 'C': return 75;
        case 'D': return 65;
        case 'E': return 55;
    }
}

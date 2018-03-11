#include "ObligatoryCourse.h"
#include <string>
#include <iostream>
using namespace std;

ObligatoryCourse::ObligatoryCourse()
{
    //ctor
}

ObligatoryCourse::ObligatoryCourse(const int num,const string& n,const int h)
    :Course(num,n,h)
{

}

ObligatoryCourse::~ObligatoryCourse()
{
    //dtor
}

void ObligatoryCourse::setScore(const int a)
{
    if(a<0 || a>100) cout<<"Wrong input! Please enter integer 0-100!\n";
    else mark=a;
}

int ObligatoryCourse::getScore() const
{
    return mark;
}

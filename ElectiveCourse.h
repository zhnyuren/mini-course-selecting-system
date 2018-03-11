#ifndef ELECTIVECOURSE_H
#define ELECTIVECOURSE_H
#include <string>
#include "Course.h"


class ElectiveCourse : public Course
{
    public:
        ElectiveCourse();
        ElectiveCourse(const int,const std::string&,const int);
        virtual ~ElectiveCourse();
        void setScore(const char);
        int getScore() const;
    protected:
        char grade;
    private:
};

#endif // ELECTIVECOURSE_H

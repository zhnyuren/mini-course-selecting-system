#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <iostream>

class Course
{
    friend std::ostream& operator<<(std::ostream&,const Course&);
    public:
        Course();
        Course(const int,const std::string&,const int);
        virtual ~Course();
        const std::string& getCourseName() const;
        int getCourseCredit() const;
        int getCourseNum() const;
        void setCourseName(const std::string&);
        void setCourseCredit(const int);
        void setCourseNum(const int);
        virtual void setScore();
        virtual int getScore() const=0;
    protected:
        int courseNum;
        std::string name;
        int creditHour;
    private:

};

#endif // COURSE_H

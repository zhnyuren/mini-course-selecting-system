#ifndef STUDENT_H
#define STUDENT_H
#include "Date.h"
#include "Course.h"
#include "ObligatoryCourse.h"
#include "ElectiveCourse.h"
#include <string>
#include <iostream>
#include <typeinfo>
#include <cstring>
#include <iomanip>
#include <sstream>
#define MAX_SIZE 9
#define MAXOC_SIZE 8
#define MAXEC_SIZE 3

class Student
{
    friend std::ostream& operator<<(std::ostream&,const Student&);
    public:
        Student();
        Student(const char* const,const int,const int,const int);
        Student(const char* const);
        Student(const Student&);
        Student(const char* const,const Date);
        virtual ~Student();
        void setName(const char* const);
        void setBirthDate(int,int,int);
        void setBirthDate(const Date&);
        int getBirthYear() const;
        int getBirthMonth() const;
        int getBirthDay() const;
        const Date& getBirthDate() const;
        char* getName() const;
        void printName() const;
        void printBirthDate() const;
        void printCount() const;
        Student& addCourse(Course*);
        Student& addCourse(const int,const std::string,const int);
        bool removeCourse(int);
        int getCourseNumber() const;
        int getLastCourseNumber() const;
        Course* getCourseList(int) const;
        bool getClassFull() const;
        bool getGradeAlready() const;
        bool checkRepetition(Course*) const;
        void printList() const;
        int setStudScore();
        int calcCredit();
        double getCreditGrade() const;
    protected:

    private:
        char* name;
        Date birthDate;//为了可以reset，所以不设const
        static int countStud;
        Course* courseList[MAX_SIZE];
        int courseNumber=0;
        int lastCourseNumber=0;
        bool classFull=false;
        bool gradeAlready=false;
        double creditGrade;
};


#endif // STUDENT_H

#ifndef FOURTH_H
#define FOURTH_H
#define MAXOC_SIZE 8
#define MAXEC_SIZE 3
#include <string>
#include "Student.h"
#include "Course.h"
#include "ObligatoryCourse.h"
#include "ElectiveCourse.h"
#include "MyException.h"

class Console
{
    public:
        Console();
        virtual ~Console();
        void beforeRun();
        void run();
    protected:

    private:
        std::string op;
        Student student1;
        Course* oc[MAXOC_SIZE];
        Course* ec[MAXEC_SIZE];
        const std::string& getOp() const;
        void createCourse();
        void welcomeInputName();
        void showTheNavi() const;
        void printAllCourse() const;
        void printChosen() const;
        void chooseOc();
        void chooseEc();
        void deleteCourse();
        void enterGrade();
        void printGrade() const;
        void printCreditGrade();
        void exitSystem() const;
        void inputOp();
        void wrongInput() const;
};

#endif // FOURTH_H

#include "Console.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

Console::Console()
{
    //ctor
}

Console::~Console()
{
    //dtor
}

const string& Console::getOp() const
{
    return op;
}

void Console::createCourse()
{
//    oc[0]=new ObligatoryCourse(1,"Object-oriented",3);
//    oc[1]=new ObligatoryCourse(2,"Data Structure",4);
//    oc[2]=new ObligatoryCourse(3,"Liner Algebra",2);
//    oc[3]=new ObligatoryCourse(4,"Physics",3);
//    oc[4]=new ObligatoryCourse(5,"Calculous2",4);
//    oc[5]=new ObligatoryCourse(6,"Physical Education",1);
//    oc[6]=new ObligatoryCourse(7,"C++",4);
//    oc[7]=new ObligatoryCourse(8,"Calculous1",4);
//    ec[0]=new ElectiveCourse(9,"Web Analysis",1);
//    ec[1]=new ElectiveCourse(10,"Software Basic",1);
//    ec[2]=new ElectiveCourse(11,"Music",1);
    ifstream OcFile("OC_in.txt",ios::in);
    ifstream EcFile("EC_in.txt",ios::in);
    for(int i=0;i<MAXOC_SIZE;i++) {
        int courseNum,courseCredit;
        string courseName;
        OcFile>>courseNum>>courseName>>courseCredit;
        oc[i]=new ObligatoryCourse(courseNum,courseName,courseCredit);
    }
    for(int i=0;i<MAXEC_SIZE;i++) {
        int courseNum,courseCredit;
        string courseName;
        EcFile>>courseNum>>courseName>>courseCredit;
        ec[i]=new ElectiveCourse(courseNum,courseName,courseCredit);
    }
    OcFile.close();
    EcFile.close();
}

void Console::welcomeInputName()
{
    cout<<"Welcome to course selecting system!\n"<<endl;
    char *name;
    Date birth;
    name=new char[500];

//    cout<<"Please enter student name:";
//    cin>>name;
//    cout<<"\nPlease enter date of birth(e.g. 1992-3-4):";
//    cin>>birth;
    //
    ifstream stuInfoInput("student_info_in.txt",ios::in);
    stuInfoInput>>name>>birth;
    //
    student1.setName(name);
    student1.setBirthDate(birth);
    cout<<"\n    Hello,"<<student1.getName()<<"("<<student1.getBirthDate()<<")\n"<<endl;
    //
    int courseNum,courseCredit;
    string courseName;
    ifstream courseInfoInput("student_select_info_inout.txt",ios::in);
    while(courseInfoInput>>courseNum>>courseName>>courseCredit) {
        if(courseNum<=MAXOC_SIZE) student1.addCourse(oc[courseNum-1]);
        else student1.addCourse(ec[courseNum-1-MAXOC_SIZE]);
    }
    //
    stuInfoInput.close();
    courseInfoInput.close();
}

void Console::showTheNavi() const
{
    cout<<"\n*********************************Press any key*********************************\n"<<endl;
    getch();
    system("cls");
    cout<<"\n*****************Welcome, please enter the number of operation*****************\n"<<endl;
    cout<<"    1. Check available courses and rules"<<endl;
    cout<<"    2. Check course selecting result & update the course selecting result file"<<endl;
    cout<<"    3. Select obligatory course"<<endl;
    cout<<"    4. Select elective course"<<endl;
    cout<<"    5. Withdraw course "<<endl;
    cout<<"    6. Enter the grade"<<endl;
    cout<<"    7. Display the grade"<<endl;
    cout<<"    8. Display Cale grade"<<endl;
    cout<<"    0. Exit the system"<<endl;
    cout<<"\n******************************************************************************\n"<<endl;
}

void Console::printAllCourse() const
{
    cout<<"\n******************************************************************************\n"<<endl;
    cout<<"    Rules: you can choose "<<MAX_SIZE<<" course at most"<<endl;
    cout<<"\n    Available course:\n"<<endl;

    cout<<"    Obligatory course:\n"<<endl;
    for(int i=0;i<MAXOC_SIZE;i++)
        cout<<"    Course number: "<<left<<setw(4)<<oc[i]->getCourseNum()<<"  Course name: "<<left<<setw(25)<<oc[i]->getCourseName()<<"Course credit: "<<left<<setw(4)<<oc[i]->getCourseCredit()<<endl;

    cout<<"\n    Elective course:\n"<<endl;
    for(int i=0;i<MAXEC_SIZE;i++)
        cout<<"    Course number: "<<left<<setw(4)<<ec[i]->getCourseNum()<<"  Course name: "<<left<<setw(25)<<ec[i]->getCourseName()<<"Course credit: "<<left<<setw(4)<<ec[i]->getCourseCredit()<<endl;
}

void Console::printChosen() const
{
    cout<<"\n******************************************************************************\n"<<endl;
    cout<<student1;
    ofstream chooseResultFile("student_select_info_out.txt",ios::out);
    chooseResultFile<<student1;
    //
    ofstream chooseResultFileInout("student_select_info_inout.txt",ios::out);
    for(int i=0;i<student1.getCourseNumber();i++) {
        chooseResultFileInout<<student1.getCourseList(i)->getCourseNum()<<" "<<student1.getCourseList(i)->getCourseName()<<" "<<student1.getCourseList(i)->getCourseCredit()<<"\n";
    }
    //
    cout<<"    File updated successfully!"<<endl;
}

void Console::chooseOc()
{
    cout<<"\n******************************************************************************\n"<<endl;
    cout<<"    Rules: you can choose "<<MAX_SIZE<<" course at most\n"<<endl;
    cout<<"    Available obligatory course:\n"<<endl;
    for(int i=0;i<MAXOC_SIZE;i++)
        cout<<"    Course number: "<<left<<setw(4)<<oc[i]->getCourseNum()<<"  Course name: "<<left<<setw(25)<<oc[i]->getCourseName()<<"Course credit: "<<left<<setw(4)<<oc[i]->getCourseCredit()<<endl;
    int num;
    cout<<endl;
    while(1) {
        cout<<"Please enter the course number to choose obligatory course (press 0 to exit): ";
        cin>>num;
        bool isCaught=false;
        try {
            if(num==0) {
                cout<<"\n    Exit successfully\n"<<endl;
                break;
            }
            if(num<0||num>MAXOC_SIZE) {
                throw MyException("\n    EXCEPTION: Course does not exist. Please re-input!\n");
            }
            if(student1.checkRepetition(oc[num-1])) {
                throw MyException("\n    EXCEPTION: Course has been chosen already. Please re-input!\n");
            }
            if(student1.getClassFull()) {
                throw MyException("\n    EXCEPTION: The courses you chose have reach maximum. Operation failed!\n");
            }
        }
        catch(MyException &e) {
            cout<<e.what()<<endl;
            isCaught=true;
        }
        if(!isCaught) {
            student1.addCourse(oc[num-1]);
            cout<<"\n    Course selecting successful!\n"<<endl;
        }
    }
}

void Console::chooseEc()
{
    cout<<"\n******************************************************************************\n"<<endl;
    cout<<"    Rules: you can choose "<<MAX_SIZE<<" course at most\n"<<endl;
    cout<<"    Available elective course:\n"<<endl;
    for(int i=0;i<MAXEC_SIZE;i++)
        cout<<"    Course number: "<<left<<setw(4)<<ec[i]->getCourseNum()<<"  Course name: "<<left<<setw(25)<<ec[i]->getCourseName()<<"Course credit: "<<left<<setw(4)<<ec[i]->getCourseCredit()<<endl;
    int num;
    cout<<endl;
    while(1) {
        cout<<"Please enter the course number to choose obligatory course (press 0 to exit): ";
        cin>>num;
        bool isCaught=false;
        try {
            if(num==0) {
                cout<<"\n    Exit successfully\n"<<endl;
                break;
            }
            if(num<=MAXOC_SIZE || num>MAXOC_SIZE+MAXEC_SIZE) {
                throw MyException("\n    EXCEPTION: Course does not exist. Please re-input!\n");
            }
            if(student1.checkRepetition(ec[num-1-MAXOC_SIZE])) {
                throw MyException("\n    EXCEPTION: Course has been chosen already. Please re-input!\n");
            }
            if(student1.getClassFull()) {
                throw MyException("\n    EXCEPTION: The courses you chose have reach maximum. Operation failed!\n");
            }
        }
        catch(MyException &e) {
            cout<<e.what()<<endl;
            isCaught=true;
        }
        if(!isCaught) {
            student1.addCourse(ec[num-1-MAXOC_SIZE]);
            cout<<"\n    Course selecting successful!\n"<<endl;
        }
    }
}

void Console::deleteCourse()
{
    cout<<"\n******************************************************************************\n"<<endl;
    cout<<student1<<endl;
    int removeNum;
    while(1) {
        cout<<"Please enter course number to withdraw courses (Press 0 to exit): ";
        cin>>removeNum;
        if(removeNum==0) break;
        bool res=student1.removeCourse(removeNum);
        try {
            if(res) cout<<"\n    Withdraw successfully!\n"<<endl;
            else throw MyException("\n    EXCEPTION: You did not choose this course. Failed to withdraw!\n");
        }
        catch(MyException &e) {
            cout<<e.what()<<endl;
        }
    }
}

void Console::enterGrade()
{
    cout<<"\n******************************************************************************\n"<<endl;
    try {
        if(student1.getCourseNumber()==0) {
            throw MyException("    EXCEPTION: You did not select any course yet. Failed to enter grade!");
        }
    }
    catch(MyException &e) {
        cout<<e.what()<<endl;
        return;
    }
    student1.setStudScore();
}

void Console::printGrade() const
{
    cout<<"\n******************************************************************************\n"<<endl;
    try {
        if(!student1.getGradeAlready()) {
            throw MyException("    EXCPTION: You did not enter grade!");
        }
    }
    catch(MyException &e) {
        cout<<e.what()<<endl;
        return;
    }
    cout<<"Student name: "<<student1.getName();
    cout<<"    Birth of date: "<<student1.getBirthDate();
    cout<<"    Grade: \n"<<endl;
    for(int i=0;i<student1.getCourseNumber();i++) {
        cout<<"    "<<*(student1.getCourseList(i))<<endl;
    }
}

void Console::printCreditGrade()
{
    cout<<"\n******************************************************************************\n"<<endl;
    try {
        if(!student1.getGradeAlready()) {
            throw MyException("    EXCEPTION: You did not enter grade!");
        }
    }
    catch(MyException &e) {
        cout<<e.what()<<endl;
        return;
    }
    student1.calcCredit();
    cout<<"    Your credit grade is: "<<student1.getCreditGrade()<<endl;
}

void Console::exitSystem() const
{
    cout<<"\n******************************************************************************\n"<<endl;
    cout<<"    You have exit the system!"<<endl;
    exit(0);
}

void Console::inputOp()
{
    cout<<"Please enter the number of operation: ";
    cin>>op;
    cout<<endl;
}

void Console::wrongInput() const
{
    cin.ignore();
    cout<<"\n******************************************************************************"<<endl;
    throw MyException("\n    EXCEPTION: invalid operation number input! Please re-input!");
}

void Console::beforeRun()
{
    createCourse();
    welcomeInputName();
}

void Console::run()
{
    while(true) {
        showTheNavi();
        inputOp();
        system("cls");
        try {
            if     (getOp()=="1") printAllCourse();
            else if(getOp()=="2") printChosen();
            else if(getOp()=="3") chooseOc();
            else if(getOp()=="4") chooseEc();
            else if(getOp()=="5") deleteCourse();
            else if(getOp()=="6") enterGrade();
            else if(getOp()=="7") printGrade();
            else if(getOp()=="8") printCreditGrade();
            else if(getOp()=="0") exitSystem();
            else wrongInput();
        }
        catch(MyException &e) {
            cout<<e.what()<<endl;
        }
    }
}

#include "Student.h"

using namespace std;

int Student::countStud=0;

ostream& operator<<(ostream &output,const Student &student)
{
    output<<"Student name: "<<student.name;
    output<<"    Date of birth: "<<student.birthDate<<endl;
    output<<"Course: \n"<<endl;
    if(student.getCourseNumber()==0) {
        output<<"    You have not chose any courses yet!"<<endl;
        return output;
    }
    for(int i=0;i<student.getCourseNumber();i++) {
//        output<<"    "<<*(student.getCourseList(i))<<endl;
        output<<"    Course number: "<<left<<setw(4)<<student.getCourseList(i)->getCourseNum()<<"  Course name: "<<left<<setw(25)<<student.getCourseList(i)->getCourseName()<<"Course credit: "<<left<<setw(4)<<student.getCourseList(i)->getCourseCredit()<<endl;
    }
    return output;
}

Student::Student()
{
    //ctor
    const char *n="Student1";
    name=new char[strlen(n)+1];
    strcpy(name,n);
    countStud++;
}

Student::Student(const char* const n,const int y1,const int m1,const int d1)
    :birthDate(y1,m1,d1)
{
    name=new char[strlen(n)+1];
    strcpy(name,n);
    countStud++;
}

Student::Student(const char* const n)
{
    name=new char[strlen(n)+1];
    strcpy(name,n);
    countStud++;
}

Student::Student(const Student& a)//const对象只能调用const成员函数,所以a调用的函数后面必须加const修饰
    :birthDate(a.getBirthYear(),a.getBirthMonth(),a.getBirthDay())
{
    strcpy(name,a.name);
    countStud++;
}

Student::Student(const char* const _name,const Date _birth)
    :birthDate(_birth)
{
    name=new char[strlen(_name)+1];
    strcpy(name,_name);
    countStud++;
}

Student::~Student()
{
    //dtor
    for(int i=0;i<getCourseNumber();i++) {
        delete getCourseList(i);
    }
    courseNumber=0;
    delete []name;
    countStud--;
}

void Student::setName(const char* const n)
{
    if(name!=nullptr) {
        delete []name;
    }
    name=new char[strlen(n)+1];
    strcpy(name,n);
}

void Student::setBirthDate(int y1,int y2,int y3)
{
    try {
        birthDate.setDate(y1,y2,y3);//这里不能.year=y1，调用私有
    }
    catch(MyException &e) {
        cout<<e.what()<<endl;
    }
}

void Student::setBirthDate(const Date& _date)
{
    try {
        birthDate.setDate(_date.getYear(),_date.getMonth(),_date.getDay());
    }
    catch(MyException &e) {
        cout<<e.what()<<endl;
    }
}

int Student::getBirthYear() const
{
    return birthDate.getYear();//这里不能.year，报错私有
}

int Student::getBirthMonth() const
{
    return birthDate.getMonth();
}

int Student::getBirthDay() const
{
    return birthDate.getDay();
}

const Date& Student::getBirthDate() const
{
    return birthDate;
}

char* Student::getName() const
{
    return name;
}

void Student::printName() const
{
    cout<<"The student name is "<<name<<endl;
}

void Student::printBirthDate() const
{
    cout<<"The birthday of the student is ";
    cout<<birthDate;//非const对象可以调用const成员函数
}

void Student::printCount() const
{
    cout<<"Now the number of the object(s) is: "<<countStud<<endl;
    //Student::count or count
}

Student& Student::addCourse(Course *course)
{
    if(courseNumber<MAX_SIZE) {
        courseList[courseNumber++]=course;
        gradeAlready=false;
    }
    else classFull=true;
    return *this;
}

//Student& Student::addCourse(const int _num,const string _courseName,const int _creditHour)
//{
//    if(courseNumber<MAX_SIZE) {
//        courseList[courseNumber++]=new Course(_num,_courseName,_creditHour);
//        gradeAlready=false;
//    }
//    else classFull=true;
//    return *this;
//}

bool Student::removeCourse(int removeNum)
{
    int found=0,i;
    for(i=0;i<courseNumber;i++) {
        if(courseList[i]->getCourseNum()==removeNum) {
            found=1;
            break;
        }
    }
    if(!found) return 0;
    else {
        for(int j=i;j<courseNumber-1;j++) {
            courseList[j]=courseList[j+1];
        }
        courseNumber--;
        lastCourseNumber--;
        if(courseNumber==0) gradeAlready=false;
        return 1;
    }
}

int Student::getCourseNumber() const
{
    return courseNumber;
}

int Student::getLastCourseNumber() const
{
    return lastCourseNumber;
}

Course* Student::getCourseList(int i) const
{
    return courseList[i];
}

bool Student::getClassFull() const
{
    return classFull;
}

bool Student::getGradeAlready() const
{
    return gradeAlready;
}

bool Student::checkRepetition(Course *course) const
{
    for(int i=0;i<getCourseNumber();i++) {
        if(courseList[i]==course)
            return true;
    }
    return false;
}

void Student::printList() const
{
    cout<<endl;
    if(getCourseNumber()==0) {
        cout<<"    You have not chose any course yet!"<<endl;
        return;
    }
    for(int i=0;i<getCourseNumber();i++) {
        cout<<"    "<<getCourseList(i)->getCourseName()<<"(credit: "<<getCourseList(i)->getCourseCredit()<<")"<<endl;
    }
}

int Student::setStudScore()
{
    int mark=0;
    string grade;
    string score;
    if(getLastCourseNumber()==getCourseNumber()) {
        cout<<"    All the grades are set!\n"<<endl;
        return 0;
    }
    for(int i=getLastCourseNumber();i<getCourseNumber();i++) {
        if(typeid(ObligatoryCourse)==typeid(*getCourseList(i))) {
            cout<<"    Obligatory course \""<<getCourseList(i)->getCourseName()<<"\" \'s score(0-100): ";
//            cin>>mark;
            cin>>score;
            bool isdigit=true;
            for(int i=0;i<score.size();i++) {
                if(score[i]<48 || score[i]>57) isdigit=false;
            }
            stringstream ss;
            ss<<score;
            ss>>mark;
            try {
                if(!isdigit || (isdigit && (mark<0 || mark>100))) {
                    i--;
                    throw MyException("\n        EXCEPTION: Wrong input! Please enter integer 0-100!\n");
                }
            }
            catch(MyException &e) {
                cout<<e.what()<<endl;
                continue;
            }
            dynamic_cast<ObligatoryCourse*>(getCourseList(i))->setScore(mark);
            cout<<"\n        Grade upgraded successfully!\n"<<endl;
        }
        else {
            cout<<"    Elective course \""<<getCourseList(i)->getCourseName()<<"\" 's grade(A-E): ";
//            cin>>grade;
            cin>>score;
            bool isdigit=true;
            for(int i=0;i<score.size();i++) {
                if(score[i]<48 || score[i]>57) isdigit=false;
            }
            grade=score;
            try {
                if(isdigit || (!isdigit && grade.size()!=1) || (!isdigit && grade.size()==1 && grade[0]!='A' && grade[0]!='B' && grade[0]!='C' && grade[0]!='D' && grade[0]!='E')) {
                    i--;
                    throw MyException("\n        EXCEPTION: Wrong input! Please enter A/B/C/D/E!\n");
                }
            }
            catch(MyException &e) {
                cout<<e.what()<<endl;
                continue;
            }
            dynamic_cast<ElectiveCourse*>(getCourseList(i))->setScore(grade[0]);
            cout<<"\n        Grade upgraded successfully!\n"<<endl;
        }
    }
    gradeAlready=true;
    lastCourseNumber=getCourseNumber();
    return 1;
}

int Student::calcCredit()
{
//    if(!getGradeAlready()) {
////        cout<<"    您还没有录入成绩！"<<endl;
//        return 0;
//    }
//    else
    {
        double ocWeight=0.6;
        double ecWeight=0.4;
        double totalWeightOfOc=0;
        double totalWeightOfEc=0;
        double sumOcGradeMulcredit=0;
        double sumEcGradeMulcredit=0;
        for(int i=0;i<getCourseNumber();i++) {
            if(typeid(ObligatoryCourse)==typeid(*getCourseList(i))) {
                totalWeightOfOc+=getCourseList(i)->getCourseCredit();
                sumOcGradeMulcredit+=(getCourseList(i)->getScore() * (getCourseList(i)->getCourseCredit()));
            }
            else {
                totalWeightOfEc+=getCourseList(i)->getCourseCredit();
                sumEcGradeMulcredit+=(getCourseList(i)->getScore() * (getCourseList(i)->getCourseCredit()));
            }
        }
//        cout<<totalWeightOfOc<<" "<<totalWeightOfEc<<" "<<sumOcGradeMulcredit<<" "<<sumEcGradeMulcredit<<endl;
        if(totalWeightOfOc==0) {
            creditGrade=ecWeight*sumEcGradeMulcredit/totalWeightOfEc;
        }
        else if(totalWeightOfEc==0) {
            creditGrade=ocWeight*sumOcGradeMulcredit/totalWeightOfOc;
        }
        else {
            creditGrade=ocWeight*sumOcGradeMulcredit/totalWeightOfOc+ecWeight*sumEcGradeMulcredit/totalWeightOfEc;
        }
        return 1;
    }
}

double Student::getCreditGrade() const
{
    return creditGrade;
}

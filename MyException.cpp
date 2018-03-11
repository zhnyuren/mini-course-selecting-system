#include "MyException.h"
using namespace std;

MyException::MyException()
    :errInfo("Unknown Error!")
{
    //ctor
}

MyException::MyException(const string& str)
    :errInfo(str)
{

}

const string& MyException::what() const
{
    return errInfo;
}

MyException::~MyException()
{
    //dtor
}

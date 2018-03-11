#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <string>

class MyException
{
    public:
        MyException();
        MyException(const std::string&);
        virtual ~MyException();
        const std::string& what() const;
    protected:

    private:
        std::string errInfo;
};

#endif // MYEXCEPTION_H

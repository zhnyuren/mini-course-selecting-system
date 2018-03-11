#ifndef OBLIGATORYCOURSE_H
#define OBLIGATORYCOURSE_H
#include <string>
#include "Course.h"


class ObligatoryCourse : public Course
{
    public:
        ObligatoryCourse();
        ObligatoryCourse(const int,const std::string&,const int);
        virtual ~ObligatoryCourse();
        void setScore(const int);
        int getScore() const;
    protected:
        int mark;
    private:
};

#endif // OBLIGATORYCOURSE_H

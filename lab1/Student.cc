#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"
#include <iostream>

std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student.

    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();

    return "";
}

// TODO: implement functions which are declared in Student.h.
double Graduate::getGrade()const{
    double pts=0,gra=0;
    for (std::vector<Class*>::const_iterator it=classes.begin();it!=classes.end();++it){
        double sc=(*it)->getScore(id);
        if(sc>=90)gra+=4*(*it)->point;
        else if(sc>=80)gra+=3.5*(*it)->point;
        else if(sc>=70)gra+=3*(*it)->point;
        else if(sc>=60)gra+=2.5*(*it)->point;
        else gra+=2*(*it)->point;
        pts+=(*it)->point;
    }
    return gra/pts;
}
double Undergraduate::getGrade() const{
    double pts=0,gra=0;
    for (std::vector<Class*>::const_iterator it=classes.begin();it!=classes.end();++it){
        double a=(*it)->getScore(id);
        gra+=a/20*(*it)->point;
        pts+=(*it)->point;
    }
    return gra/pts;
}
void Student::addClass(Class* c){
    classes.push_back(c);
}

#include "Class.h"
#include <string>
#include "Student.h"

void Class::addStudent(const Student &st)
{
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper &Class::getStudentWrapper(const std::string &studentId)
{
    for (std::vector<StudentWrapper>::iterator it = students.begin();
        it != students.end();
        ++it) {
        if (it->id == studentId)
            return *it;
    }
    throw "No matching student!";
}

double Class::getScore(std::string id) const{
    for(std::vector<StudentWrapper>::const_iterator its=students.begin();
        its!=students.end();its++){
        if(its->id==id){
            return its->getScore();
        }
    }
}
double Class::getAvgScore()
{
    double sum=0;int pe=0;
    // TODO: implement getAvgScore.
    for (std::vector<StudentWrapper>::iterator it = students.begin();
         it != students.end();
         ++it){
        pe++;sum+=it->getScore();
    }
    if(!pe)return 0;
    return sum/pe;
}

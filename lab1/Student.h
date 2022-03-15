#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
    // TODO: implement class Student.
private:
    const std::string name,year;
    Degree degree;
protected:
    std::vector<Class*> classes;
public:
    Student(const std::string a,const std::string b,const std::string c,Degree d):id(a),name(b),year(c),degree(d){}
    const std::string id;
    std::string toString() const;
    virtual double getGrade()const=0;
    void addClass(Class *c);
};

// TODO: implement class Graduate.
class Graduate:public Student{
private:
public:
    Graduate(const std::string a,const std::string b,const std::string c,Degree d):Student(a,b,c,d){}
    double getGrade()const;
};

// TODO: implement class Undergraduate.
class Undergraduate:public Student{
private:
public:
    Undergraduate(const std::string a,const std::string b,const std::string c,Degree d):Student(a,b,c,d){}
    double getGrade()const;
};

class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    // TODO: fix error
    StudentWrapper(const std::string &id, const Student &student):id(id),student(student){
    }

    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Invalid Score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_

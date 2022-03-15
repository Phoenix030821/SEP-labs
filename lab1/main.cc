#include <vector>
#include <iostream>
#include <fstream>
#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    Class *cl = nullptr;

    // Open a file as a input stream.
    ifstream stfile("./Students.txt");
    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.

        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2],undergraduate);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2],graduate);


        studentVec.push_back(st);
    }
    stfile.close();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    // Hint: how is student information read?
    ifstream clfile("./Classes.txt");

    while (getline(clfile, line)){
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;
        std::string nam=line.substr(6,string::npos);
        getline(clfile, line);
        int pt=line[7]-'0';
        cl=new Class(nam,pt);
        while(getline(clfile,line)){
            if(line.empty())break;
            for(std::vector<Student*>::iterator it=studentVec.begin();
                it!=studentVec.end();
                it++){
                if((*it)->id==line){
                    cl->addStudent(**it);
                    (*it)->addClass(cl);
                }
            }
        }
        classVec.push_back(cl);
    }
    clfile.close();
}

void AppX::inputScore()
{

    // TODO: implement inputScore.
    // Hint: Take a look at printAvgScore().
    string sbuf;
    Class *cl;
    double pts;
    while (true){
        cout<<"Please input the class name (or input q to quit): ";
        cin>>sbuf;
        if(sbuf=="q")break;
        cl=nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                while(true){
                    bool qu=0;
                    while(true){
                        cout<<"Please input the student ID (or input q to quit): ";
                        cin>>sbuf;
                        if(sbuf=="q"){
                            qu=1;break;
                        }
                        try{
                        (*it)->getStudentWrapper(sbuf);
                        }catch(char const*){
                            cout<<"No matching student!"<<endl;
                            continue;
                        }
                        break;
                    }
                    if(qu)break;
                    cout<<"please input the score: ";
                    try{
                        cin>>pts;
                        if(pts<0||pts>100){
                            throw "Wrong score!";
                        }
                    }catch(char const*){
                        cout<<"Wrong score!"<<endl;
                        continue;
                    }


                    (*it)->getStudentWrapper(sbuf).setScore(pts);
                }
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

    }
}

void AppX::printAvgScore()
{
    string sbuf;
    Class *cl;
    double avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        avg = cl->getAvgScore();
        printf("The average score is: %.2lf\n",avg);
    }
}

void AppX::printGpa()
{
    string sbuf;
    while(true){
        cout<<"Please input the student ID (or input q to quit): ";
        cin>>sbuf;
        if(sbuf=="q")break;bool fl=0;
        for(vector<Student*>::iterator it=studentVec.begin();
            it!=studentVec.end();
            it++){
            if(sbuf==(*it)->id){
               cout<<(*it)->toString();
               printf("GPA = %.2f\n",(*it)->getGrade());
               fl=1;
               break;
            }
        }
        if(!fl)cout<<"No match student!"<<endl;
    }
    // TODO: implement printGpa.
    // Hint: Take a look at printAvgScore().
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute average score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}

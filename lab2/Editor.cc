#include <iostream>
#include <sstream>
#include "Editor.h"

using namespace std;

Editor::Editor()
{
    buffer = new Buffer();
}
Editor::~Editor()
{
    delete buffer;
    // TODO: Implement destructor
}

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            cout << "? " << e << endl;
        } catch (const out_of_range &oor) {
            cout << "? " << oor.what() << endl;
        } catch (const range_error &re) {
            cout << "? " << re.what() << endl;
        }
    }
}
void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    // TODO: finish cmdAppend.
    while (true)
    {
        string text;
        getline(cin, text);
        if(text == ".")
            break;
        currentLine++;
        buffer->appendLine(text);
    }
}

void Editor::cmdInsert()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    bool firstLine = true;
    while (true)
    {
        string text;
        getline(cin, text);
        if (text == ".")
            break;
        if (firstLine) {
            buffer->insertLine(text);
            firstLine = false;
        }  else {
            buffer->appendLine(text);
        }
        currentLine++;
    }
}

void Editor::cmdDelete(int start, int end)
{
    buffer->deleteLines(start, end);
    currentLine-=(end-start+1);
}

void Editor::cmdNull(int line)
{
    cout << buffer->moveToLine(line) << endl;
    buffer->setCurrent(line);
}

void Editor::cmdNumber(int start, int end)
{
    buffer->showLines(start, end);
    buffer->setCurrent(end);
}

void Editor::cmdWrite(const string &filename)
{
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)
{
    if (cmd == "a") {
        cmdAppend();
        return;
    }
    if (cmd == "i") {
        cmdInsert();
        return;
    }
    if (cmd[0] == 'w') {
        // TODO: call cmdWrite with proper arguments
        if(cmd.length()<2){
            throw "Filename not specified";
        }
        std::string fName=cmd.substr(2,cmd.length()-2);
        if(fName.empty()){
            throw "Filename not specified";
        }
        cmdWrite(fName);
        return;
    }
    // TODO: handle special case "1,$n".
    if(cmd=="1,$n"){
        if(currentLine==0)throw "Number range error";
        buffer->showLines(1,currentLine);
        buffer->setCurrent(currentLine);
        return;
    }
    int start, end;
    char comma, type = ' ';
    stringstream ss(cmd);
    ss >> start;
    if (ss.eof()) {
        if(start<1 || start>currentLine){
            throw "Line number out of range";
        }
        cmdNull(start);
        return;
    }
    ss >> comma >> end >> type;
    if (ss.good()) {
        if(start>end){
            if(type=='d')throw "Delete range error";
            else if(type=='n')throw "Number range error";
        }
        if(start<1||end<1||start>currentLine||end>currentLine){
            throw "Line number out of range";
        }
        if (type == 'n') {
            cmdNumber(start, end);
            return;
        } else if (type == 'd') {
            cmdDelete(start, end);
            return;
        }
    }
    throw "Bad/Unknown command";
}

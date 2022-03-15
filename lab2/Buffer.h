#pragma once

#include <string>

using std::string;

class Buffer {
private:
    int currentLineNum=0;
    // TODO: add a List here for storing the input lines
    struct lines{
        std::string s;
        lines *nxt=nullptr;
    };
    lines *head=nullptr;

public:
    Buffer();
    ~Buffer();

    void writeToFile(const string &filename) const;
    void setCurrent(int i);
    const string &moveToLine(int idx) const;

    void showLines(int from, int to) const;

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};

#include <fstream>
#include <iostream>
#include "Buffer.h"
#include <cstdio>
#include <fstream>

//TODO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() {
    head=new lines;
}

Buffer::~Buffer() {
    lines *now = head;
    while(now!=nullptr){
        lines *p=now;
        now=now->nxt;
        delete p;
    }
}

void Buffer::setCurrent(int i){
    currentLineNum=i;
}
void Buffer::writeToFile(const string &filename) const {
    const char *f=filename.data();
    std::ofstream fout("./"+filename);
    lines *now=head->nxt;
    while(now!=nullptr){
        fout<<now->s<<std::endl;
        now=now->nxt;
    }
    std::cout<<fout.tellp()<<" byte(s) written"<<std::endl;
}

void Buffer::showLines(int from, int to) const {
    lines *now=head;
    for(int x=1;x<from;x++){
        now=now->nxt;
    }
    for(int x=from;x<=to;x++){
        now=now->nxt;
        std::cout<<x<<"\t"<<now->s<<std::endl;
    }
}

void Buffer::deleteLines(int from, int to){
    lines *now=head;
    for(int x=1;x<from;x++){
        now=now->nxt;
    }
    for(int x=from;x<=to;x++){
        lines *p=now->nxt;
        now->nxt=p->nxt;
        delete p;
    }
    if(now->nxt!=nullptr)currentLineNum=from;
    else currentLineNum=from-1;
}

void Buffer::insertLine(const string &text){
    lines *now=head;
    for(int  x=1;x<currentLineNum;x++){
        now=now->nxt;
    }
    lines *ins=new lines;
    ins->s=text;
    ins->nxt=now->nxt;
    now->nxt=ins;
    if(!currentLineNum)currentLineNum=1;
}

void Buffer::appendLine(const string &text){
    lines *now=head;
    for(int  x=1;x<=currentLineNum;x++){
        now=now->nxt;
    }
    lines *ins=new lines;
    ins->s=text;
    ins->nxt=now->nxt;
    now->nxt=ins;
    currentLineNum++;
}

const string &Buffer::moveToLine(int idx) const {
    lines *now = head;
    for(int x=1;x<=idx;x++){
        now=now->nxt;
    }
    return now->s;
}

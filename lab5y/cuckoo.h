#ifndef CUCKOO_H
#define CUCKOO_H

#include <iostream>
using namespace std;
class cuckoo
{
private:
    int siz=8,kickNum=0;
    bool fl=0;
    int *c[2],*to[2];
public:
    int h1(int x){
        return x%siz;
    }
    int h2(int x){
        return (x/siz)%siz;
    }
    void resize(int k,int v);
    void cuck(int k,int v,int i);
    void insert(int k,int v);
    int lookup(int k);
    void del(int k);
    void run();
};

#endif //CUCKOO_H
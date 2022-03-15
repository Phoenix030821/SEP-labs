#include<iostream>
#include<cstdio>
#include<cstring>
#include"cuckoo.h"

using namespace std;

void cuckoo::resize(int k,int v){
    int *cc[2],*tt[2];
    cc[1]=c[1];cc[0]=c[0];
    tt[1]=to[1];tt[0]=to[0];
    siz*=2;
    c[0]=new int [siz];
    c[1]=new int [siz];
    to[0]=new int [siz];
    to[1]=new int [siz];
    for(int x=0;x<2;x++){
        for(int y=0;y<siz;y++)c[x][y]=0x3f3f3f3f,to[x][y]=0;
    }
    for(int x=0;x<2;x++){
        for(int y=0;y<siz/2;y++){
            if(cc[x][y]!=0x3f3f3f3f)insert(cc[x][y],tt[x][y]);
        }
    }
    insert(k,v);
    delete cc[1];
    delete cc[0];
    delete tt[1];
    delete tt[0];
}
void cuckoo::cuck(int k,int v,int i){
    if(kickNum>=2*siz){
        printf("Loop Detect\n");
        resize(k,v);
        return;
;    }
    int t=i?h2(k):h1(k);
    if(c[i][t]==0x3f3f3f3f){
        c[i][t]=k;
        to[i][t]=v;
        return;
    }
    kickNum++;
    int kk=c[i][t],vv=to[i][t];
    c[i][t]=k;
    to[i][t]=v;
    printf("Kick %d with %d in table %d %d\n",kk,k,i,t);
    cuck(kk,vv,!i);
}
void cuckoo::insert(int k,int v){
    fl=0;
    kickNum=0;
    if(c[0][h1(k)]==0x3f3f3f3f||c[0][h1(k)]==k){
        c[0][h1(k)]=k;
        to[0][h1(k)]=v;
    }
    else{
        if(c[1][h2(k)]==0x3f3f3f3f||c[1][h2(k)]==k){
            c[1][h2(k)]=k;
            to[1][h2(k)]=v;
        }
        else cuck(k,v,0);
    }
}
int cuckoo::lookup(int k){
    fl=0;
    if(c[0][h1(k)]==k){
        fl=1;return to[0][h1(k)];
    }
    if(c[1][h2(k)]==k){
        fl=1;return to[1][h2(k)];
    }
    return 0;
}
void cuckoo::del(int k){
    if(c[0][h1(k)]==k){
        c[0][h1(k)]=0x3f3f3f3f;
        to[0][h1(k)]=0;
        return;
    }
    if(c[1][h2(k)]==k){
        c[1][h2(k)]=0x3f3f3f3f;
        to[1][h2(k)]=0;
        return;
    }
    if(!fl)printf("Key Not Found\n");
}
void cuckoo::run(){
    siz=8;
    c[1]=new int [8];
    c[0]=new int [8];
    to[1]=new int [8];
    to[0]=new int [8];
    for(int x=0;x<2;x++){
        for(int y=0;y<8;y++)c[x][y]=0x3f3f3f3f,to[x][y]=0;
    }
    string com;
    int key,val;
    int m,n;cin>>m;
    while(m--){
        cin>>com;
        if(com=="Insert"){
            cin>>key>>val;
            insert(key,val);
        }
        if(com=="Lookup"){
            cin>>key;
            int t=lookup(key);
            if(!fl)printf("Key Not Found\n");
            else printf("%d\n",t);
        }
        if(com=="Delete"){
            cin>>key;
            del(key);
        }
    }
}
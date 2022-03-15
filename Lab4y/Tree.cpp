#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
ostream &operator<<(ostream &out, const TreeNode &b){
    out<<b.data[0]<<" "<<b.data[1];
    return out;
}
istream &operator>>(istream &in, BinaryDimonTree &tree){
    int n;
    in>>n;
    for(int x=1;x<=n;x++){
        in>>tree.p[x].i>>tree.p[x].j;
    }
    tree.ins(1,n,tree.root,0);
    return in;
}
bool cmp1(nod a,nod b){
    return a.j<b.j;
}
bool cmp0(nod a,nod b){
    return a.i<b.i;
}
void BinaryDimonTree::ins(int l,int r,TreeNode *&curr,int d){
    if(l>r)return;
    if(l<r){
        if(d%2)sort(p+l,p+r+1,cmp1);
        else sort(p+l,p+r+1,cmp0);
    }
    int mid=(l+r)/2;
    curr=new TreeNode(p[mid].i,p[mid].j,d);
    ins(l,mid-1,curr->ls,d+1);
    ins(mid+1,r,curr->rs,d+1);
}
BinaryDimonTree::BinaryDimonTree(){
    root=nullptr;
}
long long distance(TreeNode *a,int x,int y){
    return (a->getX()-x)*(a->getX()-x)+(a->getY()-y)*(a->getY()-y);
}

void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode **guess){
    if(cur==nullptr)
        return;
    if(distance(cur,x,y)<min_distance){
        min_distance=distance(cur,x,y);
        *guess=cur;
        xmax=cur->getX();ymax=cur->getY();
    }
    else if(distance(cur,x,y)==min_distance&&cur->getX()<xmax){
        min_distance=distance(cur,x,y);
        *guess=cur;
        xmax=cur->getX();ymax=cur->getY();
    }
    else if(distance(cur,x,y)==min_distance&&cur->getX()==xmax&&cur->getY()<ymax){
        min_distance=distance(cur,x,y);
        *guess=cur;
        xmax=cur->getX();ymax=cur->getY();
    }
    int dat[2]={x,y};
    if(dat[cur->depth%2]<cur->data[cur->depth%2]){
        recur_search(cur->ls,x,y,min_distance,guess);
        if(abs(dat[cur->depth%2]-cur->data[cur->depth%2])<=min_distance)
            recur_search(cur->rs,x,y,min_distance,guess);
    }
    else{
        recur_search(cur->rs,x,y,min_distance,guess);
        if(abs(dat[cur->depth%2]-cur->data[cur->depth%2])<=min_distance)
            recur_search(cur->ls,x,y,min_distance,guess);
    }
}

TreeNode *BinaryDimonTree::find_nearest_node(int x, int y){
    TreeNode **guess=new TreeNode*;
    long long bestDist=1e9;
    xmax=ymax=0x3f3f3f3f;
    recur_search(root,x,y,bestDist,guess);
    return *guess;
}
/*
void BinaryDimonTree::insert(int x,int y,TreeNode *&now,int d){
    if(now==nullptr){
        now=new TreeNode(x,y,d);
        return;
    }
    if(d%2){
        if(now->data[1]>y)insert(x,y,now->ls,d+1);
        else insert(x,y,now->rs,d+1);
    }
    else{
        if(now->data[0]>x)insert(x,y,now->ls,d+1);
        else insert(x,y,now->rs,d+1);
    }
    return;
}
*/

int TreeNode::getX(){
    return this->data[0];
}
int TreeNode::getY(){
    return this->data[1];
}

TreeNode::~TreeNode(){}

void BinaryDimonTree::clear(TreeNode *i){
    if(i==nullptr)return;
    clear(i->ls);
    clear(i->rs);
    delete i;
}
BinaryDimonTree::~BinaryDimonTree(){
    clear(root);
}
//
// Created by Smile on 2019/4/8.
//

#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
struct nod{
    int i,j;
  };
bool cmp1(nod a,nod b);
bool cmp0(nod a,nod b);
class TreeNode
{
  friend ostream &operator<<(ostream &out, const TreeNode &b);
  friend class BinaryTree;
  friend class BinaryDimonTree;

private:
  /* data */
  int data[2];
  int depth;
  TreeNode *ls,*rs;
public:
  /* methods */
  TreeNode(int x,int y,int d){
    data[0]=x;data[1]=y;depth=d;
    ls=nullptr;rs=nullptr;
  }
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  ~TreeNode(); /* DO NOT CHANGE */
};


class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */

private:
  /* data */
  TreeNode *root;
  int xmax=0x3f3f3f3f,ymax=0x3f3f3f3f;
  nod p[50010];
public:
  /* methods */
  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */
  void ins(int l,int r,TreeNode *&curr,int d);
  //void insert(int x,int y,TreeNode *&now,int d);
  void recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode **guess);
  void clear(TreeNode *i);
  ~BinaryDimonTree();
};

#endif //C_BINARYDIMEN_TREE_H

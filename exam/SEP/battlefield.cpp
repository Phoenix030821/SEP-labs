#include "battlefield.h"
#include<iostream>
// find path in this function
// you can add other functions to solve this problem
// you should print the path if you can find one
// if you can find one, return true, otherwise false
void BattleField::dfs(int i,int j){
    if(i<0||j<0||i>99||j>99)return;
    if(field[i][j])return;
    if(vis[i][j])return;
    if(fl)return;
    vis[i][j]=1;
    sta[++top][0]=i;sta[top][1]=j;
    if(i==99){
        fl=1;
        for(int x=1;x<=top;x++)
            field[sta[x][0]][sta[x][1]]=2;
        return;
    }
    for(int x=0;x<4;x++){
        dfs(i+dir[x][0],j+dir[x][1]);
    }
    if(!fl)top--;
}
bool BattleField::findPath(){
    for(int x=0;x<100;x++){
        for(int i=0;i<100;i++){
            for(int j=0;j<100;j++){
                vis[i][j]=0;
                if(field[i][j]==2)field[i][j]=0;
            }

        }
        top=0;fl=0;
        dfs(0,x);
        if(fl)break;
    }
    return fl;
}


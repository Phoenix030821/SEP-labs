#include<iostream>
#include<cstdio>
#include"lexicon.h"
using namespace std;
char c[110][110];
string word[100010],now,s;
int n,score,num,l,pcscore;
bool fl,vis[110][110];
int dir[8][2]={{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,1},{1,-1},{-1,-1}};
Lexicon english("EnglishWords.txt");
Lexicon already;
Lexicon pcfind;
void find(int num,int i,int j){
    if(vis[i][j])return;
    if(fl)return;
    if(num==l){
        fl=1;return;
    }
    vis[i][j]=1;
    for(int x=0;x<8;x++){
        if(c[i+dir[x][0]][j+dir[x][1]]==now[num]||c[i+dir[x][0]][j+dir[x][1]]+32==now[num])
            find(num+1,i+dir[x][0],j+dir[x][1]);
    }
    vis[i][j]=0;
}
void dfs(int i,int j){
    if(i>n||j>n||i<1||j<1)return;
    if(vis[i][j])return;
    s+=c[i][j];
    if(!english.containsPrefix(s)){
        s=s.substr(0,s.length()-1);return;
    }
    vis[i][j]=1;
    if(english.contains(s)&&(!already.contains(s))&&(!pcfind.contains(s))&&s.length()>3){
        pcfind.add(s);pcscore+=(s.length()-3);
    }
    for(int x=0;x<8;x++)dfs(i+dir[x][0],j+dir[x][1]);
    vis[i][j]=0;
    s=s.substr(0,s.length()-1);
}
int main(){
    cin>>n;
    for(int x=1;x<=n;x++)scanf("%s",c[x]+1);
    while(1){
        for(int x=1;x<=n;x++)printf("%s\n",c[x]+1);
        printf("Your Score: %d\nYour Words: ",score);
        for(int x=1;x<=num;x++)cout<<word[x]<<" ";
        cout<<endl;
        cin>>now;l=now.length();
        if(now!="???"){
            if(l<4){
                cout<<now<<" is too short.\n";
                continue;
            }
            if(!english.contains(now)){
                cout<<now<<" is not a word.\n";
                continue;
            }
            fl=0;
            for(int x=1;x<=n;x++){
                for(int y=1;y<=n;y++){
                    if(c[x][y]==now[0]||c[x][y]+32==now[0])find(1,x,y);
                    if(fl)break;
                }
                if(fl)break;
            }
            if(!fl){
                cout<<now<<" is not on board.\n";
            }
            else{
                if(!already.contains(now)){
                    already.add(now);
                    int ll=now.length();
                    for(int x=0;x<ll;x++){
                        if(now[x]<'a')now[x]+=32;
                    }
                    word[++num]=now;
                    score+=(l-3);
                }
                else cout<<now<<" is already found.\n";
            }
        }
        else{
            for(int x=1;x<=n;x++){
                for(int y=1;y<=n;y++)dfs(x,y);
            }
            printf("Computer Score: %d\nComputer Words: ",pcscore);
            for(string it:pcfind){
                l=it.length();
                for(int x=0;x<l;x++)printf("%c",it[x]-32);printf(" ");
            }
            break;
        }
    }
    return 0;
}
#ifndef BOARD_H
#define BOARD_H
#endif // BOARD_H

// Don't change, width = N, height = N
#define N 100
class BattleField
{
public:
    int field[N][N];
    bool vis[N][N],fl;
    int sta[N*N][2],top;
    int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
    // find path in this function
    bool findPath();
    void dfs(int i,int j);
};

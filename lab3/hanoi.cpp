#include "termio.h"
#include <cstdio>

// Do not delete the following line
char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];

int sta[520][2],top=0;
int ter[3][6],head[3];
void write_hi() {
    for (int i = 0; i < 5; i++) {
        Termio::buffer[i][0] = '|';
        Termio::buffer[i][5] = '|';
        Termio::buffer[i][9] = '|';
        Termio::buffer[i][13] = '*';
    }
    Termio::buffer[3][13] = ' ';
    Termio::buffer[1][9] = ' ';
    for (int i = 1; i < 5; i++) {
        Termio::buffer[2][i] = '-';
    }
}

void mov(int i,int j){
    if(!head[i])return;
    if(head[j]&&ter[i][head[i]]>ter[j][head[j]])return;
    sta[++top][0]=i;
    sta[top][1]=j;
    ter[j][++head[j]]=ter[i][head[i]];
    head[i]--;
}

void setDisk(){
    //11,41
    Termio::ResetBuffer();
    for(int x=0;x<41;x++)Termio::buffer[10][x]='-';
    for(int x=0;x<11;x++){
        Termio::buffer[x][5]='|';
        Termio::buffer[x][20]='|';
        Termio::buffer[x][35]='|';
    }
    for(int x=1;x<=head[0];x++){
        for(int y=5-ter[0][x];y<=5+ter[0][x];y++)
            Termio::buffer[11-2*x][y]='*';
    }
    for(int x=1;x<=head[1];x++){
        for(int y=20-ter[1][x];y<=20+ter[1][x];y++)
            Termio::buffer[11-2*x][y]='*';
    }
    for(int x=1;x<=head[2];x++){
        for(int y=35-ter[2][x];y<=35+ter[2][x];y++)
            Termio::buffer[11-2*x][y]='*';
    }

}

void hanoi(int n,int i,int j,int k){
    if(!n)return;
    hanoi(n-1,i,k,j);
    mov(i,j);
    printf("Auto moving:%d->%d\n",i+1,j+1);
    setDisk();
    Termio::Clear();
    Termio::Draw();
    hanoi(n-1,k,j,i);
}
void hanoi_enhanced(int x,int y,int z,int i,int j,int k){
    hanoi(y+z,i,j,k);
    hanoi(z,j,k,i);
}

int main() {
    int a,b,c,d;char a1;
    // ---- Example: how to use termio.h ----
    // clear screen
    //Termio::Clear();
    // reset buffer
    //Termio::ResetBuffer();
    //write_hi();
    //Termio::Draw();
    // ----------- End of example -----------
    // Your code here
    while(true){
        top=0;
        std::cout << "How many disks do you want? (1 ~ 5)" << std::endl;
        cin>>a1;
        if(a1=='Q')exit(0);
        a=a1-'0';
        if(a>0&&a<6){
            for(int x=1;x<=a;x++)ter[0][x]=a-x+1;
            head[0]=a;head[1]=head[2]=0;
            while(true) {
                setDisk();
                Termio::Clear();
                Termio::Draw();
                std::cout << "Move a disk. Format: x y" << std::endl;
                char b1;
                cin>>b1;
                if(b1>'0'){
                    b=b1-'0';
                    cin>>c;
                    if(c<=0||c>3||b>3)continue;
                    mov(b-1,c-1);
                    if(head[1]==a){
                        setDisk();
                        Termio::Clear();
                        Termio::Draw();
                        std::cout << "Congratulations! You win!" << std::endl;
                        break;
                    }
                }
                if(b1=='0'){
                    cin>>c;
                    if(c!=0)continue;
                    while(top){
                        Termio::Clear();
                        printf("Auto moving:%d->%d\n",sta[top][1]+1,sta[top][0]+1);
                        mov(sta[top][1],sta[top][0]);
                        setDisk();
                        Termio::Draw();
                        top--;
                    }
                    hanoi(a,0,1,2);
                    std::cout << "Congratulations! You win!" << std::endl;
                    break;
                }
                if(b1=='-'){
                    cin>>b>>c>>d;
                    if(b-c-d==a){
                        while(top){
                            Termio::Clear();
                            printf("Auto moving:%d->%d\n",sta[top][1]+1,sta[top][0]+1);
                            mov(sta[top][1],sta[top][0]);
                            setDisk();
                            Termio::Draw();
                            top--;
                        }
                        hanoi_enhanced(b,-c,-d,0,1,2);
                        std::cout << "Congratulations! You win!" << std::endl;
                        break;
                    }
                }
                if(b1=='Q')break;
            }
        }
    }

    return 0;
}

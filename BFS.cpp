//BFS，广度优先。DFS采用栈实现，故可递归
//BFS可参考树的层次遍历，可用队列实现

//题目描述：给定一个n*m的迷宫，*代表不可穿过的墙壁，而"."代表平地，S表示起点，T代表终点当前位置是(x,y)（下标从0开始）
//每次只能上下左右移动，求最短路径

//两种思路：BFS，通过遍历每一层来寻找出口，统计路径长
//         DFS，通过枚举每一种路径，寻找最短的哪个

#include <stdio.h>
#include <string.h>
#include <queue> //BFS思想

#define MAX 100

using namespace std;

struct node
{
    int x,y;//坐标
    int step;//步数
}S,T,NODE; //起点，终点和临时结点

int n,m; //h行和列
char maze[MAX][MAX];//迷宫信息
bool inq[MAX][MAX]={0}; //记录是否已入队
int X[4]={0,0,1,-1};
int Y[4]={1,-1,0,0}; //增量数组

//判断位置(x,y)是否有效
bool test(int x,int y)
{
    if(x>=n||x<0||y>=m||y<0)  //越界
        return 0;
    if(maze[x][y]=='*')       //碰壁
        return 0;
    if(inq[x][y]==1)          //已经入队过
        return 0;
    return 1;
}

int BFS()
{
    queue<node> q;
    q.push(S);
    while(!q.empty())
    {
        node top=q.front();
        q.pop();
        if(top.x==T.x&&top.y==T.y)
            return top.step;
        for(int i=0;i<4;i++)//循环4次，得到4个位置
        {
            int newX=top.x+X[i];
            int newY=top.y+Y[i];
            if(test(newX,newY))  //如果有效
            {
                NODE.x=newX;
                NODE.y=newY;
                NODE.step=top.step+1;
                q.push(NODE);
                inq[newX][newY]=1;  //一系列入队操作
            }
        }
    }
    return -1; //没法到达终点
}

int main()
{
    scanf("%d%d",&n,&m);//地图大小
    for(int i=0;i<n;i++)
    {
        getchar();//读掉每一行的换行符
        for(int j=0;j<m;j++)
        {
            maze[i][j]=getchar();
        }
        maze[i][m+1]='\0';
    }
    scanf("%d%d%d%d",&S.x,&S.y,&T.x,&T.y);
    S.step=0;
    printf("%d",BFS());
    return 0;
}













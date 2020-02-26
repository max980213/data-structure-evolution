//BFS，广度优先。DFS采用栈实现，故可递归
//BFS可参考树的层次遍历，可用队列实现

//题目描述：给定一个n*m的迷宫，*代表不可穿过的墙壁，而"."代表平地，S表示起点，T代表终点当前位置是(x,y)（下标从0开始）
//每次只能上下左右移动，求最短路径

//两种思路：BFS，通过遍历每一层来寻找出口，统计路径长
//         DFS，通过枚举每一种路径，寻找最短的哪个

#include <stdio.h>
#include <string.h> //memset()
#include <stack>  //DFS思想，用递归好像不太合适
//#include <string.h>
//#include <queue> //BFS思想

#define MAX 100

using namespace std;

struct node
{
    int x,y;//坐标
    int step;//步数
}S,T,temp; //起点，终点和临时结点

int n,m; //h行和列
int step=999999;//记录步长，只要得到一个更小的，就更新它
char maze[MAX][MAX];//迷宫信息
int inq[MAX][MAX]={0}; //记录在当前路径上是否访问过，避免成环
int X[4]={0,0,1,-1};
int Y[4]={1,-1,0,0}; //增量数组

//判断位置(x,y)是否有效
bool test(int x,int y)
{
    if(x>=n||x<0||y>=m||y<0)  //越界
        return 0;
    if(maze[x][y]=='*')       //碰壁
        return 0;
    if(inq[x][y]!=0)          //已经路过过
        return 0;
    return 1;
}

void DFS(node a)   //使用DFS一定要注意避免路径成环死循环
{
    inq[a.x][a.y]=1; //先将该点标记为正在访问，便于递归后一步一步返回
    if(a.x==T.x&&a.y==T.y) //如果到了终点
    {
        if(a.step<step)
            step=a.step;   //更新小的步数
        inq[a.x][a.y]=0;   //重新置未访问，寻找新的可行路径
        return;
    }
    for(int i=0;i<4;i++)  //同依次递归同一层的4个方向
    {
        node temp;
        temp.x=a.x+X[i];
        temp.y=a.y+Y[i];
        if(test(temp.x,temp.y))   //如果该点可行
        {
            temp.step=a.step+1;   //步数+1
            DFS(temp);            //递归DFS该方向
        }
    }
    inq[a.x][a.y]=0;              //完成后逐步返回，访问标记置0
    return;
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
    DFS(S);
    printf("%d",step);
    //printf("%d",BFS());
    return 0;
}

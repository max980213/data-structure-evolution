//图的BFS应用
//题目描述：在不超过3层的前提下，一次BFS最多课遍历多少个结点？（有向图）
//思路：为记录层数，需要把节点编号和层号建立成结构体

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn=1010;

struct node
{
    int id; //结点编号
    int layer; //结点层号
};

vector<int> adj[maxn];  //邻接表
bool inq[maxn]={0};   //判断是否入队过

int bfs(int s,int L)  //s为起始结点，L为层数上限
{
    int num=0; //经过的节点数
    queue<node> q;
    node start;
    start.id=s;
    start.layer=0;
    q.push(start);
    inq[start.id]=1;  //标记为已入队
    while(!q.empty())   //非空
    {
        node topnode=q.front();
        q.pop();  //取队首
        int u=topnode.id;  //取结点编号
        for(int i=0;i<adj[u].size();i++)
        {
            node next;
            next.id=adj[u][i];  //从u出发能到达的结点next
            next.layer=topnode.layer+1;
            if(inq[next.id]==0&&next.layer<=L)    //以开始的结点层数为0开始统计
            {
                q.push(next);
                inq[next.id]=1;
                num++;
            }
        }
    }
    return num;
}

int main()
{
    node user;
    int n,L,numFollow,idFollow;
    cin>>n>>L; //结点个数和层数上限
    for(int i=1;i<=n;i++)
    {
        user.id=i;    //用户编号为i
        cin>>numFollow;    //该用户关注的人数
        for(int j=0;j<numFollow;j++)
        {
            cin>>idFollow; //输入关注了谁（有向边）
            adj[idFollow].push_back(user.id);   //边isfollow->i：关注了他，能接受他的消息，所以是他指向我
        }
    }
    int numQuery,s;
    cin>>numQuery; //查询个数
    for(int i=0;i<numQuery;i++)
    {
        fill(inq,inq+maxn,0);  //将inq数组初始化为0
        cin>>s; //起始结点编号
        int num=bfs(s,L);
        cout<<num<<endl;
    }
    return 0;
}



//dj斯特拉和dfs的结合
//思想：先用dj斯特拉找出所有最短路径，然后再用DFS，比较每一条最短路径的第二标尺
//存放前驱节点，可以用一个vector向量

//题目描述：一个无向图，每个路径有两个权值，一个距离一个花费，求在最短距离的同时，花费最少
//思路：先求出所有最短路径，然后比较他们（dj斯特拉+DFS）

//如果仅用dj斯特拉，可设置一个新的二维数组，用来存放花费，相当于另一个特性图，在寻找路径时，同时更新两个特性

//本题采用dj+DFS

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

const int maxn=1010;
const int INF=1000000000;   //表示不可达

int n,m,st,ed,G[maxn][maxn],cost[maxn][maxn];
int d[maxn],minCost=INF;  //d[i]记录到达i点的最短距离，minCost记录最短路径上的最小花费
bool vis[maxn]={0}; //访问位
vector<int> pre[maxn]; //前驱
vector<int> tempPath,path; //临时路径和最优路径

void djstra(int s) //s为起点
{
    fill(d,d+maxn,INF);  //初始化数组d
    d[s]=0;  //起点s到自身的距离为0
    for(int i=0;i<n;i++)  //循环n次（共n个结点）
    {
        int u=-1,MIN=INF;  //u使d[u]最小，MIN存放最小的d[u]
        for(int j=0;j<n;j++)  //找到未访问的结点中d[j]最小的
        {
            if(vis[j]==0&&d[j]<MIN)  //第一次找到的一定是自己
            {
                u=j;
                MIN=d[j];
            }
        }
        if(u==-1)
            return;  //u==-1，说明该次结点到各结点没有路径，返回
        vis[u]=true; //标记为已访问
        for(int v=0;v<n;v++)  //如果v未访问且能到达
        {
            if(vis[v]==0&&G[u][v]!=INF)
            {
                if(d[u]+G[u][v]<d[v])  //以u为中介使距离更短
                {
                    d[v]=d[u]+G[u][v]; //更新
                    pre[v].clear(); //清空所有非最优结点
                    pre[v].push_back(u); //u为v的前驱
                }
                else if(d[u]+G[u][v]==d[v])
                {
                    pre[v].push_back(u); //如果路径均为最短，添加新的最短前驱
                }
            }
        }
    }
}

void DFS(int v)  //统计每一个最短路径，v为当前节点
{
    if(v==st) //因为是从最后一个结点开始，所以起始结点为递归边界
    {
        tempPath.push_back(v);
        int tempCost=0; //记录花费之和
        for(int i=tempPath.size()-1;i>0;i--)  //倒着访问
        {
            int id=tempPath[i]; //当前节点
            int idnext=tempPath[i-1]; //下一个结点
            tempCost+=cost[id][idnext];  //增加边权
        }
        if(tempCost<minCost)
        {
            minCost=tempCost;
            path=tempPath;  //找到更优解，更新数据
        }
        tempPath.pop_back();  //退回到上层
        return;
    }
    tempPath.push_back(v);
    for(int i=0;i<pre[v].size();i++)
        DFS(pre[v][i]);
    tempPath.pop_back();
}

int main()
{
    cin>>n>>m>>st>>ed;
    int u,v;
    fill(G[0],G[0]+maxn*maxn,INF); //初始化
    fill(cost[0],cost[0]+maxn*maxn,INF);
    for(int i=0;i<m;i++)
    {
        cin>>u>>v;
        cin>>G[u][v]>>cost[u][v];
        G[v][u]=G[u][v];
        cost[v][u]=cost[u][v];
    }
    djstra(st);
    DFS(ed);
    for(int i=path.size()-1;i>=0;i--)
        cout<<path[i]<<" ";
    cout<<endl<<d[ed]<<minCost;
    return 0;
}



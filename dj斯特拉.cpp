//dj斯特拉算法的应用（最短路径）
//题目描述：N个结点M个无向边，边权点权已知，求最短路径条数，若存在多条，输出点权和最大的

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;

const int maxn=1010; //最大顶点数
const int INF=1000000000; //定义无穷大

int n,m,st,ed,G[maxn][maxn],weight[maxn]; //节点数，边数，起点终点，邻接矩阵，点权
int d[maxn],w[maxn],num[maxn];  //记录最短距离、最大点权之和、最短路径数
bool vis[maxn]={0};  //访问位


void djstra(int s)  //s为起点
{
    fill(d,d+maxn,INF);  //初始化最短路径数组d
    memset(num,0,sizeof(num));
    memset(w,0,sizeof(w));  //也可在外部初始化时定义
    d[s]=0;
    w[s]=weight[s];
    num[s]=1;  //以s为终点的最短路径数
    for(int i=0;i<n;i++)  //循环n次（n个结点，更新n次）
    {
        int u=-1,MIN=INF;  //u使d[u]最小，MIN存放最小d[u]
        for(int j=0;j<n;j++)   //找到未访问结点中d[]最小的
        {
            if(vis[j]==0&&d[j]<MIN)  //如果不可达，则不会满足条件  //所以如果是第一次执行，读入的是自身
            {                        //找到距该点最短且可达的结点
                u=j;
                MIN=d[j];
            }
        }
        if(u==-1)
            return;  //如果没找到，说明u节点与剩下所有结点都不连通
        vis[u]=1;  //标记访问过
        for(int v=0;v<n;v++)
        {
            if(vis[v]==0&&G[u][v]!=INF)  //如果没访问过且可达
            {
                if(d[u]+G[u][v]<d[v])  //如果更优
                {
                    d[v]=d[u]+G[u][v];  //更新d[v]最短路径长
                    w[v]=w[u]+weight[v];  //更新总权值
                    num[v]=num[u];   //更新路径条数
                }
                else if(d[u]+G[u][v]==d[v])  //如果路径长相等
                {
                    if(w[u]+weight[v]>w[v])  //如果权值更大
                    {
                        w[v]=w[u]+weight[v];//更新
                    }
                    num[v]+=num[u];//更新路径条数，与点权无关，所以放在外面
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m>>st>>ed;
    for(int i=0;i<n;i++)
        cin>>weight[i]; //输入点权
    int u,v;
    fill(G[0],G[0]+maxn*maxn,INF); //初始化邻接矩阵
    for(int i=0;i<m;i++)
    {
        cin>>u>>v;
        cin>>G[u][v];
        G[v][u]=G[u][v]; //读入边权
    }
    djstra(st);
    cout<<num[ed]<<" "<<w[ed]<<endl;//最短路径条数，最短路径的最大点权
    return 99;
}


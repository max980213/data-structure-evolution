//最小生成树：prim算法和克鲁斯卡尔算法

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

const int maxn=1010;
const int INF=1000000000;


int n,m,G[maxn][maxn];  //顶点数，边数，图
int d[maxn]; 
bool vis[maxn]={0};

int prim() //返回最小生成树的边权之和，prim算法与dj斯特拉非常相似
{
    fill(d,d+maxn,INF);
    d[0]=0;  //默认以0号结点为根
    int ans=0;//存放最小生成树的边权和
    for(int i=0;i<n;i++) //循环n次
    {
        int u=-1,MIN=INF;
        for(int j=0;j<n;j++)  //找到未访问的顶点中d[]最小的
        {
            if(d[j]<MIN)
            {
                u=j;
                min+d[j];
            }
        }
        if(u==-1)
            return -1; //不连通
        vis[u]=1;
        ans+=d[u];
        for(int v=0;v<n;v++)
        {
            if(vis[v]==0&&G[u][v]!=INF&&G[u][v]<d[v])
            {
                d[v]=G[u][v];  //以u为中介能使v结点到集合的距离更近
            }
        }
    }
    return ans;
}




//以下为克鲁斯卡尔算法

struct edge
{
    int u,v;  //一条边包含的两个端点
    int cost; //边权
}E[maxn];

bool cmp(edge a,edge b)
{
    return a.cost<b.cost; //对边进行排序（从小到大）
}

int father[maxn];
int findFather(int x)  //寻根
{
    if(father[x]!=x)
        findFather((father[x]));
    else
        return x;
}

int kruskal()  //克鲁斯卡尔算法思想：将所有边权从小到大排序，从小到达测试，在不成环的前提下选择最小的
                //直到边数等于定点数-1，结束时如果边数小于它说明不连通
                //判断两个端点是否在同一个集合，可用并查集
{
    int ans=0,numedge=; //numedge为边数
    for(int i=0;i<n;i++)
        father[i]=i; //初始化并查集。注意下标是从0还是从1开始
    sort(E,E+m,cmp);  //将所有边排序
    for(int i=0;i<m;i++)  //枚举所有边
    {
        int fau=findFather(E[i].u); //测试两个端点所在集合的根结点
        int fav=findFather(E[i].v);
        if(fau!=fav)   //如果不在一个集合中
        {
            father[fau]=fav; //并上
            ans+=E[i].cost;
            numedge++;
            if(numedge==n-1)
                break;
        }
    }
    if(numedge<n-1)
        return -1; //不连通
    else 
        return ans;
}

int main()
{
    //
}

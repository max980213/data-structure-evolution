//图的DFS应用
//题目描述：将一个无向图分为若干极大连通子图，统计子图个数，并找出权值最大的结点
//DFS一次，访问的是单个连通块，故可用来分块
//可用并查集实现

#include <iostream>
#include <stdio.h>
#include <map>
#include <string>

using namespace std;

const int maxn=2010;
//const int INF=1000000000000;//无穷大，表示不可达

map<int,string> intToString;  //编号->姓名
map<string,int> stringToInt;
map<string,int> Gang;  //头目->人数

int G[maxn][maxn]={0},weight[maxn]={0};  //邻接矩阵G，点权weight
int n,k,numPerson=0; //边数n，下限k，总人数numPerson
bool vis[maxn]={0}; //标记是否被访问

//DFS函数访问单个连通块，nowVisit为当前访问编号
//head为头目，numMember为成员编号，totalValue为连通块的总边权
void DFS(int nowVisit,int &head,int &numMember,int &totalValue)
{
    numMember++; //成员人数+1
    vis[nowVisit]=1;   //标记当前结点为已访问
    if(weight[nowVisit]>weight[head])
    {
        head=nowVisit;  //如果当前访问结点点权大于头目的点权，更新他
    }
    for(int i=0;i<numPerson;i++)  //枚举所有人
    {
        if(G[nowVisit][i]>0)  //如果可达
        {
            totalValue+=G[nowVisit][i];
            G[nowVisit][i]=G[i][nowVisit]=0; //删除该边，防止回头
            if(vis[i]==0) //未被访问，递归访问
                DFS(i,head,numMember,totalValue);
        }
    }
}

void DFSTrave()
{
    for(int i=0;i<numPerson;i++) //枚举所有人
    {
        if(vis[i]==0)  //如果没访问过
        {
            int head=i,numMember=0,totalValue=0; //头目，成员数，总边权
            DFS(i,head,numMember,totalValue); //遍历i所在的连通块
            if(numMember>2&&totalValue>k) //满足帮派条件
            {
                Gang[intToString[head]]=numMember; //记录该帮派人数
            }
        }
    }
}

int change(string str) //返回姓名str的编号
{
    if(stringToInt.find(str)!=stringToInt.end())  //如果出现过
    {
        return stringToInt[str];  //返回编号
    }
    else
    {
        stringToInt[str]=numPerson;  //str编号为numPerson
        intToString[numPerson]=str;  //互相存一下
        return numPerson++; //总人数加1
    }
}

int main()
{
    int w;
    string str1,str2;
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
        cin>>str1>>str2>>w; //按要求读入名字和点权  string只能用cin读入
        int id1=change(str1);
        int id2=change(str2); //将字符串转化为编号
        weight[id1]+=w;
        weight[id2]+=w;
        G[id1][id2]+=w;
        G[id2][id1]+=w;  //点权和边权加w
    }
    DFSTrave(); //遍历图，得到所有块和gang的信息
    cout<<Gang.size()<<endl; //帮派个数
    map<string,int>::iterator it;
    for(it=Gang.begin();it!=Gang.end();it++)
    {
        cout<<it->first<<" "<<it->second<<endl;   //输出帮派信息
    }
    return 0;
}





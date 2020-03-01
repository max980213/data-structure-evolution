//并查集的应用
//并查集利用数组 int father[MAX]实现，其中father[i]的含义是元素i的父结点
//利用该特性，可以对元素进行分组
//路劲压缩：将一条链上的所有节点，均指向总父节点

//题目描述：A和B是好朋友等价于B和A是好朋友，A和B是好朋友，B和C是好朋友=>A和C也是好朋友
//现输入总个数，好朋友组数和每一对好朋友，将他们进行分组，组内均是好朋友，组间没有好朋友
//求可分的组数

#include <iostream>
#include <stdio.h>

using namespace std;

const int MAX=110;
int father[MAX]; //用来存储并查集
bool isroot[MAX]; //记录是否为根结点，是为1，最后方便统计根的个数，即组数

int findfather(int x) //找到x所在集合的根
{
    int a=x;
    while(father[x]!=x)
    {
        x=father[x];
    }  //此时x是根

    //压缩路径，可剩，可放在后来的插入中
    while(a!=father[a])
    {
        int z=a;
        a=father[a];
        father[z]=x;
    }
    return x;
}

void Union(int a,int b) //合并
{
    int faA=findfather(a);
    int faB=findfather(b);
    if(faA!=faB)
    {
        father[faA]=faB;
        isroot[faB]=1;
        isroot[faA]=0;   //合题目要求
    }

}

void init(int n)  //初始化
{
    for(int i=0;i<=n;i++)
    {
        father[i]=i;
        isroot[i]=1;
    }
}


int main()   //本写法，将0也算在内，但应题目要求，应当从1开始
{
    int n,m,a,b;
    cin>>n>>m;  //总个数和组数
    init(n);
    for(int i=0;i<m;i++)
    {
        cin>>a>>b;
        Union(a,b);
    }
    /*  另一种更新根的写法
    for(int i=0;i<=n;i++)
    {
        isroot[findfather(i)]=1;  //更新根
    }
    */
    int ans=0;
    for(int i=0;i<=n;i++)
    {
        if(isroot[i]==1)
        {
            ans++;
        }
    }
    cout<<ans;
    return 0;
}



//题目描述：利用DFS思想解决背包问题1：n件物品，重量为w[i]，价值为c[i]，背包最大承受重量为V
//在不超重的前提下，使价值最大
//对于n件物品均有选和不选，可看作岔路口，当总和超过v或枚举到了最后一个物品，便到了死胡同
//利用递归，遍历每个岔路，记录每一种路径的值，选择出最大

#include <stdio.h>
#include <iostream>

#define MAX 30

using namespace std;

int n,V,maxValue=0; //物品数，最大重量，最大价值
int w[MAX],c[MAX];

void DFSr(int index,int sumW,int sumC);

void DFS(int index,int sumW,int sumC) //当前处理物品下标，当前总重量和总价值
{
    if(index==n) //到死胡同了
    {
        if(sumW<=V&&sumC>maxValue) //更新最大价值
        {
            maxValue=sumC;
        }
        return;
    }
    //岔路口
    DFS(index+1,sumW,sumC);//不选第index件物品
    DFS(index+1,sumW+w[index],sumC+c[index]);
}

int main()
{
    scanf("%d%d",&n,&V);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&w[i]);
    }
    for(int i=0;i<n;i++)
    {
        scanf("%d",&c[i]);
    }
    DFSr(0,0,0);
    cout<<maxValue;
    return 0;
}

//对于每件物品都有两种选择，因此复杂度为O(2^n)
//可进行优化：当超重的时候，就不要再比较了

void DFSr(int index,int sumW,int sumC)
{
    if(index==n)
    {
        return;//到头了
    }

    DFS(index+1,sumW,sumC);//不选第index个物品
    if(sumW+w[index]<=V)//如果装得下
    {
        if(sumC+c[index]>maxValue)   //更新最大值
        {
            maxValue=sumC+c[index];
        }
        DFSr(index+1,sumW+w[index],sumC+c[index]);
    }
}


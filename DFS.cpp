//题目描述：利用DFS思想，给定N个整数（可负），从中选择K个，使这K个数的和为给定整数X
//如果有多种方案，选择他们中元素平方和最大的一个

//一类常见DFS问题的解决方法：给定一个序列，枚举所有子序列，从中选出最优的一个
//设置一个数组，用来保存最优方案

#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

#define MAX 30

int n,k,x,maxSumSqu=-1,A[MAX];

vector<int> temp,ans; //temp存放临时方案，ans存放最终答案

//当前处理第index号数，已经选择nowK个数
//当前已选整数和为sum，平方和为sumSqu

void DFS(int index,int nowK,int sum,int sumSqu)
{
    if(nowK==k&&sum==x)  //找到k个数的和为x
    {
        if(sumSqu>maxSumSqu) //比当前方案更优
        {
            maxSumSqu=sumSqu;
            ans=temp;
        }
        return;
    }
    //已经处理完n个数，或者超过k个数，或者和超过x，返回
    if(index==n||nowK>k||sum>x)
        return;
    //选index号数
    temp.push_back(A[index]);
    DFS(index+1,nowK+1,sum+A[index],sumSqu+A[index]*A[index]);  //选index号数
    temp.pop_back();
    DFS(index+1,nowK,sum,sumSqu);  //不选index号，所以得pop
}

int main()
{
    scanf("%d%d%d",&n,&k,&x);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&A[i]); //录入数组
    }
    DFS(0,0,0,0);

    for(vector<int>::iterator it=ans.begin();it!=ans.end();it++)
        cout<<*it<<" ";

    return 0;
}

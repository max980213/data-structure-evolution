//题目描述：给定一棵树和每个节点的权值，求所有从根结点到叶子节点的路径，使每条路径上的结点权值之和
//          等于给定常数X，如果有多条这样的路径，则按路径非递增顺序输出（路径大小指权值按顺序的大小）

//思路：1.考虑在读入时就对子节点进行排序，这样就会优先遍历到权值大的子节点
//      2.令int型数组用来存放递归过程中路过的结点，当遍历到叶子节点满足条件就直接输出，不满足就return
//        因为在上一步已经提前排序，故输出时一定也是按顺序输出
//很明显，应该使用DFS思想
//注意，一定从根节点到叶子节点。


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#define MAX 10010

using namespace std;

//变量定义部分

struct node
{
    int weight;
    vector<int> child;  //必须把using namespace std放在这之前
}node[MAX];

int path[MAX];



//函数定义

bool cmp(int a,int b)
{
    return node[a].weight>node[b].weight; //实现对索引指向结点的权值进行比较
}

void DFSsearch(int index,int nodeNum,int sum,int X) //当前访问的结点下标，当前path上的结点个数（层数），当前权值总和
{
    path[nodeNum++]=index;
    sum+=node[index].weight;
    if(sum>X)
        return;
    else if(sum==X)
    {
        if(!node[index].child.empty())
            return;
        else
        {
            for(int i=0;i<nodeNum;i++)
                cout<<node[path[i]].weight<<" ";
            cout<<endl;  //可以通过计数器判断与nodeNum的关系，最后一行不输出换行
        }
    }
    else
    {
        for(vector<int>::iterator it=node[index].child.begin();it!=node[index].child.end();it++)
            DFSsearch(*it,nodeNum,sum,X);
    }

}

int main()
{
    int N,M,X; //结点总数，非叶子结点数想要的权值总和
    cin>>N>>M>>X;
    for(int i=0;i<N;i++)
        cin>>node[i].weight;
        cin>>id>>childnum;
        for(int j=0;j<childnum;j++)
        {
            cin>>child;
            node[id].child.push_back(child);
        }
        sort(node[id].child.begin(),node[id].child.end(),cmp);  //在输入时就对其排序
    }
    cout<<endl;
    DFSsearch(00,0,0,X);
    return 0;
}

    for(int i=0;i<M;i++)
    {
        int id,childnum,child;
        cin>>id>>childnum;
        for(int j=0;j<childnum;j++)
        {
            cin>>child;
            node[id].child.push_back(child);
        }
        sort(node[id].child.begin(),node[id].child.end(),cmp);  //在输入时就对其排序
    }
    cout<<endl;
    DFSsearch(00,0,0,X);
    return 0;
}




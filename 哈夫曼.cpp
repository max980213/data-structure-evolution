//哈夫曼树和哈夫曼编码
//思想：反复选择两个最小的元素合并
//一般题目不需要真的构建出树，只需要得到带权路径长度
//每次从队列中选出两个最小的，可以利用堆来实现
//也可以用内置的优先级队列容器直接实现

#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

priority_queue<long long int,vector<long long int>,greater<long long int> > q;
//这是自定优先级的写法，第二个参数填写的是用来承载底层数据结构堆的容器，与第一个参数相同
//第3个参数是堆第一个参数的比较类，less<int>表示数字大的优先级大，greater<int>表示数字小的优先级大
//见p223
//不能通过front()等访问了
//只能用top()访问顶

//可以用自定义函数实现，但明显这种方式更合适更方便









int main()
{
    int n;
    long long int temp,x,y,ans=0;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>temp;
        q.push(temp);  //入队
    }
    while(q.size()>1)  //只要队列里至少有两个元素
    {
        x=q.top();
        q.pop();
        y=q.top();
        q.pop();
        q.push(x+y);
        ans+=(x+y);   //不断累加，得到最短带权路径
    }
    cout<<ans;
    return 0;

}

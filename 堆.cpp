//堆，建堆，调整堆，堆排序
//堆的定义：每个节点的值都不大于（或不小于）其左右孩子结点的值，且其左右孩子也同样是堆
//堆的结构是一个完全二叉树

#include <iostream>
#include <stdio.h>

using namespace std;

const int maxn=100;
int heap[maxn];  //堆可利用数组实现

void downsift(int heap[],int low,int high)//调整，在之前的代码进行少量修改
{
    //调整下标为[low,high]间的数据
    int i=low,j=2*i; //i为欲调整结点，j为其左孩子
    while(j<=high) //若孩子结点存在
    {
        if(j+1<=high&&heap[j+1]>heap[j])
        {
            j++;  //如果右孩子存在且比左孩子大，就换右孩子
        }
        if(heap[j]>heap[i])
        {
            swap(heap[i],heap[j]);  //利用swap函数直接交换
            i=j;
            j=2*i;
        }
        else
            break; //如果该层满足，下层也一定满足
    }
}


//那么建堆就很容易了，由完全二叉树的性质，第一个非叶节点的下标为n/2，从右至左，从下至上依次调整
void createheap(int heap[],int n)
{
    for(int i=n/2;i>=1;i--)  //heap[0]就不用了，让下标从1开始，方便计算
    {
        downsift(heap,i,n);
    }
}

//如果插入一个数，可以把这个数插在数组尾
//调整方法有两种，一种是从第一个叶节点开始循环下调，另一种是从插入节点开始上调

void upsift(int heap[],int low,int high)
{
    int i=high,j=i/2; //i是欲调整节点，j是其父节点
    while(j>=low)   //如果父结点存在
    {
        if(heap[i]>heap[j])  //如果需要调整
        {
            swap(heap[i],heap[j]);
            i=j;
            j=i/2;
        }
        else
            break;
    }
}

//上调进行一次就够了，这是插入操作便很简单

void insert(int heap[],int n,int x)  //n是节点总数，x是欲插入节点
{
    heap[++n]=x;  //默认下标从1开始，heap[0]不要了
    upsift(heap,1,n);
}

//在这基础上，堆排序便非常容易了，每次都能筛出一个最大的

void heapsort(int heap[],int n)  //这里可看出，堆排序复杂度为O(nlogn)
{
    createheap(heap,n); //建堆
    for(int i=n;i>1;i--)  //倒着枚举，直到只剩一个元素
    {
        swap(heap[1],heap[i]);  //将筛出来最大的那个放最后面
        downsift(heap,1,i-1);
    }

}

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>heap[i];
    }
    heapsort(heap,n);
    for(int i=1;i<=n;i++)
    {
        cout<<heap[i]<<" ";
    }
    return 0;
}


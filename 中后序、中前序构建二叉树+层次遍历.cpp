//得到中序和先序序列，构建一个二叉树
//利用递归思想，不断确定子树的根

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <queue>

typedef struct node
{
    char data;
    node *lchild;
    node *rchild;
}node;

using namespace std;

node* create(char pre[],char mid[],int preL,int preR,int midL,int midR)   //均以下标为操作单位，左闭右开
{
    if(preL>=preR)   //因为是左闭右开，故条件为>=。其实==应该也可，因为num不可能为负
                     //条件为midL==midR也可
        return NULL;
    node *root=(node*)malloc(sizeof(node));
    if(root!=NULL)
    {
        root->data=pre[preL];
        int k;
        for(k=midL;k<midR;k++)  //找到根结点在中序序列中的位置
        {
            if(pre[preL]==mid[k])
                break;
        }
        int num=k-midL;   //+1;   //统计左子树的元素个数，mid[k]不算在内，故不用加1
        root->lchild=create(pre,mid,preL+1,preL+num+1,midL,k);  //注意左闭右开
        root->rchild=create(pre,mid,preL+num+1,preR,k+1,midR);
    }
    return root; //返回树根结点
}

//如果是中序和后序，稍加修改即可
node* create2(char pre[],char mid[],int preL,int preR,int midL,int midR)   //均以下标为操作单位，左闭右开
{
    if(preL>=preR)   //因为是左闭右开，故条件为>=。其实==应该也可，因为num不可能为负,条件为midL==midR也可
        return NULL;
    node *root=(node*)malloc(sizeof(node));
    if(root!=NULL)
    {
        root->data=pre[preR-1];//左闭右开，下标最大为n-1
        int k;
        for(k=midL;k<midR;k++)  //找到根结点在中序序列中的位置
        {
            if(pre[preR-1]==mid[k])  //左闭右开，下标最大为n-1
                break;
        }
        int num=k-midL;   //+1;   //统计左子树的元素个数，mid[k]不算在内，故不用加1
        root->lchild=create2(pre,mid,preL,preL+num,midL,k);  //注意左闭右开
        root->rchild=create2(pre,mid,preL+num,preR-1,k+1,midR);
    }
    return root; //返回树根结点
}

void previsit(node *root)  //先序遍历
{
    if(root==NULL)
        return;
    cout<<root->data;
    previsit(root->lchild);
    previsit(root->rchild);
}

void layervisit(node *root) //层次遍历
{
    queue<node*> q;
    q.push(root);
    node *temp;
    while(!q.empty())
    {
        temp=q.front();
        q.pop();
        if(temp->lchild!=NULL)
            q.push(temp->lchild);
        if(temp->rchild!=NULL)
            q.push(temp->rchild);
        cout<<temp->data;
    }
}

int main()
{
    int n;
    cin>>n;
    char pre[n],mid[n];
    for(int i=0;i<n;i++)
        cin>>pre[i];
    for(int i=0;i<n;i++)
        cin>>mid[i];
    node *root=create2(pre,mid,0,n,0,n);
    cout<<endl;
    previsit(root);
    cout<<endl;
    layervisit(root);
    return 0;

}




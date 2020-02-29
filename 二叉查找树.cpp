//题目描述：给出N个正整数作为一颗二叉排序树的结点插入顺序，问该串序列是否是该二叉排序树或其镜像树
//          的先序序列？（镜像树指交换左右子树）
//如果是，输出YES并输出该树后序序列，否输出NO

//思路：对于镜像树的遍历，只需将根左右换为根右左即可




#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

using namespace std;

typedef struct node
{
    int data;
    node *lchild;
    node *rchild;
}node;

void insert(node* &root,int data)  //用引用更合适
{
    if(root==NULL) //到达空位置，该位置即为二叉查找树的插入位置
    {
        root=(node*)malloc(sizeof(node));
        root->data=data;
        root->lchild=root->rchild=NULL;
        return;
    }
    if(data<root->data)
    {
        insert(root->lchild,data);
    }
    else
        insert(root->rchild,data);
}

void preorder(node *root,vector<int> &vi) //先序遍历，结果存在vi
{
    if(root==NULL)
        return;
    vi.push_back(root->data);
    preorder(root->lchild,vi);
    preorder(root->rchild,vi);
}

void preordermirror(node *root,vector<int> &vi)
{
    if(root==NULL)
        return;
    vi.push_back(root->data);
    preordermirror(root->rchild,vi);
    preordermirror(root->lchild,vi);
}

void postorder(node *root) //后序
{
    if(root==NULL)
        return;
    postorder(root->lchild);
    postorder(root->rchild);
    cout<<root->data<<" ";
}

void postordermirror(node *root) //镜像后序
{
    if(root==NULL)
        return;
    postordermirror(root->rchild);
    postordermirror(root->lchild);
    cout<<root->data<<" ";
}

vector<int> ori,pre,preM;


int main()
{
    int N;
    cin>>N;
    node *root=NULL;
    for(int i=0;i<N;i++)
    {
        int temp;
        cin>>temp;
        ori.push_back(temp);
        insert(root,temp);
    }
    preorder(root,pre);
    preordermirror(root,preM);
    if(pre==ori)
    {
        cout<<"YES"<<endl;
        postorder(root);
    }
    else if(preM==ori)
    {
        cout<<"YES"<<endl;
        postordermirror(root);
    }
    else
        cout<<"NO";
    return 0;
}

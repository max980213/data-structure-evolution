//AVL树的建立、插入、删除、调整结点

#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct node
{
    int data;
    int height; //以当前节点为根的子树的高度
    node *lchild,*rchild;
}node;

node* newnode(int data)  //生成一个新结点
{
    node *Node=(node*)malloc(sizeof(node));
    Node->data=data;
    Node->height=1 ; //结点高度初始为1
    Node->lchild=Node->rchild=NULL;  //初始状态下没有左右孩子
    return Node;
}

int getheight(node* root)  //获取高度
{
    if(root==NULL)
        return 0;  //空树高度为0
    return root->height;;
}

int getbalancefator(node* root)//获取平衡因子
{
    return getheight(root->lchild)-getheight(root->rchild);
}

void updateheight(node* root) //更新高度
{
    root->height=max(getheight(root->lchild),getheight(root->rchild))+1;  //左右子树的高度最大值加自身（1）
}

void search(node *root,int x)  //查找与查找树相同
{
    if(root==NULL)
    {
        cout<<"查找失败";
        return;
    }
    if(x==root->data)
    {
        cout<<"查找成功";  //可换成其他访问语句
    }
    else if(x<root->data)
        search(root->lchild,x);
    else
        search(root->rchild,x);
}


//AVL树插入时也许会打破平衡，这时需要左旋右旋
void L(node *&root)  //左旋
{
    node *temp=root->rchild;
    root->rchild=temp->lchild;
    temp->lchild=root;
    updateheight(root);
    updateheight(temp);
    root=temp;
}

void R(node *&root)    //右旋，只需要左右互换即可
{
    node *temp=root->lchild;
    root->lchild=temp->rchild;
    temp->rchild=root;
    updateheight(root);
    updateheight(temp);
    root=temp;
}

void insert(node *&root,int x)  //插入操作，需要加上平衡操作
{
    if(root==NULL)  //到达空结点，进行插入操作
    {
        root=newnode(x);
        return;
    }
    if(x<root->data)
    {
        insert(root->lchild,x);
        updateheight(root);//更新树高，递归过程中会逐层更新树高
        if(getbalancefator(root)==2)  //因为是往左子树插入，所以以该结点为根的子树只有可能为2
        {
            if(getbalancefator(root->lchild)==1)  //LL型
            {
                R(root);
            }
            else if(getbalancefator(root->lchild)==-1)  //LR型
            {
                L(root->lchild);
                R(root);
            }
        }
    }
    else
    {
        insert(root->rchild,x);
        updateheight(root);
        if(getbalancefator(root)==-2)
        {
            if(getbalancefator(root->rchild)==-1) //RR型
            {
                L(root);
            }
            else if(getbalancefator(root->rchild)==1)  //RL型
            {
                R(root->rchild);
                L(root);
            }
        }
    }
}

//有了插入操作，建树就简单了
node* create(int n)
{
    node *root=NULL;
    int x;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        insert(root,x);
    }
    return root;
}


void midvisit(node *root)
{
    if(root==NULL)
        return;
    midvisit(root->lchild);
    cout<<root->data<<" ";
    midvisit(root->rchild);
}



int main ()
{
    int n;
    cin>>n;
    node *root=create(n);
    midvisit(root);
    return 0;
}

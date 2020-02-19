#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <queue>
#include <stack>

using namespace std;

//栈的应用：表达式的计算
//栈利用c++的容器实现，会很容易

//输入的表达式为中缀，利用栈转化为后缀进行计算

struct node
{
    double num;  //操作数
    char op;     //操作符
    bool flag;   //true表示操作数，false表示操作符
};

string str;
stack<node> s;  //操作符栈
queue<node> q;  //后缀表达式序列
map<char,int> op;  //记录优先级

void change()  //将中缀表达式转化为后缀表达式
{
    double num;
    node temp;
    for(int i=0;i<str.length();)
    {
        if(str[i]>='0'&&str[i]<='9')   //如果是数字
        {
            temp.flag=1;  //标记是数字
            temp.num=str[i++]-'0';   //记录该操作数的第一个数位
            while(i<str.length()&&str[i]>='0'&&str[i]<='9')
            {
                temp.num=temp.num*10+(str[i]-'0'); //更新这个操作数
                i++;
            }
            q.push(temp);//将该数放入后缀表达式队列
        }
        else
        {
            temp.flag=false; //标记是操作符
            //只要操作符栈的栈顶元素比该操作符优先级高
            //就把操作符栈栈顶元素弹出到后缀表达式队列
            while(!s.empty()&&op[str[i]]<=op[s.top().op])
            {
                q.push(s.top());
                s.pop();
            }
            temp.op=str[i];
            s.push(temp);//将该操作符入栈
            i++;
        }
    }
    //如果操作符栈中还有操作符，就把它弹出到后缀表达式队列
    while(!s.empty())
    {
        q.push(s.top());
        s.pop();
    }
}

double cal() //计算后缀表达式
{
    double temp1,temp2;
    node cur,temp;
    while(!q.empty())
    {
        cur=q.front();//记录队首元素
        q.pop();
        if(cur.flag==1)
            s.push(cur); //如果是操作数，直接入栈
        else
        {
            temp2=s.top().num;
            s.pop();
            temp1=s.top().num;
            s.pop();  //记录两个操作数
            temp.flag=1; //临时记录操作数
            if(cur.op=='+')
                temp.num=temp1+temp2;
            else if(cur.op=='-')
                temp.num=temp1-temp2;
            else if(cur.op=='*')
                temp.num=temp1*temp2;
            else
                temp.num=temp1/temp2;
            s.push(temp);//算完后入栈
        }
    }
    return s.top().num; //都算完了，栈顶元素就是后缀表达式的值
}

int main()
{
    op['+']=op['-']=1;
    op['*']=op['/']=2;  //定义优先级
    while(getline(cin,str),str!="0")
    {
        //cin>>str;
        for(string::iterator it=str.begin();it!=str.end();it++)
        {
            if(*it==' ')
                str.erase(it);//删掉多余空格
        }
        while(!s.empty())
            s.pop();//初始化栈
        change();
        cout<<cal()<<endl;
    }
    return 0;
}

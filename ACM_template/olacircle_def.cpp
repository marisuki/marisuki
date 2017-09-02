
//判欧拉回路

#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#define PI acos(-1.0)
#define mem(a,b) memset(a,b,sizeof(a))
#define sca(a) scanf("%d",&a)
#define pri(a) printf("%d\n",a)
#define M 202
#define INF 100000001
using namespace std;
typedef long long ll;
struct stack
{
    int top,node[M];
}s;
int e[M][M],n;
void dfs(int x)
{
    int i;
    s.node[++s.top]=x;
    //cout<<s.top<<' '<<s.node[s.top]+1<<endl;
    for(i=0;i<n;i++)
    {
        if(e[i][x]>0)
        {
            e[i][x]=e[x][i]=0;  //删除这条边
            dfs(i);
            break;
        }
    }
}
void fleury(int x)
{
    int i,flag;
    s.top=0; s.node[s.top]=x;
    while(s.top>=0)
    {
        flag=0;
        for(i=0;i<n;i++)
        {
            if(e[s.node[s.top]][i]>0)
            {
                flag=1;
                break;
            }
        }
        if(!flag) printf("%d ",s.node[s.top--]+1);
        else dfs(s.node[s.top--]);
    }
    puts("");
}
int main( )
{
    int i,j,u,v,m,degree,num=0,start=0;
    scanf("%d%d",&n,&m);
    mem(e,0);
    for(i=0;i<m;i++)
    {
        scanf("%d%d",&u,&v);
        e[u-1][v-1]=e[v-1][u-1]=1;
    }
    for(i=0;i<n;i++)
    {
        degree=0;
        for(j=0;j<n;j++)
            degree+=e[i][j];
        if(degree&1)
        {
            start=i;
            num++;
        }
    }
    if(num==0||num==2) fleury(start);
    else printf("No Euler path\n");
    return 0;
}

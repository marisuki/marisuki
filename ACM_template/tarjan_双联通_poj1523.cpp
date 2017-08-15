// Tarjan: 1. tarjan(int u,int father) //双联通分量
//(SPF), poj-1523

#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
#include<vector>
#include<math.h>
#include<string>
#include<stack>
#include<map>
#include<cstdio>
#include<set>
using namespace std;
#define ll long long
#define MOD 1e9+7
#define INFLL 0x7fffff
#define INFI 0x7f7f7f7f
#define INF 0x3f3f3f3f
#define inf 0x3f
#define esp 1.0e-10
#define M(a,k) memset(a,k,sizeof a)
#define Endl endl
#ifndef ONLINE_JUDGE
template <class T> struct greater {
  bool operator() (const T& x, const T& y) const {return x>y;}
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};
#endif

struct pix
{
    int x,y,t;
    pix(int x,int y,int t): x(x),y(y),t(t){}
    pix(){}
    bool operator < (pix p) const
    {
        return t<p.t;
    }
};
typedef pair<int,int> pii;
typedef pair<bool,bool> pbb;
struct poi
{
    int w,u,v,next,id;
    poi(int u,int v,int w,int next,int id):w(w),u(u),v(v),next(next),id(id){}
    poi(){}
    bool operator <(poi p) const
    {
        return w<p.w;
    }
};


//template begin
int numOfCom=0;
vector<int> ans[2050];
int dfn[2050],low[2050],inst[2050];
int index=0;
stack<int> st;
vector<int> e[2005];
int belong[1005];
int flowback[1005];
int cut[1005];
void init()
{
	memset(dfn,0,sizeof dfn);
    memset(low,0,sizeof low);
    memset(inst,0,sizeof inst);
    memset(cut,0,sizeof cut);
    memset(belong,0,sizeof belong);
    memset(flowback,0,sizeof flowback);
    numOfCom=0;
	index=0;
}
void tarjan(int u,int father)
{
    dfn[u]=low[u]=++index;
    st.push(u);
    inst[u]=1;
    int child=0;
    for (int k=0;k<e[u].size();k++)
    {
        int now=e[u][k];
        if(now==father) continue;
        if(!dfn[now])
        {
            child++;
            tarjan(now,u);
            low[u]=min(low[u],low[now]);
            if(low[now]>=dfn[u])
            {
                numOfCom+=1;
                cut[u]+=1;
                int tem=-1;
                do
                {
                    tem=st.top();
                    st.pop();
                    belong[tem]=numOfCom;
                    ans[numOfCom].push_back(tem);
                    flowback[tem]=numOfCom;
                }
                while(now!=tem&&!st.empty());
                ans[numOfCom].push_back(u);
                flowback[u]=numOfCom;
            }
        }
        else if(inst[now])
        {
            low[u]=min(low[u],dfn[now]);
        }
    }
    if(u==father&&child==1)
    {
        cut[u]=0;
    }
    return;
}
//template end


int n;
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
    int u,v;
    int perx=0;
    int cntt=1;
    while(cin>>u)
    {
        if(!u)
            break;
        cin>>v;
        e[u].push_back(v);
        e[v].push_back(u);
        n=max(n,max(u,v));
        while(cin>>u)
        {
            if(!u) break;
            cin>>v;
            e[u].push_back(v);
            e[v].push_back(u);
            n=max(n,max(u,v));
        }
        while(!st.empty()) st.pop();
            
            for(int i=1;i<=n;i++)
            {
                if(!dfn[i])
                {
                    tarjan(i,i);
                }
            }
            int flag=0;
            printf("Network #%d\n",cntt++);
            for(int i=1;i<=n;i++)
            {
                if(cut[i]!=0)
                {
                    flag=1;
                    if(i!=1) 
                        printf("  SPF node %d leaves %d subnets\n",i,cut[i]+1);
                    else printf("  SPF node %d leaves %d subnets\n",i,cut[i]);
                }
            }
            if(flag==0)
            {
                cout<<"  No SPF nodes"<<endl<<endl;
            }
            else
            {
                cout<<endl;
            }
            for(int i=0;i<=2005;i++)
            {
                e[i].clear();
                ans[i].clear();
			}
            
            n=0;
    }

#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
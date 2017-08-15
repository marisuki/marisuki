// tarjan(int u)
//强连通分量
//poj-2553, divide color
//  1.树-> 强连通： add edge:(leaf+1)/2   
//  2. color+统计节点出度

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
struct EDGE
{
    int v,w,next;
    EDGE(int v,int w,int next):v(v),w(w),next(next){}
    EDGE(){}
};

//template begin
int dfn[15005],low[15005],inst[15005];
stack<int> st;
vector<int> e[50010];
int numOfCom=0;
vector<int> ans[50010];
int index=0;
void tarjan(int u)
{
    dfn[u]=low[u]=++index;
    st.push(u);
    inst[u]=1;
    for (int k=0;k<e[u].size();k++)
    {
        int v=e[u][k];
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(inst[v])
        {
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u])
    {
        numOfCom++;
        int xx=0;
        do
        {
            xx=st.top();
            ans[numOfCom].push_back(xx);
            st.pop();
            inst[xx]=0;
        }while(dfn[xx]!=low[xx]&&!st.empty());
    }
    return;
}
//template end


int color[5005];
int indeg[15005];
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
    int n,p;
    int num;
    while(cin>>n)
    {
        if(!n)
            break;
        cin>>p;
        for(int i=0;i<=n;i++)
            ans[i].clear(),e[i].clear();
        while(!st.empty()) st.pop();
        memset(dfn,0,sizeof dfn);
        memset(low,0,sizeof low);
        dfn[0]=-1;
        low[0]=-2;
        index=0;
        num=0;
        numOfCom=0;
        for(int i=0;i<p;i++)
        {
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
        }
        memset(indeg,0,sizeof indeg);
        for(int i=1;i<=n;i++)
        {
            if(!dfn[i])
            {
                tarjan(i);
            }
        }
        vector<int> anssx;
        for(int i=1;i<=numOfCom;i++)
        {
            for(int k=0;k<ans[i].size();k++)
            {
                int j=ans[i][k];
                color[j]=i;
            }
        }
        for(int i=1;i<=n;i++)
        {
            for(int k=0;k<e[i].size();k++)
            {
                int j=e[i][k];
                if(color[i]==color[j])
                {
                    continue;
                }
                else
                {
                    indeg[color[i]]+=1;
                }
            }
        }
        anssx.clear();
        for(int i=1;i<=numOfCom;i++)
        {
            if(indeg[i]==0)
            {
                for(int k=0;k<ans[i].size();k++)
                {
                    int j=ans[i][k];
                    anssx.push_back(j);
                }
            }
        }
        sort(anssx.begin(),anssx.end());
        int cnnnn=0;
        for(int k=0;k<anssx.size();k++)
        {
            int i=anssx[k];
            cnnnn+=1;
            if(cnnnn==1)
                cout<<i;
            else cout<<' '<<i;
        }
        cout<<endl;
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
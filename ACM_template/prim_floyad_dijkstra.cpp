//prim 最小生成树

int prim(int n)
{
   int ans=0;
   memset(vis,0,sizeof vis);
   vis[0]=1;
   for(int i=1;i<n;i++) lowc[i]=cost[0][i];
   for(int i=1;i<n;i++)
   {
	   int minc=INF;
	   int p=-1;
	   for(int j=0;j<n;j++)
	   {
		   if(!vis[j]&&minc>lowc[j])
		   {
			   minc=lowc[j];
			   p=j;
		   }
	   }
	   if(minc==INF)
	   {
		   return -1;
	   }
	   ans+=minc;
	   vis[p]=1;
	   for(int j=0;j<n;j++)
	   {
		   if(!vis[j]&&lowc[j]>cost[p][j])
		   {
			   lowc[j]=cost[p][j];
		   }
	   }
   }
   return ans;
}


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
};
typedef pair<int,int> pii;
typedef pair<bool,bool> pbb;
struct poi
{
	int w,v;
	poi(int w,int v):w(w),v(v){}
	poi(){}
	bool operator <(poi p) const
	{
		return w<p.w;
	}
};
queue<int> que;
vector<poi> g[1000];
int grapos[1000][1000];
int n,m;
int cost[30][30];
int vis[30],lowc[30];
int prim(int n)
{
   int ans=0;
   memset(vis,0,sizeof vis);
   vis[0]=1;
   for(int i=1;i<n;i++) lowc[i]=cost[0][i];
   for(int i=1;i<n;i++)
   {
	   int minc=INF;
	   int p=-1;
	   for(int j=0;j<n;j++)
	   {
		   if(!vis[j]&&minc>lowc[j])
		   {
			   minc=lowc[j];
			   p=j;
		   }
	   }
	   if(minc==INF)
	   {
		   return -1;
	   }
	   ans+=minc;
	   vis[p]=1;
	   for(int j=0;j<n;j++)
	   {
		   if(!vis[j]&&lowc[j]>cost[p][j])
		   {
			   lowc[j]=cost[p][j];
		   }
	   }
   }
   return ans;
}
 
int main()
{
#ifndef ONLINE_JUDGE
	system("color F0");
#endif
	int t;
	while(cin>>n)
	{
		if(!n)
			break;
		char s,t;
		memset(cost,0x3f,sizeof cost);
		for(int i=0;i<n-1;i++)
		{
			
			int numm;
			cin>>s>>numm;
			for(int j=0;j<numm;j++)
			{
				int len;
				cin>>t>>len;
				cost[s-'A'][t-'A']=len;
				cost[t-'A'][s-'A']=len;
			}
		}
		cout<<prim(n)<<endl;
	}
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}

// floyd 单源最短路：有向图，存在负边
void floyd(int a[][1000])
{
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				a[i][j]=a[i][j]||(a[i][k]&&a[k][j]);
			}
		}
	}
}

#include <iostream> 
#include <algorithm>
#include <cstring>
#include <time.h>
#include <random>
#define MAXN 1005
#define inf 0x3f
#define INF 0x3f3f3f3f
using namespace std;
int n,cost[MAXN][MAXN];
int dx[MAXN];
bool vis[MAXN];
void Dijkstra(int s)
{
    memset(dx,inf,sizeof dx);
    memset(vis,false,sizeof vis);
    dx[s]=0;
    for(int i=1;i<=n;i++)
        dx[i]=cost[0][i];
    while(true)
    {
        int v=-1;
        for(int u=1;u<=n;u++)
        {
            if(!vis[u]&&(v==-1||dx[u]<dx[v])) v=u;
        }
        if(v==-1) break;
        vis[v]=true;
        for(int u=1;u<=n;u++)
        {
            dx[u]=min(dx[u],dx[v]+cost[v][u]);
        }
    }
    return;
}
int ss[MAXN],ee[MAXN];
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
    int t,s,d;
    while(cin>>t>>s>>d)
    {
        memset(cost,inf,sizeof cost);
        n=0;
        for(int i=0;i<t;i++)
        {
            int x,y,c;
            cin>>x>>y>>c;
            n=max(max(n,x),y);
            if(c<cost[x][y])
                cost[x][y]=c,cost[y][x]=c;
        }
        for(int i=0;i<s;i++)
        {
            cin>>ss[i];
            cost[0][ss[i]]=cost[ss[i]][0]=0;
        }
        for(int i=0;i<d;i++)
        {
            cin>>ee[i];
        }
        Dijkstra(0);
        int minn=INF;
        for(int i=0;i<d;i++)
        {
            minn=min(minn,dx[ee[i]]);
        }
        cout<<minn<<endl;
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}

//Dijkstra 
void Dijkstra(int s)
{
    memset(dx,inf,sizeof dx);
    memset(vis,false,sizeof vis);
    dx[s]=0;
    for(int i=1;i<=n;i++)
        dx[i]=cost[0][i];
    while(true)
    {
        int v=-1;
        for(int u=1;u<=n;u++)
        {
            if(!vis[u]&&(v==-1||dx[u]<dx[v])) v=u;
        }
        if(v==-1) break;
        vis[v]=true;
        for(int u=1;u<=n;u++)
        {
            dx[u]=min(dx[u],dx[v]+cost[v][u]);
        }
    }
    return;
}

#include<iostream> 
#include <algorithm>
#include <cstring>
#include<time.h>
#include <random>
#define MAXN 1005
#define inf 0x3f
#define INF 0x3f3f3f3f
using namespace std;
int n,cost[MAXN][MAXN];
int dx[MAXN];
bool vis[MAXN];
void Dijkstra(int s)
{
    memset(dx,inf,sizeof dx);
    memset(vis,false,sizeof vis);
    dx[s]=0;
    for(int i=1;i<=n;i++)
        dx[i]=cost[0][i];
    while(true)
    {
        int v=-1;
        for(int u=1;u<=n;u++)
        {
            if(!vis[u]&&(v==-1||dx[u]<dx[v])) v=u;
        }
        if(v==-1) break;
        vis[v]=true;
        for(int u=1;u<=n;u++)
        {
            dx[u]=min(dx[u],dx[v]+cost[v][u]);
        }
    }
    return;
}
int ss[MAXN],ee[MAXN];
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
    int t,s,d;
    while(cin>>t>>s>>d)
    {
        memset(cost,inf,sizeof cost);
        n=0;
        for(int i=0;i<t;i++)
        {
            int x,y,c;
            cin>>x>>y>>c;
            n=max(max(n,x),y);
            if(c<cost[x][y])
                cost[x][y]=c,cost[y][x]=c;
        }
        for(int i=0;i<s;i++)
        {
            cin>>ss[i];
            cost[0][ss[i]]=cost[ss[i]][0]=0;
        }
        for(int i=0;i<d;i++)
        {
            cin>>ee[i];
        }
        Dijkstra(0);
        int minn=INF;
        for(int i=0;i<d;i++)
        {
            minn=min(minn,dx[ee[i]]);
        }
        cout<<minn<<endl;
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
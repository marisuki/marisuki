//mincost,maxflow
#define ll long long
typedef pair<ll,ll> pii;
struct Edge
{
    int from,to,cap;
	ll flow,cost;
    Edge(){}
    Edge(int f,int t,int c,ll fl,ll co):from(f),to(t),cap(c),flow(fl),cost(co){}
};
struct MCMF
{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	int inq[maxn];
	int d[maxn],p[maxn],a[maxn];
	void init(int n)
	{
		this->n=n;
		for(int i=0;i<=n+1;i++)
		{
			G[i].clear();
		}
		edges.clear();
		memset(inq,0,sizeof inq);
	}
	void addedge(int from,int to,int cap,int cost)
	{
		edges.push_back(Edge(from,to,cap,0,cost));
		edges.push_back(Edge(to,from,0,0,-cost));
		int ms=edges.size();
		G[from].push_back(ms-2);
		G[to].push_back(ms-1);
	}
	bool spfa(int s,int t,ll &flow,ll &cost)
	{
		memset(d,inf,sizeof d);
		memset(inq,0,sizeof inq);
		d[s]=0,inq[s]=1,p[s]=0,a[s]=INF;
		queue<int>que;
		que.push(s);
		while(!que.empty())
		{
			int u=que.front();
			que.pop();
			inq[u]=0;
			for(int i=0;i<G[u].size();i++)
			{
				Edge &e=edges[G[u][i]];
				if(e.cap>e.flow&&d[e.to]>d[u]+e.cost)
				{
					d[e.to]=d[u]+e.cost;
					p[e.to]=G[u][i];
					a[e.to]=min((ll)a[u],e.cap-e.flow);
					if(!inq[e.to])
					{
						inq[e.to]=1;
						que.push(e.to);
					}
				}
			}
		}
		if(d[t]==INF) return false;
		flow+=(ll)a[t];
        cost+=(ll)d[t]*a[t];
        int u=t;
        while(u!=s)
        {
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
            u=edges[p[u]].from;
        }
		return true;
	}
	pii MCMFlow(int s,int t,ll flow=0,ll cost=0)
	{
		ll f=0,c=0;
		while(spfa(s,t,f,c));
		flow=f,cost=c;
		return pii(flow,cost);
	}
}MC;



//example:
//poj-2135

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
#define maxn 1050
#define N 1050
#ifndef ONLINE_JUDGE
template <class T> struct greater {
  bool operator() (const T& x, const T& y) const {return x>y;}
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};
#endif
struct p
{
	double x,y;
	int n,m;
	p(){}
	p(double x,double y,int n,int m):x(x),y(y),n(n),m(m){}
};
typedef pair<ll,ll> pii;
struct Edge
{
    int from,to,cap;
	ll flow,cost;
    Edge(){}
    Edge(int f,int t,int c,ll fl,ll co):from(f),to(t),cap(c),flow(fl),cost(co){}
};
struct MCMF
{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	int inq[maxn];
	int d[maxn],p[maxn],a[maxn];
	void init(int n)
	{
		this->n=n;
		for(int i=0;i<=n+1;i++)
		{
			G[i].clear();
		}
		edges.clear();
		memset(inq,0,sizeof inq);
	}
	void addedge(int from,int to,int cap,int cost)
	{
		edges.push_back(Edge(from,to,cap,0,cost));
		edges.push_back(Edge(to,from,0,0,-cost));
		int ms=edges.size();
		G[from].push_back(ms-2);
		G[to].push_back(ms-1);
	}
	bool spfa(int s,int t,ll &flow,ll &cost)
	{
		memset(d,inf,sizeof d);
		memset(inq,0,sizeof inq);
		d[s]=0,inq[s]=1,p[s]=0,a[s]=INF;
		queue<int>que;
		que.push(s);
		while(!que.empty())
		{
			int u=que.front();
			que.pop();
			inq[u]=0;
			for(int i=0;i<G[u].size();i++)
			{
				Edge &e=edges[G[u][i]];
				if(e.cap>e.flow&&d[e.to]>d[u]+e.cost)
				{
					d[e.to]=d[u]+e.cost;
					p[e.to]=G[u][i];
					a[e.to]=min((ll)a[u],e.cap-e.flow);
					if(!inq[e.to])
					{
						inq[e.to]=1;
						que.push(e.to);
					}
				}
			}
		}
		if(d[t]==INF) return false;
		flow+=(ll)a[t];
        cost+=(ll)d[t]*a[t];
        int u=t;
        while(u!=s)
        {
            edges[p[u]].flow+=a[t];
            edges[p[u]^1].flow-=a[t];
            u=edges[p[u]].from;
        }
		return true;
	}
	pii MCMFlow(int s,int t,ll flow=0,ll cost=0)
	{
		ll f=0,c=0;
		while(spfa(s,t,f,c));
		flow=f,cost=c;
		return pii(flow,cost);
	}
}MC;
int n,m,k;
struct triple
{
	int x,y,z;
	triple(){}
	triple(int x,int y,int z):x(x),y(y),z(z){}
};
int dispatchint(string a)
{
	int ans=a[0]-'0';
	for(int i=1;i<a.length();i++)
	{
		ans=ans*10+a[i]-'0';
	}
	return ans;
}
vector<int>  dispatch(string a)
{
	int pre=1,end=1;
	vector<int>ans;
	for(int i=1;i<a.length();i++)
	{
		if(a[i]>='0'&&a[i]<='9') end=i;
		else
		{
			ans.push_back(dispatchint(a.substr(pre,end-pre+1)));
			pre=i+1;
			end=i+1;
		}
	}
	ans.push_back(dispatchint(a.substr(pre,end)));
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
    int t;
	while(cin>>n>>m)
	{
		MC.init(n+10);
		MC.addedge(0,1,2,0);
		MC.addedge(n,n+1,2,0);
		for(int i=0;i<m;i++)
		{
			int u,v,w;
			cin>>u>>v>>w;
			MC.addedge(u,v,1,w);
			MC.addedge(v,u,1,w);
		}
		pii p=MC.MCMFlow(0,n+1);
		cout<<p.second<<endl;
	}
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}

// Maxflow:Dinic O(min(n^2/3,m^1/2)*m),二分图：O(n^1/2 *m)

const int maxn=200+5;
struct Edge
{
    int from,to,cap,flow;
    Edge(){}
    Edge(int f,int t,int c,int fl):from(f),to(t),cap(c),flow(fl){}
};
struct Dinic
{
    int n,m,s,t;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn];
    int cur[maxn];
    int d[maxn];

    void init(int n,int s,int t)
    {
        this->n=n, this->s=s, this->t=t;
        edges.clear();
        for(int i=0;i<n;i++) G[i].clear();
    }

    void AddEdge(int from,int to,int cap)
    {
        edges.push_back( Edge(from,to,cap,0) );
        edges.push_back( Edge(to,from,0,0) );
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS()
    {
        queue<int> Q;
        memset(vis,0,sizeof(vis));
        vis[s]=true;
        d[s]=0;
        Q.push(s);
        while(!Q.empty())
        {
            int x=Q.front(); Q.pop();
            for(int i=0;i<G[x].size();++i)
            {
                Edge& e=edges[G[x][i]];
                if(!vis[e.to] && e.cap>e.flow)
                {
                    vis[e.to]=true;
                    d[e.to] = d[x]+1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x,int a)
    {
        if(x==t || a==0) return a;
        int flow=0,f;
        for(int& i=cur[x];i<G[x].size();++i)
        {
            Edge& e=edges[G[x][i]];
            if(d[e.to]==d[x]+1 && (f=DFS(e.to,min(a,e.cap-e.flow) ) )>0)
            {
                e.flow +=f;
                edges[G[x][i]^1].flow -=f;
                flow+=f;
                a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }

    int max_flow()
    {
        int ans=0;
        while(BFS())
        {
            memset(cur,0,sizeof(cur));
            ans+=DFS(s,INF);
        }
        return ans;
    }
}DC;


//example:

//poj-3498,hoj-2609

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
#define maxn 305
#define N 105
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
int gdist(p a,p b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
struct Edge
{
    int from,to,cap,flow;
    Edge(){}
    Edge(int f,int t,int c,int fl):from(f),to(t),cap(c),flow(fl){}
};
struct Dinic
{
    int n,m,s,t;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn];
    int cur[maxn];
    int d[maxn];
 
    void init(int n,int s,int t)
    {
        this->n=n, this->s=s, this->t=t;
        edges.clear();
        for(int i=0;i<n;i++) G[i].clear();
    }
 
    void AddEdge(int from,int to,int cap)
    {
        edges.push_back( Edge(from,to,cap,0) );
        edges.push_back( Edge(to,from,0,0) );
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
 
    bool BFS()
    {
        queue<int> Q;
        memset(vis,0,sizeof(vis));
        vis[s]=true;
        d[s]=0;
        Q.push(s);
        while(!Q.empty())
        {
            int x=Q.front(); Q.pop();
            for(int i=0;i<G[x].size();++i)
            {
                Edge& e=edges[G[x][i]];
                if(!vis[e.to] && e.cap>e.flow)
                {
                    vis[e.to]=true;
                    d[e.to] = d[x]+1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }
 
    int DFS(int x,int a)
    {
        if(x==t || a==0) return a;
        int flow=0,f;
        for(int& i=cur[x];i<G[x].size();++i)
        {
            Edge& e=edges[G[x][i]];
            if(d[e.to]==d[x]+1 && (f=DFS(e.to,min(a,e.cap-e.flow) ) )>0)
            {
                e.flow +=f;
                edges[G[x][i]^1].flow -=f;
                flow+=f;
                a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }
 
    int max_flow()
    {
        int ans=0;
        while(BFS())
        {
            memset(cur,0,sizeof(cur));
            ans+=DFS(s,INF);
        }
        return ans;
    }
}DC;
int n,num;
double d;
p poi[maxn];
int able[maxn][maxn];
vector<int>ans;
bool solve(int t)
{
	DC.init(2*n+2,0,t);
	for(int i=1;i<=n;i++)
	{
		if(poi[i].n)
			DC.AddEdge(0,i,poi[i].n);
	}
	for(int i=1;i<=n;i++)
	{
		if(poi[i].m)
			DC.AddEdge(i,i+n,poi[i].m);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(able[i][j])
			{
				DC.AddEdge(i+n,j,INF);
				DC.AddEdge(j+n,i,INF);
			}
		}
	}
	return DC.max_flow()==num;
}
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
    int t;
	cin>>t;
	while(t--)
	{
		ans.clear();
		cin>>n>>d;
		num=0;
		memset(able,0,sizeof able);
		for(int i=1;i<=n;i++)
		{
			double x,y;
			int nx,mx;
			cin>>x>>y>>nx>>mx;
			poi[i]=p(x,y,nx,mx);
			num+=nx;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(gdist(poi[i],poi[j])<=d*d) able[i][j]=1;
				else able[i][j]=0;
				if(i==j) able[i][j]=1;
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(solve(i)) ans.push_back(i);
		}
		if(!ans.size()) cout<<-1<<endl;
		else
		{
			cout<<ans[0]-1;
			for(int i=1;i<ans.size();i++)
			{
				cout<<' '<<ans[i]-1;
			}
			cout<<endl;
		}
	}
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
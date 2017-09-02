//spfa 可判负环

//含源最短路

void spfa(int s)
{
    memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	queue<int> que;
    que.push(s);
    dis[s]=0;
    vis[s]=true;
    while (!que.empty())
    {
        int u=que.front();
		que.pop();
        vis[u]=false;
        for (int i=head[u];i+1;i=gra[i].next)
        {
            int v=gra[i].v;
            if (dis[v]>dis[u]+gra[i].w)
            {
                dis[v]=dis[u]+gra[i].w;
                if (!vis[v])
                {
                    vis[v]=true;
                    que.push(v);
                }
            }
        }
    }
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
queue<int> que;
vector<poi> g[1000];
//int gra[1000][1000];
int n,m;
int vis[300005];
int par[300050];
ll dis[300050];
poi gra[600050];
int head[300050];
void  init(int n)
{
	for(int i=0;i<=n;i++)
		par[i]=i;
}
int find(int x)
{
	while(x!=par[x]) x=par[x];
	return x;
}
int uni(int x,int y)
{
	x=find(x),y=find(y);
	par[x]=y;
	return x;
}
void spfa(int s)
{
    memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	queue<int> que;
    que.push(s);
    dis[s]=0;
    vis[s]=true;
    while (!que.empty())
    {
        int u=que.front();
		que.pop();
        vis[u]=false;
        for (int i=head[u];i+1;i=gra[i].next)
        {
            int v=gra[i].v;
            if (dis[v]>dis[u]+gra[i].w)
            {
                dis[v]=dis[u]+gra[i].w;
                if (!vis[v])
                {
                    vis[v]=true;
                    que.push(v);
                }
            }
        }
    }
}
int main()
{
#ifndef ONLINE_JUDGE
	system("color F0");
#endif
	while(cin>>n>>m)
	{
		memset(head,-1,sizeof head);
		int num=0;
		for(int i=1;i<=m;i++)
		{
			int a,b,c;
			cin>>a>>b>>c;
			gra[num]=poi(a,b,c,head[a],i);
			head[a]=num++;
			gra[num]=poi(b,a,c,head[b],i);
			head[b]=num++;
		}
		int u;
		cin>>u;
		spfa(u);
		ll ans=0;
		vector<int> anss;
		for(int i=1;i<=n;i++)
		{
			if(i==u)
				continue;
			int tmp=0x3f3f3f3f;
			int index;
			for(int j=head[i];j+1;j=gra[j].next)
			{
				if(dis[i]==dis[gra[j].v]+gra[j].w)
				{
					if(tmp>gra[j].w)
					{
						tmp=gra[j].w;
						index=gra[j].id;
					}
				}
			}
			ans+=tmp;
			anss.push_back(index);
		}
		sort(anss.begin(),anss.end());
		cout<<ans<<endl;
 
		for(int i=0;i<anss.size();i++)
		{
			cout<<anss[i]<<' ';
		}
		cout<<endl;
	}
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
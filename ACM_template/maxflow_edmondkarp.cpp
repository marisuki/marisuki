#include<iostream>
#include<queue>
#include<stack>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;

struct edge
{
	int to,cap,rev;
	edge(){}
	edge(int to,int cap,int rev):to(to),cap(cap),rev(rev){}
};
bool vis[200];
vector<edge> flow[200];
int n,m;


int bfs(int v,int t,int f)
{
	if(v==t) return f;
	vis[v]=true;
	for(int i=0;i<flow[v].size();i++)
	{
		edge &a=flow[v][i];
		if(!vis[a.to]&&a.cap>0)
		{
			int dis=bfs(a.to,t,min(f,a.cap));
			if(dis>0)
			{
				a.cap-=dis;
				flow[a.to][a.rev].cap+=dis;
				return dis;
			}
		}
	}
	return 0;
}

int edmond()
{
	cin>>n>>m;
	for(int i=0;i<=n;i++) flow[i].clear();
	for(int i=0;i<m;i++)
	{
		int tmp,x,y;
		cin>>x>>y>>tmp;
		flow[x].push_back(edge(y,tmp,flow[y].size()));
		flow[y].push_back(edge(x,0,flow[x].size()-1));
	}
	int ans=0;
	while(true)
	{
		memset(vis,0,sizeof vis);
		int df=bfs(1,n,INF);
		if(df==0) return ans;
		ans+=df;
	}
	return 0;
}

int main()
{
	cout<<edmond()<<endl;
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
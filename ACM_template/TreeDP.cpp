
// tree dp
//hdu1520

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
#define ull unsigned long long
#define MOD 1e9+7
#define INFLL 0x7fffff
#define INFI 0x7f7f7f7f
#define INF 0x3f3f3f3f
#define inf 0x3f
#define esp 1.0e-4
#define M(a,k) memset(a,k,sizeof a)
#define Endl endl
#define maxn 50005
#define N 5005
#define sd(x) scanf("%d",&x)
#define sld(x) scanf("%lld",&x)
#define sdd(x,y) scanf("%d%d",&x,&y)
#define sc(x) scanf("%c",&x)
#define ss(x) scanf("%s",x)
#define pd(x) printf("%d\n",x)
#define NUMOFITEMS 7
#ifndef ONLINE_JUDGE
template <class T> struct greater {
  bool operator() (const T& x, const T& y) const {return x>y;}
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};
#endif
struct edge
{
	int to,next;
}poi[6005<<2];
vector<int> u[6005];
int fa[6005];
int a[6005],dp[6005][10];
bool vis[6005];
int head[6005],num;
void addedge(int x,int y)
{
	poi[num].to=y;
	poi[num].next=head[x];
	head[x]=num++;
}
void tdp(int x)
{
	for(int i=head[x];i!=-1;i=poi[i].next)
	{
		int t=poi[i].to;
		tdp(t);
		dp[x][1]+=dp[t][0];
		dp[x][0]+=max(dp[t][0],dp[t][1]);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0"); 
#endif
	int n;
	int flag=0;
	while(cin>>n)
	{
		num=0;
		if(n==0)
		{
			cin>>n;
			break;
		}
		memset(dp,0,sizeof dp);
		memset(vis,0,sizeof vis);
		memset(fa,-1,sizeof fa);
		memset(head,-1,sizeof head);
		for(int i=1;i<=n;i++) cin>>a[i],dp[i][1]=a[i];
		int root=1;int l,k;
		while(cin>>l>>k)
		{
			if(l+k==0) break;
			fa[l]=k;
			addedge(k,l);
		}
		while(fa[root]!=-1) root=fa[root];
		tdp(root);
		cout<<max(dp[root][0],dp[root][1])<<endl;
		if(flag==1) break;
	}
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}

//dp slope 
//DP deque 优化
// O(n^(x))->O(n^(x-1))
//适用模型： dp[i][j]=min/max(f[i-1][k])+g[i][i-1]...
hdu-3401,uestc-1685
hdu-3401:
{
	dp[i][j]=min(dp[i-1][k]+C*abs(j-k)+(x[i]-j)**2)
	<=>
	{
		k>j: dp[i][j]=min(dp[i-1][k]+C*k-C*j+(x[i]-j)**2)=min(f[i-1][k])-C*j+XX
		k<=j: dp[i][j]=min(dp[i-1][k]-C*k+C*j+(x[i]-j)**2)=min(f[i-1][k])+C*j+XX
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
#define INF 10000006
#define inf 0x3f
#define esp 1.0e-10
#define M(a,k) memset(a,k,sizeof a)
#define Endl endl
#define maxn 5005
#define N 5005
#define sd(x) scanf("%d",&x)
#define sld(x) scanf("%lld",&x)
#define sdd(x,y) scanf("%d%d",&x,&y)
#define sc(x) scanf("%c",&x)
#define ss(x) scanf("%s",x)
#define pd(x) printf("%d\n",x)
#ifndef ONLINE_JUDGE
template <class T> struct greater {
  bool operator() (const T& x, const T& y) const {return x>y;}
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};
#endif
int n,l,m;
int c[500005],pre[500005];
int f[500005],dp[500005],que[500005];
int alope(int j,int k)
{
	return (double)(dp[k]-dp[j]-f[j]*f[j]+f[k]*f[k]);
}
int slop(int j,int k)
{
	return (double) (f[k]-f[j]);
}
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
	while(cin>>n>>m)
	{
		memset(que,0,sizeof que);
		memset(f,0,sizeof f);
		for(int i=1;i<=n;i++) cin>>c[i];
		memset(pre,0,sizeof pre);
		for(int i=1;i<=n;i++) f[i]=f[i-1]+c[i];
		//for(ll i=1;i<=n;i++) f[i]=pre[i];
		memset(dp,0,sizeof dp);
		int lx=0,r=0;
		for(int i=1;i<=n;i++)
		{
			while(lx<r && alope(que[lx],que[lx+1])<=2*f[i]*slop(que[lx],que[lx+1])) lx++;
			dp[i]=dp[que[lx]]+slop(que[lx],i)*slop(que[lx],i)+m;//(f[i]-f[que[lx]])*(f[i]-f[que[lx]])+l;
			while(lx<r&& alope(que[r-1],que[r])*slop(que[r],i)>=alope(que[r],i)*slop(que[r-1],que[r])) r--;
			que[++r]=i;
		}
		cout<<dp[n]<<endl;
	}
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}

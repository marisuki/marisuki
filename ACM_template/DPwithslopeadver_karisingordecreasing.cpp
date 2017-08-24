/*
	DP斜率优化：

	slope(j,k) <= k(i)
	其中，k(i) 单调，slope(j,k) able

	推导：
	设 j>k ,j 比k 优，求slope(j,k)
	

	Causion:
	 slope(j,k) 函数涉及double->int/int->int~~int
*/
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
#define sdd(x,y) scanf("%d%d",&x,&y)
#define sc(x) scanf("%c",&x)
#define ss(x) scanf("%s",x)
#define pd(x) printf("%d",x)
#ifndef ONLINE_JUDGE
template <class T> struct greater {
  bool operator() (const T& x, const T& y) const {return x>y;}
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};
#endif
ll n,l;
ll c[50005],pre[50005];
ll f[50005],dp[50005],que[50005];
double alope(ll j,ll k)
{
	return (double)(dp[j]-dp[k]+(f[j]+l)*(f[j]+l)-(f[k]+l)*(f[k]+l))/(2.0*(f[j]-f[k]));
}
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
	cin>>n>>l;
	for(ll i=1;i<=n;i++) sd(c[i]);
	memset(pre,0,sizeof pre);
	for(ll i=1;i<=n;i++) pre[i]=pre[i-1]+c[i];
	for(ll i=1;i<=n;i++) f[i]=pre[i]+i;
	memset(dp,0,sizeof dp);
	ll lx=1,r=1;
	for(ll i=1;i<=n;i++)
	{
		while(lx<r && alope(que[lx],que[lx+1])<=f[i]) lx++;
		dp[i]=dp[que[lx]]+(i-que[lx]-1+pre[i]-pre[que[lx]]-l)*(i-que[lx]-1+pre[i]-pre[que[lx]]-l);
		while(lx<r&& alope(que[r-1],que[r])>alope(que[r],i)) r--;
		que[++r]=i;
	}
	cout<<dp[n]<<endl;
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
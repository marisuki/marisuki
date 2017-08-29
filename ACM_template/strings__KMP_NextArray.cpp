// KMP+Next array

char w[1000005];
int nexts[1000005];
int lw,lt;
void gen_next()
{
	memset(nexts,0,sizeof nexts);
	int i=1,j=0;
	while(i<=lw)
	{
		if(j==0||w[i]==w[j])
		{
			i++,j++;
			nexts[i]=j;
		}
		else j=nexts[j];
	}
}
int kmp()
{
	int i=0,j=0,num=0;
	while(i<lt)
	{
		if(j==-1||t[i]==w[j])
		{
			i++,j++;
		}
		else j=nexts[j];
		if(j==lw)
		{
			num++;
			j=nexts[j];
		}
	}
	return num;
}


//cf-126B

// next array in use

// fixprefixsuffix->fix
// longest repeat >=2 substrings
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
#define INF 10000006
#define inf 0x3f
#define esp 1.0e-10
#define M(a,k) memset(a,k,sizeof a)
#define Endl endl
#define maxn 220005
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

char w[1000005];
int nexts[1000005];
int lw,lt;
void gen_next()
{
	memset(nexts,0,sizeof nexts);
	int i=1,j=0;
	while(i<=lw)
	{
		if(j==0||w[i]==w[j])
		{
			i++,j++;
			nexts[i]=j;
		}
		else j=nexts[j];
	}
}
int vis[1000005];
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
	int n,tt;
	//cin>>tt;
	while(scanf("%s",w+1)!=EOF)
	{
		//scanf("%s",w);
		memset(vis,0,sizeof vis);
		lw=strlen(w+1);
		if(lw<3) 
		{
			cout<<"Just a legend"<<endl;;
			continue;
		}
		gen_next();
		bool flag=0;
		for(int i=2;i<=lw;i++)
			vis[nexts[i]]=1;
		int xx=nexts[lw+1];
		while(!vis[xx]&&xx) xx=nexts[xx];
		if(xx==1)
		{
			cout<<"Just a legend"<<endl;
		}
		else
		{
			for(int i=1;i<xx;i++)
			{
				printf("%c",w[i]);
			}
			cout<<endl;
		}
	}
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}


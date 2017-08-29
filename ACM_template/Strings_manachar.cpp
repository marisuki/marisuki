
// manachar : 回文
//

int str[maxn];
int p[maxn];
void manachar(int *a, int len)
{
	p[0]=1;
	int nmax=0,id=0;
	for(int i=1;i<len;i++)
	{
		p[i]= nmax>i ? min(p[2*id-i],nmax-i) : 1;
		while(a[i+p[i]]==a[i-p[i]])
		{
			if(a[i-p[i]]==INF) p[i]++;
			else
			{
				if((i-p[i]+2<=i&&a[i-p[i]]<=a[i-p[i]+2])||i-p[i]+2>i) ++p[i];
				else break;
			}
		}
		if(i+p[i]>id+p[id])
		{
			id=i;
			nmax=i+p[i];
		}
	}
	return;
}


// hdu 3068
// manachar only
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

char str[maxn];
int p[maxn];
void manachar(char *a, int len)
{
	p[0]=1;
	int nmax=0,id=0;
	for(int i=1;i<len;i++)
	{
		p[i]= nmax>i ? min(p[2*id-i],nmax-i) : 1;
		while(a[i+p[i]]==a[i-p[i]]) p[i]++;
		if(i+p[i]>id+p[id])
		{
			id=i;
			nmax=i+p[i];
		}
	}
	return;
}
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
	while(scanf("%s",str)!=EOF)
	{
		memset(p,0,sizeof p);
		if(str[0]=='\n') continue;
		int length=strlen(str);
		for(int i=length;i>=0;i--)
		{
			str[(i<<1)+1]='#';
			str[(i<<1)+2]=str[i];
		}
		str[0]='*';
		length=2*length+2;
		manachar(str,length);
		int ans=0;
		for(int i=0;i<length;i++)
		{
			ans=max(ans,p[i]-1);
		}
		pd(ans);
		//cout<<ans<<endl;
	}
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}


// 最长公共前缀 lcp

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
#define maxn 500005
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
 
int n,k;
int ranks[maxn],ssa[maxn],lcp[maxn];
int tmp[maxn];
bool compare_ca(int i,int j)
{
	if(ranks[i]!=ranks[j]) return ranks[i]<ranks[j];
	else
	{
		int ri= i+k<=n? ranks[i+k] :-1;
		int rj= j+k<=n? ranks[j+k] :-1;
		return ri<rj;
	}
}
void construct_sa(char *s, int *sa)
{
    n = strlen(s);
    for (int i = 0; i <= n; i++){
        sa[i] = i;
        ranks[i] = i < n ? s[i] : -1;
    }
    for (k = 1; k <= n; k <<= 1)
    {
        sort(sa, sa + n + 1, compare_ca);
        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; i++)
        {
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_ca(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for (int i = 0; i <= n; i++)
		{
            ranks[i] = tmp[i];
        }
    }
}
 
void construct_lcp(char* s,int *sa,int *lcp)
{
	int n=strlen(s);
	for(int i=0;i<=n;i++) ranks[sa[i]]=i;
	int h=0;lcp[0]=0;
	for(int i=0;i<n;i++)
	{
		int j=sa[ranks[i]-1];
		 h ? h-- : 0; 
		for(;j+h<n&&i+h<n&&s[j+h]==s[i+h];h++)
		{
			//if(s[j+h]!=s[i+h]) break;
		}
		lcp[ranks[i]-1]=h;
	}
}
char st1[maxn + 50], st2[maxn + 50];
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
	while(cin>>st1>>st2)
	{
		int len=strlen(st1);
		//st1=st1+'#'+'\0'+st2;
		st1[len]='#';
		st1[len+1]='\0';
		strcat(st1,st2);
		construct_sa(st1,ssa);
		construct_lcp(st1,ssa,lcp);
		int ans=0;
		for(int i=0;i<strlen(st1);i++)
		{
			if((ssa[i]<len)!=(ssa[i+1])<len)
			 ans=max(ans,lcp[i]);
		}
		cout<<ans<<endl;
	}
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
// AC auto machine

struct Trie_ACauto
{
	int next[maxn][NUMOFITEMS],fail[maxn],end[maxn];
	int vis[maxn];
	int root,tot;
	void init()
	{
		tot=0;
		root=newnode();
	}
	int newnode()
	{
		for(int i=0;i<=NUMOFITEMS;i++) next[tot][i]=-1;
		end[tot++]=-1;
		return tot-1;
	}
	void insert(char *buffer,int index)
	{
		int length=strlen(buffer);
		int now=root;
		for(int i=0;i<length;i++)
		{
			int k=buffer[i]-'0';
			if(next[now][k]==-1)
				next[now][k]=newnode();
			now=next[now][k];
		}
		end[now]=index;
		//endpoint[now].push_back(index);
	}
	bool build()
	{
		//bfs
		bool flag=0;
		queue<int> que;
		fail[root]=root;
		for(int i=0;i<NUMOFITEMS;i++)
		{
			if(next[root][i]==-1) next[root][i]=root;
			else
			{
				fail[next[root][i]]=root;
				que.push(next[root][i]);
			}
		}
		while(!que.empty())
		{
			int now=que.front();
			que.pop();
			for(int i=0;i<NUMOFITEMS;i++)
			{
				if(next[now][i]==-1)
				{
					next[now][i]=next[fail[now]][i];
				}
				else
				{
					fail[next[now][i]]=next[fail[now]][i];
					que.push(next[now][i]);
				}
				if(end[now]!=-1&&next[now][i]!=0)
				{
					flag=1;
				}
			}
		}
		return true;
	}
	int query(char *buffer,int index,int nmax)
	{
		memset(vis,0,sizeof vis);
		int length=strlen(buffer);
		int now=root;
		int res=0;
		int flag=0;
		for(int i=0;i<length;i++)
		{
			now=next[now][buffer[i]-'0'];
			int tmp=now;
			while(tmp!=root)
			{
				if(end[tmp]!=-1)
				{
					res++;
					flag=1;
					vis[end[tmp]]=1;
				}
				tmp=fail[tmp];
			}
		}
		return res;
	}
}AC;



// hdu 3341

// ac auto+dp(state compression)

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
#define NUMOFITEMS 7
#ifndef ONLINE_JUDGE
template <class T> struct greater {
  bool operator() (const T& x, const T& y) const {return x>y;}
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};
#endif
int AGCT[10];
char buf[100];
int hashs[50][50][50][50];
int dp[503][15005];
map<char ,int> mmp;
struct Trie_ACauto
{
	int next[maxn][NUMOFITEMS],fail[maxn],end[maxn];
	int vis[maxn];//,val[maxn];
	int root,tot;
	void init()
	{
		tot=0;
		//memset(val,0,sizeof val);
		root=newnode();
	}
	int newnode()
	{
		for(int i=0;i<4;i++) next[tot][i]=0;
		end[tot]=0;
		return tot++;
	}
	void insert(char *buffer,int index)
	{
		int length=strlen(buffer);
		int now=root;
		for(int i=0;i<length;i++)
		{
			int k=mmp[buffer[i]];
			if(!next[now][k])
				next[now][k]=newnode();
			now=next[now][k];
		}
		end[now]++;
		//endpoint[now].push_back(index);
	}
	bool build()
	{
		//bfs
		bool flag=0;
		queue<int> que;
		fail[root]=root;
		for(int i=0;i<4;i++)
		{
			if(!next[root][i]){}// next[root][i]=root;
			else
			{
				fail[next[root][i]]=root;
				que.push(next[root][i]);
			}
		}
		while(!que.empty())
		{
			int now=que.front();
			que.pop();
			end[now]+=end[fail[now]];
			for(int i=0;i<4;i++)
			{
				if(!next[now][i])
				{
					next[now][i]=next[fail[now]][i];
				}
				else
				{
					fail[next[now][i]]=next[fail[now]][i];
					que.push(next[now][i]);
				}
			}
		}
		return true;
	}
	int query(char *buffer,int index,int nmax)
	{
		memset(vis,0,sizeof vis);
		int length=strlen(buffer);
		int now=root;
		int res=0;
		int flag=0;
		for(int i=0;i<length;i++)
		{
			now=next[now][mmp[buffer[i]]];
			int tmp=now;
			while(tmp!=root)
			{
				if(end[tmp]!=0)
				{
					res++;
					flag=1;
					vis[end[tmp]]=1;
				}
				tmp=fail[tmp];
			}
		}
		return res;
	}
	void DP(int cases)
	{
		int now=root;
		memset(dp,-1,sizeof dp);
		dp[0][0]=0;
		int ans=0;
		for(int a=0;a<=AGCT[0];a++)
		{
			for(int g=0;g<=AGCT[1];g++)
			{
				for(int c=0;c<=AGCT[2];c++)
				{
					for(int t=0;t<=AGCT[3];t++)
					{
						int ori=hashs[a][g][c][t];
						if(a+g+c+t==0) continue;
						for(int i=0;i<tot;i++)
						{
							for(int j=0;j<4;j++)
							{
								int org;
								if(j==0&&a>=1) org=hashs[a-1][g][c][t];
								else if(j==1&&g>=1) org=hashs[a][g-1][c][t];
								else if(j==2&&c>=1) org=hashs[a][g][c-1][t];
								else if(j==3&&t>=1) org=hashs[a][g][c][t-1];
								else continue;
								if(dp[i][org]==-1) continue;
								dp[next[i][j]][ori]=max(dp[next[i][j]][ori],dp[i][org]+end[next[i][j]]);
								ans=max(ans,dp[next[i][j]][ori]);
							}
						}
					}
				}
			}
		}
		printf("Case %d: %d\n", cases++, ans);
	}
}AC;
 
int main()
{
#ifndef ONLINE_JUDGE
    system("color F0"); 
#endif
	int n;
	mmp['A']=0;
	mmp['G']=1;
	mmp['C']=2;
	mmp['T']=3;
	int cnt=0;
	while(scanf("%d",&n)==1)
	{
		if(!n) break;
		AC.init();
		memset(AGCT,0,sizeof AGCT);
		memset(hashs,0,sizeof hashs);
		for(int i=0;i<n;i++)
		{
			scanf("%s",buf);
			AC.insert(buf,i+1);
		}
		AC.build();
		scanf("%s",buf);
		for(int i=0;i<strlen(buf);i++)
		{
			AGCT[mmp[buf[i]]]++;
		}
		int num=0;
		for(int i=0;i<=AGCT[0];i++)
		{
			for(int j=0;j<=AGCT[1];j++)
			{
				for(int p=0;p<=AGCT[2];p++)
				{
					for(int q=0;q<=AGCT[3];q++)
					{
						hashs[i][j][p][q]=num++;
					}
				}
			}
		}
		AC.DP(++cnt);
	}
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}
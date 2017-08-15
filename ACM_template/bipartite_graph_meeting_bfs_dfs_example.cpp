# 2分图匹配：匈牙利算法

// 顶点、边的编号均从 0 开始
// 邻接表储存

//dfs:
//template begin
struct Edge
{
    int from;
    int to;
    int weight;

    Edge(int f, int t, int w):from(f), to(t), weight(w) {}
};

vector<int> G[__maxNodes]; /* G[i] 存储顶点 i 出发的边的编号 */
vector<Edge> edges;
typedef vector<int>::iterator iterator_t;
int num_nodes;
int num_left;
int num_right;
int num_edges;
int matching[__maxNodes]; /* 存储求解结果 */
int check[__maxNodes];

bool dfs(int u)
{
    for (iterator_t i = G[u].begin(); i != G[u].end(); ++i) { // 对 u 的每个邻接点
        int v = edges[*i].to;
        if (!check[v]) {     // 要求不在交替路中
            check[v] = true; // 放入交替路
            if (matching[v] == -1 || dfs(matching[v])) {
                // 如果是未盖点，说明交替路为增广路，则交换路径，并返回成功
                matching[v] = u;
                matching[u] = v;
                return true;
            }
        }
    }
    return false; // 不存在增广路，返回失败
}

int hungarian()
{
    int ans = 0;
    memset(matching, -1, sizeof(matching));
    for (int u=0; u < num_left; ++u) {
        if (matching[u] == -1) {
            memset(check, 0, sizeof(check));
            if (dfs(u))
                ++ans;
        }
    }
    return ans;
}
//template end



// bfs:
//template begin
queue<int> que;
int prev[maxnodes];
struct Edge
{
    int from;
    int to;
    int weight;

    Edge(int f, int t, int w):from(f), to(t), weight(w) {}
};
vector<int> G[__maxNodes]; /* G[i] 存储顶点 i 出发的边的编号 */
vector<Edge> edges;
typedef vector<int>::iterator iterator_t;
int num_nodes;
int num_left;
int num_right;
int num_edges;
int matching[__maxNodes]; /* 存储求解结果 */
int check[__maxNodes];
int Hungarian()
{
	int ans=0;
	memset(check,-1,sizeof check);
	memset(maching -1,sizeof maching);
	for(int i=0;i<num_left;i++)
	{
		if(maching[i]==-1)
		{
			while(!que.empty()) que.pop();
			que.push(i);
			prev[i]=-1;
			bool flag=false;
			while(!que.empty()&&!flag)
			{
				int u=que.front();
				for(iterator_t it=G[u].begin();it!G[u].end()&&!flag;it++)
				{
					int v=edges[*it].to;
					if(check[v]!=v)
					{
						check[v]=v;
						que.push(maching[v]);
						if(maching[v]>=0)
						{
							prev[maching[v]]=u;
						}
						else
						{
							flag=true;
							int d=u,e=v;
							while(d!=-1)
							{
								int t=maching[d];
								maching[d]=e;
								maching[e]=d;
								d=prev[d];
								e=t;
							}
						}
					}
				}
				que.pop();
			}
			if(maching[i]!=-1) ans++;
		}
	}
	return ans;
}
//template end


//example: 

/* **************************************************************************
//二分图匹配（匈牙利算法的DFS实现）
//初始化：g[][]两边顶点的划分情况
//建立g[i][j]表示i->j的有向边就可以了，是左边向右边的匹配
//g没有边相连则初始化为0
//L是匹配左边的顶点数，R是匹配右边的顶点数
//调用：res=hungary();输出最大匹配数
//优点：适用于稠密图，DFS找增广路，实现简洁易于理解
//时间复杂度:O(VE)
//***************************************************************************/
//顶点编号从1开始的
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define MAXN 317
int LN,RN;
int g[MAXN][MAXN], linker[MAXN];
bool used[MAXN];
int dfs(int L)
{
    int R;
    for(R = 1; R <= RN; R++)
    {
        if(g[L][R]!=0 && !used[R])
        {
            used[R]=true;
            if(linker[R] == -1 || dfs(linker[R]))
            {
                linker[R]=L;
                return 1;
            }
        }
    }
    return 0;
}
int hungary()
{
    int res = 0 ;
    int L;
    memset(linker,-1,sizeof(linker));
    for( L = 1; L <= LN; L++)
    {
        memset(used,0,sizeof(used));
        if(dfs(L) != 0)
            res++;
    }
    return res;
}
int main()
{
    int t;
    int p, n;
    int k, L, R;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&p,&n);
        memset(g,0,sizeof(g));
        for(int i = 1; i <= p; i++)
        {
            scanf("%d",&k);
            for(int j = 1; j <= k; j++)
            {
                scanf("%d",&R);
                L = i;
                g[L][R] = 1;
            }
        }
        LN = p;
        RN = n;
        int res = hungary();
        if(res == p)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0 ;
}


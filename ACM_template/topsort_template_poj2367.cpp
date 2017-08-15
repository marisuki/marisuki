// 拓扑排序
// poj 2367
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

//template begin
int n;
int indeg[150],pur[150],maps[150][150];
void topsort()
{
    int k=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(indeg[j]==0)
            {
                indeg[j]--;
                pur[k++]=j;
                for(int l=1;l<=n;l++)
                {
                    if(maps[j][l])
                        indeg[l]--;
                }
                break;
            }
            if(j>=n)
            {
                cout<<"存在环\n"<<endl;
                return;
            }
        }
    }
}
//template end


int main()
{
#ifndef ONLINE_JUDGE
    system("color F0");
#endif
    while(cin>>n)
    {
        memset(maps,0,sizeof maps);
        memset(pur,0,sizeof pur);
        memset(indeg,0,sizeof indeg);
        for(int i=1;i<=n;i++)
        {
            int tmp;
            while(cin>>tmp)
            {
                if(tmp==0) break;
                maps[i][tmp]++;
                indeg[tmp]++;
            }
        }
        topsort();
        cout<<pur[1];
        for(int i=2;i<=n;i++)
        {
            cout<<' '<<pur[i];
        }
        cout<<endl;
    }
#ifndef ONLINE_JUDGE
    system("pause");
#endif
    return 0;
}

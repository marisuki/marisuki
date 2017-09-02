# 线段树：


const int maxn = 1000100;
const int inf = 0x3f3f3f3f;
int sum[maxn<<2];
inline void pushup(int rt){
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
inline void build(int l,int r,int rt){
    if(l == r){
        sum[rt] = 0;
        return;
    }
    int m = (l + r)>>1;
    build(lson);
    build(rson);
    pushup(rt);
    return;
}
inline void update(int t,int l,int r,int rt){
    if(l == r){
        sum[rt] ++;
        return;
    }
    int m = (l + r)>>1;
    if(t <= m)update(t,lson);
    else update(t,rson);
    pushup(rt);
}
int query(int L,int R,int l,int r,int rt){
    if(L <= l&& r <= R){
        return sum[rt];
    }
    int m = (l + r)>>1;
    int ans = 0;
    if(L <= m)ans += query(L,R,lson);
    if(R > m)ans += query(L,R,rson);
    return ans;
}



//point check out
// Dynamic RMQ
// Rujia Liu
// 输入格式：
// n m    数组范围是a[1]~a[n]，初始化为0。操作有m个
// 1 p v  表示设a[p]=v
// 2 L R  查询a[L]~a[R]的min
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int maxnode = 1<<17;

int op, qL, qR, p, v;  //qL和qR为全局变量，询问区间[qL,qR];

struct IntervalTree {
  int minv[maxnode];

  void update(int o, int L, int R) {
    int M = L + (R-L)/2;
    if(L == R) minv[o] = v; // 叶结点，直接更新minv
    else {
      // 先递归更新左子树或右子树
      if(p <= M) update(o*2, L, M); else update(o*2+1, M+1, R);
      // 然后计算本结点的minv
      minv[o] = min(minv[o*2], minv[o*2+1]);
    }
  }

  int query(int o, int L, int R) {
    int M = L + (R-L)/2, ans = INF;
    if(qL <= L && R <= qR) return minv[o]; // 当前结点完全包含在查询区间内
    if(qL <= M) ans = min(ans, query(o*2, L, M)); // 往左走
    if(M < qR) ans = min(ans, query(o*2+1, M+1, R)); // 往右走
    return ans;
  }
};


IntervalTree tree;

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    memset(&tree, 0, sizeof(tree));
    while(m--) {
      scanf("%d", &op);
      if(op == 1) {
        scanf("%d%d", &p, &v);
        tree.update(1, 1, n);  // 修改树节点，或者是建树的过程
      } else {
        scanf("%d%d", &qL, &qR);  //修改询问区间
        printf("%d\n", tree.query(1, 1, n));
      }
    }
  }
  return 0;
}

// array check out

// Fast Sequence Operations I
// Rujia Liu
// 输入格式：
// n m     数组范围是a[1]~a[n]，初始化为0。操作有m个
// 1 L R v 表示设a[L]+=v, a[L+1]+v, ..., a[R]+=v
// 2 L R   查询a[L]~a[R]的sum, min和max
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxnode = 1<<17;

int <span style="color:#ff0000;">_sum</span>, _min, _max, op, qL, qR, v; //<span style="color:#ff0000;">_sum为全局变量</span>

struct IntervalTree {
  int sumv[maxnode], minv[maxnode], maxv[maxnode], addv[maxnode];

  // 维护信息
  void maintain(int o, int L, int R) {
    int lc = o*2, rc = o*2+1;
    sumv[o] = minv[o] = maxv[o] = 0;
    if(R > L) {
      sumv[o] = sumv[lc] + sumv[rc];
      minv[o] = min(minv[lc], minv[rc]);
      maxv[o] = max(maxv[lc], maxv[rc]);
    }
    if(addv[o]) { minv[o] += addv[o]; maxv[o] += addv[o]; sumv[o] += addv[o] * (R-L+1); }
  }

  void update(int o, int L, int R) {
    int lc = o*2, rc = o*2+1;
    if(qL <= L && qR >= R) { // 递归边界      
      addv[o] += v; // 累加边界的add值
    } else {
      int M = L + (R-L)/2;
      if(qL <= M) update(lc, L, M);
      if(qR > M) update(rc, M+1, R);
    }
    maintain(o, L, R); // 递归结束前重新计算本结点的附加信息
  }

  void query(int o, int L, int R, int add) {
    if(qL <= L && qR >= R) { // 递归边界：用边界区间的附加信息更新答案
      _sum += sumv[o] + add * (R-L+1);
      _min = min(_min, minv[o] + add);
      _max = max(_max, maxv[o] + add);
    } else { // 递归统计，累加参数add
      int M = L + (R-L)/2;
      if(qL <= M) query(o*2, L, M, add + addv[o]);
      if(qR > M) query(o*2+1, M+1, R, add + addv[o]);
    }
  }
};

const int INF = 1000000000;

IntervalTree tree;

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    memset(&tree, 0, sizeof(tree));
    while(m--) {
      scanf("%d%d%d", &op, &qL, &qR);
      if(op == 1) {
        scanf("%d", &v);
        tree.update(1, 1, n);
      } else {
        _sum = 0; _min = INF; _max = -INF;
        tree.query(1, 1, n, 0);
        printf("%d %d %d\n", _sum, _min, _max);
      }
    }
  }
  return 0;
}


// Fast Sequence Operations II
// Rujia Liu
// 输入格式：
// n m     数组范围是a[1]~a[n]，初始化为0。操作有m个
// 1 L R v 表示设a[L]=a[L+1]=...=a[R] = v。其中v > 0
// 2 L R  查询a[L]~a[R]的sum, min和max
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxnode = 1<<17;

int _sum, _min, _max, op, qL, qR, v;

struct IntervalTree {
  int sumv[maxnode], minv[maxnode], maxv[maxnode], setv[maxnode];

  // 维护信息
  void maintain(int o, int L, int R) {
    int lc = o*2, rc = o*2+1;
    if(R > L) {
      sumv[o] = sumv[lc] + sumv[rc];
      minv[o] = min(minv[lc], minv[rc]);
      maxv[o] = max(maxv[lc], maxv[rc]);
    }
    if(setv[o] >= 0) { minv[o] = maxv[o] = setv[o]; sumv[o] = setv[o] * (R-L+1); }
  }

  // 标记传递
  void pushdown(int o) {
    int lc = o*2, rc = o*2+1;
    if(setv[o] >= 0) { //本结点有标记才传递。注意本题中set值非负，所以-1代表没有标记
      setv[lc] = setv[rc] = setv[o];
      setv[o] = -1; // 清除本结点标记
    }
  }

  void update(int o, int L, int R) {
    int lc = o*2, rc = o*2+1;
    if(qL <= L && qR >= R) { // 标记修改
      setv[o] = v;
    } else {
      pushdown(o);
      int M = L + (R-L)/2;
      if(qL <= M) update(lc, L, M); else maintain(lc, L, M);
      if(qR > M) update(rc, M+1, R); else maintain(rc, M+1, R);
    }
    maintain(o, L, R);
  }

  void query(int o, int L, int R) {
    if(setv[o] >= 0) { // 递归边界1：有set标记
      _sum += setv[o] * (min(R,qR)-max(L,qL)+1);
      _min = min(_min, setv[o]);
      _max = max(_max, setv[o]);
    } else if(qL <= L && qR >= R) { // 递归边界2：边界区间
      _sum += sumv[o]; // 此边界区间没有被任何set操作影响
      _min = min(_min, minv[o]);
      _max = max(_max, maxv[o]);
    } else { // 递归统计
      int M = L + (R-L)/2;
      if(qL <= M) query(o*2, L, M);
      if(qR > M) query(o*2+1, M+1, R);
    }
  }
};

const int INF = 1000000000;

IntervalTree tree;

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    memset(&tree, 0, sizeof(tree));
    memset(tree.setv, -1, sizeof(tree.setv));
    tree.setv[1] = 0;
    while(m--) {
      scanf("%d%d%d", &op, &qL, &qR);
      if(op == 1) {
        scanf("%d", &v);
        tree.update(1, 1, n);
      } else {
        _sum = 0; _min = INF; _max = -INF;
        tree.query(1, 1, n);
        printf("%d %d %d\n", _sum, _min, _max);
      }
    }
  }
  return 0;
}



// */+
#include <cstdio>

typedef long long LL;

static const int maxm=100005;

LL A[maxm],pls[maxm<<2],mul[maxm<<2],tr[maxm<<2];
int left[maxm<<2],right[maxm<<2];
int n,m;
LL MOD;

int build(int id,int l,int r){
    left[id]=l;right[id]=r;mul[id]=1;
    if(l==r)return tr[id]=A[l]%MOD,0;
    int mid=(l+r)>>1;
    build(id<<1,l,mid);
    build(id<<1|1,mid+1,r);
    tr[id]=(tr[id<<1]+tr[id<<1|1])%MOD;
}

void pushdown(int id){
    int l=left[id];int r=right[id];int mid=(l+r)>>1;
    pls[id<<1]=(pls[id<<1]*mul[id]%MOD+pls[id])%MOD;
    pls[id<<1|1]=(pls[id<<1|1]*mul[id]%MOD+pls[id])%MOD;
    mul[id<<1]=(mul[id]*mul[id<<1])%MOD;
    mul[id<<1|1]=(mul[id]*mul[id<<1|1])%MOD;
    tr[id<<1]=(tr[id<<1]*mul[id]%MOD+pls[id]*(mid-l+1)%MOD)%MOD;
    tr[id<<1|1]=(tr[id<<1|1]*mul[id]%MOD+pls[id]*(r-mid)%MOD)%MOD;
    mul[id]=1;pls[id]=0;
}

void modify(int id,int l,int r,int c,int opt){
    if(left[id]>=l&&right[id]<=r){
        if(opt==1){
            mul[id]=(mul[id]*c)%MOD;
            pls[id]=(pls[id]*c)%MOD;
            tr[id]=(tr[id]*c)%MOD;
        }else if(opt==2){
            pls[id]=(pls[id]+c)%MOD;
            tr[id]=(tr[id]+(LL)c*(right[id]-left[id]+1)%MOD)%MOD;
        }
        return ;
    }
    if(right[id]<l||left[id]>r)return ;
    pushdown(id);
    modify(id<<1,l,r,c,opt);
    modify(id<<1|1,l,r,c,opt);
    tr[id]=(tr[id<<1]+tr[id<<1|1])%MOD;
}

LL Query(int id,int l,int r){
    if(left[id]>=l&&right[id]<=r)return tr[id]%MOD;
    if(left[id]>r||right[id]<l)return 0;
    pushdown(id);
    return (Query(id<<1,l,r)%MOD+Query(id<<1|1,l,r)%MOD)%MOD;
}

int main(){
    int opt,l,r,c;
    scanf("%d%lld",&n,&MOD);
    for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
    scanf("%d",&m);

    build(1,1,n);
    
    while(m--){
        scanf("%d",&opt);
        if(opt!=3){
            scanf("%d%d%d",&l,&r,&c);
            modify(1,l,r,c,opt);
        }
        else scanf("%d%d",&l,&r),printf("%lld\n",Query(1,l,r)%MOD);
    }

    return 0;
}
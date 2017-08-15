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
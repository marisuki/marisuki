// 树状数组：只有区间修改和区间查询，O（nlogn）

int C[x], data[x];
inline int lowbit(int x)
{
	return x&(-x);
}
int sum(int x)
{
	int ret=0;
	while(x>0)
	{
		ret+=C[x];
		x-=lowbit(x);
	}
	return ret;
}
void add(int x,int d)
{
	while(x<=n)
	{
		C[x]+=d;
		x+=lowbit(x);
	}
	return;
}

// RMQ:O(nlogn)建立，O(1)查询

int dp[maxn][(int)log(maxn)+5];
vector <int> data;
void RMQ_init(const vector<int>& vec)
{
	int n=vec.size();
	for(int i=0;i<n;i++) dp[i][0]=vec[i];
	for(int j=1;(1<<j)<=n;j++)
	{
		for(int i=0;i+(i<<j)-1<n;i++)
		{
			dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
		}
	}return;
}
int RMQ(int L,int R)
{
	int k=0;
	while((1<<(k+1))<=R+1-L) k++;
	return min(dp[L][k], dp[R-(1<<k)+1][k]);
}

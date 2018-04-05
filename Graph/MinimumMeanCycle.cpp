#include<cstdint>//for DBL_MAX
int dp[maxN+1][maxN+1];
double mnc(int n){
	int u,v,w;
	const int inf=0x7f7f7f7f;
	memset(dp,0x7f,sizeof(dp));
	memset(dp[0],0,sizeof(dp[0]));
	for(int i=0;i<n;++i){
		for(auto e:E){
			tie(u,v,w)=e;
			if(dp[i][u]!=inf)
			dp[i+1][v]=min(dp[i+1][v],dp[i][u]+w);
		}
		double res = DBL_MAX;
		for(int i=1;i<=n;++i){
			double val = DBL_MIN;
			for(int j=0;j<n;++j)
				val=max(val,double(dp[n][i]-dp[i][j])/(n-j));
			res=min(res,val);
		}
	}
	return res;
}
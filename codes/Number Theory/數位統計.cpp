ll d[65], dp[65][2];//up區間是不是完整
ll dfs(int p,bool is8,bool up){
	if(!p)return 1; // 回傳0是不是答案
	if(!up&&~dp[p][is8])return dp[p][is8];
	int mx = up?d[p]:9;//可以用的有那些
	ll ans=0;
	for(int i=0;i<=mx;++i){
		if( is8&&i==7 )continue;
		ans += dfs(p-1,i==8,up&&i==mx);
	}
	if(!up)dp[p][is8]=ans;
	return ans;
}
ll f(ll N){
	int k=0;
	while(N){  // 把數字先分解到陣列
		d[++k] = N%10;
		N/=10; 
	}
	return dfs(k,false,true);
}

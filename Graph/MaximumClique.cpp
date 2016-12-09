struct MaxClique{
	static const int MAXN=105;
	int N,ans;
	int g[MAXN][MAXN],dp[MAXN],stk[MAXN][MAXN];
	int sol[MAXN],tmp[MAXN];//sol[0~ans-1]為答案
	void init(int n){
		N=n;//0-base
		memset(g,0,sizeof(g));
	}
	void add_edge(int u,int v){
		g[u][v]=g[v][u]=1;
	}
	int dfs(int ns,int dep){
		if(!ns){
			if(dep>ans){
				ans=dep;
				memcpy(sol,tmp,sizeof tmp);
				return 1;
			}else return 0;
		}
		for(int i=0;i<ns;++i){
			if(dep+ns-i<=ans)return 0;
			int u=stk[dep][i],cnt=0;
			if(dep+dp[u]<=ans)return 0;
			for(int j=i+1;j<ns;++j){
				int v=stk[dep][j];
				if(g[u][v])stk[dep+1][cnt++]=v;
			}
			tmp[dep]=u;
			if(dfs(cnt,dep+1))return 1;
		}
		return 0;
	}
	int clique(){
		int u,v,ns;
		for(ans=0,u=N-1;u>=0;--u){
			for(ns=0,tmp[0]=u,v=u+1;v<N;++v)
				if(g[u][v])stk[1][ns++]=v;
			dfs(ns,1),dp[u]=ans;
		}
		return ans;
	}
};

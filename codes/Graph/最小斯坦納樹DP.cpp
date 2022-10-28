//n個點，其中r個要構成斯坦納樹
//答案在max(dp[(1<<r)-1][k]) k=0~n-1
//p表示要構成斯坦納樹的點集
//O( n^3 + n*3^r + n^2*2^r )
#define REP(i,n) for(int i=0;i<(int)n;++i)
const int MAXN=30,MAXM=8;// 0-base
const int INF=0x3f3f3f3f;
int dp[1<<MAXM][MAXN];
int g[MAXN][MAXN];//圖
void init(){memset(g,0x3f,sizeof(g));}
void add_edge(int u,int v,int w){
	g[u][v]=g[v][u]=min(g[v][u],w);
}
void steiner(int n,int r,int *p){
	REP(k,n)REP(i,n)REP(j,n)
		g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
	REP(i,n)g[i][i]=0;
	REP(i,r)REP(j,n)dp[1<<i][j]=g[p[i]][j];
	for(int i=1;i<(1<<r);++i){
		if(!(i&(i-1)))continue;
		REP(j,n)dp[i][j]=INF;
		REP(j,n){
			int tmp=INF;
			for(int s=i&(i-1);s;s=i&(s-1))
				tmp=min(tmp,dp[s][j]+dp[i^s][j]);
			REP(k,n)dp[i][k]=min(dp[i][k],g[j][k]+tmp);
		}
	}
}
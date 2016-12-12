//POJ 3123
//n個點，m個要構成生成樹的點個數 
//答案在dp[1<<m][n]
//e表示要構成生成樹的點集 
//O( n^3 + 3^m + 2^m*n^2 )
#define REP(i,n) for(int i=0;i<(int)n;++i)
const int MAXN=30;// 0-base 
const int MAXM=8;
const int INF=0x3f3f3f3f;
int dp[1<<MAXM][MAXN];
int vis[MAXN];
int d[MAXN][MAXN];//圖 
void init(){
	memset(d,0x3f,sizeof(d));
}
void add_edge(int u,int v,int w){
	d[u][v]=d[v][u]=min(d[v][u],w);
}
void steiner(int n,int m,int *e){
	REP(k,n)REP(i,n)REP(j,n)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	memset(dp,0x3f,sizeof(dp));
	REP(k,n)d[k][k]=0;
	REP(i,m)REP(j,n)dp[1<<i][j]=d[e[i]][j];
	for(int i=1;i<(1<<m);++i){
		if(!(i&(i-1)))continue;
		REP(j,n){
			dp[i][j]=INF;
			for(int k=i;k;k=(k-1)&i)
				dp[i][j]=min(dp[i][j],dp[k][j]+dp[i-k][j]);
		}
		memset(vis,0,sizeof(vis));
		REP(j,n){
			int c=-1;
			REP(k,n)if(!vis[k]&&(c==-1||dp[i][k]<dp[i][c]))c=k;
			vis[c]=true;
			REP(k,n)dp[i][c]=min(dp[i][c],dp[i][k]+d[k][c]);
		}
	}
}
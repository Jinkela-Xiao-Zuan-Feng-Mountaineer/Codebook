const int MAXN=1005,K=30;//K要夠大
const long long A=3,B=11,C=2,D=19,P=0xdefaced;
long long f[K+1][MAXN];
vector<int> g[MAXN],rg[MAXN];
int n;
inline void init(){
	for(int i=0;i<n;++i){
		f[0][i]=1;
		g[i].clear();
		rg[i].clear();
	}
}
inline void add_edge(int u,int v){
	g[u].push_back(v);
	rg[v].push_back(u);
}
inline long long point_hash(int u){//O(N) 
	for(int t=1;t<=K;++t){
		for(int i=0;i<n;++i){
			f[t][i]=f[t-1][i]*A%P;
			for(int j:g[i])f[t][i]=(f[t][i]+f[t-1][j]*B%P)%P;
			for(int j:rg[i])f[t][i]=(f[t][i]+f[t-1][j]*C%P)%P;
			if(i==u)f[t][i]+=D;//如果圖太大的話，把這行刪掉，執行一次後f[K]就會是所有點的答案 
			f[t][i]%=P;
		}
	}
	return f[K][u];
}
inline vector<long long> graph_hash(){
	vector<long long> ans;
	for(int i=0;i<n;++i)ans.push_back(point_hash(i));//O(N^2) 
	sort(ans.begin(),ans.end());
	return ans;
}
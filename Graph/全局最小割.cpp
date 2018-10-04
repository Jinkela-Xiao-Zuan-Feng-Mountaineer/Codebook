const int INF=0x3f3f3f3f;
template<typename T>
struct stoer_wagner{// 0-base
	static const int MAXN=150;
	T g[MAXN][MAXN],dis[MAXN];
	int nd[MAXN],n,s,t;
	void init(int _n){
		n=_n;
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)g[i][j]=0;
	}
	void add_edge(int u,int v,T w){
		g[u][v]=g[v][u]+=w;
	}
	T min_cut(){
		T ans=INF;
		for(int i=0;i<n;++i)nd[i]=i;
		for(int ind,tn=n;tn>1;--tn){
			for(int i=1;i<tn;++i)dis[nd[i]]=0;
			for(int i=1;i<tn;++i){
				ind=i;
				for(int j=i;j<tn;++j){
					dis[nd[j]]+=g[nd[i-1]][nd[j]];
					if(dis[nd[ind]]<dis[nd[j]])ind=j;
				}
				swap(nd[ind],nd[i]);
			}
			if(ans>dis[nd[ind]])
				ans=dis[t=nd[ind]],s=nd[ind-1];
			for(int i=0;i<tn;++i)
				g[nd[ind-1]][nd[i]]=g[nd[i]][nd[ind-1]]+=g[nd[i]][nd[ind]];
		}
		return ans;
	}
};
template<typename T>
struct ISAP{
	static const int MAXN=105;
	static const T INF=INT_MAX;
	int n;//點數 
	int d[MAXN],gap[MAXN],cur[MAXN];
	struct edge{
		int v,pre;
		T cap,r;
		edge(int v,int pre,T cap):v(v),pre(pre),cap(cap),r(cap){}
	};
	int g[MAXN];
	vector<edge> e;
	void init(int _n){
		memset(g,-1,sizeof(int)*((n=_n)+1));
		e.clear();
	}
	void add_edge(int u,int v,T cap,bool directed=false){
		e.push_back(edge(v,g[u],cap));
		g[u]=e.size()-1;
		e.push_back(edge(u,g[v],directed?0:cap));
		g[v]=e.size()-1;
	}
	T dfs(int u,int s,int t,T CF=INF){
		if(u==t)return CF;
		T tf=CF,df;
		for(int &i=cur[u];~i;i=e[i].pre){
			if(e[i].r&&d[u]==d[e[i].v]+1){
				df=dfs(e[i].v,s,t,min(tf,e[i].r));
				e[i].r-=df;
				e[i^1].r+=df;
				if(!(tf-=df)||d[s]==n)return CF-tf;
			}
		}
		int mh=n;
		for(int i=cur[u]=g[u];~i;i=e[i].pre){
			if(e[i].r&&d[e[i].v]<mh)mh=d[e[i].v];
		}
		if(!--gap[d[u]])d[s]=n;
		else ++gap[d[u]=++mh];
		return CF-tf;
	}
	T isap(int s,int t,bool clean=true){
		memset(d,0,sizeof(int)*(n+1));
		memset(gap,0,sizeof(int)*(n+1));
		memcpy(cur,g,sizeof(int)*(n+1));
		if(clean) for(size_t i=0;i<e.size();++i)
			e[i].r=e[i].cap;
		T MF=0;
		for(gap[0]=n;d[s]<n;)MF+=dfs(s,s,t);
		return MF;
	}
	vector<int> cut_e;//最小割邊集
	bool vis[MAXN];
	void dfs_cut(int u){
		vis[u]=1;//表示u屬於source的最小割集 
		for(int i=g[u];~i;i=e[i].pre)
			if(e[i].r>0&&!vis[e[i].v])dfs_cut(e[i].v);
	}
	T min_cut(int s,int t){
		T ans=isap(s,t);
		memset(vis,0,sizeof(bool)*(n+1));
		dfs_cut(s), cut_e.clear();
		for(int u=0;u<=n;++u)if(vis[u])
			for(int i=g[u];~i;i=e[i].pre)
				if(!vis[e[i].v])cut_e.push_back(i);
		return ans;
	}
};
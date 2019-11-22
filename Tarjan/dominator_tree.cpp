struct dominator_tree{
	static const int MAXN=5005;
	int n;// 1-base
	vector<int> G[MAXN], rG[MAXN];
	int pa[MAXN], dfn[MAXN], id[MAXN], dfnCnt;
	int semi[MAXN], idom[MAXN], best[MAXN];
	vector<int> tree[MAXN]; // tree here
	void init(int _n){
		n = _n;
		for(int i=1; i<=n; ++i)
			G[i].clear(), rG[i].clear();
	}
	void add_edge(int u, int v){
		G[u].push_back(v);
		rG[v].push_back(u);
	}
	void dfs(int u){
		id[dfn[u]=++dfnCnt]=u;
		for(auto v:G[u]) if(!dfn[v])
			dfs(v),pa[dfn[v]]=dfn[u];
	}
	int find(int y,int x){
		if(y <= x) return y;
		int tmp = find(pa[y],x);
		if(semi[best[y]] > semi[best[pa[y]]])
			best[y] = best[pa[y]];
		return pa[y] = tmp;
	}
	void tarjan(int root){
		dfnCnt = 0;
		for(int i=1; i<=n; ++i){
			dfn[i] = idom[i] = 0;
			tree[i].clear();
			best[i] = semi[i] = i;
		}
		dfs(root);
		for(int i=dfnCnt; i>1; --i){
			int u = id[i];
			for(auto v:rG[u]) if(v=dfn[v]){
				find(v,i);
				semi[i]=min(semi[i],semi[best[v]]);
			}
			tree[semi[i]].push_back(i);
			for(auto v:tree[pa[i]]){
				find(v, pa[i]);
				idom[v] = semi[best[v]]==pa[i]
						? pa[i] : best[v];
			}
			tree[pa[i]].clear();
		}
		for(int i=2; i<=dfnCnt; ++i){
			if(idom[i] != semi[i])
				idom[i] = idom[idom[i]];
			tree[id[idom[i]]].push_back(id[i]);
		}
	}
}dom;
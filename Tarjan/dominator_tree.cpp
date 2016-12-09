struct dominator_tree{
	static const int MAXN=5005;
	int n;// 1-base
	vector<int> suc[MAXN],pre[MAXN];//存圖和反向圖 
	int fa[MAXN],dfn[MAXN],id[MAXN],Time;//for dfs
	int semi[MAXN],idom[MAXN];
	int anc[MAXN],best[MAXN];//disjoint set 
	vector<int> dom[MAXN];//dominator_tree存這裡 
	void init(int _n){
		n=_n;
		for(int i=1;i<=n;++i)suc[i].clear(),pre[i].clear();
	}
	void add_edge(int u,int v){
		suc[u].push_back(v);
		pre[v].push_back(u);
	}
	void dfs(int u){
		dfn[u]=++Time,id[Time]=u;
		for(auto v:suc[u]){
			if(dfn[v])continue;
			dfs(v),fa[dfn[v]]=dfn[u];
		}
	}
	int find(int x){
		if(x==anc[x])return x;
		int y=find(anc[x]);
		if(semi[best[x]]>semi[best[anc[x]]])best[x]=best[anc[x]];
		return anc[x]=y;
	}
	void tarjan(int r){
		Time=0;
		for(int t=1;t<=n;++t){
			dfn[t]=idom[t]=0;//u=r或是u無法到達r時idom[id[u]]=0 
			dom[t].clear();
			anc[t]=best[t]=semi[t]=t;
		}
		dfs(r);
		for(int y=Time;y>=2;--y){
			int x=fa[y],idy=id[y];
			for(auto z:pre[idy]){
				if(!(z=dfn[z]))continue;
				find(z);
				semi[y]=min(semi[y],semi[best[z]]);
			}
			dom[semi[y]].push_back(y);
			anc[y]=x;
			for(auto z:dom[x]){
				find(z);
				idom[z]=semi[best[z]]<x?best[z]:x;
			}
			dom[x].clear();
		}
		for(int u=2;u<=Time;++u){
			if(idom[u]!=semi[u])idom[u]=idom[idom[u]];
			dom[id[idom[u]]].push_back(id[u]);
		}
	}
}dom;

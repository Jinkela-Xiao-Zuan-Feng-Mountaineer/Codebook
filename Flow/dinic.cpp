template<typename T>
struct DINIC{
	static const int MAXN=105;
	static const T INF=INT_MAX;
	int n, LV[MAXN], cur[MAXN];
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
	int bfs(int s,int t){
		memset(LV,0,sizeof(int)*(n+1));
		memcpy(cur,g,sizeof(int)*(n+1));
		queue<int> q;
		q.push(s);
		LV[s]=1;
		while(q.size()){
			int u=q.front();q.pop();
			for(int i=g[u];~i;i=e[i].pre){
				if(!LV[e[i].v]&&e[i].r){
					LV[e[i].v]=LV[u]+1;
					q.push(e[i].v);
					if(e[i].v==t)return 1;
				}
			}
		}
		return 0;
	}
	T dfs(int u,int t,T CF=INF){
		if(u==t)return CF;
		T df;
		for(int &i=cur[u];~i;i=e[i].pre){
			if(LV[e[i].v]==LV[u]+1&&e[i].r){
				if(df=dfs(e[i].v,t,min(CF,e[i].r))){
					e[i].r-=df;
					e[i^1].r+=df;
					return df;
				}
			}
		}
		return LV[u]=0;
	}
	T dinic(int s,int t,bool clean=true){
		if(clean)for(size_t i=0;i<e.size();++i)
			e[i].r=e[i].cap;
		T ans=0, f=0;
		while(bfs(s,t))while(f=dfs(s,t))ans+=f;
		return ans;
	}
};
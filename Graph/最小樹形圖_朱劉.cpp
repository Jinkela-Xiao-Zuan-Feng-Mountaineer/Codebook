#define INF 0x3f3f3f3f
template<typename T>
struct zhu_liu{
	static const int MAXN=110;
	struct edge{
		int u,v;
		T w;
		edge(int u=0,int v=0,T w=0):u(u),v(v),w(w){}
	};
	vector<edge>E;// 0-base
	int pe[MAXN],id[MAXN],vis[MAXN];
	T in[MAXN];
	void init(){E.clear();}
	void add_edge(int u,int v,T w){
		if(u!=v)E.push_back(edge(u,v,w));
	}
	T build(int root,int n){
		T ans=0;int N=n;
		for(;;){
			for(int u=0;u<n;++u)in[u]=INF;
			for(size_t i=0;i<E.size();++i)
			if(E[i].u!=E[i].v&&E[i].w<in[E[i].v])
					pe[E[i].v]=i,in[E[i].v]=E[i].w;
			for(int u=0;u<n;++u)//無解
				if(u!=root&&in[u]==INF)return -INF;
			int cntnode=0;
			memset(id,-1,sizeof(int)*N);
			memset(vis,-1,sizeof(int)*N);
			for(int u=0;u<n;++u){
				if(u!=root)ans+=in[u];
				int v=u;
				for(;vis[v]!=u&&id[v]==-1&&v!=root;v=E[pe[v]].u)
					vis[v]=u;
				if(v!=root&&id[v]==-1){
					for(int x=E[pe[v]].u;x!=v;x=E[pe[x]].u)
						id[x]=cntnode;
					id[v]=cntnode++;
				}
			}
			if(!cntnode)break;//無環
			for(int u=0;u<n;++u)if(id[u]==-1)id[u]=cntnode++;
			for(size_t i=0;i<E.size();++i){
				int v=E[i].v;
				E[i].u=id[E[i].u];
				E[i].v=id[E[i].v];
				if(E[i].u!=E[i].v)E[i].w-=in[v];
			}
			n=cntnode;
			root=id[root];
		}
		return ans;
	}
};
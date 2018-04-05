template<typename _T>
struct MCMF{
	static const int MAXN=440;
	static const _T INF=999999999;
	struct edge{
		int v,pre;
		_T cap,cost;
		edge(int v,int pre,_T cap,_T cost):v(v),pre(pre),cap(cap),cost(cost){}
	};
	int n,S,T;
	_T dis[MAXN],piS,ans;
	bool vis[MAXN];
	vector<edge> e;
	int g[MAXN];
	void init(int _n){
		memset(g,-1,sizeof(int)*((n=_n)+1));
		e.clear();
	}
	void add_edge(int u,int v,_T cap,_T cost,bool directed=false){
		e.push_back(edge(v,g[u],cap,cost));
		g[u]=e.size()-1;
		e.push_back(edge(u,g[v],directed?0:cap,-cost));
		g[v]=e.size()-1;
	}
	_T augment(int u,_T cur_flow){
		if(u==T||!cur_flow)return ans+=piS*cur_flow,cur_flow;
		vis[u]=1;
		_T r=cur_flow,d;
		for(int i=g[u];~i;i=e[i].pre){
			if(e[i].cap&&!e[i].cost&&!vis[e[i].v]){
				d=augment(e[i].v,min(r,e[i].cap));
				e[i].cap-=d;
				e[i^1].cap+=d;
				if(!(r-=d))break;
			}
		}
		return cur_flow-r;
	}
	bool modlabel(){
		for(int u=0;u<=n;++u)dis[u]=INF;
		static deque<int>q;
		dis[T]=0,q.push_back(T);
		while(q.size()){
			int u=q.front();q.pop_front();
			_T dt;
			for(int i=g[u];~i;i=e[i].pre){
				if(e[i^1].cap&&(dt=dis[u]-e[i].cost)<dis[e[i].v]){
					if((dis[e[i].v]=dt)<=dis[q.size()?q.front():S]){
						q.push_front(e[i].v);
					}else q.push_back(e[i].v);
				}
			}
		}
		for(int u=0;u<=n;++u)
			for(int i=g[u];~i;i=e[i].pre)
				e[i].cost+=dis[e[i].v]-dis[u];
		return piS+=dis[S], dis[S]<INF;
	}
	_T mincost(int s,int t){
		S=s,T=t;
		piS=ans=0;
		while(modlabel()){
			do memset(vis,0,sizeof(bool)*(n+1));
			while(augment(S,INF));
		}return ans;
	}
};

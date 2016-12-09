#define MAXN 440
#define INF 999999999
struct edge{
	int v,pre;
	int cap,cost;
	edge(int v,int pre,int cap,int cost):v(v),pre(pre),cap(cap),cost(cost){}
};
int n,S,T;
int dis[MAXN],piS,ans;
bool vis[MAXN];
std::vector<edge> e;
int g[MAXN];
inline void init(){
	memset(g,-1,sizeof(int)*n);
	e.clear();
}
inline void add_edge(int u,int v,int cost,int cap,bool directed=false){
	e.push_back(edge(v,g[u],cap,cost));
	g[u]=e.size()-1;
	e.push_back(edge(u,g[v],directed?0:cap,-cost));
	g[v]=e.size()-1;
}
int augment(int u,int cur_flow){
	if(u==T||!cur_flow)return ans+=piS*cur_flow,cur_flow;
	vis[u]=1;
	int r=cur_flow,d;
	for(int i=g[u];~i;i=e[i].pre){
		if(e[i].cap&&!e[i].cost&&!vis[e[i].v]){
			d=augment(e[i].v,std::min(r,e[i].cap));
			e[i].cap-=d;
			e[i^1].cap+=d;
			if(!(r-=d))break;
		}
	}
	return cur_flow-r;
}
inline bool modlabel(){
	for(int i=0;i<n;++i)dis[i]=INF;
	dis[T]=0;
	static std::deque<int>q;
	q.push_back(T);
	while(q.size()){
		int u=q.front();
		q.pop_front();
		int dt;
		for(int i=g[u];~i;i=e[i].pre){
			if(e[i^1].cap&&(dt=dis[u]-e[i].cost)<dis[e[i].v]){
				if((dis[e[i].v]=dt)<=dis[q.size()?q.front():S]){
					q.push_front(e[i].v);
				}else q.push_back(e[i].v);
			}
		}
	}
	for(int u=0;u<n;++u){
		for(int i=g[u];~i;i=e[i].pre){
			e[i].cost+=dis[e[i].v]-dis[u];
		}
	}
	piS+=dis[S];
	return dis[S]<INF;
}
inline int mincost(){
	piS=ans=0;
	while(modlabel()){
		do memset(vis,0,sizeof(bool)*n);
		while(augment(S,INF));
	}
	return ans;
}

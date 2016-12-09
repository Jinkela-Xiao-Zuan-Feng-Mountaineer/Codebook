#define MAXN 105
#define INF INT_MAX
int n;/*number of nodes*/
int level[MAXN],cur[MAXN];/*layer, current arc*/
struct edge{
	int v,pre;
	long long cap,flow,r;
	edge(int v,int pre,long long cap):v(v),pre(pre),cap(cap),flow(0),r(cap){}
};
int g[MAXN];
std::vector<edge> e;
inline void init(){
	memset(g,-1,sizeof(int)*(n+1));
	e.clear();
}
inline void add_edge(int u,int v,long long cap,bool directed=false){
	e.push_back(edge(v,g[u],cap));
	g[u]=e.size()-1;
	e.push_back(edge(u,g[v],directed?0:cap));
	g[v]=e.size()-1;
}
inline int bfs(int s,int t){
	memset(level,0,sizeof(int)*(n+1));
	memcpy(cur,g,sizeof(int)*(n+1));
	std::queue<int >q;
	q.push(s);
	level[s]=1;
	while(q.size()){
		int u=q.front();q.pop();
		for(int i=g[u];~i;i=e[i].pre){
			if(!level[e[i].v]&&e[i].r){
				level[e[i].v]=level[u]+1;
				q.push(e[i].v);
				if(e[i].v==t)return 1;
			}
		}
	}
	return 0;
}
long long dfs(int u,int t,long long cur_flow=INF){
	if(u==t||!cur_flow)return cur_flow;
	long long df,tf=0;
	for(int &i=cur[u];~i;i=e[i].pre){
		if(level[e[i].v]==level[u]+1&&e[i].r){
			if(df=dfs(e[i].v,t,std::min(cur_flow,e[i].r))){
				e[i].flow+=df;
				e[i^1].flow-=df;
				e[i].r-=df;
				e[i^1].r+=df;
				tf+=df;
				if(!(cur_flow-=df))break;
			}
		}
	}
	if(!df)level[u]=0;
	return tf;
}
inline long long dinic(int s,int t,bool clean=true){
	if(clean){
		for(size_t i=0;i<e.size();++i){
			e[i].flow=0;
			e[i].r=e[i].cap;
		}
	}
	long long ans=0;
	while(bfs(s,t))ans+=dfs(s,t);
	return ans;
}

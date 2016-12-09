#define MAXN 105
#define INF INT_MAX
int n;/*點數*/
int d[MAXN],gap[MAXN],cur[MAXN];
/*層次、gap[i]=層次為i的點之個數、當前弧優化*/ 
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
long long dfs(int u,int s,int t,long long cur_flow=INF){
	if(u==t)return cur_flow;
	long long tf=cur_flow,df;
	for(int &i=cur[u];~i;i=e[i].pre){
		if(e[i].r&&d[u]==d[e[i].v]+1){
			df=dfs(e[i].v,s,t,std::min(tf,e[i].r));
			e[i].flow+=df;
			e[i^1].flow-=df;
			e[i].r-=df;
			e[i^1].r+=df;
			if(!(tf-=df)||d[s]==n)return cur_flow-tf;
		}
	}
	int minh=n;
	for(int i=cur[u]=g[u];~i;i=e[i].pre){
		if(e[i].r&&d[e[i].v]<minh)minh=d[e[i].v];
	}
	if(!--gap[d[u]])d[s]=n;
	else ++gap[d[u]=++minh];
	return cur_flow-tf;
}
inline long long isap(int s,int t,bool clean=true){
	memset(d,0,sizeof(int)*(n+1));
	memset(gap,0,sizeof(int)*(n+1));
	memcpy(cur,g,sizeof(int)*(n+1));
	if(clean){
		for(size_t i=0;i<e.size();++i){
			e[i].flow=0;
			e[i].r=e[i].cap;
		}
	}
	long long max_flow=0;
	for(gap[0]=n;d[s]<n;)max_flow+=dfs(s,s,t);
	return max_flow;
}

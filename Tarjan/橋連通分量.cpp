#define N 1005
struct edge{
	int u,v;
	bool is_bridge;
	edge(int u=0,int v=0):u(u),v(v),is_bridge(0){}
};
vector<edge> E;
vector<int> G[N];// 1-base
int low[N],vis[N],Time;
int bcc_id[N],bridge_cnt,bcc_cnt;// 1-base
int st[N],top;//BCC用 
inline void add_edge(int u,int v){
	G[u].push_back(E.size());
	E.push_back(edge(u,v));
	G[v].push_back(E.size());
	E.push_back(edge(v,u));
}
void dfs(int u,int re=-1){//u當前點，re為u連接前一個點的邊 
	int v;
	low[u]=vis[u]=++Time;
	st[top++]=u;
	for(size_t i=0;i<G[u].size();++i){
		int e=G[u][i];v=E[e].v;
		if(!vis[v]){
			dfs(v,e^1);//e^1反向邊 
			low[u]=min(low[u],low[v]);
			if(vis[u]<low[v]){
				E[e].is_bridge=E[e^1].is_bridge=1;
				++bridge_cnt;
			}
		}else if(vis[v]<vis[u]&&e!=re)
			low[u]=min(low[u],vis[v]);
	}
	if(vis[u]==low[u]){//處理BCC
		++bcc_cnt;// 1-base
		do bcc_id[v=st[--top]]=bcc_cnt;//每個點所在的BCC
		while(v!=u);
	}
}
inline void bcc_init(int n){
	Time=bcc_cnt=bridge_cnt=top=0;
	E.clear();
	for(int i=1;i<=n;++i){
		G[i].clear();
		vis[i]=bcc_id[i]=0;
	}
}
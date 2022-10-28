#define MAXN1 1005
#define MAXN2 505
int n1,n2;
//n1個點連向n2個點，其中n2個點可以匹配很多邊 
vector<int> g[MAXN1];//圖 0-base
size_t c[MAXN2];
//每個屬於n2點最多可以接受幾條匹配邊 
vector<int> matchs[MAXN2];
//每個屬於n2的點匹配了那些點 
bool vis[MAXN2];
bool dfs(int u){
	for(int v:g[u]){
		if(vis[v])continue;
		vis[v] = 1;
		if(matchs[v].size()<c[v]){
			return matchs[v].push_back(u), 1;
		}else for(size_t j=0;j<matchs[v].size();++j){
			if(dfs(matchs[v][j]))
				return matchs[v][j]=u, 1;
		}
	}
	return 0;
}
int max_match(){
	for(int i=0;i<n2;++i) matchs[i].clear();
	int cnt=0;
	for(int u=0;u<n1;++u){
		memset(vis,0,sizeof(bool)*n2);
		if(dfs(u))++cnt;
	}
	return cnt;
}
#define MAXN1 505
#define MAXN2 505
int n1,n2;//n1個點連向n2個點
int match[MAXN2];//屬於n2的點匹配了哪個點
vector<int > g[MAXN1];//圖 0-base
bool vis[MAXN2];//是否走訪過
bool dfs(int u){
	for(int v:g[u]){
		if(vis[v]) continue;
		vis[v]=1;
		if(match[v]==-1||dfs(match[v]))
			return match[v]=u, 1;
	}
	return 0;
}
int max_match(){
	int ans=0;
	memset(match,-1,sizeof(int)*n2);
	for(int i=0;i<n1;++i){
		memset(vis,0,sizeof(bool)*n2);
		if(dfs(i)) ++ans;
	}
	return ans;
}
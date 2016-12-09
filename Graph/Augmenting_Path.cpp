#define MAXN1 505
#define MAXN2 505
int n1,n2;/*n1個點連向n2個點*/ 
int match[MAXN2];/*每個屬於n2的點匹配了哪個點*/
vector<int > g[MAXN1];/*圖*/
bool vis[MAXN2];/*是否走訪過*/ 
bool dfs(int u){
	for(size_t i=0;i<g[u].size();++i){
		int v=g[u][i];
		if(vis[v])continue;
		vis[v]=1;
		if(match[v]==-1||dfs(match[v])){
			match[v]=u;
			return 1;
		}
	}
	return 0;
}
inline int max_match(){
	int ans=0;
	memset(match,-1,sizeof(int)*n2);
	for(int i=0;i<n1;++i){
		memset(vis,0,sizeof(bool)*n2);
		if(dfs(i))++ans;
	}
	return ans;
}
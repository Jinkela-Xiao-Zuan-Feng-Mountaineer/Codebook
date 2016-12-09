#define MAXN1 1005
#define MAXN2 505
int n1,n2;//n1個點連向n2個點，其中n2個點可以匹配很多邊 
vector<int > g[MAXN1];//圖 
int c[MAXN2];//每個屬於n2點最多可以接受幾條匹配邊 
vector<int> match_list[MAXN2];//每個屬於n2的點匹配了那些點 
bool vis[MAXN2];//是否走訪過 
bool dfs(int u){
	for(size_t i=0;i<g[u].size();++i){
		int v=g[u][i];
		if(vis[v])continue;
		vis[v]=true;
		if((int)match_list[v].size()<c[v]){
			match_list[v].push_back(u);
			return true;
		}else{
			for(size_t j=0;j<match_list[v].size();++j){
				int next_u=match_list[v][j];
				if(dfs(next_u)){
					match_list[v][j]=u;
					return true;
				}
			}
		}
	}
	return false;
}
inline int max_match(){
	for(int i=0;i<n2;++i)match_list[i].clear();
	int cnt=0;
	for(int u=0;u<n1;++u){
		memset(vis,0,sizeof(bool)*n2);
		if(dfs(u))++cnt;
	}
	return cnt;
}
#define N 1005
vector<int> G[N];// 1-base
vector<int> bcc[N];//存每塊雙連通分量的點
int low[N],vis[N],Time;
int bcc_id[N],bcc_cnt;// 1-base
bool is_cut[N];//是否為割點，割點的bcc_id沒意義
int st[N],top;
void dfs(int u,int pa=-1){//u當前點，pa父親 
	int v,child=0;
	low[u]=vis[u]=++Time;
	st[top++]=u;
	for(size_t i=0;i<G[u].size();++i){
		if(!vis[v=G[u][i]]){
			dfs(v,u),++child;
			low[u]=min(low[u],low[v]);
			if(vis[u]<=low[v]){
				is_cut[u]=1;
				bcc[++bcc_cnt].clear();
				int t;
				do{
					bcc_id[t=st[--top]]=bcc_cnt;
					bcc[bcc_cnt].push_back(t);
				}while(t!=v);
				bcc_id[u]=bcc_cnt;
				bcc[bcc_cnt].push_back(u);
			}
		}else if(vis[v]<vis[u]&&v!=pa)//反向邊 
			low[u]=min(low[u],vis[v]);
	}
	if(pa==-1&&child<2)is_cut[u]=0;//u是dfs樹的根要特判
}
inline void bcc_init(int n){
	Time=bcc_cnt=top=0;
	for(int i=1;i<=n;++i){
		G[i].clear();
		is_cut[i]=vis[i]=bcc_id[i]=0;
	}
}
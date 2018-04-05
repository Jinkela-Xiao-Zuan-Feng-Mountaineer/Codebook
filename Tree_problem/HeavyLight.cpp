#include<vector>
#define MAXN 100005
int siz[MAXN],max_son[MAXN],pa[MAXN],dep[MAXN];
int link_top[MAXN],link[MAXN],cnt;
vector<int> G[MAXN];
void find_max_son(int u){
	siz[u]=1;
	max_son[u]=-1;
	for(auto v:G[u]){
		if(v==pa[u])continue;
		pa[v]=u;
		dep[v]=dep[u]+1;
		find_max_son(v);
		if(max_son[u]==-1||siz[v]>siz[max_son[u]])max_son[u]=v;
		siz[u]+=siz[v];
	}
}
void build_link(int u,int top){
	link[u]=++cnt;
	link_top[u]=top;
	if(max_son[u]==-1)return;
	build_link(max_son[u],top);
	for(auto v:G[u]){
		if(v==max_son[u]||v==pa[u])continue;
		build_link(v,v);
	}
}
int find_lca(int a,int b){
	//求LCA，可以在過程中對區間進行處理
	int ta=link_top[a],tb=link_top[b];
	while(ta!=tb){
		if(dep[ta]<dep[tb]){ 
			swap(ta,tb);
			swap(a,b);
		}
		//這裡可以對a所在的鏈做區間處理  
		//區間為(link[ta],link[a]) 
		ta=link_top[a=pa[ta]];
	}
	//最後a,b會在同一條鏈，若a!=b還要在進行一次區間處理
	return dep[a]<dep[b]?a:b;
}

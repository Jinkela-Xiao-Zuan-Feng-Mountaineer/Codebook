#include<vector>
#define MAXN 100005
typedef std::vector<int >::iterator VIT;
int siz[MAXN],max_son[MAXN],pa[MAXN],dep[MAXN];
/*節點大小、大小最大的孩子、父母節點、深度*/
int link_top[MAXN],link[MAXN],cnt;
/*每個點所在鍊的鏈頭、樹鏈剖分的DFS序、時間戳*/ 
std::vector<int >G[MAXN];/*用vector存樹*/ 
void find_max_son(int x){
	siz[x]=1;
	max_son[x]=-1;
	for(VIT i=G[x].begin();i!=G[x].end();++i){
		if(*i==pa[x])continue;
		pa[*i]=x;
		dep[*i]=dep[x]+1;
		find_max_son(*i);
		if(max_son[x]==-1||siz[*i]>siz[max_son[x]])max_son[x]=*i;
		siz[x]+=siz[*i];
	}
}
void build_link(int x,int top){
	link[x]=++cnt;/*記錄x點的時間戳*/
	link_top[x]=top;
	if(max_son[x]==-1)return;
	build_link(max_son[x],top);/*優先走訪最大孩子*/ 
	for(VIT i=G[x].begin();i!=G[x].end();++i){
		if(*i==max_son[x]||*i==pa[x])continue;
		build_link(*i,*i);
	}
}
inline int find_lca(int a,int b){
	/*求LCA，可以在過程中對區間進行處理*/ 
	int ta=link_top[a],tb=link_top[b];
	while(ta!=tb){
		if(dep[ta]<dep[tb]){ 
			std::swap(ta,tb);
			std::swap(a,b);
		}
		//這裡可以對a所在的鏈做區間處理  
		//區間為(link[ta],link[a]) 
		ta=link_top[a=pa[ta]];
	}
	/*最後a,b會在同一條鏈，若a!=b還要在進行一次區間處理*/ 
	return dep[a]<dep[b]?a:b;
}

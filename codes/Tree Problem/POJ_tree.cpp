#include<bits/stdc++.h>
using namespace std;
#define MAXN 10005
int n,k;
vector<pair<int,int> >g[MAXN];
int size[MAXN];
bool vis[MAXN];
inline void init(){
	for(int i=0;i<=n;++i){
		g[i].clear();
		vis[i]=0;
	}
}
void get_dis(vector<int> &dis,int u,int pa,int d){
	dis.push_back(d);
	for(size_t i=0;i<g[u].size();++i){
		int v=g[u][i].first,w=g[u][i].second;
		if(v!=pa&&!vis[v])get_dis(dis,v,u,d+w);
	}
}
vector<int> dis;//這東西如果放在函數裡會TLE 
int cal(int u,int d){
	dis.clear();
	get_dis(dis,u,-1,d);
	sort(dis.begin(),dis.end());
	int l=0,r=dis.size()-1,res=0;
	while(l<r){
		while(l<r&&dis[l]+dis[r]>k)--r;
		res+=r-(l++);
	}
	return res;
}
pair<int,int> tree_centroid(int u,int pa,const int sz){
	size[u]=1;//找樹重心，second是重心
	pair<int,int> res(INT_MAX,-1);
	int ma=0;
	for(size_t i=0;i<g[u].size();++i){
		int v=g[u][i].first;
		if(v==pa||vis[v])continue;
		res=min(res,tree_centroid(v,u,sz));
		size[u]+=size[v];
		ma=max(ma,size[v]);
	}
	ma=max(ma,sz-size[u]);
	return min(res,make_pair(ma,u));
}
int tree_DC(int u,int sz){
	int center=tree_centroid(u,-1,sz).second;
	int ans=cal(center,0);
	vis[center]=1;
	for(size_t i=0;i<g[center].size();++i){
		int v=g[center][i].first,w=g[center][i].second;
		if(vis[v])continue;
		ans-=cal(v,w);
		ans+=tree_DC(v,size[v]);
	}
	return ans;
}
int main(){
	while(scanf("%d%d",&n,&k),n||k){
		init();
		for(int i=1;i<n;++i){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			g[u].push_back(make_pair(v,w));
			g[v].push_back(make_pair(u,w));
		}
		printf("%d\n",tree_DC(1,n));
	}
	return 0;
}

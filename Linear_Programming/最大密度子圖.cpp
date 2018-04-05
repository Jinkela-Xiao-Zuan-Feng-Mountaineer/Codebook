typedef double T;//POJ 3155 
const int MAXN=105;
struct edge{
	int u,v;
	T w;
	edge(int u=0,int v=0,T w=0):u(u),v(v),w(w){}
};
vector<edge> E;
int n,m;// 1-base
T de[MAXN],pv[MAXN];//每個點的邊權和和點權(有些題目會給) 
void init(){
	E.clear();
	for(int i=1;i<=n;++i)de[i]=pv[i]=0;
}
void add_edge(int u,int v,T w){
	E.push_back(edge(u,v,w));
	de[u]+=w,de[v]+=w;
}
T U;//二分搜的最大值 
void get_U(){
	U=0;
	for(int i=1;i<=n;++i)U+=2*pv[i];
	for(size_t i=0;i<E.size();++i)U+=E[i].w;
}
ISAP<T> isap;//網路流 
int s,t;//原匯點 
void build(T L){
	isap.init(n+2);
	for(size_t i=0;i<E.size();++i){
		isap.add_edge(E[i].u,E[i].v,E[i].w);
	}
	for(int v=1;v<=n;++v){
		isap.add_edge(s,v,U);
		isap.add_edge(v,t,U+2*L-de[v]-2*pv[v]);
	}
}
int main(){
	while(~scanf("%d%d",&n,&m)){
		if(!m){
			puts("1\n1");
			continue;
		}
		init();
		int u,v;
		for(int i=0;i<m;++i){
			scanf("%d%d",&u,&v);
			add_edge(u,v,1);
		}
		get_U();
		s=n+1,t=n+2;
		T l=0,r=U,k=1.0/(n*n);
		while(r-l>k){//二分搜最大值
			T mid=(l+r)/2;
			build(mid);
			T res=(U*n-isap.isap(s,t))/2;
			if(res>0)l=mid;
			else r=mid;
		}
		build(l);
		isap.min_cut(s,t);
		vector<int> ans;
		for(int i=1;i<=n;++i)
			if(isap.vis[i])ans.push_back(i);
		printf("%d\n",ans.size());
		for(size_t i=0;i<ans.size();++i)
			printf("%d\n",ans[i]);
	}
	return 0;
}
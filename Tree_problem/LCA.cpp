const int MAXN=100000; // 1-base
const int MLG=17; //log2(MAXN)+1;
int pa[MLG+1][MAXN+5];
int dep[MAXN+5];
vector<int> G[MAXN+5];
void dfs(int x,int p=0){//dfs(root);
	pa[0][x]=p;
	for(int i=0;i<=MLG;++i)
		pa[i+1][x]=pa[i][pa[i][x]];
	for(auto &i:G[x]){
		if(i==p)continue;
		dep[i]=dep[x]+1;
		dfs(i,x);
	}
}
inline int jump(int x,int d){
	for(int i=0;i<=MLG;++i)
		if((d>>i)&1) x=pa[i][x];
	return x;
}
inline int find_lca(int a,int b){
	if(dep[a]>dep[b])swap(a,b);
	b=jump(b,dep[b]-dep[a]);
	if(a==b)return a;
	for(int i=MLG;i>=0;--i){
		if(pa[i][a]!=pa[i][b]){
			a=pa[i][a];
			b=pa[i][b];
		}
	}
	return pa[0][a];
}

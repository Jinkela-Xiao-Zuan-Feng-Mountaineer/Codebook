#define MAXN 505
vector<int>g[MAXN];
int pa[MAXN],match[MAXN],st[MAXN],S[MAXN],v[MAXN];
int t,n;
inline int lca(int x,int y){
	for(++t;;swap(x,y)){
		if(x==0)continue;
		if(v[x]==t)return x;
		v[x]=t;
		x=st[pa[match[x]]];
	}
}
#define qpush(x) q.push(x),S[x]=0
inline void flower(int x,int y,int l,queue<int> &q){
	while(st[x]!=l){
		pa[x]=y;
		if(S[y=match[x]]==1)qpush(y);
		st[x]=st[y]=l,x=pa[y];
	}
}
inline bool bfs(int x){
	for(int i=1;i<=n;++i)st[i]=i;
	memset(S+1,-1,sizeof(int)*n);
	queue<int>q;qpush(x);
	while(q.size()){
		x=q.front(),q.pop();
		for(size_t i=0;i<g[x].size();++i){
			int y=g[x][i];
			if(S[y]==-1){
				pa[y]=x,S[y]=1;
				if(!match[y]){
					for(int lst;x;y=lst,x=pa[y])
						lst=match[x],match[x]=y,match[y]=x;
					return 1;
				}
				qpush(match[y]);
			}else if(!S[y]&&st[y]!=st[x]){
				int l=lca(y,x);
				flower(y,x,l,q),flower(x,y,l,q);
			}
		}
	}
	return 0;
}
inline int blossom(){
	int ans=0;
	for(int i=1;i<=n;++i)
		if(!match[i]&&bfs(i))++ans;
	return ans;
}

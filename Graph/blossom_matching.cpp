#define MAXN 505
int n; //1-base
vector<int> g[MAXN];
int MH[MAXN]; //output MH
int pa[MAXN],st[MAXN],S[MAXN],v[MAXN],t;
int lca(int x,int y){
	for(++t;;swap(x,y)){
		if(!x) continue;
		if(v[x]==t) return x;
		v[x] = t;
		x = st[pa[MH[x]]];
	}
}
#define qpush(x) q.push(x),S[x]=0
void flower(int x,int y,int l,queue<int>&q){
	while(st[x]!=l){
		pa[x]=y;
		if(S[y=MH[x]]==1)qpush(y);
		st[x]=st[y]=l, x=pa[y];
	}
}
bool bfs(int x){
	iota(st+1, st+n+1, 1);
	memset(S+1,-1,sizeof(int)*n);
	queue<int>q; qpush(x);
	while(q.size()){
		x=q.front(),q.pop();
		for(int y:g[x]){
			if(S[y]==-1){
				pa[y]=x,S[y]=1;
				if(!MH[y]){
					for(int lst;x;y=lst,x=pa[y])
						lst=MH[x],MH[x]=y,MH[y]=x;
					return 1;
				}
				qpush(MH[y]);
			}else if(!S[y]&&st[y]!=st[x]){
				int l=lca(y,x);
				flower(y,x,l,q),flower(x,y,l,q);
			}
		}
	}
	return 0;
}
int blossom(){
	memset(MH+1,0,sizeof(int)*n);
	int ans=0;
	for(int i=1; i<=n; ++i)
		if(!MH[i]&&bfs(i)) ++ans;
	return ans;
}

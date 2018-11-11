#define MAXN 405
#define INF 0x3f3f3f3f3f3f3f3f
int n;// 1-base，0表示沒有匹配 
LL g[MAXN][MAXN]; //input graph
int My[MAXN],Mx[MAXN]; //output match
LL lx[MAXN],ly[MAXN],pa[MAXN],Sy[MAXN];
bool vx[MAXN],vy[MAXN];
void augment(int y){
	for(int x, z; y; y = z){
		x=pa[y],z=Mx[x];
		My[y]=x,Mx[x]=y;
	}
}
void bfs(int st){
	for(int i=1; i<=n; ++i)
		Sy[i] = INF, vx[i]=vy[i]=0;
	queue<int> q; q.push(st);
	for(;;){
		while(q.size()){
			int x=q.front(); q.pop();
			vx[x]=1;
			for(int y=1; y<=n; ++y) if(!vy[y]){
				LL t = lx[x]+ly[y]-g[x][y];
				if(t==0){
					pa[y]=x;
					if(!My[y]){augment(y);return;}
					vy[y]=1,q.push(My[y]);
				}else if(Sy[y]>t) pa[y]=x,Sy[y]=t;
			}
		}
		LL cut = INF;
		for(int y=1; y<=n; ++y)
			if(!vy[y]&&cut>Sy[y]) cut=Sy[y];
		for(int j=1; j<=n; ++j){
			if(vx[j]) lx[j] -= cut;
			if(vy[j]) ly[j] += cut;
			else Sy[j] -= cut;
		}
		for(int y=1; y<=n; ++y){
			if(!vy[y]&&Sy[y]==0){
				if(!My[y]){augment(y);return;}
				vy[y]=1, q.push(My[y]);
			}
		}
	}
}
LL KM(){
	memset(My,0,sizeof(int)*(n+1));
	memset(Mx,0,sizeof(int)*(n+1));
	memset(ly,0,sizeof(LL)*(n+1));
	for(int x=1; x<=n; ++x){
		lx[x] = -INF;
		for(int y=1; y<=n; ++y)
			lx[x] = max(lx[x],g[x][y]);
	}
	for(int x=1; x<=n; ++x) bfs(x);
	LL ans = 0;
	for(int y=1; y<=n; ++y) ans+=g[My[y]][y];
	return ans;
}
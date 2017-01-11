#define MAXN 405
#define INF 0x3f3f3f3f
int n;// 1-base，0表示沒有匹配 
int g[MAXN][MAXN],lx[MAXN],ly[MAXN],pa[MAXN],slack_y[MAXN];
int match_y[MAXN],match_x[MAXN];
bool vx[MAXN],vy[MAXN];
void augment(int y){
	for(int x,z;y;y=z){
		x=pa[y],z=match_x[x];
		match_y[y]=x,match_x[x]=y;
	}
}
void bfs(int st){
	for(int i=1;i<=n;++i)slack_y[i]=INF,vx[i]=vy[i]=0;
	queue<int> q;q.push(st);
	for(;;){
		while(q.size()){
			int x=q.front();q.pop();
			vx[x]=1;
			for(int y=1;y<=n;++y)if(!vy[y]){
				int t=lx[x]+ly[y]-g[x][y];
				if(t==0){
					pa[y]=x;
					if(!match_y[y]){augment(y);return;}
					vy[y]=1,q.push(match_y[y]);
				}else if(slack_y[y]>t)pa[y]=x,slack_y[y]=t;
			}
		}
		int cut=INF;
		for(int y=1;y<=n;++y){
			if(!vy[y]&&cut>slack_y[y])cut=slack_y[y];
		}
		for(int j=1;j<=n;++j){
			if(vx[j])lx[j]-=cut;
			if(vy[j])ly[j]+=cut;
			else slack_y[j]-=cut;
		}
		for(int y=1;y<=n;++y){
			if(!vy[y]&&slack_y[y]==0){
				if(!match_y[y]){augment(y);return;}
				vy[y]=1,q.push(match_y[y]);
			}
		}
	}
}
long long KM(){
	memset(match_y,0,sizeof(int)*(n+1));
	memset(ly,0,sizeof(int)*(n+1));
	for(int x=1;x<=n;++x){
		lx[x]=-INF;
		for(int y=1;y<=n;++y)
			lx[x]=max(lx[x],g[x][y]);
	}
	for(int x=1;x<=n;++x)bfs(x);
	long long ans=0;
	for(int y=1;y<=n;++y)ans+=g[match_y[y]][y];
	return ans;
}
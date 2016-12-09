#define MAXN 100
int n;
int g[MAXN][MAXN],lx[MAXN],ly[MAXN],slack_y[MAXN];
int match_y[MAXN];
bool vx[MAXN],vy[MAXN];//要保證g是完全二分圖
bool dfs(int x,bool adjust=1){//DFS找增廣路，is=1表示要交換邊 
	if(vx[x])return 0;
	vx[x]=1;
	for(int y=0;y<n;++y){
		if(vy[y])continue;
		int t=lx[x]+ly[y]-g[x][y];
		if(t==0){
			vy[y]=1;
			if(match_y[y]==-1||dfs(match_y[y],adjust)){
				if(adjust)match_y[y]=x;
				return 1;
			}
		}else if(slack_y[y]>t)slack_y[y]=t;
	}
	return 0;
}
inline int km(){
	memset(ly,0,sizeof(int)*n);
	memset(match_y,-1,sizeof(int)*n);
	for(int x=0;x<n;++x){
		lx[x]=0;
		for(int y=0;y<n;++y){
			lx[x]=max(lx[x],g[x][y]);
		}
	}
	for(int x=0;x<n;++x){
		for(int y=0;y<n;++y)slack_y[y]=INT_MAX;
		memset(vx,0,sizeof(bool)*n);
		memset(vy,0,sizeof(bool)*n);
		if(dfs(x))continue;
		bool flag=1;
		while(flag){
			int cut=INT_MAX;
			for(int y=0;y<n;++y){
				if(!vy[y]&&cut>slack_y[y])cut=slack_y[y];
			}
			for(int j=0;j<n;++j){
				if(vx[j])lx[j]-=cut;
				if(vy[j])ly[j]+=cut;
				else slack_y[j]-=cut;
			}
			for(int y=0;y<n;++y){
				if(!vy[y]&&slack_y[y]==0){
					vy[y]=1;
					if(match_y[y]==-1||dfs(match_y[y],0)){
						flag=0;//測試成功，有增廣路 
						break;
					}
				}
			}
		}
		memset(vx,0,sizeof(bool)*n);
		memset(vy,0,sizeof(bool)*n);
		dfs(x);//最後要記得將邊翻反轉 
	}
	int ans=0;
	for(int y=0;y<n;++y)ans+=g[match_y[y]][y];
	return ans;
}

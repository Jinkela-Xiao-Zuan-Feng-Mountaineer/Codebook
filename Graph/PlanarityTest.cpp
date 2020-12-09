const int MAXN = 22;
bool hasK33(bool G[MAXN][MAXN], const int n){
		for(int a=0;a<n;++a)
		for(int b=a+1;b<n;++b)
		for(int c=b+1;c<n;++c)
		for(int d=0;d<n;++d)
	if(G[a][d]&&G[b][d]&&G[c][d])
		for(int e=d+1;e<n;++e)
	if(G[a][e]&&G[b][e]&&G[c][e])
		for(int f=e+1;f<n;++f)
	if(G[a][f]&&G[b][f]&&G[c][f]) return true;
	return false;
}
bool hasK5(bool G[MAXN][MAXN], const int n){
		for(int a=0;a<n;++a)
		for(int b=a+1;b<n;++b)
	if(G[b][a])
		for(int c=b+1;c<n;++c)
	if(G[c][a]&&G[c][b])
		for(int d=c+1;d<n;++d)
	if(G[d][a]&&G[d][b]&&G[d][c])
		for(int e=d+1;d<n;++d)
	if(G[e][a]&&G[e][b]&&G[e][c]&&G[e][d])
		return true;
	return false;
}
// O(n^6) judge a given undirected graph has K33 or K5 as a minor.
bool isPlanar(bool G[MAXN][MAXN], const int n){
	for(;;){
		bool merge = false;
		for(int u=0;u<n;++u){
			vector<int> V;
			for(int v=0;v<n&&V.size()<3;++v)
				if(G[u][v]&&u!=v) V.push_back(v);
			if(V.size() == 1){
				G[u][V[0]] = G[V[0]][u] =false;
				merge = true;
			}else if(V.size() == 2){
				G[u][V[0]] = G[V[0]][u] =false;
				G[u][V[1]] = G[V[1]][u] =false;
				G[V[0]][V[1]] = G[V[1]][V[0]] =true;
				merge = true;
			}
		}
		if(!merge)break;
	}
	for(int u=0;u<n;++u) G[u][u] =false;
	return !(hasK33(G, n) || hasK5(G, n));
}
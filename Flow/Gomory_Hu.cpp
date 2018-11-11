//最小割樹+求任兩點間最小割
//0-base, root=0
LL e[MAXN][MAXN]; //任兩點間最小割
int p[MAXN]; //parent
ISAP D; // original graph
void gomory_hu(){
	fill(p, p+n, 0);
	fill(e[0], e[n], INF);
	for( int s = 1; s < n; ++s ) {
		int t = p[s];
		ISAP F = D;
		LL tmp = F.min_cut(s, t);
		for( int i = 1; i < s; ++i )
			e[s][i] = e[i][s] = min(tmp, e[t][i]);
		for( int i = s+1; i <= n; ++i ) 
			if( p[i] == t && F.vis[i] ) p[i] = s;
	}
}
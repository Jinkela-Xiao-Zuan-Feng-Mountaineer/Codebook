static const int MAXN = 20;
struct Edge{
	int u, v;
	Edge(int s, int d) : u(s), v(d) {}
};
bool isK33(int n, int degree[]){
	int t = 0, z = 0;
	for(int i=0;i<n;++i){
		if(degree[i] == 3)++t;
		else if(degree[i] == 0)++z;
		else return false;
	}
	return t == 6 && t + z == n;
}
bool isK5(int n, int degree[]){
	int f = 0, z = 0;
	for(int i=0;i<n;++i){
		if(degree[i] == 4)++f;
		else if(degree[i] == 0)++z;
		else return false;
	}
	return f == 5 && f + z == n;
}
// it judge a given graph is Homeomorphic with K33 or K5
bool isHomeomorphic(bool G[MAXN][MAXN], const int n){
	for(;;){
		int cnt = 0;
		for(int i=0;i<n;++i){
			vector<Edge> E;
			for(int j=0;j<n&&E.size()<3;++j)
				if(G[i][j] && i != j)
					E.push_back(Edge(i, j));
			if(E.size() == 1){
				G[i][E[0].v] = G[E[0].v][i] = false;
			}else if(E.size() == 2){
				G[i][E[0].v] = G[E[0].v][i] = false;
				G[i][E[1].v] = G[E[1].v][i] = false;
				G[E[0].v][E[1].v] = G[E[1].v][E[0].v] = true;
				++cnt;
			}
		}
		if(cnt == 0)break;
	}
	static int degree[MAXN];
	fill(degree, degree + n, 0);
	for(int i=0;i<n;++i){
		for(int j=i+1; j<n; ++j){
			if(!G[i][j])continue;
			++degree[i];
			++degree[j];
		}
	}
	return !(isK33(n,degree)||isK5(n,degree));
}
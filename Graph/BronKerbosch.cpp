struct maximalCliques{
	using Set = vector<int>;
	size_t n; //1-base
	vector<Set> G;
	static Set setUnion(const Set &A, const Set &B){
		Set C(A.size() + B.size());
		auto it = set_union(A.begin(),A.end(),B.begin(),B.end(),C.begin());
		C.erase(it, C.end());
		return C;
	}
	static Set setIntersection(const Set &A, const Set &B){
		Set C(min(A.size(), B.size()));
		auto it = set_intersection(A.begin(),A.end(),B.begin(),B.end(),C.begin());
		C.erase(it, C.end());
		return C;
	}
	static Set setDifference(const Set &A, const Set &B){
		Set C(min(A.size(), B.size()));
		auto it = set_difference(A.begin(),A.end(),B.begin(),B.end(),C.begin());
		C.erase(it, C.end());
		return C;
	}
	void BronKerbosch1(Set R, Set P, Set X){
		if(P.empty()&&X.empty()){
			// R form an maximal clique
			return;
		}
		for(auto v: P){
			BronKerbosch1(setUnion(R,{v}), setIntersection(P,G[v]), setIntersection(X,G[v]));
			P = setDifference(P,{v});
			X = setUnion(X,{v});
		}
	}
	void init(int _n){
		G.clear();
		G.resize((n = _n) + 1);
	}
	void addEdge(int u, int v){
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	void solve(int n){
		Set P;
		for(int i=1; i<=n; ++i){
			sort(G[i].begin(), G[i].end());
G[i].erase(unique(G[i].begin(), G[i].end()), G[i].end());
			P.emplace_back(i);
		}
		BronKerbosch1({}, P, {});
	}
};
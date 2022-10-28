struct chordal{
	static const int MAXN=1005;
	int n;// 0-base
	vector<int>G[MAXN];
	int rank[MAXN],label[MAXN];
	bool mark[MAXN];
	void init(int _n){n=_n;
		for(int i=0;i<n;++i)G[i].clear();
	}
	void add_edge(int u,int v){
		G[u].push_back(v);
		G[v].push_back(u);
	}
	vector<int> MCS(){
		memset(rank,-1,sizeof(int)*n);
		memset(label,0,sizeof(int)*n);
		priority_queue<pair<int,int> > pq;
		for(int i=0;i<n;++i)pq.push(make_pair(0,i));
		for(int i=n-1;i>=0;--i)for(;;){
			int u=pq.top().second;pq.pop();
			if(~rank[u])continue;
			rank[u]=i;
			for(auto v:G[u])if(rank[v]==-1){
				pq.push(make_pair(++label[v],v));
			}
			break;
		}
		vector<int> res(n);
		for(int i=0;i<n;++i)res[rank[i]]=i;
		return res;
	}
	bool check(vector<int> ord){//弦圖判定
		for(int i=0;i<n;++i)rank[ord[i]]=i;
		memset(mark,0,sizeof(bool)*n);
		for(int i=0;i<n;++i){
			vector<pair<int,int> > tmp;
			for(auto u:G[ord[i]])if(!mark[u])
				tmp.push_back(make_pair(rank[u],u));
			sort(tmp.begin(),tmp.end());
			if(tmp.size()){
				int u=tmp[0].second;
				set<int> S;
				for(auto v:G[u])S.insert(v);
				for(size_t j=1;j<tmp.size();++j)
					if(!S.count(tmp[j].second))return 0;
			}
			mark[ord[i]]=1;
		}
		return 1;
	}
};

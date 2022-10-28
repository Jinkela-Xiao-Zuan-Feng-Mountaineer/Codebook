void solve(int n,int a[],int b[]){// 1-base
	int ans=0;
	deque<int>da,db;
	for(int l=1,r=1;r<=n;++r){
		while(da.size()&&a[da.back()]>=a[r]){
			da.pop_back();
		}
		da.push_back(r);
		while(db.size()&&b[db.back()]>=b[r]){
			db.pop_back();
		}
		db.push_back(r);
		for(int d=a[da.front()]+b[db.front()];r-l+1>d;++l){
			if(da.front()==l)da.pop_front();
			if(db.front()==l)db.pop_front();
			if(da.size()&&db.size()){
				d=a[da.front()]+b[db.front()];
			}
		}
		ans=max(ans,r-l+1);
	}
	printf("%d\n",ans);
}
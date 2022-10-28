LL max_rectangle(vector<int> s){
	stack<pair<int,int > > st;
	st.push(make_pair(-1,0));
	s.push_back(0);
	LL ans=0;
	for(size_t i=0;i<s.size();++i){
		int h=s[i];
		pair<int,int > now=make_pair(h,i);
		while(h<st.top().first){
			now=st.top();
			st.pop();
			ans=max(ans,(LL)(i-now.second)*now.first);
		}
		if(h>st.top().first){
			st.push(make_pair(h,now.second));
		}
	}
	return ans;
}
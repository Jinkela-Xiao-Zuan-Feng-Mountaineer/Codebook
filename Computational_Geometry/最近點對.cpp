template<typename _IT=point<T>* >
T cloest_pair(_IT L, _IT R){
	if(R-L <= 1) return INF;
	_IT mid = L+(R-L)/2;
	T x = mid->x;
	T d = min(cloest_pair(L,mid),cloest_pair(mid,R));
	inplace_merge(L, mid, R, ycmp);
	static vector<point> b; b.clear();
	for(auto u=L;u<R;++u){
		if((u->x-x)*(u->x-x)>=d) continue;
		for(auto v=b.rbegin();v!=b.rend();++v){
			T dx=u->x-v->x, dy=u->y-v->y;
			if(dy*dy>=d) break;
			d=min(d,dx*dx+dy*dy);
		}
		b.push_back(*u);
	}
	return d;
}
T closest_pair(vector<point<T>> &v){
	sort(v.begin(),v.end(),xcmp);
	return closest_pair(v.begin(),v.end());
}
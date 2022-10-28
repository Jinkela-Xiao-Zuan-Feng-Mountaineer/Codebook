vector<int> F_OR_T(vector<int> f, bool inverse){
	for(int i=0; (2<<i)<=f.size(); ++i) 
		for(int j=0; j<f.size(); j+=2<<i) 
			for(int k=0; k<(1<<i); ++k) 
				f[j+k+(1<<i)] += f[j+k]*(inverse?-1:1);
	return f;
}
vector<int> rev(vector<int> A) {
	for(int i=0; i<A.size(); i+=2)
		swap(A[i],A[i^(A.size()-1)]);
	return A;
}
vector<int> F_AND_T(vector<int> f, bool inverse){
	return rev(F_OR_T(rev(f), inverse));
}
vector<int> F_XOR_T(vector<int> f, bool inverse){
	for(int i=0; (2<<i)<=f.size(); ++i) 
		for(int j=0; j<f.size(); j+=2<<i) 
			for(int k=0; k<(1<<i); ++k){
				int u=f[j+k], v=f[j+k+(1<<i)];
				f[j+k+(1<<i)] = u-v, f[j+k] = u+v;
			}
	if(inverse) for(auto &a:f) a/=f.size();
	return f;
}

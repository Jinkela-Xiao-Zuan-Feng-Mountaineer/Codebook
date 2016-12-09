int eulerPhi(int n){
	int m = sqrt(n+0.5);
	int res=n;
	for(int i=2; i<=m; i++){
		if(n%i==0){
			res = res*(i-1)/i;
			while(n%i==0)n/=i;
		}
	}
	if(n>1) res = res*(n-1)/n;
	return res;
}

vector<int> phiTable(int n){
	vector<int>phi(n+1, 0);
	phi[1] = 1;
	for(int i=2; i<=n; i++) if(!phi[i])
		for(int j=i; j<=n; j+=i){
			if(!phi[j])phi[j] = j;
			phi[j] = phi[j]*(i-1)/i;
		}
	return phi;
}
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

long long int phi[N+1];
void phiTable(){
	for(int i=1;i<=N;i++)phi[i]=i;
	for(int i=1;i<=N;i++)for(x=i*2;x<=N;x+=i)phi[x]-=phi[i];
}

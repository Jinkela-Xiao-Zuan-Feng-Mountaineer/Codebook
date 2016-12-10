template<typename T>
T Euler(T n){
	T ans=n;
	for(T i=2;i*i<=n;++i){
		if(n%i==0){
			ans=ans/i*(i-1);
			while(n%i==0)n/=i;
		}
	}
	if(n>1)ans=ans/n*(n-1);
	return ans;
}
template<typename T>
T pow_mod(T n,T k,T m){
	T ans=1;
	for(n=(n>=m?n%m:n);k;k>>=1){
		if(k&1)ans=ans*n%m;
		n=n*n%m;
	}
	return ans;
}
template<typename T>
T crt(vector<T> &m,vector<T> &a){
	T M=1,tM,ans=0;
	for(int i=0;i<(int)m.size();++i)M*=m[i];
	for(int i=0;i<(int)a.size();++i){
		tM=M/m[i];
		ans=(ans+(a[i]*tM%M)*pow_mod(tM,Euler(m[i])-1,m[i])%M)%M;
		/*如果m[i]是質數，Euler(m[i])-1=m[i]-2，就不用算Euler了*/
	}
	return ans;
}

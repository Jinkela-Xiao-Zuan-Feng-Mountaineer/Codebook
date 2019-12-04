ll C(ll n, ll m, ll p){// n!/m!/(n-m)!
 if(n<m) return 0;
 return f[n]*inv(f[m],p)%p*inv(f[n-m],p)%p;
}
ll L(ll n, ll m, ll p){
 if(!m) return 1;
 return C(n%p,m%p,p)*L(n/p,m/p,p)%p;
}
ll Wilson(ll n, ll p){ // n!%p
	if(!n)return 1; 
	ll res=Wilson(n/p, p);  
	if((n/p)%2) return res*(p-f[n%p])%p;	
	return  res*f[n%p]%p; //(p-1)!%p=-1
}

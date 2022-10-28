LL func(const LL n,const LL mod,const int c) {
	return (LLmul(n,n,mod)+c+mod)%mod;
}

LL pollorrho(const LL n, const int c) {//循環節長度 
	LL a=1, b=1;
	a=func(a,n,c)%n;
	b=func(b,n,c)%n; b=func(b,n,c)%n;
	while(gcd(abs(a-b),n)==1) {
		a=func(a,n,c)%n;
		b=func(b,n,c)%n; b=func(b,n,c)%n;
	}
	return gcd(abs(a-b),n);
}

void prefactor(LL &n, vector<LL> &v) {
	for(int i=0;i<12;++i) {
		while(n%prime[i]==0) {
			v.push_back(prime[i]);
			n/=prime[i];
		}
	}
}

void smallfactor(LL n, vector<LL> &v) {
	if(n<MAXPRIME) {
		while(isp[(int)n]) {
			v.push_back(isp[(int)n]);
			n/=isp[(int)n];
		}
		v.push_back(n);
	} else {
		for(int i=0;i<primecnt&&prime[i]*prime[i]<=n;++i) {
			while(n%prime[i]==0) {
				v.push_back(prime[i]);
				n/=prime[i];
			}
		}
		if(n!=1) v.push_back(n);
	}
}

void comfactor(const LL &n, vector<LL> &v) {
	if(n<1e9) {
		smallfactor(n,v);
		return;
	}
	if(Isprime(n)) {
		v.push_back(n);
		return;
	}
	LL d;
	for(int c=3;;++c) {
		d = pollorrho(n,c);
		if(d!=n) break;
	}
	comfactor(d,v);
	comfactor(n/d,v);
}

void Factor(const LL &x, vector<LL> &v) {
	LL n = x;
	if(n==1) { puts("Factor 1"); return; }
	prefactor(n,v);
	if(n==1) return;
	comfactor(n,v);
	sort(v.begin(),v.end());
}

void AllFactor(const LL &n,vector<LL> &v) {
	vector<LL> tmp;
	Factor(n,tmp);
	v.clear();
	v.push_back(1);
	int len;
	LL now=1;
	for(int i=0;i<tmp.size();++i) {
		if(i==0 || tmp[i]!=tmp[i-1]) {
			len = v.size();
			now = 1;
		}
		now*=tmp[i];
		for(int j=0;j<len;++j)
			v.push_back(v[j]*now);
	}
}

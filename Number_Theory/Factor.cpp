LL LLmul(LL a, LL b, const LL &mod) {
    LL ans=0;
    while(b) {
        if(b&1) {
            ans+=a;
            if(ans>=mod) ans-=mod;
        }
        a<<=1, b>>=1;
        if(a>=mod) a-=mod;
    }
    return ans;
}
inline long long mod_mul(long long a,long long b,long long m){
	a%=m,b%=m;
	long long y=(long long)((double)a*b/m+0.5);/* fast for m < 2^58 */
	long long r=(a*b-y*m)%m;
	return r<0?r+m:r;
}
template<typename T>
inline T pow(T a,T b,T mod){//a^b%mod
	T ans=1;
	for(;b;a=mod_mul(a,a,mod),b>>=1)
		if(b&1)ans=mod_mul(ans,a,mod);
	return ans;
}
int sprp[3]={2,7,61};//int範圍可解
int llsprp[7]={2,325,9375,28178,450775,9780504,1795265022};//至少unsigned long long範圍
template<typename T>
inline bool isprime(T n,int *sprp,int num){
	if(n==2)return 1;
	if(n<2||n%2==0)return 0;
	int t=0;
	T u=n-1;
	for(;u%2==0;++t)u>>=1;
	for(int i=0;i<num;++i){
		T a=sprp[i]%n;
		if(a==0||a==1||a==n-1)continue;
		T x=pow(a,u,n);
		if(x==1||x==n-1)continue;
		for(int j=0;j<t;++j){
			x=mod_mul(x,x,n);
			if(x==1)return 0;
			if(x==n-1)break;
		}
		if(x==n-1)continue;
		return 0;
	}
	return 1;
}

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

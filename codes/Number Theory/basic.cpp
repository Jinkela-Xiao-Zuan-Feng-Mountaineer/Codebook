template<typename T>
void gcd(const T &a,const T &b,T &d,T &x,T &y){
	if(!b) d=a,x=1,y=0;
	else gcd(b,a%b,d,y,x), y-=x*(a/b);
}
long long int phi[N+1];
void phiTable(){
	for(int i=1;i<=N;i++)phi[i]=i;
	for(int i=1;i<=N;i++)for(x=i*2;x<=N;x+=i)phi[x]-=phi[i];
}
void all_divdown(const LL &n) {// all n/x
	for(LL a=1;a<=n;a=n/(n/(a+1))){
		// dosomething;
	}
}
const int MAXPRIME = 1000000;
int iscom[MAXPRIME], prime[MAXPRIME], primecnt;
int phi[MAXPRIME], mu[MAXPRIME];
void sieve(void){
	memset(iscom,0,sizeof(iscom));
	primecnt = 0;
	phi[1] = mu[1] = 1;
	for(int i=2;i<MAXPRIME;++i) {
		if(!iscom[i]) {
			prime[primecnt++] = i;
			mu[i] = -1;
			phi[i] = i-1;
		}
		for(int j=0;j<primecnt;++j) {
			int k = i * prime[j];
			if(k>=MAXPRIME) break;
			iscom[k] = prime[j];
			if(i%prime[j]==0) {
				mu[k] = 0;
				phi[k] = phi[i] * prime[j];
				break;
			} else {
				mu[k] = -mu[i];
				phi[k] = phi[i] * (prime[j]-1);
			}
		}
	}
}

bool g_test(const LL &g, const LL &p, const vector<LL> &v) {
	for(int i=0;i<v.size();++i)
		if(modexp(g,(p-1)/v[i],p)==1)
			return false;
	return true;
}
LL primitive_root(const LL &p) {
	if(p==2) return 1;
	vector<LL> v;
	Factor(p-1,v);
	v.erase(unique(v.begin(), v.end()), v.end());
	for(LL g=2;g<p;++g)
		if(g_test(g,p,v))
			return g;
	puts("primitive_root NOT FOUND");
	return -1;
}
int Legendre(const LL &a, const LL &p) { return modexp(a%p,(p-1)/2,p); }

LL inv(const LL &a, const LL &n) {
	LL d,x,y;
	gcd(a,n,d,x,y);
	return d==1 ? (x+n)%n : -1;
}

int inv[maxN];
LL invtable(int n,LL P){
	inv[1]=1;
	for(int i=2;i<n;++i)
		inv[i]=(P-(P/i))*inv[P%i]%P;
}

LL log_mod(const LL &a, const LL &b, const LL &p) {
	// a ^ x = b ( mod p )
	int m=sqrt(p+.5), e=1;
	LL v=inv(modexp(a,m,p), p);
	map<LL,int> x;
	x[1]=0;
	for(int i=1;i<m;++i) {
		e = LLmul(e,a,p);
		if(!x.count(e)) x[e] = i;
	}
	for(int i=0;i<m;++i) {
		if(x.count(b)) return i*m + x[b];
		b = LLmul(b,v,p);
	}
	return -1;
}

LL Tonelli_Shanks(const LL &n, const LL &p) {
	// x^2 = n ( mod p )
	if(n==0) return 0;
	if(Legendre(n,p)!=1) while(1) { puts("SQRT ROOT does not exist"); }
	int S = 0;
	LL Q = p-1;
	while( !(Q&1) ) { Q>>=1; ++S; }
	if(S==1) return modexp(n%p,(p+1)/4,p);
	LL z = 2;
	for(;Legendre(z,p)!=-1;++z)
	LL c = modexp(z,Q,p);
	LL R = modexp(n%p,(Q+1)/2,p), t = modexp(n%p,Q,p);
	int M = S;
	while(1) {
		if(t==1) return R;
		LL b = modexp(c,1L<<(M-i-1),p);
		R = LLmul(R,b,p);
		t = LLmul( LLmul(b,b,p), t, p);
		c = LLmul(b,b,p);
		M = i;
	}
	return -1;
}

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

//Chinese_remainder_theorem
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

//java code
//求sqrt(N)的連分數
public static void Pell(int n){
	BigInteger N,p1,p2,q1,q2,a0,a1,a2,g1,g2,h1,h2,p,q;
	g1=q2=p1=BigInteger.ZERO;
	h1=q1=p2=BigInteger.ONE;
	a0=a1=BigInteger.valueOf((int)Math.sqrt(1.0*n));
	BigInteger ans=a0.multiply(a0);
	if(ans.equals(BigInteger.valueOf(n))){
		System.out.println("No solution!");
		return ;
	}
	while(true){
		g2=a1.multiply(h1).substract(g1);
		h2=N.substract(g2.pow(2)).divide(h1);
		a2=g2.add(a0).divide(h2);
		p=a1.multiply(p2).add(p1);
		q=a1.multiply(q2).add(q1);
		if(p.pow(2).substract(N.multiply(q.pow(2))).compareTo(BigInteger.ONE)==0)break;
		g1=g2;h1=h2;a1=a2;
		p1=p2;p2=p;
		q1=q2;q2=q;
	}
	System.out.println(p+" "+q);
}
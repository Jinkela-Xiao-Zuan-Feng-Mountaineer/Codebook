#include<bits/stdc++.h>
using namespace std;
#ifndef CHINESE_REMAINDER_THEOREM
#define CHINESE_REMAINDER_THEOREM
template<typename T>
inline T Euler(T n){
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
inline T pow_mod(T n,T k,T m){
	T ans=1;
	for(n=(n>=m?n%m:n);k;k>>=1){
		if(k&1)ans=ans*n%m;
		n=n*n%m;
	}
	return ans;
}
template<typename T>
inline T crt(std::vector<T> &m,std::vector<T> &a){
	T M=1,tM,ans=0;
	for(int i=0;i<(int)m.size();++i)M*=m[i];
	for(int i=0;i<(int)a.size();++i){
		tM=M/m[i];
		ans=(ans+(a[i]*tM%M)*pow_mod(tM,Euler(m[i])-1,m[i])%M)%M;
		/*如果m[i]是質數，Euler(m[i])-1=m[i]-2，就不用算Euler了*/
	}
	return ans;
}
#endif
int n;
vector<long long> a,m;
int main(){
	while(~scanf("%d",&n)){
		for(int i=0;i<n;++i){
			long long x,y;
			scanf("%lld%lld",&x,&y);
			m.push_back(x);
			a.push_back(y);
		}
		long long ans=crt(m,a);
		printf("%lld\n",ans);
		for(int i=0;i<n;++i)printf("%lld %lld\n",m[i],ans%m[i]);
		m.clear();
		a.clear();
	}
	return 0;
}
/*
4
199 198
200 199
201 197
137 88
2
265163 465
66546165 7122
5
379 46
853 852
971 777
659 128
281 256
4
6359 1
4877 5
1627 6
8941 7122
*/

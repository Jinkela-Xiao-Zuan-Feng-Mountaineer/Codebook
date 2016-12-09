//a[0]^(a[1]^a[2]^...)
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000000
int euler[maxn+5];
bool is_prime[maxn+5];
inline void init_euler(){
	is_prime[1]=1;//一不是質數
	for(int i=1;i<=maxn;i++)euler[i]=i;
	for(int i=2;i<=maxn;i++){
		if(!is_prime[i]){//是質數
			euler[i]--;
			for(int j=i<<1;j<=maxn;j+=i){
				is_prime[j]=1;
				euler[j]=euler[j]/i*(i-1);
			}
		}
	}
}
inline long long pow(long long a,long long b,long long mod){//a^b%mod
	long long ans=1;
	for(;b;a=a*a%mod,b>>=1)
		if(b&1)ans=ans*a%mod;
	return ans;
}
bool isless(long long *a,int n,int k){
	if(*a==1)return k>1;
	if(--n==0)return *a<k;
	int next=0;
	for(long long b=1;b<k;++next)
		b*=*a;
	return isless(a+1,n,next);
}
long long high_pow(long long *a,int n,long long mod){
	if(*a==1||--n==0)return *a%mod;
	int k=0,r=euler[mod];
	for(long long tma=1;tma!=pow(*a,k+r,mod);++k)
		tma=tma*(*a)%mod;
	if(isless(a+1,n,k))return pow(*a,high_pow(a+1,n,k),mod);
	int tmd=high_pow(a+1,n,r);
	int t=(tmd-k+r)%r;
	return pow(*a,k+t,mod);
}
long long a[1000005];
int t,mod;
int main(){
	init_euler();
	scanf("%d",&t);
	#define n 4 
	while(t--){
		for(int i=0;i<n;++i)scanf("%lld",&a[i]);
		scanf("%d",&mod);
		printf("%lld\n",high_pow(a,n,mod));
	}
	return 0;
}

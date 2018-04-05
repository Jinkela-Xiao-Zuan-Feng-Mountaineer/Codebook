//a[0]^(a[1]^a[2]^...)
#define maxn 1000000
int euler[maxn+5];
bool is_prime[maxn+5];
void init_euler(){
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
LL pow(LL a,LL b,LL mod){//a^b%mod
	LL ans=1;
	for(;b;a=a*a%mod,b>>=1)
		if(b&1)ans=ans*a%mod;
	return ans;
}
bool isless(LL *a,int n,int k){
	if(*a==1)return k>1;
	if(--n==0)return *a<k;
	int next=0;
	for(LL b=1;b<k;++next)
		b*=*a;
	return isless(a+1,n,next);
}
LL high_pow(LL *a,int n,LL mod){
	if(*a==1||--n==0)return *a%mod;
	int k=0,r=euler[mod];
	for(LL tma=1;tma!=pow(*a,k+r,mod);++k)
		tma=tma*(*a)%mod;
	if(isless(a+1,n,k))return pow(*a,high_pow(a+1,n,k),mod);
	int tmd=high_pow(a+1,n,r), t=(tmd-k+r)%r;
	return pow(*a,k+t,mod);
}
LL a[1000005];
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

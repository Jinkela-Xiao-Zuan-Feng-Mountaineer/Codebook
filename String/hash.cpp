#define MAXN 1000000
#define prime_mod 1073676287
/*prime_mod 必須要是質數*/
typedef long long T;
char s[MAXN+5];
T h[MAXN+5];/*hash陣列*/ 
T h_base[MAXN+5];/*h_base[n]=(prime^n)%prime_mod*/ 
inline void hash_init(int len,T prime=0xdefaced){
	h_base[0]=1;
	for(int i=1;i<=len;++i){
		h[i]=(h[i-1]*prime+s[i-1])%prime_mod;
		h_base[i]=(h_base[i-1]*prime)%prime_mod;
	}
}
inline T get_hash(int l,int r){/*閉區間寫法，設編號為0 ~ len-1*/
	return (h[r+1]-(h[l]*h_base[r-l+1])%prime_mod+prime_mod)%prime_mod;
}

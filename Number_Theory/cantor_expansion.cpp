int factorial[MAXN];
void init(){
	factorial[0]=1;
	for(int i=1;i<=MAXN;++i)factorial[i]=factorial[i-1]*i;
}
int encode(const vector<int> &s){
	int n=s.size(),res=0;
	for(int i=0;i<n;++i){
		int t=0;
		for(int j=i+1;j<n;++j)
			if(s[j]<s[i])++t;
		res+=t*factorial[n-i-1];
	}
	return res;
}
vector<int> decode(int a,int n){
	vector<int> res;
	vector<bool> vis(n,0);
	for(int i=n-1;i>=0;--i){
		int t=a/factorial[i],j;
		for(j=0;j<n;++j)
			if(!vis[j]){
				if(t==0)break;
				--t;
			}
		res.push_back(j);
		vis[j]=1;
		a%=factorial[i];
	}
	return res;
}

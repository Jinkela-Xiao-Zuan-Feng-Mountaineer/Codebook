void sub_set(int S){
	int sub=S;
	do{
		//對某集合的子集合的處理 
		sub=(sub-1)&S;
	}while(sub!=S);
}
void k_sub_set(int k,int n){
	int comb=(1<<k)-1,S=1<<n;
	while(comb<S){
		//對大小為k的子集合的處理 
		int x=comb&-comb,y=comb+x;
		comb=((comb&~y)/x>>1)|y;
	}
}

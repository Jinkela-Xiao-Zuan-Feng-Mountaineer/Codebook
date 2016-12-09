#define radix_sort(x,y){\
	for(i=0;i<A;++i)c[i]=0;\
	for(i=0;i<len;++i)c[x[y[i]]]++;\
	for(i=1;i<A;++i)c[i]+=c[i-1];\
	for(i=len-1;i>=0;--i)sa[--c[x[y[i]]]]=y[i];\
}
void suffix_array(const char *s,int len,int *sa,int *rank,int *tmp,int *c){
	int A='z'+1,i,k,id,*t;
	for(i=0;i<len;++i){
		tmp[i]=i;
		rank[i]=s[i];
	}
	radix_sort(rank,tmp);
	for(k=1;id<len-1;k<<=1){
		id=0;
		for(i=len-k;i<len;++i)tmp[id++]=i;
		for(i=0;i<len;++i){
			if(sa[i]>=k)tmp[id++]=sa[i]-k;
		}
		radix_sort(rank,tmp);
		t=rank;rank=tmp;tmp=t;
		id=0;
		rank[sa[0]]=0;
		for(i=1;i<len;++i){
			if(tmp[sa[i-1]]!=tmp[sa[i]]||sa[i-1]+k>=len||tmp[sa[i-1]+k]!=tmp[sa[i]+k])++id;
			rank[sa[i]]=id;
		}
		A=id+1;
	}
}
#undef radix_sort
//h:高度數組 sa:後綴數組 rank:排名 
inline void suffix_array_lcp(const char *s,int len,int *h,int *sa,int *rank){
	for(int i=0;i<len;++i)rank[sa[i]]=i;
	for(int i=0,k=0;i<len;++i){
		if(rank[i]==0)continue;
		if(k)--k;
		while(s[i+k]==s[sa[rank[i]-1]+k])++k;
		h[rank[i]]=k;
	}
	h[0]=0;
}

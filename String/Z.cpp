inline void z_alg(char *s,int len,int *z){
	int l=0,r=0;
	z[0]=len;
	for(int i=1;i<len;++i){
		z[i]=i>r?0:(i-l+z[i-l]<z[l]?z[i-l]:r-i+1);
		while(i+z[i]<len&&s[i+z[i]]==s[z[i]])++z[i];
		if(i+z[i]-1>r)r=i+z[i]-1,l=i;
	}
}

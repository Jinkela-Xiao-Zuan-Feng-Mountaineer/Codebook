//原字串: asdsasdsa 
//先把字串變成這樣: @a#s#d#s#a#s#d#s#a#
inline void manacher(char *s,int len,int *z){
	int l=0,r=0;
	for(int i=1;i<len;++i){
		z[i]=r>i?min(z[2*l-i],r-i):1;
		while(s[i+z[i]]==s[i-z[i]])++z[i];
		if(z[i]+i>r)r=z[i]+i,l=i;
	}
}

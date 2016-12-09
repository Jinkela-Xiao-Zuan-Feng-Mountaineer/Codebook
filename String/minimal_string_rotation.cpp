int min_string_rotation(const string &s){
	int n=s.size(),i=0,j=1,k=0;
	while(i<n&&j<n&&k<n){
		int t=s[(i+k)%n]-s[(j+k)%n];
		++k;
		if(t){
			if(t>0)i+=k;
			else j+=k;
			if(i==j)++j;
			k=0;
		}
	}
	return min(i,j);//傳回最小循環表示法起始位置
}
const int MAXN = 305, MAXC = 'Z';
int ranks[MAXN], tots[MAXC], first[MAXC];
void rankBWT(const string &bw){
	memset(ranks,0,sizeof(int)*bw.size());
	memset(tots,0,sizeof(tots);
	for(size_t i=0;i<bw.size();++i)
		ranks[i] = tots[int(bw[i])]++;
}
void firstCol(){
	memset(first,0,sizeof(first));
	int totc = 0;
	for(int c='A';c<='Z';++c){
		if(!tots[c]) continue;
		first[c] = totc;
		totc += tots[c];
	}
}
string reverseBwt(const string &bw,int begin){
	rankBWT(bw), firstCol();
	int i = begin; //原本字串最後一個元素的位置
	string res;
	do{
		char c = bw[i];
		res = c + res;
		i = first[int(c)] + ranks[i];
	}while( i != begin );
	return res;
}
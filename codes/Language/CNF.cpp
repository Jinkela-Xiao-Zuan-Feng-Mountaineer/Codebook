#define MAXN 55
struct CNF{
	int s,x,y;//s->xy | s->x, if y==-1
	int cost;
	CNF(){}
	CNF(int s,int x,int y,int c):s(s),x(x),y(y),cost(c){}
};
int state;//規則數量 
map<char,int> rule;//每個字元對應到的規則，小寫字母為終端字符
vector<CNF> cnf;
void init(){
	state=0;
	rule.clear();
	cnf.clear();
}
void add_to_cnf(char s,const string &p,int cost){
	//加入一個s -> <p>的文法，代價為cost 
	if(rule.find(s)==rule.end())rule[s]=state++;
	for(auto c:p)if(rule.find(c)==rule.end())rule[c]=state++;
	if(p.size()==1){
		cnf.push_back(CNF(rule[s],rule[p[0]],-1,cost));
	}else{
		int left=rule[s];
		int sz=p.size();
		for(int i=0;i<sz-2;++i){
			cnf.push_back(CNF(left,rule[p[i]],state,0));
			left=state++;
		}
		cnf.push_back(CNF(left,rule[p[sz-2]],rule[p[sz-1]],cost));
	}
}
vector<long long> dp[MAXN][MAXN];
vector<bool> neg_INF[MAXN][MAXN];//如果花費是負的可能會有無限小的情形 
void relax(int l,int r,const CNF &c,long long cost,bool neg_c=0){
	if(!neg_INF[l][r][c.s]&&(neg_INF[l][r][c.x]||cost<dp[l][r][c.s])){
		if(neg_c||neg_INF[l][r][c.x]){
			dp[l][r][c.s]=0;
			neg_INF[l][r][c.s]=true;
		}else dp[l][r][c.s]=cost;
	}
}
void bellman(int l,int r,int n){
	for(int k=1;k<=state;++k)
		for(auto c:cnf)
			if(c.y==-1)relax(l,r,c,dp[l][r][c.x]+c.cost,k==n);
}
void cyk(const vector<int> &tok){
	for(int i=0;i<(int)tok.size();++i){
		for(int j=0;j<(int)tok.size();++j){
			dp[i][j]=vector<long long>(state+1,INT_MAX);
			neg_INF[i][j]=vector<bool>(state+1,false);
		}
		dp[i][i][tok[i]]=0;
		bellman(i,i,tok.size());
	}
	for(int r=1;r<(int)tok.size();++r){
		for(int l=r-1;l>=0;--l){
			for(int k=l;k<r;++k)
				for(auto c:cnf)
					if(~c.y)relax(l,r,c,dp[l][k][c.x]+dp[k+1][r][c.y]+c.cost);
			bellman(l,r,tok.size());
		}
	}
}
